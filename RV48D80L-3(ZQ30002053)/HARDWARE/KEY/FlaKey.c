#include "HARDWARE/main/SysInc.h"

//bit     FlaLock;

uint8   FlaGears=1;
/************************************************************
* ������:
* ����˵��:
************************************************************/
void FlaDisp(void)
{
  if(FlaGears)
  {
    DispDct1 =  L;			//��ʾ�ַ�L
    DispDct2 =  (FLA_MAX+1)-FlaGears;	//��ʾ���浵λֵ
  }
}
/************************************************************
* ������:
* ����˵��:
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
* ������:
* ����˵��:
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

#if (LUM_EN==1)
/************************************************************
* ������:
* ����˵��:
************************************************************/
u8 FlaLum=0;
void FlaLumDisp(void)
{
  if(FlaGears){
   if(FlaLum > 2)FlaLum = 2;
   DispDct2 = 3-FlaLum;
  }
}
void FlaAutoKey(void)
{
 if(FlaGears){
  if(FlaGears > FLA_MAX) FlaGears = FLA_MAX;
  //---------------
  if(FlaGears!=FLA_MAX){
    DispDataSet = &FlaLumDisp;
	if(KeyAct & K2_FAO){
     if(++FlaLum > 2){FlaLum = 0;}
	}
  }
  KeyAct = K2_FAO;
 }
}
#endif