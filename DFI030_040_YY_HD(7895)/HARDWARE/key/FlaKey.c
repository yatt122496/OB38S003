/***********************************************************
*  �ļ�˵����
************************************************************
*  ����:
*
*  ����:
*
************************************************************
*  Ӳ����sh79f083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE\main\SysInc.h"
#include "HARDWARE\Lib\inc\epwm.h"
//-----------------
U8  FlaGears;
bit DotAotoCon;
//-----------------
/************************************************************
* ������:
* ����˵��:
************************************************************/
void FlaKey(void)
{
//  if(!Standby)
//  {
//    Standby = 1;
//	Specify_Volume();
//	if(!FlaGears)
//    goto OnFla;
//  }else
//  {
//    OnFla:
#if VTX_TEST
	bVtime++;
#endif
  if(!FlaGears){
	FlaGears   = 5;
  }else
  if(FlaGears){
    FlaGears--;
  }
  if(!FlaGears){
	DotAotoCon = 0;
	EPWM_ConfigChannelPeriod(EPWM0, PWM_MAX / 2);
	EPWM_ConfigChannelPeriod(EPWM3, PWM_MAX / 2);
	EPWM_ConfigChannelSymDuty(EPWM0, 0);
	EPWM_ConfigChannelSymDuty(EPWM3, 0);
  }
  KeySaveDat();

//	FlaGears++;
//	if(FlaGears > 5)
//	{
//	  FlaGears   = 0;
//	  DotAotoCon = 0;
//	}
//  }
//  KeySaveDat();
}
void FlaUKey(void)
{
//  if(!Standby)
//  {
//    Standby = 1;
//	Specify_Volume();
//	if(!FlaGears)
//    goto OnFla;
//  }else
  {
//    OnFla:
	FlaGears++;
	if(FlaGears > 5){
	  FlaGears   = 5;
	}else{
      KeySaveDat();
    }
  }
}
void FlaDKey(void)
{
  if(FlaGears){
    FlaGears--;
    KeySaveDat();
  }
  if(!FlaGears){
	DotAotoCon = 0;
	EPWM_ConfigChannelPeriod(EPWM0, PWM_MAX / 2);
	EPWM_ConfigChannelPeriod(EPWM3, PWM_MAX / 2);
	EPWM_ConfigChannelSymDuty(EPWM0, 0);
	EPWM_ConfigChannelSymDuty(EPWM3, 0);
  }
}
/************************************************************
* ������:
* ����˵��:
************************************************************/
void DotAutoKey(void)
{
  DotAotoCon = ~DotAotoCon;
  if (DotAotoCon) {
			//����EPWM �����Լ�ռ�ձ�
		EPWM_ConfigChannelPeriod(EPWM0, PWM_MAX);
		EPWM_ConfigChannelPeriod(EPWM3, PWM_MAX);
		EPWM_ConfigChannelSymDuty(EPWM0, 0);
		EPWM_ConfigChannelSymDuty(EPWM3, 0);
	} else {
		  	//����EPWM �����Լ�ռ�ձ�
		EPWM_ConfigChannelPeriod(EPWM0, PWM_MAX / 2);
		EPWM_ConfigChannelPeriod(EPWM3, PWM_MAX / 2);
		EPWM_ConfigChannelSymDuty(EPWM0, 0);
		EPWM_ConfigChannelSymDuty(EPWM3, 0);
	}
  KeySaveDat();
}