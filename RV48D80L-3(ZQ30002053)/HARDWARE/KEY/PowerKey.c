/***********************************************************
*  TM1638����
************************************************************
*  ����:2011.9.21 5:00
*
*  ����:  cuoiszf
*
************************************************************
*  Ӳ����MB95F204K
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE/main/SysInc.h"

bit           Standby;
unsigned int  KeyAct;
/************************************************************
* ������:
* ����˵��:
************************************************************/
void PowKey( void )
{
   CancelAllFlash(1);
   if(!Standby)//����״̬
   {
	 Standby     = 1;//���빤��״̬
	 HeatTest = 0;
	 if(!HeaOnOff && !FlaGears && !DowGears)
	 FlaGears = 1;
	 if(HeaOnOff && !HeatLock)//��ʾ�¶ȱ�־λ1��������ʾ�¶�
	 {
	   DispDataSet = &HeatDisp;
	   KeyAct = K2_HEA;
	   Heat3min();
	 }
	 else//�¶���ʾ��־λ0 ������ʾ���浵λ
	 if(FlaGears)
	 {
	   DispDataSet = &FlaDisp;
	   KeyAct = K2_FLA;
	 }else
	  if(DowGears){
	   DispDataSet = &DowDisp;
	   KeyAct = K2_DOW;
	  }
   }
   else//�������״̬
   {
     TimerCon   = 0;//��ʱ����
	 clk[0]     = 0;
	 clk[1]     = 0;
	 clk[2]     = 0;
	 Standby    = 0;
	 KeyAct     = 0;
   }
}

