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
#include "HARDWARE/main/SysInc.h"
#include "HARDWARE\Lib\inc\wdt.h"

#if IR_TEST
	extern xdata u8 bData[40], bAD_indx;
#endif

U8 KeyTestSize;
U8 UpKeyValue;

void main(void)
{
#if UART_TEST
#if IR_TEST
	xdata u8 i;
#endif
	xdata unsigned long dwSys_time = 0;
#endif
	FlaInit();
	InitSys();
	//--------------------------
	UpKeyValue   = 0x55;
	KeyTestSize  = 4;
#if UART_TEST
	// init_UART0();
#endif
	while(KeyTestSize)
	{
		if(KeyNew) {
#if WDT_SWITCH
		WDT_ClearWDT();					//清除看门狗计数器
#endif
			GainAdKeyValue  ();
			if(PcbKeyValue != UpKeyValue)
				UpKeyValue = PcbKeyValue;
			else {		//两次比较结果相同键值确定
				switch(PcbKeyValue)
				{
				case 1    :EepRomBoot(1);KeyTestSize = 0;break;  //上电按POWER键复位系统，
				default   :              KeyTestSize = 0;break;
				}
			}
			if(KeyTestSize)
				KeyTestSize--;
		}
	}
	//--------------------------
	EepromInit(0);
	//--------------------------
	while(1)
	{
#if UART_TEST
		if (Sys_Time - dwSys_time > 399) {
			dwSys_time = Sys_Time;
			// FOT = !FOT;
			// UART0_TX(0xff);
#if IR_TEST
			// UART0_TX(bAD_indx);
			if (bAD_indx) {
				for ( i = 0; i < bAD_indx; i++) {
					// UART0_TX(bData[i]);
					bData[i];
				}
				bAD_indx = 0;
			}
#endif
		}
#endif
#if WDT_SWITCH
		WDT_ClearWDT();					//清除看门狗计数器
#endif
		// RSTSTAT=Bin(00000010);
		KeyValueApart();
		AdNtc();
		ArAd();
		HeatCon();
		SysTimer50ms();
	}
}
