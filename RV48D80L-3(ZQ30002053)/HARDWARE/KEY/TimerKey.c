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
//uint8   TimerGears;

bit T1s;
unsigned char  Tim1s;
/************************************************************
* ������:
* ����˵��:��ʱ��ʾ
************************************************************/
void TimDisp( void )
{
  if(clk[2]){		 //Сʱ������0��ʾСʱ
    DispDct1 = clk[2];//ʱ��ʾ,��ʾ������:"1","2","3"...."8".
	DispDct2 = H;
	DispLed = LED_TIM;
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
  if(!clk[2]){
   TimerCon = 0;
   clk[2] = 8;
   clk[1] = 59;
   clk[0] = 59;
   T1s      = 0;
   Tim1s    = 0;
   TimerCon = 1;
  }else
  if(KeyAct & K2_TIM){//0�����ü���,��������������
    TimerCon = 0;
	clk[0]   = 0; 	    //clr timer
	clk[1]   = 0;
	clk[2]   = 0;
  }
  KeyAct       = K2_TIM;
}

void TimerUp(void)
{
  if(AllOffTimerCon ||!TimerCon)//
  return;
  DispDataSet=&TimDisp;
  //
  TimerCon = 0;
  if(++clk[2] > 8)//max 8h
  clk[2]   = 1;
  clk[1]   = 59;
  clk[0]   = 59;
  T1s      = 0;
  Tim1s    = 0;
  TimerCon = 1;
  KeyAct   = K2_TIM;
}
/************************************************************
* ������:
* ����˵��:�����ж�
************************************************************/
void TimerFun( void )
{
  unsigned char count;
  if(Standby){
    if(TimerCon){
      if(T1s){T1s= 0;
        //
	    count   = 0;//����"0"�Ǵ��뿪ʼ���
        while(!clk[count])  {
          count++;   //��"1" ָ���,�ټ�ָ��ʱ
	      if(count==3)//����"3"��ʱΪ"0".
          break;
        }
        //
	    if(clk[2] > 8) clk[2] = 8;
        //
	    if(!clk[2]){
	      TimerCon    = 0;
	      clk[0]      = 0;
	      clk[1]      = 0;
		  Standby     = 0;//��ʱ��,����
	      return;
	    }
        //
        clk[count]-=1;//��,��,ʱ��Ϊ"0"��"1"
        switch(count){             //count����"0",�벻Ϊ"0".
	      case 2: clk[1]=59;//����"2"��ʾʱ��Ϊ"0",��"��"."��"��ֵ"59"
	      case 1: clk[0]=59;break;//����"1"��ʾ�ֲ�Ϊ"0",����"��ֵ"59"
	      default:break;
        }
        //
      }
    }
  }else{
    TimerCon    = 0;
    clk[0]      = 0;
    clk[1]      = 0;
    clk[2]      = 0;
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
	}
	AllOffTimerCon = 1;
  }else
  AllOffTimerCon   = 0;
}
