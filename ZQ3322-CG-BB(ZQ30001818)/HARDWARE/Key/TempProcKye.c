#include "HARDWARE\main\sysinc.h"

void DispTempValue(void)
{
  float        DatBuf;
  unsigned int DispBuff;
  DatBuf  =  TempValue;
  if(DatBuf > 99)
  DispBuff  = 99;
  else
  DispBuff  = (int)(DatBuf+0.5);
  DispDct1  = DispBuff / 10;
  DispDct2  = DispBuff % 10;
}

void TempProcKey(void)
{
  CancelAllFlash(0);
  DispDataSet = DispTempValue;
  KeyAct = 0;
}