/***********************************************************
*  �ļ�˵����ҡ�س���
************************************************************
*  ����:2011.12.22 19:55
*
*  ����:  cuoiszf
*
************************************************************
*  Ӳ����sh79f083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
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
#define   TEMP_ADJUST               2	/* �¶Ȳ�����  4��  4*1.8=7.2    (7) �H */
#define   TEMP_CONTROL_NEGATIVE     1 	/* ���� �ָ�   1��  1*1.8=1.8    (2) �H */
#define   TEMP_CONTROL_POSITIVE     1 	/* ���� ���� 0.5��  0.5*1.8=0.9  (1) �H */
//
bit HotOnOff;
bit MotDelayOff;
void HeaClr1min(void)
{
	OnfHeaTmr = 0;
}
/************************************************************
* ������:
* ����˵��:
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
	if(!Standby  || !HeatGears || !AdReady || ErrCon){//������»�����ؼ���
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