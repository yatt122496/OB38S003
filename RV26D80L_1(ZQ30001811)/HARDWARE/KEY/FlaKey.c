#include "HARDWARE/main/SysInc.h"

//bit     FlaLock;

uint8   FlaGears=1;
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void FlaDisp(void)
{
  if(FlaGears)
  {
    DispDct1 =  L;			//显示字符L
    DispDct2 =  (FLA_MAX+1)-FlaGears;	//显示火焰档位值
  }
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void GinFlaPsw(void)
{
  if(FlaGears)
  {
    DispDataSet = &FlaDisp;
	  if(!(KeyAct & K2_FLA))
	   KeyAct      = 0;
  }
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void FlaKey(void)
{
  CancelAllFlash(0);
  DispDataSet = &FlaDisp;
  if((KeyAct & K2_FLA) || !FlaGears){
	if(++FlaGears	> FLA_MAX){FlaGears = 0;
      KeyAct = 0;
	  return;
	}
	if(FlaGears == FLA_MAX)FlaSpeedInit();
  }
  KeyAct = K2_FLA;
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
//void FlaLockKey(void)
//{
//   if(FlaGears)
//   {
//     KeyAct  = K2_FLA;//激活火焰档位键
//	 FlaLock = ~FlaLock;
//	 LookFlhWood(0);
//   }
//}