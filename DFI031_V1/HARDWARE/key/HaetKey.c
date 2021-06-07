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
//-----------------------
bit HeatOnOff;
bit HeatLock;
//-----------------------

void HeatKey(void)
{
  if(HeatLock)
  {
//    if(!Standby)
//	{
//	  Standby = 1;
//	  Specify_Volume();
//	  KeySaveDat();
//	}
    LookFlhWood();
  }else
  {
//    if(!Standby)
//    {
//      Standby = 1;
//	  Specify_Volume();
//	  if(!HeatOnOff)
//      goto OnHeat;
//    }else
    {
//      OnHeat:
	  HeatOnOff = ~HeatOnOff;
      if(HeatOnOff)
  	  Hot3min();
    }
    KeySaveDat();
  }
}

/************************************************************
*
* 		   加热锁
************************************************************/
void HeatLook( void )
{
  if(Standby){
//  Standby   = 1;
    HeatLock  = ~HeatLock;
  //HeatOnOff = 0;
    KeySaveDat();
    LookFlhWood();
  }
}