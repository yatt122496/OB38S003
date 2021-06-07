/***********************************************************
*  文件说明：摇控程序
************************************************************
*  日期:2011.12.22 19:55
*
*  作者:  cuoiszf
*
************************************************************
*  硬件：sh79f083
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\main\SysInc.h"
//--------------------
bit     TimerCon;
uint8   MsTimer;
uint8   clk[3];
uint8   TimerGears;
//clk1[3];
//bit     TmrDisOtp;
//bit     SecFlh;


/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void ClrTmr(void)
{
  TimerCon = 0;
  TimerGears=0;
  clk[0]   = 0;
  clk[1]   = 0;
  clk[2]   = 0;
  MsTimer  = 0;
}
/************************************************************
* 函数名:
* 功能说明:定时显示
************************************************************/
//void TimDisp( void )
//{
//  if((clk[0] || clk[1] || clk[2])){
//    if(TmrDisOtp){
//      if(clk[2]){
//        DispDct1 = clk[2];
//        DispDct2 = _h_;
//      }else{
//	    goto TmrDispMin;
//      }
//    }else{
//      if(!SecFlh){
//        LedSec = 1;
//      }
//      DispDct1 = clk[2];
//      TmrDispMin:
//      DispDct1 = clk[1]/10;
//	  DispDct2 = clk[1]%10; // 8:88
//    }
//  }else{
//    DispDct1= 0 ;   //"0FF"
//    DispDct2=_F_;
////    DispDct3=_F_;
//  }
//  LedTmr = 1;
//}
void TimDisp( void )
{
  if(TimerGears)
  {
	if(TimerGears==1)
	{
	  DispDct1 = 3;
  	  DispDct2 = 0;
	}else
	{
	  DispDct1 = TimerGears-1;
	  DispDct2 = _H_;
	}
  }else{
    DispDct1= 0 ;   //"0FF"
    DispDct2=_F_;
  }
  LedTmr = 1;
}
/************************************************************
* 函数名:
* 功能说明:定时
************************************************************/
void TimKey( void )
{
  if(!Standby){
    Standby = 1;
    if(ErrCon)
    return;
    KeyAct  = 0;
  }
  CancelAllFlash(0);
  DispDataSet = &TimDisp;
  if((KeyAct & K2_TIM) || !TimerGears)
  {
    TimerCon = 0;
	TimerGears++;
	if(TimerGears > 10)
	{
	  TimerGears = 0;
	  clk[0]       = 0; 	 //clr timer
	  clk[1]       = 0;
	  clk[2]       = 0;
	  KeyAct       = 0;
	  return;
	}
	if(TimerGears==1)
	{
	  clk[1] = 30;
	  clk[2] = 0;
	}else
	{
	  clk[2] = TimerGears - 1;
	  clk[1] = 0;
	}
	clk[0]       = 0;
	MsTimer      = 0;
	TimerCon     = 1;
  }
  KeyAct = K2_TIM;
}

/************************************************************
* 函数名:
* 功能说明:倒计中断
************************************************************/
void TimerFun( void )  interrupt TMR1_VECTOR //10ms
{
	unsigned char count;
	TH1 = (d_MODEVALUE_T1 - d_RELOADVALUE_T1) >> 8;
	TL1 = (d_MODEVALUE_T1 - d_RELOADVALUE_T1);
	if (TimerCon)
	{
		if (++MsTimer > 99)
		{
			MsTimer = 0;
			count = 0; //等于"0"是从秒开始检测
			while (!clk[count])
			{
				count++;		//加"1" 指向分,再加指向时
				if (count == 3) //等于"3"是时为"0".
				{
					Standby = 0; //定时到,待机
					TimerCon = 0;
					TimerGears = 0;
					return;
				}
			}
			clk[count] -= 1; //秒,分,时不为"0"减"1"
			switch (count)
			{ //count等于"0",秒不为"0".
			case 2:
				clk[1] = 59; //等于"2"表示时不为"0",给"分"."秒"赋值"59"
			case 1:
				clk[0] = 59;
				break; //等于"1"表示分不为"0",给秒"赋值"59"
			default:
				break;
			}
		}
		//    if(MsTimer < 64)SecFlh = 0;
		//    else            SecFlh = 1;
	}
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void TimerOff(void)
{

}