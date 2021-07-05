/***********************************************************
*
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
#include "HARDWARE/main/SysInc.h"

/************************************************************
* �¶Ȳ�����  ¯���¶ȱ������¶ȸߣ��������¶Ȳ���
* ������������Ϊ�¶ȿ��Ʒ�Ϊ���������ٶ�
***********************************************************/
#define   TEMP_ADJUST               1.5	/* �¶Ȳ�����  4��  4*1.8=7.2    (7) �H */
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
#define   HEA_WAIT_TIME    6   /* ���ȵȴ�ʱ��  */
/*	 ���������Ǹ�����͵ȴ�ʱ������������ȼ���3���ӣ������͵ȴ�ʱ�俪ʼ����  */
#define   STA_WAIT_TIME	   LOW_WAIT_TIME            	/* ��ʼ�ȴ�                        */
#define   STA_HEA_TIME	   LOW_WAIT_TIME-LOW_HEA_TIME	/* ��ʼ����ʱ��                    */

bit   HotOnOff;
bit   MotDelayOff;
bit   HotDelayeOn;
bit   TempFallSubWait;

uint8 HeaterMinute;
uint8 HeaterOffTime;
uint8 AutoAddTime=HEA_WAIT_TIME;
/************************************************************
* ������:
* ����˵��:
************************************************************/
void Heat3min(void)
{
  //----------------------
   HotDelayeOn       = 1;
  //----------------------
   HotOnOff           = 1;
   TempFallSubWait    = 1;
   AutoAddTime        = STA_WAIT_TIME;		//3
   HeaterOffTime      = STA_HEA_TIME;		//0
   HeaterMinute       = 0;
}
/************************************************************
* ������:
* ����˵��:
************************************************************/
void TsetHeat(void)
{
   HotOnOff       = 0;
   TempFallSubWait= 0;
   HeaterOffTime  = 0;
   HeaterMinute   = 0;
   //-----------------------
   AutoAddTime    = HEA_WAIT_TIME;	//6
}
/************************************************************
* ������:
* ����˵��:
************************************************************/
void HeatCon( void )
{
   unsigned char  DataBuff;
   float  TfBuff;
   float  SetTcBuff;
   DigitalFiltering();
   //---------------------------
   if(GoErrCon&&Standby)
   {
   //HOT         = 0;
	 FAN         = 0;
	 MotDelayOff = 0;
	 HotDelayeOn = 0;
     return;
   }
   if(!Standby || !HeaOnOff || ErrCon)//������»�����ؼ���
   {
	 HOT      = 0;
	 HotOnOff = 0;
	 //------------------------------------------
	 HotDelayeOn = 0;//���ȹأ������ӳٿ���־����
	 //------------------------------------------
	 if(!MotDelayOff)
	 FAN      = 0;
   //-------------------------
     return;
   }
   SetTcBuff = (float)SetTcTable[HeatGears];
   if(SetTcBuff  >= 60)
   SetTcBuff     = 60;
   else
   if(SetTcBuff <= 20)
   SetTcBuff = SetTcBuff + TEMP_ADJUST;////+5;//�����¶ȼ�3������¯���¶ȱ������¶ȸ�3��
   //-----------------------------------
   TfBuff = TempValue + TEMP_CONTROL_NEGATIVE;
   if(SetTcBuff >= TfBuff)//�������趨�¶ȵġ�1��,�趨�¶ȼ�1���������ڡ�1����
   {
     if(HotOnOff == 0)//�����趨�¶ȵġ�1��,����
     {
	  //----------------------
       HotDelayeOn       = 1;
      //----------------------
       HotOnOff    = 1;
       AutoAddTime = HEA_WAIT_TIME;//6 ����3���Ӽ���3���ӵȴ���ʼ
     }
     if(TempFallSubWait == 1)//ִ�е���������Ϊ�¶ȵ������еı߾�,
     {                 //�����ڵȴ��������¶Ƚ��ͣ��Եݼ�3���ָ��¶�
       TempFallSubWait = 0;
       DataBuff = HeaterOffTime + LOW_HEA_TIME;	 //3
       if(DataBuff > AutoAddTime)
       {
         DataBuff = AutoAddTime - LOW_HEA_TIME;
         if(DataBuff <= HEA_WAIT_TIME)
         DataBuff     = HEA_WAIT_TIME;	//6
         AutoAddTime  = DataBuff;
       }
     }      //�ȴ���ʱʧЧ
     HeaterOffTime = 0;     //������Ӽ��������¿�ʼ�ȴ�
     HeaterMinute  = 0;      //����ǰ������9�ֵȴ�3�ּ���9+3=12�����ڼ��¶��½�����1������
   }                      //�ܵ�������ִ�о�Ҫ12-3=9��Ϊ6�ֵȴ�3�ּ��ȣ����������������
   else                   //����������¶Ȼ�û�лָ�������3ֱ���¶Ȼָ�
   {
      TfBuff = TempValue - TEMP_CONTROL_POSITIVE;
      if(SetTcBuff <= TfBuff)
      {    //�趨�¶ȵ���������
        if(HotOnOff == 1)//����������Ӧ�ùرռ���
        {
          if(TempFallSubWait == 0)
		  {
            HotOnOff            = 0;
		    //------------------------------
		    if(AutoAddTime <= STA_WAIT_TIME)		//3
		    AutoAddTime     = HEA_WAIT_TIME;		//6
		    //------------------------------
		  }
        }
      }
      else
      {//��������˵�����ǵĿ��ƺܺ�,�¶��Ծ��ﵽ����(��1����)
        if(HotOnOff == 1)
        {
          if(TempFallSubWait == 0)//��ʱ��������ǿ���,��ô��������������
          goto GoOutCon;
        }
        else
        AutoAddTime = 12;//HEA_WAIT_TIME;//15���¶ȵ��ڡ�1����ʱ,����12���ӵĵȴ�
      }
	  //-----------------
      if(HeaterSec)//���һ�뵽�����ǵļ�����ؼ��ȵȴ���ʱ����ʼ������
      {
        HeaterSec = 0;
        HeaterMinute++;
        if(HeaterMinute > 59)
        {
          HeaterMinute = 0;
          HeaterOffTime++;        //6,3, 3+3=6  6==6 ON HEAT
          DataBuff = HeaterOffTime + LOW_HEA_TIME;
          if(DataBuff >= AutoAddTime)
          {
            TempFallSubWait = 1;
		   //----------------------
            HotDelayeOn       = 1;
           //----------------------
            HotOnOff        = 1;
            if(HeaterOffTime >= AutoAddTime)//ִ�е�����˵���¶�һֱ��û������
            {								 //3 >= 6  != !> ->>>>-> 6 = 6 6+3=9  6���ӵȴ�3���Ӽ���
              DataBuff = AutoAddTime + LOW_HEA_TIME;//���ǵ���ʱ����3���ӵȴ���3���Ӽ��ȣ�6���ӵȴ�3���Ӽ����Դ����ơ�����������
              if(DataBuff >= MAX_WAIT_TIME)
              DataBuff     = MAX_WAIT_TIME;           //ֱ��103���Ӳ��ټ�3
              AutoAddTime     = DataBuff;
	          HotOnOff        = 0;           //����Ҫ�ص�
	          TempFallSubWait = 0;       //�¶��½�����Ҳ��Ҫ�ص�
	          HeaterOffTime   = 0;      //�����
	          HeaterMinute    = 0;
            }
          }
		}
	  }
   }
   GoOutCon:
   if(HotOnOff)
   {
  //-------------------------------
	 if(!HotDelayeOn)
	  HOT  = 1;
  //-------------------------------
	 FAN  = 1;
	 MotDelayOff=1;
   }else
   {
	 HOT  = 0;
	 if(!MotDelayOff)
	 FAN  = 0;
	 //------------------------------------------
	 HotDelayeOn = 0;//���ȹأ������ӳٿ���־����
	 //------------------------------------------
   }
}