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

/**********************************************************
*
*	 SEG1  SEG2  SEG3  SEG4  SEG5  SEG6  SEG7
*
*	  B		C	  E		D	  G		A	  F
*
*    LED1			  LED2		   LED3
**********************************************************/
//数码管代码表
unsigned char code LedDispCode[]=
{
	0x6F,		// 0
	0x03,		// 1
	0x3D,		// 2
	0x3B,		// 3
	0x53,		// 4
	0x7A,		// 5
	0x7E,		// 6
	0x23,		// 7
	0x7F,		// 8
	0x7B,		// 9
	0x77,		// A
	0x5E,		// B
	0x6C,		// C
	0x1F,		// D
	0x7C,		// E
	0x74,		// F
	0x00,		// -
	0x56,		// h
	0x4C,		// L
	0x67		// N
};

void (*DispDataSet)();
uint8   DispDct1;
uint8   DispDct2;
uint8   DispLed;
uint8   HidTimer;
uint8   SlowlyHidden;
uint8   DispSensFreq;

bit     BiGuangCon;

void ClrDisp(void)
{
  DispDct1 = DISP_OFF;
  DispDct2 = DISP_OFF;
#if (KEY_BG_EN==1)
  DispLed = 0;
#else
  DispLed = DISP_OFF;
#endif
}

void Disp( void )
{
  unsigned char DispBuff[4];
  if(DispSensFreq==0)
  {
    DispSensFreq = 2;//20ms循环一次
	DispBuff[0]  = 0;
	DispBuff[1]  = 0;
	DispBuff[2]  = 0;
	ClrDisp();
  #if (KEY_BG_EN==1)
    if(!Hidden)
  #else
	if(!Hidden || !Standby)//待机状态或隐藏
  #endif
	{
	  KeyAct       = 0;
	  SlowlyHidden = 0x80;
	  DispDataSet  = &ClrDisp;
	}
	else
	{
	  DispDataSet();
	  if(!TempFlash && !TempSwFah)
	  {
		DispBuff[0] = LedDispCode[DispDct1];
		DispBuff[1] = DispLed;
	    DispBuff[2] = LedDispCode[DispDct2]; //
	  }
	  SlowlyHidden = 0x8A;
	}
  #if (KEY_BG_EN==1)
	if(BiGuangCon)
  #else
	if(BiGuangCon && Standby)
  #endif
	{
	  DispBuff[1]  = LED_POW | LED_FLA | LED_HEA | LED_TIM;
	  SlowlyHidden = 0x8a;
	}
	DispBuff[3]  = SlowlyHidden;
	WriteTm1638Data(&DispBuff[0]);
  }
}