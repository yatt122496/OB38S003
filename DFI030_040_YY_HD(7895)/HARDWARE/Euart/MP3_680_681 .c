/***********************************************************
*  文件说明：
************************************************************
*  日期:
*
*  作者:
*
************************************************************
*  硬件：sh79f083
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\main\SysInc.h"
/*
   ("*********************************************\n");
   ("//项 目 名:680/681 MP3芯片参考代码\n");
   ("//功能要求:\n");
   ("//硬件配置:\n");
   ("//1) MCU型号: AT89C51\n");
   ("//2) 内部振荡频率为:11.0592MHz\n");
   ("//软件版本:UART1: \n");
   ("//公 司 名: 广州语创电子科技有限公司\n");
   ("//作    者: \n");
   ("//		硬件：\n");
   ("//		软件：piao\n");
   ("//技术支持：E-mail:1677080092@qq.com\n");
   ("//技术支持：QQ:1677080092,手机：15622277367\n");
   ("//修改记录: 1）\n");
   ("//          2）\n");
   ("*********************************************\n");
*/
/*************************************************
*
*
*
*
*************************************************/
void EuartInit(void)
{
  #define ES1      1<<( 4 )
  #define BAUD  19200	   //串行速度
  #define FOSC  8300000
  #define FD    12
  //	    bit7   bit6   bit5   bit4	bit3   bit2	  bit1   bit0
  //SCON    SM0    SM1    SM2    REN    TB8    TB8    TI     RI
  //SBUF
  //PCON1   SMOD   SSTAT   -- 	   --	  --	 --		--	   --
  //SADDR	SADDR7 SADDR6 SADDR5 SADDR4 SADDR3 SADDR2 SADDR1 SADDR0
  //SADEN	SADEN7 SADEN6 SADEN5 SADEN4 SADEN3 SADEN2 SADEN1 SADEN0
  //RXCON   --     --     --     --     --     --     RXCON1 RXCON0
	// PCON|=0X80;
	// SCON=0x40;/*SCON:模式1,8-bitUART,*/
	// TMOD &= 0x0f;		//?????1???
	// TMOD |= 0x20;		//?????1?8???????
	// TL1 = 0xF7;		//??????
	// TH1 = 0xF7;		//????????
	// TR1=1;/*TR1:timer1run*/
	// ES0=1;/*打开串口中断*/
}
bit SendOk;
void delay_us(u16 us)
{
	u16 y;
	for (y=0; y<us;y++);
}

void UART1_SendByte(u8 dat)
{
    // SendOk = 1;
    // SBUF = dat;
	// while(SendOk);
	u8 i = 0;

	VTX=0;		//!<起始位
	delay_us(cVTX_Time);
	for(i = 0; i < 8; i++){
		if(dat & 0x01)
			VTX=1;
		else
			VTX=0;
		delay_us(cVTX_Time);
		dat >>= 1;
	}
	VTX=1;		//!<停止位
	delay_us(cVTX_Time);
}
/*********************************************************************************************
//函数名:void UART_SER(void)EUART
//
//功能说明:
//
//入口参数:NO
//
//出口参数:NO
***********************************************************************************************/
// void UART_SER(void)EUART//串行中断服务程序
// {
// //	u8 Temp;//定义临时变量
// 	if(RI)//判断是接收中断产生
// 	{
// 		RI=0;//标志位清零
// //		Temp=SBUF;//读入缓冲区的值
// //		P1=Temp;//把值输出到P1口，用于观察
// //		SBUF=Temp;//把接收到的值再发回电脑端
// 	}
// 	if(TI)//如果是发送标志位，清零
//     {
// 	  TI=0;
//       SendOk = 0;
//     }
// }
u8  Vol;
bit NewVol;
u8  SendSize;
u8  MusicTime50ms;

u8 code VolList[]={0,10,20,25};
/*********************************************************************************************
//函数名:Specify_Volume()
//
//功能说明:指定音量
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Specify_Volume(void)
{
  SendSize = 2;
  NewVol   = 1;
  MusicTime50ms = 0;
}

void VolKey(void)
{
  if(!Vol)
  SendSize = 2;
  else
  SendSize = 3;
  Vol++;
  if(Vol > 3)
  {
    Vol = 0;
	Music_stop();
  }else
  {
	 NewVol   = 1;
     MusicTime50ms = 0;
  }
  //Specify_Volume(Vol);
}

/*********************************************************************************************
//函数名:Music_stop()
//
//功能说明:停止
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Music_stop()
{
  NewVol = 1;
}
void MusicCon(void)
{
  if(Standby && Vol)
  {
    if(NewVol)
	{
	  if(!MusicTime50ms)
	  {
		if(SendSize == 2 || SendSize == 3)
		{
		  SendSize = 0;
		  //-------------------
	      UART1_SendByte(0x7E);
	      UART1_SendByte(0x03);
	      UART1_SendByte(0x31);
	      UART1_SendByte(VolList[Vol]); //指定音量
	      UART1_SendByte(0xEF);
		  //-------------------
		  MusicTime50ms = 4;
		  if(SendSize == 3)
		  NewVol = 0;
		  else
		  SendSize = 1;
		}else
		if(SendSize == 1)
		{
		  UART1_SendByte(0x7E);
	      UART1_SendByte(0x02);
	      UART1_SendByte(0x01);
	      UART1_SendByte(0xEF);
		  NewVol = 0;
		  SendSize = 0;
		}
	  }
	}
  }else
  {
	if(NewVol)
	{
	  NewVol = 0;
	  if(!MusicTime50ms)
	  {
	    UART1_SendByte(0x7E);
	    UART1_SendByte(0x02);
	    UART1_SendByte(0x0E);
	    UART1_SendByte(0xEF);
	  }
	}
  }
}
void Cycle_play(u8 num)
{
	UART1_SendByte(0x7E);
	UART1_SendByte(0x03);
	UART1_SendByte(0x33);
	UART1_SendByte(num);
	UART1_SendByte(0xEF);
}
