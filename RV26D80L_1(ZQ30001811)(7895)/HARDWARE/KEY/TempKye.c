/***********************************************************
*
************************************************************
*  ����:
*
*  ����:
*
************************************************************
*  Ӳ����SH79F083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE/main/SysInc.h"
bit   TcTf;
uint8 code SetTcTable[] =
{//���������¶�
	0,	   //32	 	0
//	17,	   //63 	1
	18,	   //63 	2
	19,	   //66 	3
	20,	   //63 	4
	21,	   //70 	5
	22,	   //63 	6
	23,	   //73 	7
	24,	   //75 	8
	25,	   //77 	9
	26,	   //63 	10
	27,	   //82 	11
	60	   //63 	12
};
uint8 code SetTfTable[] =
{//���û����¶�
	0,	   //OFF 	0
//	62,	   //16.67 	1
	64,	   //17.78 	2
	66,	   //18.89 	3
	68,	   //20.00 	4
	70,	   //21.11 	5
	72,	   //22.22 	6
	74,	   //23.33 	7
	76,	   //24.44 	8
	78,	   //25.56 	9
	80,	   //26.67 	10
	82,	   //27.78 	11
	140,   //ON 	12
};
bit     HeaOnOff;
uint8   HeatGears;

bit     SetTemp;
bit     HeatLock;
uint8   HeatLockTimer;

void HeatDisp(void)
{
	if(ErrCon){
	  DispDct1 = E;
	  DispDct2 = ErrCon;
	}else if(!HeatLock && HeaOnOff)//�������򿪣������Ա�־λ1 ����ʾ�¶�
	{
		if(HeatGears >= 11)
		{
			DispDct1 = 0;//��ʾ�ַ�0
			DispDct2 = N;//��ʾ�ַ�N
		}else if(HeatGears)//�¶ȵ�λ��Ϊ0
		{
			if(TcTf)//�����±�Ϊ1 ����ʾ�����¶�
			{
				DispDct1 = SetTcTable[HeatGears] / 10;
				DispDct2 = SetTcTable[HeatGears] % 10;
			}
			else//�����±�Ϊ0 ����ʾ�����¶�
			{
			   	DispDct1 = SetTfTable[HeatGears] / 10;
				DispDct2 = SetTfTable[HeatGears] % 10;
			}
		}
//		if(!TempSwFah)
//		{
		  if(TcTf)//�����±�Ϊ1 ����ʾ�����¶�
		  DispLed = 0X40;//�����¶�ָʾ����
		  else
		  DispLed = 0X08;//�����¶�ָʾ����
//		}
	}
}
/************************************************************
* ������:
* ����˵��:  ��ü��ȼ�״̬
************************************************************/
void GainHeaterPsw(void)
{
   if(!SetTemp)//�����¶�����״̬
   HeatLockTimer = 0;//��������ʱ����
   if(ErrCon){
    SetTemp = 1; TempFlash = 1;
	KeyAct = K2_HEA;
	DispDataSet = &HeatDisp;
   }if(HeatLock)//���ȼ�������״̬
   {
	 LookFlhWood(1);//��˸
	 KeyAct = K2_HEA;
   }
   else//���ȼ���������״̬
   {
	 if(HeaOnOff)//���Ա�־λ1 ����ʾ�¶�
	 DispDataSet = &HeatDisp;
	 //CancelAllFlash(2);
   }
}

void TempSetKey(void)
{
   if(ErrCon){
	 SetTemp = 1; TempFlash = 1;
     return;
   }
   if(!HeaOnOff || HeatLock){// || !(KeyAct & K2_HEA)){
     return;
   }
   DispDataSet = &HeatDisp;//�¶ȼ����£���ʾ�¶�
   if(KeyAct & K2_HEA){
     HeatGears++;
     if(HeatGears > 11)
     HeatGears = 1;
     //
     if(HeatGears < 11  && !HeatTest)
     Heat3min();
     else{
	   TsetHeat();
	   HeatTest = 1;
     }
   }
   if(!SetTemp){
     TempFlash  = 1;
     SetTemp    = 1;
   }
   TempFlashTimerCon=0;
   KeyAct = K2_HEA;
}
/************************************************************
*
*
************************************************************/
void HeatKey(bit PcbIr)
{
  DispDataSet = &HeatDisp;//�¶ȼ����£���ʾ�¶�

  if(ErrCon){
	SetTemp = 1;TempFlash = 1;
	KeyAct = K2_HEA;//������ȣ���ʾ
    return;
  }
  //------------------------------
  if(HeatLock)//����������
  {
    LookFlhWood(1);//��˸
	KeyAct = K2_HEA;//������ȣ���ʾ
    return;
  }
  //CancelAllFlash(0);

  if(!PcbIr)
  SetTemp = 0;

  if(!SetTemp)
  {
    if(!HeatGears)
	HeatGears = 10;
	//
	HeatTest = 0;
    if(HeaOnOff)
	{
      if(KeyAct & K2_HEA)
	  {
		HeaOnOff   = 0;
		KeyAct     = 0;
		return;
	  }
	}
	else
	{
	  HeaOnOff   = 1;
	  Heat3min();
	}
  }else
  {
	HeatGears++;
	if(HeatGears > 11)
	HeatGears = 1;
	//
	if(HeatGears < 11  && !HeatTest)
	Heat3min();
	else
	{
	  TsetHeat();
	  HeatTest = 1;
	}
	TempFlashTimerCon=0;
  }
  KeyAct = K2_HEA;
}

/************************************************************
* ������: UpKey()
* ����˵��:  ��������
************************************************************/
void HeatSetAndLook( void )
{
  HeatLockTimer++;
  if(HeaOnOff && !HeatLock && (HeatLockTimer == 1))
  {
    SetTemp    = 1;//�¶����ñ�־��1
	TempFlash  = 1;
	KeyAct = K2_HEA;//������ȣ����
  }
  else
  {
  	if(HeatLockTimer > 1)
	{
	  HeatLockTimer = 0;
	  SetTemp       = 0;
	  HeatLock      = ~HeatLock;
	  HeatTest = 0;
      if(!HeatLock)
      {
	    if(KeyAct & K2_HEA)
	    {
		  HeatGears = 10;
		  HeaOnOff  = 1;
		  Heat3min();
	    }
      }else
	  {
	    HeatGears  = 0;
	    HeaOnOff   = 0;
	  }
      DispDataSet = &HeatDisp;
      LookFlhWood(1);
	}
  }
//  KeyAct = K2_HEA;
}
/***********************************************************
*
*				�¶�ת��
***********************************************************/
void TempSw(void)
{
	if(!HeatLock && HeaOnOff)
	{
   	  KeyAct = K2_HEA;
	  TempSwFahSet();
	  DispDataSet = &HeatDisp;
	}
}