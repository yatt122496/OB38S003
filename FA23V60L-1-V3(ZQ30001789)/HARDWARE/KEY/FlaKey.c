#include "HARDWARE/main/SysInc.h"

bit     FlaLock;

uint8   FlaGears;
/************************************************************
* ������:
* ����˵��:
************************************************************/
void FlaDisp(void)
{
  if(FlaGears)
  {
    DispDct1 =  L;			//��ʾ�ַ�L
    DispDct2 =  FlaGears;	//��ʾ���浵λֵ
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
  if(!FlaGears)
  FlaGears = 4;
  else
  if(KeyAct & K2_FLA)
  {
	if(FlaGears)
	FlaGears--;
  }
  KeyAct = K2_FLA;//������浵λ��
}
/************************************************************
* ������:
* ����˵��:
************************************************************/
void FlaLockKey(void)
{
   if(FlaGears)
   {
     KeyAct  = K2_FLA;//������浵λ��
	 FlaLock = ~FlaLock;
	 LookFlhWood(0);
   }
}