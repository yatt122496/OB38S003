#include "HARDWARE\include\SysInc.h"
/************************************************************
* ������:
* ����˵��:
************************************************************/
unsigned int  NtcErrDat;
unsigned char ErrCon;
/************************************************************
* ������:
* ����˵��:	  ����10���ӻָ���ʱ����
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