/***********************************************************
*  TM1638驱动
************************************************************
*  日期:2011.9.21 5:00
*
*  作者:  cuoiszf
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
uint8 Timer50ms;
//-----------------------
bit   Hidden;
uint8 HiddenTimer;
//-----------------------
bit   HeaterSec;
uint8 HotWaitModeTimer;
uint8 MotTimer;
uint8 MotTimer1;
//-----------------------
//bit    ErrBzCon;
//uint8  ErrBzTmr,ErrBzSize;
//
bit   ErrDisCon,ErrDisFlh;
uint8 ErrDisTmr,ErrDisSize;
//
void ErrDisIni(void)
{
  if(!ErrDisCon){
    ErrDisTmr = 0;
    ErrDisFlh = 0;
    //
  }
  ErrDisCon  = 1;
  ErrDisSize = 0;
//  BzSet();
}
//-----------------
//void BzSet(void)
//{
//  if(!ErrBzCon){
//    ErrBzTmr = 0;
//    ErrBzSize= 0;
//    BZ_ON();
//    ErrBzCon = 1;
//  }
//}
//-----------------------
bit   FunEndFlash;//功能退出闪烁控制
bit   FunEndFlashCon;
uint8 FunEndFlashTimer;
uint8 FunEndFlashTmerCon;
//-----------------------
bit    AdNtcNew;
uint16 AdNtcValue;
//-----------------------
bit    AdKeyNew;
uint8  AdKeyValue;
//-----------------------
uint8  GoErrTimer;
//-----------------------
bit    SysTimerCon;
//-----------------------
uint8  CfTmr;
/************************************************************
*
* 		取消所有闪烁
************************************************************/
void CancelAllFlash(bit NoFlhWood)
{
  NoFlhWood = NoFlhWood;
  FunEndFlashCon = 0;
  ErrDisCon      = 0;
//  TempSwFlashCon     = 0;
//  if(!NoFlhWood)
//  {
//    LockWoodCon        = 0;
//    LockWoodFah        = 0;
//    LookWoodConTimer   = 0;
//    LookWoodConTimerCon= 0;
//  }
}
/************************************************************
*
* 		   功能退出闪图标
************************************************************/
void FunEndFlashSet(void)
{
  FunEndFlash        = 1;
  FunEndFlashCon     = 1;
  FunEndFlashTimer   = 0;
  FunEndFlashTmerCon = 0;
}
/************************************************************
*
* 			锁闪底灰灯
************************************************************/
//void LookFlhWood(void)
//{
//  if(LockWoodCon)
//  LockWoodFah=1;
//  LockWoodCon=1;
//
//}
/************************************************************
*
* 		  温度转换闪
************************************************************/
//void TempSwFlashSet(void)
//{
//  if(TempSwFlashCon==0)
//  {
//    TempSwFlash        = 1;
//    TempSwFlashTimer   = 0;
//    TempSwFlashTimerCon= 0;
//  }
//  TempSwFlashCon       = 1;
//}
void ClrErrTmr(void)
{
   ErrDisSize = 0;
}
/************************************************************
* 函数名:
* 功能说明:  	  时序定时
************************************************************/
u8 AdErrTim;
void SysTimer(void)  interrupt TMR2_VECTOR   //1ms中断一次
{
	static uint8 Timer1Ms;
	//-----------------
	if (TMR2_GetOverflowIntFlag())
	{
		FlaCon(); // LED亮度控制
		//***********************************************
		if (++Timer1Ms > 9)
		{
			Timer1Ms = 0;
			//***********************************************
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
			// if ((ADCON & 0X01) == 0)
			// {
			// 	if (!(ADCON & 0x04)) //转换的是通道1（按键）
			// 	{
			// 		AdKeyNew = 1;
			// 		AdKeyValue = ADDH;
			// 		ADCON = AD_NTC; //Bin(10000001);
			// 		if (TouchKeyTim)
			// 		{
			// 			if (AdKeyValue > 250)
			// 			{
			// 				TouchKeyCnt1 = 0;
			// 				if (++TouchKeyCnt0 > 9)
			// 				{
			// 					TouchKeyCnt0 = 9;
			// 					TouchKeyOpt = 0;
			// 				}
			// 			}
			// 			else
			// 			{
			// 				TouchKeyCnt0 = 0;
			// 				if (++TouchKeyCnt1 > 9)
			// 				{
			// 					TouchKeyCnt1 = 9;
			// 					TouchKeyOpt = 1;
			// 				}
			// 			}
			// 		}
			// 	}
			// 	else //转换的是通道3（温度传感器）
			// 	{
			// 		AdNtcNew = 1;
			// 		AdNtcValue = (ADDH << 2) | (ADDL & 0x03);
			// 		ADCON = AD_KEY; //Bin(10000011);
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
			if (DispSensFreq != 0)
				DispSensFreq--;
			if (TouchKeyTim)
				TouchKeyTim--;
			//***********************************************
			if (++Timer50ms > 4)
			{
				Timer50ms = 0;
				SysTimerCon = 1;
			}
		}
		//***********************************************
		TMR2_ClearOverflowIntFlag();
	}
}
#if (DWL_EN==1)
	u16  TestMin;

	void TestClrMin(void)
	{
	  TestMin = 0;
	}
