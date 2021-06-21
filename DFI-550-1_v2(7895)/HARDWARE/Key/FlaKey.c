/***********************************************************
*
************************************************************
*  日期: 2015-1-5 16:31
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

u8  FlaGears;

void FlaUpKey(void)
{
  if(FlaGears > 6)
  FlaGears = 6;
  if(FlaGears)
  {
    FlaGears--;
   	BzSet(1);
	SaveSetCall();
  }
  FlaFahSet(1);
}

void FlaDoKey(void)
{
  if(FlaGears > 6)
  FlaGears = 6;
  if(FlaGears < 6)
  {
    FlaGears++;
   	BzSet(1);
	SaveSetCall();
  }
  FlaFahSet(0);
}

void SysRest(void)
{
  EepromInit(0x99);
}
