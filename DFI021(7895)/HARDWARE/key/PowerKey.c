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
//---------------
bit Standby;
//---------------
void PowerKey(void)
{
  if(!FlaGears && (!HeatOnOff || HeatLock)){
    FlaGears   = 1;
    DotAotoCon = 0;
	  	//����EPWM �����Լ�ռ�ձ�
		EPWM_ConfigChannelPeriod(EPWM0, PWM_MAX / 2);
		EPWM_ConfigChannelPeriod(EPWM3, PWM_MAX / 2);
		EPWM_ConfigChannelSymDuty(EPWM0, 0);
		EPWM_ConfigChannelSymDuty(EPWM3, 0);
  }
  Standby = ~Standby;
  KeySaveDat();
}