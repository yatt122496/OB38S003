/***********************************************************
*  �ļ�˵����ҡ�س���
************************************************************
*  ����:2011.12.22 19:55
*
*  ����:  cuoiszf
*
************************************************************
*  Ӳ����sh79f083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE\main\SysInc.h"
//--------------------
bit     TimerCon;
uint8   MsTimer;
uint8   clk[3];
uint8   TimerGears;
//clk1[3];
//bit     TmrDisOtp;
//bit     SecFlh;


/************************************************************
* ������:
* ����˵��:
************************************************************/
void ClrTmr(void)
{
  TimerCon = 0;
  TimerGears=0;
  clk[0]   = 0;
  clk[1]   = 0;
  clk[2]   = 0;
  MsTimer  = 0;
}
/************************************************************
* ������:
* ����˵��:��ʱ��ʾ
************************************************************/
//void TimDisp( void )
//{
//  if((clk[0] || clk[1] || clk[2])){
//    if(TmrDisOtp){
//      if(clk[2]){
//        DispDct1 = clk[2];
//        DispDct2 = _h_;
//      }else{
//	    goto TmrDispMin;
//      }
//    }else{
//      if(!SecFlh){
//        LedSec = 1;
//      }
//      DispDct1 = clk[2];
//      TmrDispMin:
//      DispDct1 = clk[1]/10;
//	  DispDct2 = clk[1]%10; // 8:88
//    }
//  }else{
//    DispDct1= 0 ;   //"0FF"
//    DispDct2=_F_;
////    DispDct3=_F_;
//  }
//  LedTmr = 1;
//}
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
	  DispDct2 = _H_;
	}
  }else{
    DispDct1= 0 ;   //"0FF"
    DispDct2=_F_;
  }
  LedTmr = 1;
}
/************************************************************
* ������:
* ����˵��:��ʱ
************************************************************/
void TimKey( void )
{
  if(!Standby){
    Standby = 1;
    if(ErrCon)
    return;
    KeyAct  = 0;
  }
  CancelAllFlash(0);
  DispDataSet = &TimDisp;
  if((KeyAct & K2_TIM) || !TimerGears)
  {
    TimerCon = 0;
	TimerGears++;
	if(TimerGears > 10)
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
void TimerFun( void )  interrupt TMR1_VECTOR //10ms
{
	unsigned char count;
	TH1 = (d_MODEVALUE_T1 - d_RELOADVALUE_T1) >> 8;
	TL1 = (d_MODEVALUE_T1 - d_RELOADVALUE_T1);
	if (TimerCon)
	{
		if (++MsTimer > 99)
		{
			MsTimer = 0;
			count = 0; //����"0"�Ǵ��뿪ʼ���
			while (!clk[count])
			{
				count++;		//��"1" ָ���,�ټ�ָ��ʱ
				if (count == 3) //����"3"��ʱΪ"0".
				{
					Standby = 0; //��ʱ��,����
					TimerCon = 0;
					TimerGears = 0;
					return;
				}
			}
			clk[count] -= 1; //��,��,ʱ��Ϊ"0"��"1"
			switch (count)
			{ //count����"0",�벻Ϊ"0".
			case 2:
				clk[1] = 59; //����"2"��ʾʱ��Ϊ"0",��"��"."��"��ֵ"59"
			case 1:
				clk[0] = 59;
				break; //����"1"��ʾ�ֲ�Ϊ"0",����"��ֵ"59"
			default:
				break;
			}
		}
		//    if(MsTimer < 64)SecFlh = 0;
		//    else            SecFlh = 1;
	}
}
/************************************************************
* ������:
* ����˵��:
************************************************************/
void TimerOff(void)
{

}