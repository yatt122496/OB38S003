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
#include "MYADC.h"
//-----------------------
bit HeaterSec;
U16 HotWaitModeTimer;
//-----------------------
U8  code AdCh[2]={AD_VR,AD_NTC};
//-----------------------
bit HeatTest;
U8  TestNtcTimer;
//----------------------
bit AdNtcNew;
U16 AdNtcValue;
//-----------------------
//bit AdKeyNew;
//U8  AdKeyValue;
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
U8  Timer50Ms;
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
u8 b10Ms_time = 0;
void Timer0ISR( void ) interrupt TIMER2_VECTOR   //5ms中断一次
{
	TF2   =  0;

	//***********************************************
	AdSensFreq++;
	if(AdSensFreq > 1)
	{
		AdSensFreq = 0;
		if(ADCfinish) {//
			ADCfinish = 0;
			if((ADCC2&0x01)) {//??????1????
				AdNtcNew    = 1;
				AdNtcValue  = n_data >> 2;
				// AdNtcValue  = (ADDH << 2) | (ADDL & 0x03);
				// ADCON       = AD_KEY  ;//Bin(10000011);
				ADC_Start(d_ADC_CH4_IN);
				// FLA_Y = !FLA_Y;
			} else {//??????3???????
				AdVrNew    = 1;
				// AdKeyValue  = ADDH;
				AdVrValue  = n_data >> 4;
				// uart_send(&AdKeyValue, 1);
				// ADCON       = AD_NTC  ;//Bin(10000001);
				ADC_Start(d_ADC_CH1_IN);
				// FLA_B = !FLA_B;
			}
			// if((ADCON&0X01)==0)
			// {
			// 	switch(AdSize)
			// 	{
			// 		case 0 : AdVrValue  = ADDH;AdVrNew  = 1;break;
			// 		case 1 : AdNtcValue =(ADDH << 2) | (ADDL & 0x03);AdNtcNew = 1;break;
			// 		default:break;
			// 	}
			// 	AdSize++;
			// 	if(AdSize > 1)
			// 	AdSize    = 0;
			// 	ADCON       = AdCh[AdSize];
			// }
		}
	}
	//***********************************************
	HotWaitModeTimer++;
	if(HotWaitModeTimer > 199)
	{
		HotWaitModeTimer = 0;
		HeaterSec        = 1;
		if(HeatTest)		 //Hot Test Timer 1mim
		{
		TestNtcTimer++;
		if(TestNtcTimer > 59)
		{
			TestNtcTimer = 0;
			HeatTest     = 0;		//Test cancel
		}
		}
	}
	Timer50Ms++;
	if(Timer50Ms > 9)
	{
		Timer50Ms   = 0;
		SysTimerCon = 1;

		KeyNew      = 1;

		if(KeySwitchTimer)
		KeySwitchTimer--;
		//***********************************************
		if(LockWoodCon==1)
		{
		LookWoodConTimer++;
		if(LookWoodConTimer > 1)
		{
			LookWoodConTimer=0;
			LookWoodConTimerCon++;
			if(LookWoodConTimerCon>10)
			{
			LookWoodConTimerCon=0;
			LockWoodCon=0;
			LockWoodFah=0;
			}
			else
			LockWoodFah = ~LockWoodFah;
		}
		}
	}
	b10Ms_time++;
	if (b10Ms_time > 1) {
		b10Ms_time = 0;
		IrLockTmr();
	}
}
// void Timer0ISR( void ) TIMER0   //5ms中断一次
// {
//    TH0   = 0Xf2;
//    TL0   = 0X7e;
//    TF0   = 0   ;
//    //***********************************************
//    AdSensFreq++;
//    if(AdSensFreq > 1)
//    {
// 	 AdSensFreq = 0;
// 	 if((ADCON&0X01)==0)
//      {
// 	   switch(AdSize)
// 	   {
// 	     case 0 : AdVrValue  = ADDH;AdVrNew  = 1;break;
// 	     case 1 : AdNtcValue =(ADDH << 2) | (ADDL & 0x03);AdNtcNew = 1;break;
// 	     default:break;
// 	   }
// 	   AdSize++;
// 	   if(AdSize > 1)
// 	   AdSize    = 0;
// 	   ADCON       = AdCh[AdSize];
// 	 }
//    }
//    //***********************************************
//    HotWaitModeTimer++;
//    if(HotWaitModeTimer > 199)
//    {
// 	 HotWaitModeTimer = 0;
// 	 HeaterSec        = 1;
//      if(HeatTest)		 //Hot Test Timer 1mim
//      {
// 	   TestNtcTimer++;
//        if(TestNtcTimer > 59)
//        {
//          TestNtcTimer = 0;
//          HeatTest     = 0;		//Test cancel
//        }
//      }
//    }
//    Timer50Ms++;
//    if(Timer50Ms > 9)
//    {
//    	 Timer50Ms   = 0;
// 	 SysTimerCon = 1;

// 	 KeyNew      = 1;

// 	 if(KeySwitchTimer)
// 	 KeySwitchTimer--;
//      //***********************************************
//      if(LockWoodCon==1)
//      {
//        LookWoodConTimer++;
//        if(LookWoodConTimer > 1)
//        {
//          LookWoodConTimer=0;
// 	     LookWoodConTimerCon++;
// 	     if(LookWoodConTimerCon>10)
// 	     {
// 		   LookWoodConTimerCon=0;
//            LockWoodCon=0;
//            LockWoodFah=0;
// 	     }
// 	     else
//          LockWoodFah = ~LockWoodFah;
// 	   }
//      }
//    }
// }
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