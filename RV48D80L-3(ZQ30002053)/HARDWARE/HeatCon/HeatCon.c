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
#define   TEMP_ADJUST               3	/* �¶Ȳ�����  4��  4*1.8=7.2    (7) �H */
#define   TEMP_CONTROL_NEGATIVE     1 	/* ���� �ָ�   1��  1*1.8=1.8    (2) �H */
#define   TEMP_CONTROL_POSITIVE     1 	/* ���� ���� 0.5��  0.5*1.8=0.9  (1) �H */
/************************************************************
* ����Ϊ���ȴ�����
*                    			   ���¶�Ҫ�Է���Ϊ��λ
***********************************************************/
#define   MAX_WAIT_TIME    101		                    /* ���ȴ�ʱ��				       */
#define   LOW_WAIT_TIME	   3					        /* ��͵ȴ�ʱ��				       */
#define   LOW_HEA_TIME     1                            /* ��ͼ���ʱ��                    */
/*   �ȴ�����ȹ����˶���ʱ��                          */
#define   HEA_WAIT_TIME    4                            /* ���ȵȴ�ʱ��  */
/*	 ���������Ǹ�����͵ȴ�ʱ������������ȼ���3���ӣ������͵ȴ�ʱ�俪ʼ����  */
#define   STA_WAIT_TIME	   LOW_WAIT_TIME            	/* ��ʼ�ȴ�                        */
#define   STA_HEA_TIME	   LOW_WAIT_TIME-LOW_HEA_TIME	/* ��ʼ����ʱ��                    */

bit   HotOnOff;
bit   MotDelayOff;
bit   HotDelayeOn;
bit   FanOnOff;

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
   HotDelayeOn     = 1;
  //----------------------
   HotOnOff        = 1;
   AutoAddTime     = 0;//STA_WAIT_TIME;		//3
   HeaterOffTime   = STA_HEA_TIME;		//0
   HeaterMinute    = 0;
  //----------------------
   FanOnOff = 0;
}
/************************************************************
* ������:
* ����˵��:
************************************************************/
void TsetHeat(void)
{
   HotOnOff       = 0;
   HeaterOffTime  = 0;
   HeaterMinute   = 0;
   //-----------------------
   AutoAddTime    = LOW_WAIT_TIME;
}
/************************************************************
* ������:
* ����˵��:
************************************************************/
void HeatCon( void )
{
   unsigned char  SetTcBuff;
   unsigned char  DataBuff;
   float          TfBuff;
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
   if(!Standby  || !HeaOnOff || ShowCon || ErrCon)//������»�����ؼ���
   {
	 HOT      = 0;
     FanOnOff = 0;
	 HotOnOff = 0;
	 //------------------------------------------
	 HotDelayeOn = 0;//���ȹأ������ӳٿ���־����
	 //------------------------------------------
	 if(!MotDelayOff)
	 FAN      = 0;
   //-------------------------
     return;
   }
   SetTcBuff = SetTcTable[HeatGears];
   if(SetTcBuff  >= 60)
   SetTcBuff     = 60;
   else
   SetTcBuff = SetTcBuff + TEMP_ADJUST;//+5;//�����¶ȼ�3������¯���¶ȱ������¶ȸ�3��
   //-----------------------------------
   TfBuff = TempValue + TEMP_CONTROL_NEGATIVE;
   if(SetTcBuff >= TfBuff)//�������趨�¶ȵġ�1��,�趨�¶ȼ�1���������ڡ�1����
   {
     if(HotOnOff == 0)//�����趨�¶ȵġ�1��,����
     {
	   FanOnOff = 0;
	  //----------------------
       HotDelayeOn = 1;
      //----------------------
       HotOnOff    = 1;
       AutoAddTime = 0;
     }
     HeaterOffTime = 0;     //������Ӽ��������¿�ʼ�ȴ�
     HeaterMinute  = 0;      //����ǰ������9�ֵȴ�3�ּ���9+3=12�����ڼ��¶��½�����1������
   }                      //�ܵ�������ִ�о�Ҫ12-3=9��Ϊ6�ֵȴ�3�ּ��ȣ����������������
   else                   //����������¶Ȼ�û�лָ�������3ֱ���¶Ȼָ�
   {
      TfBuff = TempValue - TEMP_CONTROL_POSITIVE;
      if(SetTcBuff > TfBuff)
      {//��������˵�����ǵĿ��ƺܺ�,�¶��Ծ��ﵽ����(��1����)
        if(HotOnOff == 1)
        {
          goto GoOutCon;
        }
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
          DataBuff = HeaterOffTime + LOW_HEA_TIME;//
          if(DataBuff > AutoAddTime)
          {
			FanOnOff  = 1;
            HotOnOff  = 0;
            if(HeaterOffTime > AutoAddTime)//ִ�е�����˵���¶�һֱ��û������
            {								 //3 >= 6  != !> ->>>>-> 6 = 6 6+3=9  6���ӵȴ�3���Ӽ���
              DataBuff = AutoAddTime + LOW_WAIT_TIME;//���ǵ���ʱ����3���ӵȴ���3���Ӽ��ȣ�6���ӵȴ�3���Ӽ����Դ����ơ�����������
              if(DataBuff >= MAX_WAIT_TIME)
              DataBuff     = MAX_WAIT_TIME;  //ֱ��103���Ӳ��ټ�3
              AutoAddTime  = DataBuff;
	          FanOnOff     = 0;          //����Ҫ�ص�
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
	 if(!FanOnOff){
	   if(!MotDelayOff)
	    FAN  = 0;
     }else
	  FAN  = 1;
	 //------------------------------------------
	 HotDelayeOn = 0;//���ȹأ������ӳٿ���־����
	 //------------------------------------------
   }
}