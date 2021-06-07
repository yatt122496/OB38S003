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
/***********************************************************
*
*
*
*
***********************************************************/
#define  HEA_1MIN    1200 // (60*1000)ms / 50ms

#define  HEA_4MIN    4800 //((4*60*1000l)/50)
#define  HEA_30S     600  //((30*1000)/50)


uint16 OnfHeaTmr;
/************************************************************
*
*
*
*
*
*
***********************************************************/
#define   TEMP_ADJUST               2	/* 温度补尝，  4℃  4*1.8=7.2    (7) ℉ */
#define   TEMP_CONTROL_NEGATIVE     1 	/* 负数 恢复   1℃  1*1.8=1.8    (2) ℉ */
#define   TEMP_CONTROL_POSITIVE     1 	/* 正数 保护 0.5℃  0.5*1.8=0.9  (1) ℉ */
//
bit HotOnOff;
bit MotDelayOff;
void HeaClr1min(void)
{
	OnfHeaTmr = 0;
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void HeatCon(void)
{
   unsigned char  SetTcBuff;
   float          TfBuff;
	if(GoErrCon){
		HOT         = 0;
		FAN         = 0;
		MotDelayOff = 0;
		return;
	}
	if(!Standby  || !HeatGears || !AdReady || ErrCon){//如果超温或待机关加热
		HOT      = 0;
		HotOnOff = 0;
		if(!MotDelayOff)
			FAN      = 0;
		OnfHeaTmr= 0;
		return;
	}
   //=================
#if (DWL_EN==1)
	if(TestCon == 0x55){
		HotOnOff = 1;
		OnfHeaTmr= 0;
		goto GoHeat;
	}
#endif
   //=================
	if(HeatGears  > 27)
		HeatGears     = 27;
	SetTcBuff = SetTcTable[HeatGears];
	if(SetTcBuff  >= 40)
		SetTcBuff     = 40;
	else
		SetTcBuff = SetTcBuff + TEMP_ADJUST;
	//-----------------------------------
	TfBuff = TempValue + TEMP_CONTROL_NEGATIVE;
	if(SetTcBuff >= TfBuff){
		if(!OnfHeaTmr){
			OnfHeaTmr = HEA_1MIN;
			HotOnOff = 1;
		}
	}else{
		TfBuff = TempValue - TEMP_CONTROL_POSITIVE;
		if(SetTcBuff <= TfBuff){
			if(!OnfHeaTmr){
				OnfHeaTmr = HEA_4MIN;
				HotOnOff = 0;
			}
		}
	}
#if (DWL_EN==1)
	GoHeat:
#endif
	if(HotOnOff){
		HOT  = 1;
		FAN  = 1;
		MotDelayOff=1;
	}else{
		HOT  = 0;
		if(!MotDelayOff)
			FAN  = 0;
	}
}