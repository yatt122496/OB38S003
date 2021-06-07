/***********************************************************
*  文件名: SH_EEPROM.C
************************************************************
*  日期:
*
*  作者:
*  功能说明：79F083 类EEPROM的擦写寿命有10W次，若每次只需要保存8个字节，整个512空间划分为64个block，
*             每个block 8个字节，当写满64个block即整个512空间才对全部共2个扇区进行擦除，这样理论上寿
*			  命可以达到10W*(512/8) = 640万次，大大提高可靠性能
*
*       原理：每次写保存到eeprom的地址都不一样,假若每个block为8个字节,第一次保存数据是保存到 0x00～0x07，
*			  则第二次写flash后数据则保存到0x08～0x0f，如此类推
*             通过二分法算法可以知道上次保存的数据保存到那个block，以便读出最新写入的数据，或者继续写数据到
*			  空页处，二分法算法大大提供索引效率。
************************************************************
*  硬件：  sh79f083
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "OB38S003.h"
#include <INTRINS.H>
#include "EEPROM.h"
/************************************************************
*       SH79F083 EEPROM 参数
************************************************************/
// #define  FLASH_SIZE            512	//EEPROM大小   SH79F083只有512字节EEPROM
#define  FLASH_SIZE            128	//EEPROM大小   SH79F083只有512字节EEPROM
// #define  FAN_SECTION_SIZE	   256	//EEPROM一个扇区大小
#define  FAN_SECTION_SIZE	   128	//EEPROM一个扇区大小
#define  FLASH_MSGBYTES	       8	//单次存8个字节
#define  FLASH_MSGCOUNT	  FLASH_SIZE/FLASH_MSGBYTES	//EEPROM可以割分成多少个(8个字节组成的区)
#define	 SMG_SIZE         FLASH_SIZE/FAN_SECTION_SIZE	//EEPROM有多少个扇区
/************************************************************
* 		SH79F083 控制命令
************************************************************/
#define	 FLASH_CON_CODE        0X00	//选择代码
#define	 FLASH_CON_EEPROM      0X01	//选择数据存储器（EEPROM）

#define	 CON1_ERASE_MOD        0XE6	//EepRom Erase mod 擦命令
#define	 CON1_WRITE_MOD        0x6e //EepRom Write mod 写命令
#define	 CON2_MOD			   0x05	//  以下命令为我们不用的，
#define	 CON3_MOD			   0x0a	//  但我们没有这些命令却无
#define	 CON4_MOD			   0x09	//  法对EEPROM进行操作
#define	 CON5_MOD			   0x06


unsigned char ChecksumErr0x5a;
unsigned char ChecksumErr0xa5;



void SspWrite(unsigned int addr,unsigned char dat)
{
	Write_EEPROM(addr, dat);
}
// void SspWrite(unsigned int addr,unsigned char dat)
// {
//     bit SaveEa;
//     SaveEa = EA;
// 	EA = 0;
// 	//-----------------------
// 	IB_DATA   = dat;
// 	IB_OFFSET = (unsigned char)(addr)&0xff;
// 	XPAGE     = ((addr>>8) & 7);
// 	//-----------------------
// #pragma asm
// 	//-----------------------
// 	MOV     FLASHCON,#FLASH_CON_EEPROM;
// 	//-----------------------
// 	MOV  	A,ChecksumErr0x5a
// 	CJNE 	A,#05AH,Write_Err
// 	//-----------------------
// 	MOV  	A,ChecksumErr0xa5
//     CJNE 	A,#0A5H,Write_Err
// 	//-----------------------
// 	MOV     IB_CON1,#CON1_WRITE_MOD
// 	MOV     IB_CON2,#CON2_MOD
// 	MOV     IB_CON3,#CON3_MOD
// 	MOV     IB_CON4,#CON4_MOD
// 	MOV     IB_CON5,#CON5_MOD
//     NOP
// 	NOP
// 	NOP
// 	NOP
// 	Write_Err:
// 	//-----------------------
// 	MOV     ChecksumErr0x5a,#0
// 	MOV  	IB_CON2,#0
// 	MOV     ChecksumErr0xa5,#0
// 	//-----------------------
// 	MOV     FLASHCON,#FLASH_CON_CODE
// 	//-----------------------
// 	MOV     XPAGE,#0;
// 	//-----------------------
// #pragma endasm
// 	EA   =  SaveEa;
// }

