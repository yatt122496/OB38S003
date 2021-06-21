#include "HARDWARE\include\SysInc.h"
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
unsigned int  NtcErrDat;
unsigned char ErrCon;
/************************************************************
* 函数名:
* 功能说明:	  错误10分钟恢复定时控制
************************************************************/
void SysErrCon(void)
{
  if(AdReady)
  {
    if(NtcErrDat > 1010)
    ErrCon = 2;
    else
    if(NtcErrDat < 14)
    ErrCon = 1;
    else
    ErrCon = 0;
  }else
  ErrCon = 0;
}