#include "HARDWARE/main/SysInc.h"

uint8   DwlGears;
uint8   DwlAutoGears;

void DwlDisp(void)
{
  if(DwlGears)
  DispDct1 =  DwlGears;
}

void DwlKey(void)
{
  CancelAllFlash(0);
  DispDataSet = &ClrDisp;
  if((KeyAct & K2_DWL) || !DwlGears)
  {
    DwlGears++;
	if(DwlGears	> 4)
	DwlGears     = 0;
	DwlAutoGears = 1;
  }
  KeyAct = K2_DWL;
}