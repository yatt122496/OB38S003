/***********************************************************
*  �ļ�˵����
************************************************************
*  ����:
*
*  ����:
*
************************************************************
*  Ӳ����sh79f083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE\main\SysInc.h"

U8 FlaTimer;
U8 FlaTimerOn;
U8 FlameTimOff;
U8 FalTimer1ms;

U8 code  FlameLumConst[]=
{
  0,  //��
  2,  //΢΢��
  4,  //΢��
  6,  //����
  8,  //����
  10,  //����
  0
};
/************************************************************
* ������:
* ����˵��:
************************************************************/
void FlaCon( void )  //1ms
{
  if(!Standby)
  {
    MOT  = 0;
	FOT  = 0;
	DOT1 = 0;
	DOT2 = 0;
  }else
  {
    FlaTimer++;
    if(FlaTimer>10)
	{
	   FlaTimer=0;
	  //-------------------
	  if(FlaGears > FLA_MAX)
	  FlaGears    = FLA_MAX;
	  //-------------------
	   if(AdNtcErr)
	   {
	     FOT = 1;
		 MOT  = 0;
		 DOT1 = 1;
		 DOT2 = 1;
	     FlaTimerOn  = 10;
		 FlameTimOff = FlaTimerOn;
	   }else
       {
		  if(FlaGears)
		  {
			 FOT = 1;
			 MOT  = 1;
			 DOT1 = 1;
			 DOT2 = 1;
			 FlaTimerOn  = FlameLumConst[FlaGears];
			 FlameTimOff = FlaTimerOn;
		  }else
		  {
			 FOT = 0;
			 MOT  = 0;
			 if((HeatOnOff)&&(!HeatLock))
			 {
			   FlameTimOff = 1;
			   FlaTimerOn  = FlameTimOff;
			   DOT1        = 1;
			   DOT2        = 1;
			 }else{
			   DOT1 = 0;
			   DOT2 = 0;
			 }
		  }
	  }
	}
	//----------------------------------------
	if(FlaTimerOn!=10)
    {
	  if(FlameTimOff != 0)
	  FlameTimOff--;
	  else
	  {
		FOT  = 0;
		DOT1 = 0;
		DOT2 = 0;
	  }
    }
	//----------------------------------------
	if(LockWoodFah)//--100MS��˸�ͻ�
	{
	   FOT   = 1;
	   DOT1  = 1;
	   DOT2  = 1;
	}else if(LockWoodCon || GoErrCon)
	{
	   FOT   = 0;
	   DOT1  = 0;
	   DOT2  = 0;
	}
	/**********************************/
  }
}
