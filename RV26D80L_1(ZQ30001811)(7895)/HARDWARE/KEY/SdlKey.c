/***********************************************************
*
************************************************************
*  ����:
*
*  ����:
*
************************************************************
*  Ӳ����SH79F083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE/main/SysInc.h"

uint8   SdlGears;
uint8   SdlAutoGears;

/*void SdlDisp(void)
{
  if(SdlGears)
  DispDct1 =  SdlGears;
}  */

void SdlKey(void)
{
  OffFlash(0);
  DispDataSet = &ClrDisp;
  //if((KeyAct & K2_SDL) || !SdlGears)
  //{
    SdlGears++;
	if(SdlGears	> 4)
	SdlGears     = 0;
	SdlAutoGears = 1;
  //}
//  KeyAct = K2_SDL;
}