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
/************************************************************
* ������:
* ����˵��:
************************************************************/
//void FlaLockKey(void)
//{
//   if(FlaGears)
//   {
//     KeyAct  = K2_FLA;//������浵λ��
//	 FlaLock = ~FlaLock;
//	 LookFlhWood(0);
//   }
//}