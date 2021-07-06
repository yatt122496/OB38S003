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
#include "HARDWARE\main\SysInc.h"
#include "HARDWARE\Lib\inc\adc.h"
//-----------------------
bit HeaterSec;
U16 HotWaitModeTimer;
//-----------------------
#if (IO_AD_KEY_OTP == 0)
	U8  code AdCh[3]={AD_VR,AD_NTC};
#else
	U8  code AdCh[3]={AD_VR,AD_NTC,AD_KEY};
	bit AdKeyNew;
	U8  AdKeyValue;
#endif
//-----------------------
bit HeatTest;
U8  TestNtcTimer;
//----------------------
bit AdNtcNew;
U16 AdNtcValue;
//----------------------
bit AdVrNew;
U8  AdVrValue;
//------------------------
U8  AdSensFreq;
U8  AdSize;
//------------------------
bit SysTimerCon;
U8  SysSaveTim;
//-----------------------
bit LockWoodCon;	  //加执上锁试图加热闪烁温度单位
bit LockWoodFah;
U8  LookWoodConTimer;
U8  LookWoodConTimerCon;
//-----------------------
U8  Timer5Ms;
U8  Timer50Ms;

U8  T1MotTimer,T1MotTimer1;
//------------------------
bit GoErrCon;
U8  GoErrCount;
U16 GoErrTimer;
u8 AdErrTim;
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void GoErrTestInit(void)
{
	GoErrCon   = 0;
	GoErrCount = 0;
  //------------
}
/************************************************************
*
* 		  跳制保护检测
************************************************************/
// void Int1Isr_ErrTest(void) interrupt INT0
// {
// 	IE0  = 0;
// 	GoErrCount++;
// 	if(GoErrCount > 80)
// 		GoErrCount    = 90;
// }
/************************************************************
*
* 			锁闪底灰灯
************************************************************/
void LookFlhWood(void)
{
	if (LockWoodCon) {
		LockWoodFah         = 1;
		LookWoodConTimer    = 0;
		LookWoodConTimerCon = 0;
	}
	LockWoodCon=1;
}
#if UART_TEST
xdata unsigned long Sys_Time = 0;
#endif
/************************************************************
* 函数名:
* 功能说明:  	  时序定时
************************************************************/
void Timer0ISR( void )  interrupt TMR2_VECTOR   //1ms中断一次
{
	if (TMR2_GetOverflowIntFlag())
	{
		//***********************************************
		AdSensFreq++;
#if UART_TEST
		Sys_Time++;
#endif
#if (IO_AD_KEY_OTP == 0)
		if (AdSensFreq > 9)
		{ //3ms
			AdSensFreq = 0;
			if (0 == ADC_IS_BUSY) { //ADC????????????/???é????????
				if (ADCCHS == ADC_CH_5) {
					AdNtcNew    = 1;
					// AdNtcValue  = (((ADRESH & 0x0f) << 8) | ADRESL) >> 2;
					AdNtcValue  = ADC_GetADCResult() >> 2;
					// ADCON       = AD_KEY  ;//Bin(10000011);
					ADC_EnableChannel(ADC_CH_18);
					ADC_GO();
					// FLA_Y = !FLA_Y;
					AdErrTim = 0;
				} else if (ADCCHS == ADC_CH_18) {
					AdVrNew    = 1;
					// AdVrValue  = (((ADRESH & 0x0f) << 8) | ADRESL) >> 4;
					AdVrValue  = ADC_GetADCResult() >> 4;
					// ADCON       = AD_KEY  ;//Bin(10000011);
					ADC_EnableChannel(ADC_CH_5);
					ADC_GO();
					AdErrTim = 0;
				}
			} else {
				AdErrTim++;
				if (AdErrTim > 2) {
					AdErrTim = 0;
					//	   ADT   = Bin(11101111);	//????????°?AD?§?§??100MS?ó×???????
					//       ADCH  = Bin(01000000);
					//	   ADCON = AD_NTC;
					ADCCHS = 0x05;
					ADCON1 = 0xF0;
					ADC_GO();
				}
			}
		}
#else
		if (AdSensFreq > 2)
		{ //3ms
			AdSensFreq = 0;
			if ((ADCON & 0X01) == 0)
			{ //
				switch (AdSize)
				{
				case 0:
					AdVrValue = ADDH;
					AdVrNew = 1;
					break;
				case 1:
					AdNtcValue = (ADDH << 2) | (ADDL & 0x03);
					AdNtcNew = 1;
					break;
				case 2:
					AdKeyValue = ADDH;
					AdKeyNew = 1;
					break;
				default:
					break;
				}

				if (++AdSize > 2)
					AdSize = 0;
				ADCON = AdCh[AdSize];
			}
		}
#endif
		//***********************************************
		if (HOT && !GoErrCon)
		{
			// EX0 = 1;
			P3EXTIE |= (1 << 1);
			GoErrTimer++;
			if (GoErrTimer > 999)
			{
				GoErrTimer = 0;
				if (GoErrCount > 40)
				{
					GoErrCon = 0;
					GoErrCount = 0;
				}
				else
				{
#if CONFIG_ZERO_CHECK
					GoErrCon = 1;
#else
					GoErrCon = 0;
					GoErrCount = 0;
#endif
				}
			}
		}
		else
		{
			P3EXTIE &= ~(1 << 1);
			// EX0 = 0;
			P3EXTIF &= ~(1 << 1);
			// IE0 = 0;
			GoErrCount = 0;
			GoErrTimer = 0;
		}
		//***********************************************
		if (++Timer5Ms > 9)
		{
			Timer5Ms = 0; //10ms
			HotWaitModeTimer++;
			if (HotWaitModeTimer > 99)
			{ //1s
				HotWaitModeTimer = 0;
				HeaterSec = 1;
				if (HeatTest)
				{ //Hot Test Timer 1mim
					TestNtcTimer++;
					if (TestNtcTimer > 59)
					{ //1min
						TestNtcTimer = 0;
						HeatTest = 0; //Test cancel
					}
				}
			}
			//-------------------------
			if (!HotOnOff && MotDelayOff)
			{
				//-----------------------
				if (++T1MotTimer > 99)
				{
					T1MotTimer = 0; //1s
					if (++T1MotTimer1 > 19)
					{
						T1MotTimer1 = 0; //20S
						MotDelayOff = 0;
					}
				}
			}
			else
			{
				T1MotTimer = 0;
				T1MotTimer1 = 0;
			}
		}
		Timer50Ms++;
		if (Timer50Ms > 49)
		{ //50ms
			Timer50Ms = 0;
			SysTimerCon = 1;
#if (IO_AD_KEY_OTP == 0)
			KeyNew = 1;
#endif
			if (KeySwitchTimer)
				KeySwitchTimer--;
			//***********************************************
			if ((LockWoodCon == 1) || GoErrCon)
			{
				LookWoodConTimer++;
				if (LookWoodConTimer > 1)
				{
					LookWoodConTimer = 0;
					LookWoodConTimerCon++;
					if (LookWoodConTimerCon > 10)
					{
						LookWoodConTimerCon = 0;
						LockWoodCon = 0;
						LockWoodFah = 0;
					}
					else
						LockWoodFah = ~LockWoodFah;
				}
			}
		}
		//----------------------------
		FlaCon();
		TMR2_ClearOverflowIntFlag();
	}
}
/************************************************************
*
*
************************************************************/
void KeySaveDat(void)
{
	SaveSet     = 1;
	SysSaveTim  = 0;
}
/************************************************************
*
*
***********************************************************/
void SysTimer50ms(void)
{
	if(SysTimerCon) {
		SysTimerCon = 0;
			//----------------
		if(SaveSet) {
			SysSaveTim++;
			if(SysSaveTim > 19) {
				SysSaveTim = 0;
				SaveSet    = 0;
				SaveSetCall();
			}
		}
	}
}
