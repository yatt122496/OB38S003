/***********************************************************
*
************************************************************
*  ����:2015-1-5 16:31
*
*  ����:
*
************************************************************
*  Ӳ����  SH79F1622
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE\include\SysInc.h"

bit HeatOnOff;
bit HeatLock;

void HeatKey(void)
{
  if(!HeatLock)
  {
    HeatOnOff = ~HeatOnOff;
	Hot3min();
	BzSet(1);
	SaveSetCall();
  }else
  {
    HlTimeSet();
	BzSet(17);
  }
}

void HeatLockKey(void)
{
  HeatLock  = ~HeatLock;
  HeatOnOff = 0;
  if(HeatLock)
  BzSet(17);
  else
  BzSet(1);
  SaveSetCall();
}