void SspErase(unsigned char addr)
{
	unsigned char i;
	addr = addr;
	for ( i = 0; i < 128; i++) {
		Write_EEPROM(i, 0xff);
	}
}
// void SspErase(unsigned char addr)
// {
//     bit SaveEa;
//     //-----------------------
// 	SaveEa    = EA;
// 	EA 	      = 0;
// 	//-----------------------
// 	IB_DATA   = 0;
// 	IB_OFFSET = 0;
// 	XPAGE = addr & 0X07;
// #pragma asm
// 	//-----------------------
// 	MOV     FLASHCON,#FLASH_CON_EEPROM;
// 	//-----------------------
// 	MOV  	A,ChecksumErr0x5a
// 	CJNE 	A,#05AH,Erase_Err
// 	//-----------------------
// 	MOV  	A,ChecksumErr0xa5
//     CJNE 	A,#0A5H,Erase_Err
// 	//-----------------------
// 	MOV     IB_CON1,#CON1_ERASE_MOD
// 	MOV     IB_CON2,#CON2_MOD
// 	MOV     IB_CON3,#CON3_MOD
// 	MOV     IB_CON4,#CON4_MOD
// 	MOV     IB_CON5,#CON5_MOD
//     NOP
// 	NOP
// 	NOP
// 	NOP
// 	Erase_Err:
// 	//-----------------------
// 	MOV     ChecksumErr0x5a,#0
// 	MOV  	IB_CON2,#0
// 	MOV     ChecksumErr0xa5,#0
// 	//-----------------------
// 	MOV     FLASHCON,#FLASH_CON_CODE
// 	//-----------------------
// 	MOV     XPAGE,#0;
// 	//-----------------------
// #pragma endasm
// 	EA 	  = SaveEa;
// }

