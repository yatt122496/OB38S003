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
U8 AdErrTim;

U8 T1MotTimer,T1MotTimer1;
/************************************************************
*
* 			锁闪底灰灯
************************************************************/
void LookFlhWood(void)
{
  if(LockWoodCon)
  {
    LockWoodFah         = 1;
	LookWoodConTimer    = 0;
	LookWoodConTimerCon = 0;
  }
  LockWoodCon=1;
}
/************************************************************
* 函数名:
* 功能说明:  	  时序定时
************************************************************/
#if UART_TEST
unsigned long Sys_Time = 0;
#endif
void Timer0ISR( void )  interrupt TMR2_VECTOR   //1ms中断一次
{
	//***********************************************
	if (TMR2_GetOverflowIntFlag())
	{
#if UART_TEST
		Sys_Time++;
#endif
		AdSensFreq++;
#if (IO_AD_KEY_OTP == 0)
		if (AdSensFreq > 9)
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
				default:
					break;
				}
				if (++AdSize > 1)
					AdSize = 0;
				ADCON = AdCh[AdSize];
			}
		}
#else
		if (AdSensFreq > 2)
		{ //3ms
			AdSensFreq = 0;
			if (0 == ADC_IS_BUSY) { //ADC????????????/???é????????
				if (ADCCHS == ADC_CH_5) {
					AdNtcNew    = 1;
					// AdNtcValue  = (((ADRESH & 0x0f) << 8) | ADRESL) >> 2;
					AdNtcValue  = ADC_GetADCResult() >> 2;
					// ADCON       = AD_KEY  ;//Bin(10000011);
					ADC_EnableChannel(ADC_CH_10);
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
				} else if (ADCCHS == ADC_CH_10) {
					AdKeyNew    = 1;
					// AdVrValue  = (((ADRESH & 0x0f) << 8) | ADRESL) >> 4;
					AdKeyValue  = ADC_GetADCResult() >> 4;
					// ADCON       = AD_KEY  ;//Bin(10000011);
					ADC_EnableChannel(ADC_CH_18);
					ADC_GO();
					AdErrTim = 0;
				}
			} else {
				AdErrTim++;
				if (AdErrTim > 9) {
					AdErrTim = 0;
					//	   ADT   = Bin(11101111);	//????????°?AD?§?§??100MS?ó×???????
					//       ADCH  = Bin(01000000);
					//	   ADCON = AD_NTC;
					ADCCHS = ADC_CH_18;
					ADCON1 = 0xF0;
					ADC_GO();
				}
			}
			// if ((ADCON & 0X01) == 0)
			// { //
			// 	switch (AdSize)
			// 	{
			// 	case 0:
			// 		AdVrValue = ADDH;
			// 		AdVrNew = 1;
			// 		break;
			// 	case 1:
			// 		AdNtcValue = (ADDH << 2) | (ADDL & 0x03);
			// 		AdNtcNew = 1;
			// 		break;
			// 	case 2:
			// 		AdKeyValue = ADDH;
			// 		AdKeyNew = 1;
			// 		break;
			// 	default:
			// 		break;
			// 	}

			// 	if (++AdSize > 2)
			// 		AdSize = 0;
			// 	ADCON = AdCh[AdSize];
			// }
		}
#endif
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

			if (MusicTime50ms)
				MusicTime50ms--;
#if (IO_AD_KEY_OTP == 0)
			KeyNew = 1;
#endif
			if (KeySwitchTimer)
				KeySwitchTimer--;
			//***********************************************
			if (LockWoodCon == 1)
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
  if(SysTimerCon)
  {
	SysTimerCon = 0;
	 //----------------
	if(SaveSet)
	{
	  SysSaveTim++;
	  if(SysSaveTim > 19)
	  {
		 SysSaveTim = 0;
		 SaveSet    = 0;
		 SaveSetCall();
	  }
	}
  }
}