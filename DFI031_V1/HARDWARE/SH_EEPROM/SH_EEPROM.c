/***********************************************************
*  �ļ���: SH_EEPROM.C
************************************************************
*  ����:
*
*  ����:
*  ����˵����79F083 ��EEPROM�Ĳ�д������10W�Σ���ÿ��ֻ��Ҫ����8���ֽڣ�����512�ռ仮��Ϊ64��block��
*             ÿ��block 8���ֽڣ���д��64��block������512�ռ�Ŷ�ȫ����2���������в�����������������
*			  �����Դﵽ10W*(512/8) = 640��Σ������߿ɿ�����
*
*       ԭ��ÿ��д���浽eeprom�ĵ�ַ����һ��,����ÿ��blockΪ8���ֽ�,��һ�α��������Ǳ��浽 0x00��0x07��
*			  ��ڶ���дflash�������򱣴浽0x08��0x0f���������
*             ͨ�����ַ��㷨����֪���ϴα�������ݱ��浽�Ǹ�block���Ա��������д������ݣ����߼���д���ݵ�
*			  ��ҳ�������ַ��㷨����ṩ����Ч�ʡ�
************************************************************
*  Ӳ����  sh79f083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "OB38S003.h"
#include <INTRINS.H>
#include "EEPROM.h"
/************************************************************
*       SH79F083 EEPROM ����
************************************************************/
// #define  FLASH_SIZE            512	//EEPROM��С   SH79F083ֻ��512�ֽ�EEPROM
#define  FLASH_SIZE            128	//EEPROM��С   SH79F083ֻ��512�ֽ�EEPROM
// #define  FAN_SECTION_SIZE	   256	//EEPROMһ��������С
#define  FAN_SECTION_SIZE	   128	//EEPROMһ��������С
#define  FLASH_MSGBYTES	       8	//���δ�8���ֽ�
#define  FLASH_MSGCOUNT	  FLASH_SIZE/FLASH_MSGBYTES	//EEPROM���Ը�ֳɶ��ٸ�(8���ֽ���ɵ���)
#define	 SMG_SIZE         FLASH_SIZE/FAN_SECTION_SIZE	//EEPROM�ж��ٸ�����
/************************************************************
* 		SH79F083 ��������
************************************************************/
#define	 FLASH_CON_CODE        0X00	//ѡ�����
#define	 FLASH_CON_EEPROM      0X01	//ѡ�����ݴ洢����EEPROM��

#define	 CON1_ERASE_MOD        0XE6	//EepRom Erase mod ������
#define	 CON1_WRITE_MOD        0x6e //EepRom Write mod д����
#define	 CON2_MOD			   0x05	//  ��������Ϊ���ǲ��õģ�
#define	 CON3_MOD			   0x0a	//  ������û����Щ����ȴ��
#define	 CON4_MOD			   0x09	//  ����EEPROM���в���
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
* ������:
* ����˵��:
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
* ������:
* ����˵��:
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
* ������:
* ����˵��:
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
* ������:
* ����˵��:
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
* ������:
* ����˵��:
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
* ������:
* ����˵��:
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
* ������:
* ����˵��:
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
* ������:
* ����˵��:
************************************************************/
bit ReadEepromLike(unsigned char *ReadWriteData)
{
	bit Ret;
	unsigned char SaveMsgAddr;
	//------------------------------
	if(locateEepromMsg(&SaveMsgAddr)) {//������һ��д�������
		ReadEepromMsg(SaveMsgAddr,ReadWriteData);
		Ret=1;//���ݶ�ȡ�ɹ�
	} else
		Ret=0;  //����0,��ʾ�����������ǿյ�
	//------------------------------
	return  Ret;
}
/************************************************************
* ������:
* ����˵��:
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
	return  Ret;  //����0,��ʾ�����������ǿյ�
}
