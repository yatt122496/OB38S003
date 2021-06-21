/***********************************************************
*
************************************************************
*  日期:2015-1-5 16:31
*
*  作者:
*
************************************************************
*  硬件：  SH79F1622
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
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