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
uint8  MotTimer;
uint8  MotTimer1;
//-----------------------
bit   Hidden;
uint8 HiddenTimer;
//--------------------
bit   TempFlash;
uint8 idata TempFlashTimer;
uint8 idata TempFlashTimerCon;
//----------------------------
uint8 idata GoErrTimer;
//----------------------------
uint8 idata TimeTimer;
bit   idata TimeTimerCon;
//---------------------------
bit   HeaterSec;
uint8 HotWaitModeTimer;
//-----------------------
bit   HeatTest;
uint8 TestNtcTimer;	//测试NTC 1分钟后取消测试控制
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
//------------------------------
bit   ShowCon;
bit   ShowOnCon;
u8    idata ShowHcnt;
u8    idata ShowLcnt;
u16   idata ShowTim;

uint8 FlaTimer;
uint8 FlaTimerOn;
uint8 FlameTimOff;
uint8 FalTimer1ms;
u8 AdErrTim;

unsigned char  code FlameLumConst[7]=
{
  0,   //关
  10,  //常亮
  2,   //微微亮
  5,   //高亮
  10,  //常亮
  0
};
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
/************************************************************
*
*
***********************************************************/
void SysTimer_Isr(void)  interrupt TMR2_VECTOR   //1ms中断一次
{
	static u8 b1ms = 0;
	if (TMR2_GetOverflowIntFlag())
	{
		//***********************************************
#if UART_TEST
		Sys_Time++;
#endif
		b1ms++;
		if (b1ms > 9)
		{
			b1ms = 0;
			if (0 == ADC_IS_BUSY) {
				if (ADCCHS == ADC_CH_9) {
					AdKeyNew = 1;
					AdKeyValue = ADC_GetADCResult() >> 4;
					ADC_EnableChannel(ADC_CH_10);
					ADC_GO();
					AdErrTim = 0;
					if (TouchKeyTim)
					{
						if (AdKeyValue > 250)
						{
							TouchKeyCnt1 = 0;
							if (++TouchKeyCnt0 > 9)
							{
								TouchKeyCnt0 = 9;
								TouchKeyOpt = 0;
							}
						}
						else
						{
							TouchKeyCnt0 = 0;
							if (++TouchKeyCnt1 > 9)
							{
								TouchKeyCnt1 = 9;
								TouchKeyOpt = 1;
							}
						}
					}
				} else if (ADCCHS == ADC_CH_10) {
					AdNtcNew = 1;
					AdNtcValue = ADC_GetADCResult() >> 2;
					ADC_EnableChannel(ADC_CH_9);
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
					ADC_EnableChannel(ADC_CH_9);
					ADCON1 = 0xF0;
					ADC_GO();
				}
			}
			// if((ADCON&0X01)==0)
			// {
			// 	if(!(ADCON&0x04))//转换的是通道1（按键）
			// 	{
			// 	AdKeyNew    = 1;
			// 	AdKeyValue  = ADDH;
			// 	ADCON       = AD_NTC  ;//Bin(10000001);
			// 	}else//转换的是通道3（温度传感器）
			// 	{
			// 	AdNtcNew    = 1;
			// 	AdNtcValue  = (ADDH << 2) | (ADDL & 0x03);
			// 	ADCON       = AD_KEY  ;//
			// 	}
			// }
			//***********************************************
			if (HOT && !GoErrCon)
			{
				P3EXTIE |= (1 << 1);
				// EX0 = 1;
				if (++GoErrTimer > 99)
				{
					GoErrTimer = 0;
					if (GoErrCount > 40) {
						GoErrCon = 0;
						GoErrCount = 0;
					}
					else {
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
			if (DispSensFreq)
				DispSensFreq--;
			if (TouchKeyTim)
				TouchKeyTim--;
			//***********************************************
			HotWaitModeTimer++;
			if (HotWaitModeTimer > 99)
			{
				HotWaitModeTimer = 0;
				HeaterSec = 1;
				if (HeatTest) //Hot Test Timer 1mim
				{
					TestNtcTimer++;
					if (TestNtcTimer > 59)
					{
						TestNtcTimer = 0;
						HeatTest = 0; //Test cancel
					}
				}
			}
			//***********************************************
			if (!HotOnOff && MotDelayOff) //风机延时
			{
				MotTimer++;
				if (MotTimer > 99)
				{ //1S
					MotTimer = 0;
					MotTimer1++;
					if (MotTimer1 > FAN_DELAY_TIME) //8s
					{
						MotTimer1 = 0;
						MotDelayOff = 0;
					}
				}
			}
			else
			{
				MotTimer = 0;
				MotTimer1 = 0;
			}
			//***********************************************
			TimeTimer++;	   //加10ms
			if (TimeTimer > 4) //到50ms
			{
				TimeTimer = 0;	  //清零
				TimeTimerCon = 1; //计时加50ms
				//--------------------
				if (KeySwitchTimer)
					KeySwitchTimer--; //减50ms
				//--------------------
				if (LockWoodCon) //闪低灰功能开
				{
					LookWoodConTimer++;					 //50ms
					if (LookWoodConTimer > LockTimerOtp) //
					{
						LookWoodConTimer = 0;		  //100ms
						LookWoodConTimerCon++;		  //加100ms
						if (LookWoodConTimerCon > 11) //到1s
						{
							LookWoodConTimerCon = 0;
							LockWoodCon = 0;
							LockWoodFalsh = 0;
						}
						else //没到1s，闪低灰功能翻转
						{
							if (!LockWoodFalsh)
								LockWoodFalsh = 1;
							else
								LockWoodFalsh = 0;
						}
					}
				}
			}
			//-------------------------------
			if (!SHOWKEY)
			{
				ShowLcnt = 0;
				if (++ShowHcnt > 9)
				{
					ShowHcnt = 0;
					ShowCon = 1;
					if (!Standby)
						Standby = 1;
				}
			}
			else
			{
				ShowHcnt = 0;
				if (++ShowLcnt > 9)
				{
					ShowLcnt = 0;
					ShowCon = 0;
					ShowOnCon = 0;
				}
			}
			//-----------------------------------------
			TimerFun();
		}
		if (!Standby) //待机状态，关灯关电机
		{
			MOT = 0;
			FOT = 0;
			DOT = 0;
			DWL1 = 0;
			DWL2 = 0;
			DOT1 = 0;
			//--------
		}
		else
		{
			FlaTimer++;		   //火焰时间
			if (FlaTimer > 10) //大于10ms
			{
				FlaTimer = 0; //清零
				if (FlaGears || ShowOnCon)
				{
					//--------
					DOT = 1;
					DOT1 = 1;
					//--------
					if ((FlaGears != 1) || ShowOnCon) //档位为2.3.4
					{
						MOT = 1;
						FOT = 1;
						DWL1 = 1;
						DWL2 = 1;
					}
					else //档位为1
					{
						MOT = 0;
						FOT = 0;
						DWL1 = 0;
						DWL2 = 0;
					}
					if (ShowOnCon)
						FlaTimerOn = FlameLumConst[4];
					else
						FlaTimerOn = FlameLumConst[FlaGears]; //火焰档位亮度
					FlameTimOff = FlaTimerOn;
				}
				else //档位为0
				{
					MOT = 0;
					FOT = 0;
					DWL1 = 0;
					DWL2 = 0;
					if ((HeaOnOff) && (!HeatLock))
					{
						//--------
						DOT = 1;
						DOT1 = 1;
						//--------
						FlameTimOff = 1;
						//FlameTimOff = 2;
						FlaTimerOn = FlameTimOff;
					}
					else
					{
						DOT = 0;
						DOT1 = 0;
					}
				}
			}
			if (FlaTimerOn != 10)
			{
				if (FlameTimOff != 0)
					FlameTimOff--;
				else
				{
					FOT = 0;
					DOT = 0;
					DOT1 = 0;
				}
			}
			if (LockWoodFalsh) //--100MS闪烁低灰
			{
				DOT = 1;
				DOT1 = 1;
			}
			else if (LockWoodCon)
			{
				DOT = 0;
				DOT1 = 0;
			}
		}
		TMR2_ClearOverflowIntFlag();
	}
}
// void SysTimer_Isr(void) interrupt TIMER2    //10ms
// {
//   TF2   =  0;
//   //***********************************************
//   if((ADCON&0X01)==0)
//   {
//     if(!(ADCON&0x04))//转换的是通道1（按键）
//     {
//       AdKeyNew    = 1;
//       AdKeyValue  = ADDH;
//       ADCON       = AD_NTC  ;//Bin(10000001);
//     }else//转换的是通道3（温度传感器）
//     {
//       AdNtcNew    = 1;
// 	  AdNtcValue  = (ADDH << 2) | (ADDL & 0x03);
//       ADCON       = AD_KEY  ;//
//     }
//    }
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
//   //-------------------------------
//   if(!SHOWKEY){
//     ShowLcnt=0;
//     if(++ShowHcnt>9){ShowHcnt=0;
//      ShowCon = 1;
// 	 if(!Standby)Standby=1;
//     }
//   }else{
//     ShowHcnt=0;
//     if(++ShowLcnt>9){ShowLcnt=0;
//      ShowCon = 0;
// 	 ShowOnCon = 0;
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
	#if (KEY_BG_EN==1)
        DispDataSet = &ClrDisp;
	#endif
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
   //-----------------------------
   if(ShowCon)
   {
	 if(ShowTim)ShowTim--;
     if(!ShowTim){
	   if(!ShowOnCon){
		 ShowOnCon = 1;
	   }
	 }
   }
  }
}