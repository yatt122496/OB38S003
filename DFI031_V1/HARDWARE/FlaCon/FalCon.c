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

U8 FlaTimer;
U8 FlaTimerOn;
U8 FlameTimOff;
U8 FalTimer1ms;

U8 code  FlameLumConst[]=
{
  0,  //关
  2,  //微微亮
  4,  //微亮
  6,  //中亮
  8,  //高亮
  10,  //常亮
  0
};
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void FlaCon( void )  //1ms
{
  if(!Standby)
  {
    MOT  = 0;
	FOT  = 0;
	DOT1 = 0;
	DOT2 = 0;
  }else
  {
    FlaTimer++;
    if(FlaTimer>10)
	{
	   FlaTimer=0;
	  //-------------------
	  if(FlaGears > FLA_MAX)
	  FlaGears    = FLA_MAX;
	  //-------------------
	   if(AdNtcErr)
	   {
	     FOT = 1;
		 MOT  = 0;
		 DOT1 = 1;
		 DOT2 = 1;
	     FlaTimerOn  = 10;
		 FlameTimOff = FlaTimerOn;
	   }else
       {
		  if(FlaGears)
		  {
			 FOT = 1;
			 MOT  = 1;
			 DOT1 = 1;
			 DOT2 = 1;
			 FlaTimerOn  = FlameLumConst[FlaGears];
			 FlameTimOff = FlaTimerOn;
		  }else
		  {
			 FOT = 0;
			 MOT  = 0;
			 if((HeatOnOff)&&(!HeatLock))
			 {
			   FlameTimOff = 1;
			   FlaTimerOn  = FlameTimOff;
			   DOT1        = 1;
			   DOT2        = 1;
			 }else{
			   DOT1 = 0;
			   DOT2 = 0;
			 }
		  }
	  }
	}
	//----------------------------------------
	if(FlaTimerOn!=10)
    {
	  if(FlameTimOff != 0)
	  FlameTimOff--;
	  else
	  {
		FOT  = 0;
		DOT1 = 0;
		DOT2 = 0;
	  }
    }
	//----------------------------------------
	if(LockWoodFah)//--100MS闪烁低灰
	{
	   FOT   = 1;
	   DOT1  = 1;
	   DOT2  = 1;
	}else if(LockWoodCon || GoErrCon)
	{
	   FOT   = 0;
	   DOT1  = 0;
	   DOT2  = 0;
	}
	/**********************************/
  }
}