unsigned char ReadFlash(unsigned int addr)
{
	return Read_EEPROM(addr);
}
// unsigned char ReadFlash(unsigned int addr)
// {
// 	unsigned char temp;
// 	FLASHCON=FLASH_CON_EEPROM;
// 	temp=*(unsigned char code *)(addr);
//    	FLASHCON=FLASH_CON_CODE;
// 	return(temp);
// }
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void WriteBootData( void )
{
	SspWrite(0,0x55);
	SspWrite(1,0xaa);
}
// void WriteBootData( void )
// {
// #pragma asm
//   MOV    ChecksumErr0x5a,#0x5a;
//   MOV    ChecksumErr0xa5,#0xa5;
// #pragma endasm
//   SspWrite(0,0x55);
// #pragma asm
//   MOV    ChecksumErr0x5a,#0x5a;
//   MOV    ChecksumErr0xa5,#0xa5;
// #pragma endasm
//   SspWrite(1,0xaa);
// }
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
bit CheckEepromMsgNull(unsigned char eepMsgDat)
{
	unsigned int EepMsgMul;
	unsigned char i;
	unsigned char DataBuff;
	//---------------------
	EepMsgMul = eepMsgDat * FLASH_MSGBYTES;
	//---------------------
	i = FLASH_MSGBYTES;
	//---------------------
	do {
		i--;
		DataBuff=ReadFlash(EepMsgMul+i);
		if(DataBuff!=0xff)
			return 1;
	}while(i);
	//---------------------
	return 0;
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
bit locateEepromMsg(unsigned char *Lndex)
{
	unsigned char High,Low,Mid,buff;
	bit VoidFlag;
	High=(FLASH_MSGCOUNT-1);
	Low=0;
	loopLocate:
	buff=High-Low;
	buff/=2;
	Mid=Low+buff;
	VoidFlag=CheckEepromMsgNull(Mid);
	if(Mid==Low) {
		if(CheckEepromMsgNull(High)) {
			*Lndex=High;
			return  1;
		} else {
			*Lndex=Mid;
			return VoidFlag;
		}
	} else {
		if(VoidFlag==0)
			High=Mid;
		else
			Low =Mid;
		goto loopLocate;
	}
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void EraseEepromMsg( void )
{
     SspErase(0);
}
// void EraseEepromMsg( void )
// {
//    unsigned char MsgSize;
//    for(MsgSize=0;MsgSize<SMG_SIZE;MsgSize++)
//    {
// #pragma asm
//      MOV    ChecksumErr0x5a,#0x5a;
//      MOV    ChecksumErr0xa5,#0xa5;
// #pragma endasm
//      SspErase(MsgSize);
//    }
// }
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void WriteEepromMsg(unsigned char MsgAddr,unsigned char *WriteData)
{
	unsigned int AddrBuff;
	unsigned char WriteDataSize;
	AddrBuff=MsgAddr*FLASH_MSGBYTES;
	WriteDataSize=0;
	do {
		SspWrite(AddrBuff,*WriteData);
		AddrBuff++;
		WriteData++;
		WriteDataSize++;
	}while(WriteDataSize<FLASH_MSGBYTES);
}
// void WriteEepromMsg(unsigned char MsgAddr,unsigned char *WriteData)
// {
//   unsigned int AddrBuff;
//   unsigned char WriteDataSize;
//   AddrBuff=MsgAddr*FLASH_MSGBYTES;
//   WriteDataSize=0;
//   do
//   {
// #pragma asm
//     MOV    ChecksumErr0x5a,#0x5a;
//     MOV    ChecksumErr0xa5,#0xa5;
// #pragma endasm
//     SspWrite(AddrBuff,*WriteData);
// 	AddrBuff++;
// 	WriteData++;
// 	WriteDataSize++;
//   }while(WriteDataSize<FLASH_MSGBYTES);
// }
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void ReadEepromMsg(unsigned char MsgAddr,unsigned char *ReadData)
{
	unsigned int AddrBuff;
	unsigned char ReadDataSize;
	AddrBuff=MsgAddr*FLASH_MSGBYTES;
	ReadDataSize=0;
	do {
		*ReadData = ReadFlash(AddrBuff);
		AddrBuff++;
		ReadData++;
		ReadDataSize++;
	}while(ReadDataSize<FLASH_MSGBYTES);
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void WriteEepromLike(unsigned char *ReadWriteData)
{
	bit VoidFull;
	unsigned char SaveMsgAddr;
	RepeatWriteData:
	VoidFull=locateEepromMsg(&SaveMsgAddr);
	if(SaveMsgAddr!=(FLASH_MSGCOUNT-1)) {
		if(VoidFull==1)
			SaveMsgAddr++;
	} else {
		EraseEepromMsg();
		WriteBootData();
		goto RepeatWriteData;
	}
	WriteEepromMsg(SaveMsgAddr,ReadWriteData);
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
bit ReadEepromLike(unsigned char *ReadWriteData)
{
	bit Ret;
	unsigned char SaveMsgAddr;
	//------------------------------
	if(locateEepromMsg(&SaveMsgAddr)) {//获得最后一次写入的数据
		ReadEepromMsg(SaveMsgAddr,ReadWriteData);
		Ret=1;//数据读取成功
	} else
		Ret=0;  //反回0,表示整个分区都是空的
	//------------------------------
	return  Ret;
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
bit EepRomBoot(unsigned char PowerErase)
{
	bit BootCon;
	bit Ret;
	//-----------------
	BootCon = 0;
	//-----------------
	if(PowerErase==1)
		goto EraseEeprom;
	//-----------------
	RepeatRead:
	if((ReadFlash(0x0000)==0x55) && (ReadFlash(0x0001)==0xaa)) {
		if(BootCon==0)
			Ret=1;
		else
			Ret=0;
	} else {
		EraseEeprom:
		BootCon=1;
		EraseEepromMsg();
		WriteBootData();
		goto RepeatRead;
	}
	return  Ret;  //反回0,表示整个分区都是空的
}
