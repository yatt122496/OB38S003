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
#include "HARDWARE\main\SysInc.h"
#include "PWM.h"

U8  FlaTimer;
U8  FlaTimerOn;
U8  FlameTimOff;
U8  FalTimer1ms;

U8  code FlameLumList[]=
{
  0,
  10, //常亮
  7,  //高亮
  4,  //中亮
  2,  //微亮
  1,  //微微亮
  0	  //关
};
//-----------------------
U8  FlaTimerOn;
U8  FlaTimerOff;
U8  Fla1MsTimer;
//-----------------------
U16 DotSpeedTimer1;
U8  DotAotoGears1;
U8  DotTimerOn1=49;
U8  DotTimerOff1;
U8  DotTimerOnBuf1;
U8  DotTimerOffBuf1;
U8	DotAutoTim1;
//-----------------------
U16 DotSpeedTimer2;
U8  DotAotoGears2=17;
U8  DotTimerOn2=100;
U8  DotTimerOff2;
U8  DotTimerOnBuf2;
U8  DotTimerOffBuf2;
U8	DotAutoTim2;
//-----------------------
U16 code DotSpeedList[]=
{
//  1   2   3   4 	5   6   7   8   9  10
   25,100, 50,175, 25, 25, 55, 40, 30, 50,
// 11  12  13  14  15  16  17  18  19  20
   50, 75,100, 20,  5, 62, 88, 25, 25, 75,
// 21  22  23  24  25  26  27  28  29  30
   25, 55, 20, 20, 80,150,275, 20, 30, 75,
// 31  32  33  34  35  36  37  38  39  40
   25, 50, 25, 25, 20, 80,250, 70,130, 50,
// 41  42  43  44  45  46
   25, 50, 50,200, 25, 25
};
//-----------------------
U8 code DotOnList[]=
{
//  1   2   3   4 	5   6   7   8   9  10
  100, 10, 10, 70,100,100, 27, 31, 87,100,
// 11  12  13  14  15  16  17  18  19  20
  100, 60, 20, 10, 10, 83, 49, 49, 20,100,
// 21  22  23  24  25  26  27  28  29  30
  100, 47, 50, 47,100,100, 45, 35,100,100,
// 31  32  33  34  35  36  37  38  39  40
   90, 80, 80, 75, 75, 10, 95, 84, 10, 10,
// 41  42  43  44  45  46
   30, 50, 50, 90,100,100
};
U8 code DotOffTimeList[]=
{
// 1  2  3  4  5  6  7  8  9 10
   0, 2, 0, 5, 2, 0, 0,20, 0, 7,
//11 12 13 14 15 16 17 18 19 20
   0, 3, 5, 4, 0, 0, 5, 0, 0, 2,
//21 22 23 24 25 26 27 28 29 30
   0, 2,13,13, 3, 0,10, 4, 0, 0,
//31 32 33 34 35 36 37 38 39 40
   5,10, 0,10, 0, 2, 5,12, 3, 0,
//41 42 43 44 45 46
   0, 5, 0,10, 5, 0
};
void FlaInit(void)
{
  //---------------
  DotAotoGears1   = 17;
  DotTimerOffBuf1 = 49;
  //---------------
  DotAotoGears2   = 0;
  DotTimerOffBuf2 = 100;
  //---------------
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
unsigned int dot1pwm = 0;        //dot1pwm[9:0]=Duty (PWM Channel 0 Data Register 0~1023)
unsigned int fotpwm = 0;        //fotpwm[9:0]=Duty (PWM Channel 2 Data Register 0~1023)
unsigned int dot2pwm = 0;        //dot2pwm[9:0]=Duty (PWM Channel 3 Data Register 0~1023)
unsigned char b5Ms0 = 0, b5Ms1 = 0;
void Timer0( void ) interrupt TIMER1_VECTOR  //1ms //50us
{
	TH1   = (d_MODEVALUE_T1-d_RELOADVALUE_T1)/256;
	TL1   = (d_MODEVALUE_T1-d_RELOADVALUE_T1)%256;

	if(!Standby) {
		MOT  = 0;
		// FOT = 0;
		// DOT1 = 0;
		// DOT2 = 0;
		dot1pwm = 0;
		fotpwm = 0;
		dot2pwm = 0;
		PWM_Output(dot1pwm, 0, fotpwm, dot2pwm);
		//---------------
		DotAotoGears1   = 17;
		DotTimerOffBuf1 = 49;
		//---------------
		DotAotoGears2   = 0;
		DotTimerOffBuf2 = 100;
		//---------------
	} else {
		//-----------------------
		if(!FlaGears) {
			//-----------------------
			// FOT  = 0;
			// dot1pwm = 0;
			fotpwm = 0;
			// dot2pwm = 0;
			PWM_Output(dot1pwm, 0, fotpwm, dot2pwm);
			MOT  = 0;
			//-----------------------
			if(!HeatOnOff || HeatLock) {
				//-----------------------
				// DOT1 = 0;
				// DOT2 = 0;
				dot1pwm = 0;
				// fotpwm = 0;
				dot2pwm = 0;
				PWM_Output(dot1pwm, 0, fotpwm, dot2pwm);
				//-----------------------
			} else {
				//-----------------------
				// Fla1MsTimer++;
				// if(Fla1MsTimer > 19) {
				// 	Fla1MsTimer = 0;
				// 	if(FlaTimerOn) {
				// 		FlaTimerOn--;
				// 		DOT1 = 1;
				// 		DOT2 = 1;
				// 	} else if(FlaTimerOff) {
				// 		FlaTimerOff--;
				// 		DOT1 = 0;
				// 		DOT2 = 0;
				// 	} else {
				// 		FlaTimerOn  = 1;
				// 		FlaTimerOff = 9;
				// 	}
				// }
				dot1pwm = 100;
				// fotpwm = 0;
				dot2pwm = 100;
				PWM_Output(dot1pwm, 0, fotpwm, dot2pwm);
				//-----------------------
			}
		//-----------------------
		} else {
			Fla1MsTimer++;
			if(Fla1MsTimer > 199) {
				Fla1MsTimer = 0;
				// if(FlaTimerOn) {   //火焰开	火焰亮度控制
				// 	FlaTimerOn--;
				// 	FOT    = 1;
				// 	if(DotAotoCon) {
				// 		DOT1 = 1;	   //底灰自动关，底灰跟随火焰
				// 		DOT2 = 1;
				// 	}
				// } else if(FlaTimerOff) {
				// 	FlaTimerOff--;
				// 	FOT  = 0;
				// 	if(DotAotoCon) {
				// 		DOT1 = 0;   //底灰自动关，底灰跟随火焰
				// 		DOT2 = 0;
				// 	}
				// } else {
				// 	//-----------------------
					MOT  = 1;	  //重置火焰亮度值
					FlaTimerOn  = FlameLumList[FlaGears];
					// FlaTimerOff = 10 - FlaTimerOn;
				// 	//-----------------------
				// }
				fotpwm = FlaTimerOn * 100;
				if(DotAotoCon) {
					dot1pwm = fotpwm;
					dot2pwm = fotpwm;
				}
				PWM_Output(dot1pwm, 0, fotpwm, dot2pwm);

			}
			if(!DotAotoCon) {				  //底灰自动开，底灰不随火焰
				b5Ms0++;
				if (b5Ms0 > 99) {
					b5Ms0 = 0;
					if(DotSpeedTimer1)//底灰动态速度控制
						DotSpeedTimer1--;
					else {
						DotSpeedTimer1 = DotSpeedList[DotAotoGears1]*2;
						DotAotoGears1++;		//动态效果控制
						if(DotAotoGears1 > 45)
							DotAotoGears1    = 0;
						DotAutoTim1 = DotOffTimeList[DotAotoGears1-1];
					}
					//-----------------------
					DotAutoTim1++;
					if(DotAutoTim1 >= DotOffTimeList[DotAotoGears1-1]) {
						DotAutoTim1 = 0;
						//-----------------------
						DotTimerOnBuf1 = DotOnList[DotAotoGears1-1];
						//-----------------------
						if(DotTimerOnBuf1!=DotTimerOffBuf1) {
							if(DotTimerOnBuf1>DotTimerOffBuf1)DotTimerOffBuf1++;
							else                              DotTimerOffBuf1--;
						}
					}
					DotTimerOn1 = DotTimerOffBuf1;
					// DotTimerOff1= 100 - DotTimerOn1;
					dot1pwm = DotTimerOn1 * 10;
					// fotpwm = 0;
					// dot2pwm = 0;
					PWM_Output(dot1pwm, 0, fotpwm, dot2pwm);
				}

				//-----------------------
				// if(DotTimerOn1) {//底灰1自动
				// 	DotTimerOn1--;
				// 	DOT1 = 1;
				// } else if(DotTimerOff1) {
				// 	DotTimerOff1--;
				// 	DOT1 = 0;
				// } else {
				// 	if(DotSpeedTimer1)//底灰动态速度控制
				// 		DotSpeedTimer1--;
				// 	else {
				// 		DotSpeedTimer1 = DotSpeedList[DotAotoGears1]*2;
				// 		DotAotoGears1++;		//动态效果控制
				// 		if(DotAotoGears1 > 45)
				// 			DotAotoGears1    = 0;
				// 		DotAutoTim1 = DotOffTimeList[DotAotoGears1-1];
				// 	}
				// 	//-----------------------
				// 	DotAutoTim1++;
				// 	if(DotAutoTim1 >= DotOffTimeList[DotAotoGears1-1]) {
				// 		DotAutoTim1 = 0;
				// 		//-----------------------
				// 		DotTimerOnBuf1 = DotOnList[DotAotoGears1-1];
				// 		//-----------------------
				// 		if(DotTimerOnBuf1!=DotTimerOffBuf1) {
				// 			if(DotTimerOnBuf1>DotTimerOffBuf1)DotTimerOffBuf1++;
				// 			else                              DotTimerOffBuf1--;
				// 		}
				// 	}
				// 	DotTimerOn1 = DotTimerOffBuf1;
				// 	DotTimerOff1= 100 - DotTimerOn1;
				// 	//-----------------------
				// }
				//-----------------------
				b5Ms1++;
				if (b5Ms1 > 99) {
					b5Ms1 = 0;
					if(DotSpeedTimer2)//底灰动态速度控制
						DotSpeedTimer2--;
					else {
						DotSpeedTimer2 = DotSpeedList[DotAotoGears2]*2;
						DotAotoGears2++;		//动态效果控制
						if(DotAotoGears2 > 45)
							DotAotoGears2    = 0;
						DotAutoTim2 = DotOffTimeList[DotAotoGears2-1];
					}
					//-----------------------
					DotAutoTim2++;
					if(DotAutoTim2 >= DotOffTimeList[DotAotoGears2-1]) {
						DotAutoTim2 = 0;
						DotTimerOnBuf2 = DotOnList[DotAotoGears2-1];
						//-----------------------
						if(DotTimerOnBuf2!=DotTimerOffBuf2) {
							if(DotTimerOnBuf2>DotTimerOffBuf2)DotTimerOffBuf2++;
							else                              DotTimerOffBuf2--;
						}
					}
					DotTimerOn2 = DotTimerOffBuf2;
					// DotTimerOff2= 100 - DotTimerOn2;
					// dot1pwm = DotTimerOn1 * 10;
					// fotpwm = 0;
					dot2pwm = DotTimerOn2 * 10;
					PWM_Output(dot1pwm, 0, fotpwm, dot2pwm);
				}
				// if(DotTimerOn2) {	//底灰2自动
				// 	DotTimerOn2--;
				// 	DOT2 = 1;
				// } else if(DotTimerOff2) {
				// 	DotTimerOff2--;
				// 	DOT2 = 0;
				// } else { //取动态效果
				// 	if(DotSpeedTimer2)//底灰动态速度控制
				// 		DotSpeedTimer2--;
				// 	else {
				// 		DotSpeedTimer2 = DotSpeedList[DotAotoGears2]*2;
				// 		DotAotoGears2++;		//动态效果控制
				// 		if(DotAotoGears2 > 45)
				// 			DotAotoGears2    = 0;
				// 		DotAutoTim2 = DotOffTimeList[DotAotoGears2-1];
				// 	}
				// 	//-----------------------
				// 	DotAutoTim2++;
				// 	if(DotAutoTim2 >= DotOffTimeList[DotAotoGears2-1]) {
				// 		DotAutoTim2 = 0;
				// 		DotTimerOnBuf2 = DotOnList[DotAotoGears2-1];
				// 		//-----------------------
				// 		if(DotTimerOnBuf2!=DotTimerOffBuf2) {
				// 			if(DotTimerOnBuf2>DotTimerOffBuf2)DotTimerOffBuf2++;
				// 			else                              DotTimerOffBuf2--;
				// 		}
				// 	}
				// 	DotTimerOn2 = DotTimerOffBuf2;
				// 	DotTimerOff2= 100 - DotTimerOn2;
					//-----------------------
				// }
				//-----------------------
			}
		}
		if(LockWoodFah) {//--100MS闪烁低灰
			// DOT1 = 0;   //底灰自动关，底灰跟随火焰
			// DOT2 = 0;
			dot1pwm = 0;
			// fotpwm = 0;
			dot2pwm = 0;
			PWM_Output(dot1pwm, 0, fotpwm, dot2pwm);
		} else if(LockWoodCon) {
			// DOT1 = 1;	   //底灰自动关，底灰跟随火焰
			// DOT2 = 1;
			dot1pwm = 999;
			// fotpwm = 0;
			dot2pwm = 999;
			PWM_Output(dot1pwm, 0, fotpwm, dot2pwm);
		}
		//-----------------------
	}
}
