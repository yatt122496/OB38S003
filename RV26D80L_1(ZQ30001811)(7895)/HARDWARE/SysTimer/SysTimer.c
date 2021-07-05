/***********************************************************
*
************************************************************
*  日期:
*
*  作者:
*
************************************************************
*  硬件：SH79F083
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE/main/SysInc.h"
#include "HARDWARE\Lib\inc\adc.h"
//---------------------
bit           AdNtcNew;
unsigned int  AdNtcValue;
//---------------------
bit           AdKeyNew;
unsigned char AdKeyValue;
//---------------------
xdata uint8  MotTimer;
xdata uint8  MotTimer1;

xdata uint8  HotTimer;
xdata uint8  HotTimer1;
//-----------------------
bit   Hidden;
uint8 HiddenTimer;
//--------------------
bit   TempFlash;
uint8 idata TempFlashTimer;
uint8 idata TempFlashTimerCon;
//-------------------------------
uint8 idata GoErrTimer;
//--------------------
uint8 idata TimeTimer;
bit   idata TimeTimerCon;
//--------------------
//-----------------------
bit   HeaterSec;
xdata uint8 HotWaitModeTimer;
//-----------------------
bit   HeatTest;
xdata uint8 TestNtcTimer;	//测试NTC 1分钟后取消测试控制
//-----------------------
//uint8 KeySensTimer;
//加热上锁试图加热闪烁温度单位
bit   LockWoodCon;
bit   LockWoodFalsh;
uint8 idata LookWoodConTimer;
uint8 idata LookWoodConTimerCon;
uint8 idata LockTimerOtp;
//------------------------------
bit   TempSwCon;
bit   TempSwFah;
bit   TempSwFahCon;
unsigned char idata TempSwFahTimer;
unsigned char idata TempSwFahTimerCon;
/************************************************************
*
*
***********************************************************/
void LookFlhWood(uint8 Otp)
{
  if(!LockWoodCon)
  {
    LockWoodFalsh      = 1;
	LookWoodConTimer   = 0;
	LookWoodConTimerCon= 0;
  }
  LockWoodCon   = 1;
  if(Otp)
  LockTimerOtp  = 2;
  else
  LockTimerOtp  = 9;
}

void TempSwFahSet(void)
{
  if(!TempSwFahCon)
  {
    TempSwFah         = 1;
	TempSwFahTimer    = 0;
	TempSwFahTimerCon = 0;
	TempSwCon         = 1;
  }
  TempSwFahCon = 1;
}
/************************************************************
*
*
***********************************************************/
void CancelAllFlash(uint8 Otp)
{
  TempSwCon       = 0;
  if(Otp != 2)
  {
    SetTemp         = 0;
    TempFlash       = 0;
  }
  if(Otp)
  {
    LockWoodCon     = 0;
    LockWoodFalsh   = 0;
  }
}
u8 Timer1Ms;
/************************************************************
*
*
***********************************************************/
// void SysTimer_Isr(void) interrupt TIMER2_VECTOR    //10ms
// {
//   TF2   =  0;
//   //***********************************************
// 	if(ADCfinish) {
// 		ADCfinish = 0;
// 		if((ADCC2&0x02)) {//转换的是通道1（按键）
// 			AdKeyNew    = 1;
// 			// AdKeyValue  = ADDH;
// 			AdKeyValue  = n_data;
// 			// ADCON       = AD_NTC  ;//Bin(10000001);
// 			ADC_Start(d_ADC_CH0_IN);
// 		}
// 		else//转换的是通道3（温度传感器）
// 		{
// 			AdNtcNew    = 1;
// 			AdKeyValue  = n_data;
// 			// AdNtcValue  = (ADDH << 2) | (ADDL & 0x03);
// 			// ADCON       = AD_KEY  ;//Bin(10000011);
// 			ADC_Start(d_ADC_CH2_IN);
// 		}
// 	}
//   //***********************************************
//    if(HOT && !GoErrCon){
//      EX0 = 1;
//      if(++GoErrTimer > 99){
// 	   GoErrTimer = 0;
// 	   if(GoErrCount > 40){
// 	     GoErrCon   = 0;
// 		 GoErrCount = 0;
// 	   }
//        else
// 	   GoErrCon = 1;
// 	 }
//    }else{
//      EX0 = 0;
// 	 IE0 = 0;
// 	 GoErrCount = 0;
//      GoErrTimer = 0;
//    }
//   //***********************************************
//   if(DispSensFreq)
//   DispSensFreq--;
//   //***********************************************
//   HotWaitModeTimer++;
//   if(HotWaitModeTimer > 99)
//   {
// 	HotWaitModeTimer = 0;
// 	HeaterSec        = 1;
//     if(HeatTest)		 //Hot Test Timer 1mim
//     {
// 	   TestNtcTimer++;
//        if(TestNtcTimer > 59)
//        {
//          TestNtcTimer = 0;
//          HeatTest      = 0;		//Test cancel
//        }
//     }
//   }
//   //***********************************************
//    if(!HotOnOff && MotDelayOff)   //风机延时
//    {
// 	 MotTimer++;
// 	 if(MotTimer > 99)
// 	 {				   //1S
// 	   MotTimer   = 0;
// 	   MotTimer1++;
// 	   if(MotTimer1 > FAN_DELAY_TIME)  //8s
// 	   {
// 	     MotTimer1   = 0;
// 	     MotDelayOff = 0;
// 	   }
// 	 }
//    }else
//    {
//      MotTimer  = 0;
// 	 MotTimer1 = 0;
//    }
//    //----------------------------------
//    if(FAN && HotDelayeOn)
//    {
// 	 if(++HotTimer > 99)
// 	 {
// 	   HotTimer = 0;
//        if(++HotTimer1 > HOT_DELAY_TIME)
// 	   {
// 		 HotTimer1   = 0;
// 		 HotDelayeOn = 0;
// 	   }
// 	 }

