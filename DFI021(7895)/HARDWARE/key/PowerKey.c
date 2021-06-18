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
#include "HARDWARE\Lib\inc\epwm.h"
//---------------
bit Standby;
//---------------
void PowerKey(void)
{
  if(!FlaGears && (!HeatOnOff || HeatLock)){
    FlaGears   = 1;
    DotAotoCon = 0;
	  	//设置EPWM 周期以及占空比
		EPWM_ConfigChannelPeriod(EPWM0, PWM_MAX / 2);
		EPWM_ConfigChannelPeriod(EPWM3, PWM_MAX / 2);
		EPWM_ConfigChannelSymDuty(EPWM0, 0);
		EPWM_ConfigChannelSymDuty(EPWM3, 0);
  }
  Standby = ~Standby;
  KeySaveDat();
}