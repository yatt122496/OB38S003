/***********************************************************
*             触摸驱动
************************************************************
*  日期:  2014.1.6  14:00
*
*  作者:  cuoiszf
*
************************************************************
*  硬件：  SH79F1622
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\include\SysInc.h"
//-------------------------------
u8 InitKeyTime;
//-------------------------------
void main(void)
{
  u8 SysInitBz;
  McuInit();
  FlaInit();
  HeatInit();
  EA = 1;
  //
  InitKeyTime = 10;
  while(InitKeyTime){
    SysInitBz   = 0;
    if(PcbKeyValue == 1){
	  EepromInit(0x55);
	  PcbKeyValue= 0xff;
	  UpKeyValue = 0xff;
	  SysInitBz  = 1;
	  break;
	}
  }
  UpKeyValue= 0xff;
  //---
  if(!SysInitBz)
  EepromInit(0xaa);
  while(1)
  {
	RSTSTAT = 0X02;
	SysKey();
	FlaMotOut();
	Bz();
	ArAd();
	AdNtc();
	SysErrCon();
	HeatCon();
	Disp();
#ifdef EUART_EN
	UartTxDat();
#endif
  }
}