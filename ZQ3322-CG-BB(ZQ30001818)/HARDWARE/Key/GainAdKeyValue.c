/***********************************************************
*  TM1638����
************************************************************
*  ����:
*
*  ����:  cuoiszf
*
************************************************************
*  Ӳ����MCS51
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE/main/SysInc.h"
//--------------------------
u8  TouchKeyOpt;
u8  TouchKeyCnt0,TouchKeyCnt1;
u8  TouchKeyTim=30;
//--------------------------
u8  PcbKeyValue;
u8  UpPcbKeyValue;
//--------------------------
bit AdKeyLock;
u8  UpDatabuff;
//--------------------------
u8  CompoundKeyCnt;
//--------------------------
#define  KEY_SIZE     6
#define  MAX_AD_KEY   92
//									 VOD DOW TIM HEA FLA POW
unsigned char code AdKeyConst0[7]   ={92, 72, 52, 33, 12,  0};
unsigned char code KeyValueTable0[7]={0 ,  3,  1,  2,  0,  4};

unsigned char code AdKeyConst1[7]   ={190,164,148,134,120,106};
unsigned char code KeyValueTable1[7]={0 ,  4,  3,  2,  1,  0};
/************************************************************
* ������:
* ����˵��:AD��ֵ����
************************************************************/
void GainAdKeyValue(void)
{
  unsigned char Databuff;
  unsigned char KeyValueSize;
  unsigned char KeySize,MaxAdKey,AdKeyConstValue;
  if(AdKeyNew&&!TouchKeyTim){
	 AdKeyNew = 0;		          //���µİ���ֵ
	 Databuff = AdKeyValue;		  //�°���ֵ
	 //-----------------------------------
	 if(TouchKeyOpt==0)
	 {
	   KeySize  = 6;
	   MaxAdKey = 92;
	 }else
	 {
	   KeySize  = 6;
	   MaxAdKey = 190;
	 }
	 //-----------------------------------
     if(Databuff >= MaxAdKey){  //�������240˵��û�м�����
       AdKeyLock        = 0;	  //û�м�����
	   UpPcbKeyValue    = 0;
	   PcbKeyValue      = 0;
	   UpDatabuff       = 0;
       return;
     }
     if(!AdKeyLock){//�˼�ȷ��������
       for(KeyValueSize = 0; KeyValueSize < KeySize; KeyValueSize++){//
		  //
	      if(TouchKeyOpt==0)
	      {
            AdKeyConstValue = AdKeyConst0[KeyValueSize];
	      }else
	      {
           AdKeyConstValue  = AdKeyConst1[KeyValueSize];
	      }
		   //
         if(Databuff >= AdKeyConstValue){//�ɹ���ü�ֵ
           if(TouchKeyOpt==0)
           {
			 Databuff =  KeyValueTable0[KeyValueSize];
		   }else
           {
			 Databuff =  KeyValueTable1[KeyValueSize];
		   }
	       if(UpDatabuff != Databuff)
		   UpDatabuff = Databuff;		//���αȽ�ȥ����������
		   else{
             if(UpDatabuff==3 || UpDatabuff==4){
				if(++CompoundKeyCnt>3){
				  CompoundKeyCnt = 3;
				  PcbKeyValue = UpDatabuff; //�˼�ȷ��������
				  if(UpDatabuff==3)ClrErrTmr();
				}
			 }else{
			    CompoundKeyCnt = 0;
                PcbKeyValue = UpDatabuff; //�˼�ȷ��������
			 }
	          if(UpPcbKeyValue && (UpPcbKeyValue != PcbKeyValue)) {//�Ƚ������ǲ���ͬ�����£����ǣ�ȥ��ȴ��������ɿ����ٴ���Ӧ
                 AdKeyLock   =  1;          //�˴���Ӧ������
			     PcbKeyValue =  0xff;		  //���߰����������,ȥ����
			  }else{
			     UpPcbKeyValue = PcbKeyValue; //�����������쳣
			  }
		   }
		   break;
         }
	   }
	 }
  }
}
