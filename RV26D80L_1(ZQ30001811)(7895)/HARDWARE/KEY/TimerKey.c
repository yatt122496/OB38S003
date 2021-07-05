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

bit     AllOffTimerCon;
bit     TimerCon;
uint8   Hou = 0;
uint8   Min = 0;
uint8   MsTimer;
uint8   clk[3]; //时间缓存  ： clk[2]小时，clk[1]分钟，clk[0]秒，
uint8   TimerGears;
/************************************************************
* 函数名:
* 功能说明:定时显示
************************************************************/
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
	  DispDct2 = H;
	}
	DispLed = 0x20;
  }
}
/************************************************************
* 函数名:
* 功能说明:定时显示
************************************************************/
void TimKey( void )
{
  CancelAllFlash(0);
  DispDataSet = &TimDisp;
  if(AllOffTimerCon)
  return;
  if((KeyAct & K2_TIM) || !TimerGears)
  {
    TimerCon = 0;
	TimerGears++;
	if(TimerGears > 7)
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
//void Timer1Isr( void ) interrupt TIMER1
//{
//  unsigned char count;
//  TF1 = 0;
//  if(TimerCon)
//  {
//    MsTimer++;
//    if(MsTimer > 127)
//    {
//      MsTimer = 0;
//	  count   = 0;//等于"0"是从秒开始检测
//      while(!clk[count])
//      {
//        count++;   //加"1" 指向分,再加指向时
//	    if(count==3)//等于"3"是时为"0".
//        {
//	      Standby        = 0;//定时到,待机
//		  TimerCon       = 0;
//	      TimerGears     = 0;
//	      return;
//	    }
//      }
//      clk[count]-=1;//秒,分,时不为"0"减"1"
//      switch(count)
//      {             //count等于"0",秒不为"0".
//	    case 2: clk[1]=59;//等于"2"表示时不为"0",给"分"."秒"赋值"59"
//	    case 1: clk[0]=59;break;//等于"1"表示分不为"0",给秒"赋值"59"
//	    default:break;
//      }
//    }
//  }
//}
void TimerFun( void )
{
  unsigned char count;
//  TF1 = 0;
  if(TimerCon)
  {
    MsTimer++;
    if(MsTimer > 99)
    {
      MsTimer = 0;
	  count   = 0;//等于"0"是从秒开始检测
      while(!clk[count])
      {
        count++;   //加"1" 指向分,再加指向时
	    if(count==3)//等于"3"是时为"0".
        {
	      Standby        = 0;//定时到,待机
		  TimerCon       = 0;
	      TimerGears     = 0;
	      return;
	    }
      }
      clk[count]-=1;//秒,分,时不为"0"减"1"
      switch(count)
      {             //count等于"0",秒不为"0".
	    case 2: clk[1]=59;//等于"2"表示时不为"0",给"分"."秒"赋值"59"
	    case 1: clk[0]=59;break;//等于"1"表示分不为"0",给秒"赋值"59"
	    default:break;
      }
    }
  }
}
void TimerOff(void)
{
  if(!HeaOnOff && !FlaGears && !DowGears)
  {
    if(!AllOffTimerCon || TimerCon)
	{
      TimerCon = 0;
	  clk[0]   = 0; 	    //clr timer
	  clk[1]   = 0;
	  clk[2]   = 0;
	  TimerGears = 0;
	}
	AllOffTimerCon = 1;
  }else
  AllOffTimerCon   = 0;
}