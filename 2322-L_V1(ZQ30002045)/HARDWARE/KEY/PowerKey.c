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
unsigned char KeyAct;
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
	 if(!FlaGears)//����Ϊ0 ����λ�������
	 FlaGears = 4;
	 if(HeaOnOff)//��ʾ�¶ȱ�־λ1��������ʾ�¶�
	 {
	   DispDataSet = &HeatDisp;
	   if(ErrCon){
		SetTemp    = 1;
	    TempFlash = 1;
	   }
	   KeyAct = K2_HEA;
	   Heat3min();
	 }
	 else//�¶���ʾ��־λ0 ������ʾ���浵λ
	 {
	   DispDataSet = &FlaDisp;
	   KeyAct = K2_FLA;
	 }
   }else//�������״̬
   {
     TimerCon   = 0;//��ʱ����
	 clk[0]     = 0;
	 clk[1]     = 0;
	 clk[2]     = 0;
	 TimerGears = 0;
	 Standby    = 0;
	 KeyAct     = 0;
  #if (KEY_BG_EN==1)
	 DispDataSet = &ClrDisp;
	 Hidden     = 0;
	 BiGuangCon = 0;
  #endif
   }
}

