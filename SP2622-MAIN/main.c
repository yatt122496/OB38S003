/***********************************************************
*  文件说明：
************************************************************
*  日期:
*
*  作者:  cuoiszf
*
************************************************************
*  硬件：sh79f083
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "SysInc.h"
//------------------------------------------
uint8 KeyTestSize;
//------------------------------------------
bit CancelErrDispEc;
//------------------------------------------
uint8 TestKeyBuf;
uint8 UpPowerTest;
uint8 Test0x5a;
bit   DBugBit;
//------------------------------------------
uint8 Disturb0xAA;
uint8 Disturb0x55;
//------------------------------------------
#if UART_TEST
	extern xdata u8 bData[40], bAD_indx;
#endif
void main(void)
{
#if UART_TEST
	xdata u8 i;
	xdata unsigned long dwSys_time = 0;
#endif
	//--------------------------
	DBugBit        = 0;
	CancelErrDispEc= 0;
	//------------
	SysInit();
	InitSys();
	IicInit();
	//--------------------------
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	// if(Disturb0x55 != 0x55 || Disturb0xAA != 0xaa)
	// while(1);
	//--------------------------
	DispInit();
	GoErrTestInit();
#if UART_TEST
	init_UART0();
#endif
	//---------------------------
	//  if(HeatGears)
	//  FirstHeat = 1;
	while(1){
#if UART_TEST
		if (Sys_Time - dwSys_time > 999) {
			dwSys_time = Sys_Time;
			UART0_TX(bAD_indx);
			for ( i = 0; i < bAD_indx; i++) {
				UART0_TX(bData[i]);
			}
			bAD_indx = 0;
			// UART0_TX(0xaa);
		}
#endif
		// RSTSTAT=Bin(00000010); //170ms
		WDT_CountClear();           //Clear WDT Count Subroutine
		TimerOff();
		SysTimer50ms();
		KeyValueApart();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		// if(Disturb0xAA != 0xaa || Disturb0x55 != 0x55)
		// while(1);
		AdNtc();
		HeatCon();
		//---------------
		ErrTest();
		Disp();
#if (DWL_EN==1)
		DwlCon();
#endif
		//--------------
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
	while(1);
}
