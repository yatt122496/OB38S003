/***********************************************************
*  TM1638驱动
************************************************************
*  日期:2011.9.21 5:00
*
*  作者:  cuoiszf
*
************************************************************
*  硬件：MB95F204K
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE/main/SysInc.h"

bit           Standby;
unsigned int  KeyAct;
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void PowKey( void )
{
   CancelAllFlash(1);
   if(!Standby)//待机状态
   {
	 Standby     = 1;//进入工作状态
	 HeatTest = 0;
	 if(!HeaOnOff && !FlaGears && !DowGears)
	 FlaGears = 1;
	 if(HeaOnOff && !HeatLock)//显示温度标志位1则优先显示温度
	 {
	   DispDataSet = &HeatDisp;
	   KeyAct = K2_HEA;
	   Heat3min();
	 }
	 else//温度显示标志位0 ，则显示火焰档位
	 if(FlaGears)
	 {
	   DispDataSet = &FlaDisp;
	   KeyAct = K2_FLA;
	 }else
	  if(DowGears){
	   DispDataSet = &DowDisp;
	   KeyAct = K2_DOW;
	  }
   }
   else//进入待机状态
   {
     TimerCon   = 0;//定时清零
	 clk[0]     = 0;
	 clk[1]     = 0;
	 clk[2]     = 0;
	 Standby    = 0;
	 KeyAct     = 0;
   }
}

