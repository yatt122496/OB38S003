/***********************************************************
*
************************************************************
*  ����:2015-1-8 08:18
*
*  ����:
*
************************************************************
*  Ӳ����
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE\include\SysInc.h"

/************************************************************
* �¶Ȳ�����  ¯���¶ȱ������¶ȸߣ��������¶Ȳ���
* ������������Ϊ�¶ȿ��Ʒ�Ϊ���������ٶ�
***********************************************************/
#define   TEMP_ADJUST               0	/* �¶Ȳ�����  1��  1*1.8=1.8    (2) �H */
#define   TEMP_CONTROL_NEGATIVE     1 	/* ���� �ָ�   1��  1*1.8=1.8    (2) �H */
#define   TEMP_CONTROL_POSITIVE     1 	/* ���� ���� 0.5��  0.5*1.8=0.9  (1) �H */
/************************************************************
* ����Ϊ���ȴ�����
*                    			   ���¶�Ҫ�Է���Ϊ��λ
***********************************************************/
#define   MAX_WAIT_TIME    103		                    /* ���ȴ�ʱ��				       */
#define   LOW_WAIT_TIME	   3					        /* ��͵ȴ�ʱ��				       */
#define   LOW_HEA_TIME     3                            /* ��ͼ���ʱ��                    */
/*     �ȴ�����ȹ����˶���ʱ��                         */
#define   HEA_WAIT_TIME    LOW_WAIT_TIME + LOW_HEA_TIME /* ����ʱ��+�ȴ�ʱ��=���ȵȴ�ʱ��  */
#define   WAIT_TIME        15 							/* ��ʱʱ��						   */
/*	 ���������Ǹ�����͵ȴ�ʱ������������ȼ���3���ӣ������͵ȴ�ʱ�俪ʼ����  */
#define   STA_WAIT_TIME	   LOW_WAIT_TIME            	/* ��ʼ�ȴ�                        */
#define   STA_HEA_TIME	   LOW_WAIT_TIME-LOW_HEA_TIME	/* ��ʼ����ʱ��                    */


bit HotOnOff;
bit MotDelayOff;
bit TempFallSubWait;
unsigned char AutoAddTime=HEA_WAIT_TIME;
unsigned char HeaterOffTime;
unsigned char HeaterMinute;
/************************************************************
* ������:
* ����˵��:
************************************************************/
void Hot3min(void)
{
   HotOnOff=1;
   TempFallSubWait=1;
   AutoAddTime=STA_WAIT_TIME;
   HeaterOffTime=STA_HEA_TIME;
   HeaterMinute=0;
}
/************************************************************
* ������:
* ����˵��:
************************************************************/
void HeatInit(void)
{
//   P4M0  &=~Bin(00000110);
//   P4M1  |= Bin(00000110);
	P33CFG = GPIO_MUX_GPIO;
	P32CFG = GPIO_MUX_GPIO;

	// P0TRIS = (P0TRIS & ~((0))) | ((0));
	// P1TRIS = (P1TRIS & ~((0))) | ((0));
	// P2TRIS = (P2TRIS & ~((0))) | ((1 << 3));
	P3TRIS = (P3TRIS & ~((0))) | ((1 << 2) | (1 << 3));
}
/************************************************************
* ������:
* ����˵��:
************************************************************/
void HeatCon( void )
{
   unsigned char  SetTfBuff;
   unsigned char  TfBuff;
   float   TempValueBuff;
   if(!Standby || !HeatOnOff || !AdReady || HeatLock)//�����ؼ���
   {
	 HOT     = 0;
	 HotOnOff= 0;
     if(!MotDelayOff)
	 FAN = 0;
     return;
   }
   if(ErrCon)
   {
     HotOnOff = 1;
	 goto GoOutCon;
   }
   //-----------------------------------
   if(VrValue < 10)
   SetTfBuff   = 10;
   else
   if(VrValue > 65)
   SetTfBuff  = 65;
   else
   SetTfBuff   = VrValue;
   //-----------------------------------
   SetTfBuff  += TEMP_ADJUST;//+5;//�����¶ȼ�3
   //-----------------------------------
   TempValueBuff = TempValue + TEMP_CONTROL_NEGATIVE; /* ���� */
   //-----------------------------------
   if(SetTfBuff >= TempValueBuff)
   {
     if(HotOnOff==0)
     {
       HotOnOff=1;
       AutoAddTime=HEA_WAIT_TIME;
     }
     if(TempFallSubWait==1)
     {
       TempFallSubWait=0;
       TfBuff=HeaterOffTime+LOW_HEA_TIME;
       if(TfBuff>=AutoAddTime)
       {
         TfBuff=AutoAddTime-LOW_HEA_TIME;
         if(TfBuff<=HEA_WAIT_TIME)
         TfBuff=HEA_WAIT_TIME;
         AutoAddTime=TfBuff;
       }
     }
     HeaterOffTime=0;
     HeaterMinute=0;
   }
   else
   {
      //-----------------------------------
	  TempValueBuff = TempValue - TEMP_CONTROL_POSITIVE; /* ���� */
	  //-----------------------------------
      if(SetTfBuff <= TempValueBuff)
      {
        if(HotOnOff==1)
        {
          if(TempFallSubWait==0)
		  {
            HotOnOff        = 0;
			if(AutoAddTime <= LOW_WAIT_TIME)
			AutoAddTime     = HEA_WAIT_TIME;
		  }
        }
      }
      else
      {
        if(HotOnOff==1)
        {
          if(TempFallSubWait==0)
          goto GoOutCon;
        }
        else
        AutoAddTime = WAIT_TIME;//15min
      }
	  //------------------
	  if(!HotOnOff && MotDelayOff)
	  {
		HeaterMinute  = 0;
		HeaterOffTime = 0;				   //�����ʱ1.5���Ӽ��뱣���ȴ�15������
	  }else
      if(HeaterSec==1)//���һ�뵽�����ǵļ�����ؼ��ȵȴ���ʱ����ʼ������
      {
        HeaterSec=0;
		//------------------
        HeaterMinute++;
        if(HeaterMinute>59)
        {
          HeaterMinute=0;
		  //----------------
          HeaterOffTime++;
		}
	  }
      TfBuff=HeaterOffTime+LOW_HEA_TIME;
      if(TfBuff>=AutoAddTime)
      {
        TempFallSubWait= 1;
        HotOnOff       = 1;
        if(HeaterOffTime>=AutoAddTime)
        {
          TfBuff=AutoAddTime+LOW_HEA_TIME;
          if(TfBuff>=MAX_WAIT_TIME)
          TfBuff=MAX_WAIT_TIME;
          AutoAddTime=TfBuff;
	      HotOnOff=0;
	      TempFallSubWait=0;
	      HeaterOffTime=0;
	      HeaterMinute=0;
        }
      }
   }
   GoOutCon:
   if(HotOnOff==1)
   {
	 HOT        = 1;
	 FAN        = 1;
	 MotDelayOff= 1;
   }
   else
   {
     HOT=0;
     if(MotDelayOff==0)
	 FAN=0;
   }
}