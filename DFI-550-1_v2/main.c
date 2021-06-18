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
#include "HARDWARE\include\SysInc.h"
#include "HARDWARE\Lib\inc\wdt.h"

//-------------------------------
u8 InitKeyTime;
//-------------------------------
#if IR_TEST
extern xdata u8 bData[40], bAD_indx;
#endif
void main(void)
{
#if UART_TEST
#if IR_TEST
	xdata u8 i;
#endif
	xdata unsigned long dwSys_time = 0;
#endif
	u8 SysInitBz, bseg = 0;
  McuInit();
  FlaInit();
  HeatInit();
  EA = 1;
  //
  InitKeyTime = 10;
  while(InitKeyTime){
#if WDT_SWITCH
		WDT_ClearWDT(); //清除看门狗计数器
#endif
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
#if UART_TEST
	// init_UART0();
#endif
	while (1)
	{
#if UART_TEST
		if (Sys_Time - dwSys_time > 499) {
			dwSys_time = Sys_Time;
			// P04 = !P04;
#if IR_TEST
			// UART0_TX(bAD_indx);
			if (bAD_indx)
			{
				for (i = 0; i < bAD_indx; i++)
				{
					// UART0_TX(bData[i]);
					bData[i];
				}
				bAD_indx = 0;
			}
#endif
		}
#endif
#if WDT_SWITCH
		WDT_ClearWDT(); //清除看门狗计数器
#endif
		// RSTSTAT = 0X02;
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
