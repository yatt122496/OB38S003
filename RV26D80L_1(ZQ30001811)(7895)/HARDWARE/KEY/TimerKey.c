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

bit     AllOffTimerCon;
bit     TimerCon;
uint8   Hou = 0;
uint8   Min = 0;
uint8   MsTimer;
uint8   clk[3]; //ʱ�仺��  �� clk[2]Сʱ��clk[1]���ӣ�clk[0]�룬
uint8   TimerGears;
/************************************************************
* ������:
* ����˵��:��ʱ��ʾ
************************************************************/
void TimDisp( void )
{
  if(TimerGears)
  {
	if(TimerGears==1)
	{
	  DispDct1 = 3;
  	  DispDct2 = 0;
	}else
	{
	  DispDct1 = TimerGears-1;
	  DispDct2 = H;
	}
	DispLed = 0x20;
  }
}
/************************************************************
* ������:
* ����˵��:��ʱ��ʾ
************************************************************/
void TimKey( void )
{
  CancelAllFlash(0);
  DispDataSet = &TimDisp;
  if(AllOffTimerCon)
  return;
  if((KeyAct & K2_TIM) || !TimerGears)
  {
    TimerCon = 0;
	TimerGears++;
	if(TimerGears > 7)
	{
	  TimerGears = 0;
	  clk[0]       = 0; 	 //clr timer
	  clk[1]       = 0;
	  clk[2]       = 0;
	  KeyAct       = 0;
	  return;
	}
	if(TimerGears==1)
	{
	  clk[1] = 30;
	  clk[2] = 0;
	}else
	{
	  clk[2] = TimerGears - 1;
	  clk[1] = 0;
	}
	clk[0]       = 0;
	MsTimer      = 0;
	TimerCon     = 1;
  }
  KeyAct = K2_TIM;
}
/************************************************************
* ������:
* ����˵��:�����ж�
************************************************************/
//void Timer1Isr( void ) interrupt TIMER1
//{
//  unsigned char count;
//  TF1 = 0;
//  if(TimerCon)
//  {
//    MsTimer++;
//    if(MsTimer > 127)
//    {
//      MsTimer = 0;
//	  count   = 0;//����"0"�Ǵ��뿪ʼ���
//      while(!clk[count])
//      {
//        count++;   //��"1" ָ���,�ټ�ָ��ʱ
//	    if(count==3)//����"3"��ʱΪ"0".
//        {
//	      Standby        = 0;//��ʱ��,����
//		  TimerCon       = 0;
//	      TimerGears     = 0;
//	      return;
//	    }
//      }
//      clk[count]-=1;//��,��,ʱ��Ϊ"0"��"1"
//      switch(count)
//      {             //count����"0",�벻Ϊ"0".
//	    case 2: clk[1]=59;//����"2"��ʾʱ��Ϊ"0",��"��"."��"��ֵ"59"
//	    case 1: clk[0]=59;break;//����"1"��ʾ�ֲ�Ϊ"0",����"��ֵ"59"
//	    default:break;
//      }
//    }
//  }
//}
void TimerFun( void )
{
  unsigned char count;
//  TF1 = 0;
  if(TimerCon)
  {
    MsTimer++;
    if(MsTimer > 99)
    {
      MsTimer = 0;
	  count   = 0;//����"0"�Ǵ��뿪ʼ���
      while(!clk[count])
      {
        count++;   //��"1" ָ���,�ټ�ָ��ʱ
	    if(count==3)//����"3"��ʱΪ"0".
        {
	      Standby        = 0;//��ʱ��,����
		  TimerCon       = 0;
	      TimerGears     = 0;
	      return;
	    }
      }
      clk[count]-=1;//��,��,ʱ��Ϊ"0"��"1"
      switch(count)
      {             //count����"0",�벻Ϊ"0".
	    case 2: clk[1]=59;//����"2"��ʾʱ��Ϊ"0",��"��"."��"��ֵ"59"
	    case 1: clk[0]=59;break;//����"1"��ʾ�ֲ�Ϊ"0",����"��ֵ"59"
	    default:break;
      }
    }
  }
}
void TimerOff(void)
{
  if(!HeaOnOff && !FlaGears && !DowGears)
  {
    if(!AllOffTimerCon || TimerCon)
	{
      TimerCon = 0;
	  clk[0]   = 0; 	    //clr timer
	  clk[1]   = 0;
	  clk[2]   = 0;
	  TimerGears = 0;
	}
	AllOffTimerCon = 1;
  }else
  AllOffTimerCon   = 0;
}