#endif
/************************************************************
*
*
************************************************************/
void SysTimer50ms(void)
{
  if(SysTimerCon){SysTimerCon = 0;
	 //----------------
     //***********************************************
     if(KeySwitchTimer!=0)KeySwitchTimer--;
     //***********************************************
     if(!HotOnOff && MotDelayOff){
	   if(++MotTimer > 19){MotTimer   = 0;				   //1.5min
	     if(++MotTimer1 > FAN_DELAY_TIME){MotTimer1   = 0;  //EF033 7:II033 :15S
	       MotDelayOff = 0;
	     }
	   }
     }else{
       MotTimer  = 0;
	   MotTimer1 = 0;
     }
     //***********************************************
     if(KeyLock && Standby){
	   HiddenTimer=0;
     }
	 //***********************************************
	 if(!ErrDisCon && (Hidden || Test0x5a ==0x5a || BiGuangCon)){
	   if(++HiddenTimer > 99){
	     HiddenTimer=0;
	     Hidden=0;
		 Test0x5a = 0;
         BiGuangCon = 0;
	   }
       if(HiddenTimer == 60){
          if(DispDataSet == CfDisp){ // && HeatGears
            DispDataSet = &TempDisp;
            TempSwCon = 0;
            TcTf   = ~TcTf;//加热锁了不能转换温度
          }
       }
	 }else
	 HiddenTimer=0;
     if(!HeatLock){
       if(DispDataSet != CfDisp && TempSwCon){
          TempSwCon = 0;
          TcTf   = ~TcTf;//加热锁了不能转换温度
       }
     }else{
       TempSwCon = 0;
     }
	 //***********************************************
     if(ErrDisCon){
       if(++ErrDisTmr > 9){ErrDisTmr = 0;
         if(++ErrDisSize > 19){ErrDisSize = 0;
            ErrDisCon = 0;
            ErrDisFlh = 0;
            Hidden    = 0;
            BiGuangCon = 0;
         }else{
           ErrDisFlh = ~ErrDisFlh;
         }
       }
     }
     //***********************************************
     if(FunEndFlashCon){
       if(++FunEndFlashTimer>9){FunEndFlashTimer=0;
         if(++FunEndFlashTmerCon>5){FunEndFlashTmerCon=0;
		   FunEndFlashCon=0;
           FunEndFlash= 0;
		   Hidden     = 0;
           if(!KeyLock){BiGuangCon = 0;}
           DispDataSet = &ClrDisp;
         }else
         FunEndFlash=~FunEndFlash;
	   }
     }else
     FunEndFlash=0;
     //***********************************************
     if(OnfHeaTmr)OnfHeaTmr--;
     //***********************************************
//     if(ErrBzCon){
//       if(++ErrBzTmr < 4){//200MS
//         goto OnBz;
//       }else{
//         if(ErrBzTmr > 8){ErrBzTmr = 0;//400MS
//           if(++ErrBzSize > 2){ErrBzSize = 0;//3次
//             ErrBzCon = 0;
//             goto OffBz;
//           }else{
//             OnBz:
//             BZ_ON();
//           }
//         }else{
//           goto OffBz;
//         }
//       }
//     }else{
//       OffBz:
//       BZ_OF(); //BZ = 2000HZ
//     }
#if (DWL_EN==1)
     if(TestCon == 0x55){
       if(++TestMin > 1199){
         TestMin = 0;
         TestCon = 0;
       }
     }else{
       TestMin = 0;
     }
#endif
	 //***********************************************
  }
}