//    }else
//    {
//      HotTimer  = 0;
// 	 HotTimer1 = 0;
//    }
//   //***********************************************
//   TimeTimer++;//加10ms
//   if(TimeTimer > 4)//到50ms
//   {
// 	TimeTimer     = 0;//清零
// 	TimeTimerCon  = 1;//计时加50ms
// 	//--------------------
// 	if(KeySwitchTimer)
// 	KeySwitchTimer--;//减50ms
// 	//--------------------
//     if(LockWoodCon)//闪低灰功能开
//     {
//       LookWoodConTimer++;//50ms
//       if(LookWoodConTimer > LockTimerOtp)//
//       {
//         LookWoodConTimer  = 0;//100ms
// 	    LookWoodConTimerCon++;//加100ms
// 	    if(LookWoodConTimerCon > 11)//到1s
// 	    {
// 		  LookWoodConTimerCon  = 0;
//           LockWoodCon          = 0;
//           LockWoodFalsh        = 0;
// 	    }
// 	    else//没到1s，闪低灰功能翻转
// 	    {
//           if(!LockWoodFalsh)
//           LockWoodFalsh = 1;
//           else
//           LockWoodFalsh = 0;
// 	    }
//       }
//     }
//   }
//   //-----------------------------------------
//    TimerFun();
// }
/************************************************************
*
*
***********************************************************/
void SysTimer(void)
{
  if(TimeTimerCon)
  {
    TimeTimerCon = 0;
	//--------------------
    if(SetTemp)
    {
      TempFlashTimer++;
      if(TempFlashTimer > 9)
      {
        TempFlashTimer  = 0;
	    TempFlashTimerCon++;
        if(TempFlashTimerCon > 8)
        {
          TempFlashTimerCon = 0;
          TempFlash         = 0;
	  	  SetTemp           = 0;
        }
        else
        TempFlash = ~TempFlash;
      }
    }
    else
    {
      TempFlash      = 0;
	  TempFlashTimer = 0;
    }
	//--------------------
	if((BiGuangCon || Hidden) && !KeyLock)
	{
	  HiddenTimer++;
	  if(HiddenTimer > 200)
	  {
		HiddenTimer = 0;
		Hidden      = 0;
		BiGuangCon  = 0;
	  }
	}else
	{
	  HiddenTimer       = 0;
	  //TempFlashTimerCon = 0;
	}
    //--------------------
   if(TempSwFahCon)
   {
     if(!TempSwCon)
	 goto   GoOffFahLed;
   	 TempSwFahTimer++;
	 if(TempSwFahTimer>9)
	 {
	   TempSwFahTimer = 0;
	   TempSwFahTimerCon++;
	   if(TempSwFahTimerCon>5)
	   {
		 GoOffFahLed:
		 TempSwFahTimer    = 0;
	     TempSwFahTimerCon = 0;
		 TempSwFahCon      = 0;
		 TempSwCon         = 0;
		 TcTf = ~TcTf;
	   }else
	   TempSwFah = ~TempSwFah;
	 }
   }else TempSwFah = 0;
  }
}
