/***********************************************************
*
************************************************************
*  日期:
*
*  作者:
*
************************************************************
*  硬件：
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\include\SysInc.h"


#ifdef EUART_EN

#define BAUD  38400
#define FD    12
//#define FOSC  9830400L
#define TX_DAT 1

#define SBRT_EN  ( 1 )<<7

u8 xdata DatBuf[16];
u8 xdata TxBuf[16];

u8 xdata RxBuf[2];

u8  TxSize;
u8 TxDatFinish;

bit RxFinish;
u8  RxDat;

//	    bit7   bit6   bit5   bit4	bit3   bit2	  bit1   bit0
//SCON   SM0    SM1    SM2    REN    TB8    TB8    TI     RI
//SBUF
//PCON  SSTAT1 SSTAT   -- 	   --	  --	 --		--	   --
//SADDR	SADDR7 SADDR6 SADDR5 SADDR4 SADDR3 SADDR2 SADDR1 SADDR0
//SADEN	SADEN7 SADEN6 SADEN5 SADEN4 SADEN3 SADEN2 SADEN1 SADEN0
//RXCON   --     --     --     --     --     --     RXCON1 RXCON0

void EuartInit(void)
{
#ifdef  REG79F1622_H
   P3    |= Bin(00000001);
   P3CR  |= Bin(00000000);
   P3PCR |= Bin(00000001);
   //---------------------
   P1    |= Bin(10000000);
   P1CR  |= Bin(10000000);
   P1PCR |= Bin(00000000);
   //---------------------
   SCON   = Bin(01000000);
   SBRTL  =((32768-(SCLK/FD/BAUD) - 1))%256;
   SBRTH  =((32768-(SCLK/FD/BAUD) - 1))/256;
   SBRTH |= SBRT_EN;  //打开波特率发生器
   REN    = 1;
#endif

#ifdef  REG79F083A_H
    P3 	 |= Bin(00000010);
    P3M0 &=~Bin(00000010);
    P3M1 &=~Bin(00000010);

	PCON|=0X80;
	SCON=0x40;/*SCON:模式1,8-bitUART,*/
	TMOD &= 0x0f;		//?????1???
	TMOD |= 0x20;		//?????1?8???????
	TL1 = ((65536-(SCLK/FD/BAUD) - 1))%256;//0xF7;		//??????
	TH1 = ((65536-(SCLK/FD/BAUD) - 1))%256;//0xF7;		//????????
	TR1=1;/*TR1:timer1run*/
#endif
   IntSet(EUART,1,1);
}
/*************************************************
*
*
*
*
*************************************************/
u8 EuartDatTxFinish(void)
{
  return TxDatFinish;
}
/*************************************************
*
*
*
*
*************************************************/
void EuartTx(u8 *PDat)
{
  u8 n,Dat;
  u8 CheckSum;
  CheckSum = 0;
  for(n=0;n<TX_DAT;n++)
  {
    Dat = *PDat;
	PDat++;
	TxBuf[n] = Dat;
	CheckSum+= Dat;
  }
  TxBuf[n] = CheckSum;
  TxDatFinish = 1;// 完成
  SBUF        = 0x55;
}
/*************************************************
*
*
*
*
*************************************************/
void EuartIsr(void) interrupt EUART
{
  u8 Dat;
  static bit DatStaFlag;
  if(TI)
  {
	if(TxSize < TX_DAT)
	{
	  SBUF = TxBuf[TxSize];
      TxSize++;
	}else
	{
	  TxDatFinish = 0;// 完成
	  TxSize = 0;
	}
	DatStaFlag = 0;
	TI = 0;
  }else
  if(RI)
  {
	Dat = SBUF;
	if(!DatStaFlag)
	{
	  if(Dat == 0x5a)
	  DatStaFlag = 1;
	  else
	  DatStaFlag = 0;
	  TxSize     = 0;
	}else
	{
	  RxBuf[TxSize] = Dat;
	  TxSize++;
	  if(TxSize > 1)
	  {
	    if(RxBuf[0] == ~RxBuf[1])
	    {
	      RxFinish = 1;
	      RxDat    = RxBuf[0];
	    }
	    DatStaFlag = 0;
	    TxSize     = 0;
	  }
	}
	RI = 0;
  }
}
/*************************************************
*
*
*
*
*************************************************/
u8 TxTimer;
u8 TxErrTimer;
//----------------------
void UartTxDat(void)
{
  static u8 data ErrCount;
  if(!TxTimer)
  {
	if(!EuartDatTxFinish())
	{
	  TxTimer = 2;

	  DatBuf[0]=VrValue;

	  EuartTx(&DatBuf[0]);
	  ErrCount = 0;
	}else
	{
	  if(!TxErrTimer)
	  {
	    TxErrTimer = 1;
	    ErrCount++;
	    if(ErrCount > 5)
	    {
		  ErrCount    = 0;
		  TxDatFinish = 0;
	    }
	  }
	}
  }
}
#endif