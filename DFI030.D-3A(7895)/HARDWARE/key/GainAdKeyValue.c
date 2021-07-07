/***********************************************************
*
************************************************************
*  ����:
*
*  ����:
*
************************************************************
*  Ӳ����
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE\main\SysInc.h"

bit KeyNew;

#if (IO_AD_KEY_OTP == 0)
/************************************************************
* ������:
* ����˵��:
************************************************************/
U8 PcbKeyValue;
U8 UpPcbKeyValue;
U8 UpKeyBuff;
/************************************************************
* ������:
* ����˵��:
************************************************************/
void GainAdKeyValue(void)
{
  U8 KeyDat;
  KeyDat = 0;
  if(!KEY1)KeyDat |= 1;	 //POW
  if(!KEY2)KeyDat |= 2;	 //FLA
  if(!KEY3)KeyDat |= 4;	 //PLA
  if(KeyDat){
	if(KeyNew){
	  KeyNew = 0;
	  if(UpKeyBuff != KeyDat)
      UpKeyBuff = KeyDat;
	  else{
	    if(!UpPcbKeyValue || UpPcbKeyValue == KeyDat){
		  if(KeyDat == 1)
		  PcbKeyValue = 3;
		  else
		  if(KeyDat == 2)
		  PcbKeyValue = 2;
		  else
		  if(KeyDat == 4)
		  PcbKeyValue = 1;
		  else{
		    PcbKeyValue   = 0xff;
		    UpPcbKeyValue = 0xff;
		  }
		}else{
		  UpPcbKeyValue = 0xff;
		  PcbKeyValue   = 0xff;
		}
	  }
    }
  }else{
	PcbKeyValue  = 0;
	UpPcbKeyValue= 0;
	//---------------
	UpKeyBuff    = 0;
  }
}

#endif
/************************************************************
* ������:
* ����˵��:
************************************************************/
#if (IO_AD_KEY_OTP == 1)
//--------------------------
U8  PcbKeyValue;
U8  UpPcbKeyValue;
//--------------------------
bit AdKeyLock;
U8  UpDatabuff;
//U8  KeyValueBuf;
//--------------------------
#if  (D030_040_KEY == 0)  // 030
  #define  KEY_SIZE    4
  #define  AD_KEY_MAX  52
  //						             void  HEA FLA  POW
  U8 code AdKeyConst[KEY_SIZE]   ={AD_KEY_MAX, 33, 12,  0};
  U8 code KeyValueTable[KEY_SIZE]={      0xff,  3,  2,  1};
#else                     // 040
  #define  KEY_SIZE    5
  #define  AD_KEY_MAX  72
  //						             void  HEA FLA SPK POW
  U8 code AdKeyConst[KEY_SIZE]   ={AD_KEY_MAX, 52, 33, 12,  0};
  U8 code KeyValueTable[KEY_SIZE]={      0xff,  3,  2,  5,  1};
#endif
/************************************************************
* ������:
* ����˵��:
************************************************************/
void GainAdKeyValue(void)
{
   U8 Databuff;
   U8 KeyValueSize;
   if(AdKeyNew)
   {
	   AdKeyNew = 0;		           //���µİ���ֵ
	   Databuff = AdKeyValue;		   //�°���ֵ
     if(Databuff >= AD_KEY_MAX)   //�������240˵��û�м�����
     {
       AdKeyLock        = 0;	   //û�м�����
	   UpPcbKeyValue    = 0;
	   PcbKeyValue      = 0;
       return;
     }
     if(!AdKeyLock)
     {
       for(KeyValueSize = 0; KeyValueSize < KEY_SIZE; KeyValueSize++)
       {						   //
         if(Databuff >= AdKeyConst[KeyValueSize])
         {              		   //�ɹ���ü�ֵ
            Databuff    =  KeyValueTable[KeyValueSize];
			if(UpDatabuff != Databuff)
			UpDatabuff = Databuff;		//���αȽ�ȥ����������
			else
			{
			  PcbKeyValue = UpDatabuff; //�˼�ȷ��������
	          if(UpPcbKeyValue && (UpPcbKeyValue != PcbKeyValue))
			  {//�Ƚ������ǲ���ͬ�����£����ǣ�ȥ��ȴ��������ɿ����ٴ���Ӧ
                AdKeyLock   =  1;          //�˴���Ӧ������
			    PcbKeyValue =  0xff;		  //���߰����������,ȥ����
			  }
			  else
			  UpPcbKeyValue = PcbKeyValue; //�����������쳣
			}
			break;
         }
       }
	 }
   }
}
#endif