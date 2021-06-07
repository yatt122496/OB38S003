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
//u8  n;
bit AdKeyLock;
u8  UpDatabuff;
//-----------------------
//bit AdKeyNew;
//u8  AdKeyValue;
//--------------------------
#define  KEY_SIZE 7
//									 VOD  UP DOW TIM HEA FLA POW
unsigned char code AdKeyConst0[7]   ={113, 92, 72, 52, 33, 12,  0};
#if (TK6_G23K_OTP==0)
 unsigned char code KeyValueTable0[7]={ 0 , 7,  5,  4,  6,  2,  1};
#else
 unsigned char code KeyValueTable0[7]={ 0 , 4,  2,  1,  6,  7,  5};
#endif

unsigned char  code AdKeyConst1[]    ={190, 164, 148, 134, 120, 106, 94};
unsigned char  code KeyValueTable1[] ={0 ,   6,   4,   5,   7,   1,   2};
// unsigned char  code KeyValueTable1[] ={0 ,   3,   4,   5,   7,   1,   2};
/************************************************************
* ������:
* ����˵��:AD��ֵ����
************************************************************/
void GainAdKeyValue(void)
{
   unsigned char Databuff;
   unsigned char KeyValueSize;
   unsigned char KeySize,MaxAdKey,AdKeyConstValue;
   if(AdKeyNew)
   {
	 AdKeyNew = 0;		   //���µİ���ֵ
	 Databuff = AdKeyValue;//�°���ֵ
	 //-----------------------------------
	 if(TouchKeyOpt==0)
	 {
	   KeySize  = 7;
	   MaxAdKey = 113;
	 }else
	 {
	   KeySize  = 7;
	   MaxAdKey = 190;
	 }
	 //-----------------------------------
     if(Databuff >= MaxAdKey)   //�������240˵��û�м�����
     {
       AdKeyLock        = 0;//û�м�����
	   UpPcbKeyValue    = 0;
	   PcbKeyValue      = 0;
	   UpDatabuff       = 0;
     }else
     if(!AdKeyLock)
     {
       for(KeyValueSize = 0; KeyValueSize < KEY_SIZE; KeyValueSize++)
       {
	      if(TouchKeyOpt==0)
	      {
            AdKeyConstValue = AdKeyConst0[KeyValueSize];
	      }else
	      {
           AdKeyConstValue  = AdKeyConst1[KeyValueSize];
	      }
    	  //
		   //
          if(Databuff >= AdKeyConstValue)
          {              		   //�ɹ���ü�ֵ
             if(TouchKeyOpt==0)
             {
			   Databuff =  KeyValueTable0[KeyValueSize];
			 }else
             {
			   Databuff =  KeyValueTable1[KeyValueSize];
			 }
			 //
			 if(UpDatabuff != Databuff)
			 {
			   UpDatabuff = Databuff;		//���αȽ�ȥ����������
			 }
			 else
			 {
				//-----------------------------------------------
		        if(!UpPcbKeyValue || (UpDatabuff == UpPcbKeyValue))
		        {
		           UpPcbKeyValue = UpDatabuff; //�����������쳣
		           switch(UpDatabuff)
		           {
			         case 1:if(!Standby)BiGuangCon = 1;break;
//			         case 2:                       break;
//			         case 3:                       break;	//���Ǽ��ȼ��˳��±��л�������֮
//		             case 4:                       break;
//		             case 5:                       break;
			         default  :                    break;
		           }
				   //-------------
		           if(!BiGuangCon)
		           {
		             if(Standby)
			         {
			           AdKeyLock    = 1;//����û�е���������Ӧ�������˴���Ӧ������
					   BiGuangCon   = 1;
					   PcbKeyValue  = 0;
			         }
		           }else
				   { //�����������⣬��Ӧ����
					  PcbKeyValue = UpDatabuff; //�˼�ȷ��������
				   }
		        }else
				{ //�Ƚ������ǲ���ͬ�����£����ǣ�ȥ��ȴ��������ɿ����ٴ���Ӧ
                  AdKeyLock   =  1;   //�˴���Ӧ������
			      PcbKeyValue =  0xff;//���߰����������,ȥ����
				}//-------
			 }
			 break;	//��������������������ֵѭ��
          }
	   }
	 }
   }
}

///************************************************************
//* ������:
//* ����˵��:AD��ֵ����
//************************************************************/
//bit                  AdKeyLock;
//unsigned char        UpDatabuff;
//unsigned char        PcbKeyValue;
//unsigned char        UpPcbKeyValue;
////									 VOD TIM SDL DWL HEA FLA POW
//unsigned char code AdKeyConst[7]   ={92, 52, 33, 12,  0};
//unsigned char code KeyValueTable[7]={ 0,  4,  5,  2,  1};
///************************************************************
//* ������:
//* ����˵��:AD��ֵ����
//************************************************************/
//void GainAdKeyValue(void)
//{
//   unsigned char Databuff;
//   unsigned char KeyValueSize;
//   if(AdKeyNew)
//   {
//	 AdKeyNew = 0;		           //���µİ���ֵ
//	 Databuff = AdKeyValue;		   //�°���ֵ
//     if(Databuff >= 92)           //�������240˵��û�м�����
//     {
//       AdKeyLock        = 0;	   //û�м�����
//	   PcbKeyValue      = 0;
//	   UpPcbKeyValue    = 0;
//       return;
//     }
//     if(!AdKeyLock)
//     {
//	   if(UpDatabuff != Databuff)
//	   UpDatabuff     = Databuff;  //���αȽ�ȥ����������
//	   else
//	   { 						   //�˼�ȷ��������
//         for(KeyValueSize = 0; KeyValueSize <= 5; KeyValueSize++)
//         {						   //
//           if(Databuff >= AdKeyConst[KeyValueSize])
//           {              		   //�ɹ���ü�ֵ
//             PcbKeyValue      =  KeyValueTable[KeyValueSize];
//	         if(UpPcbKeyValue && (UpPcbKeyValue != PcbKeyValue))
//			 {//�Ƚ������ǲ���ͬ�����£����ǣ�ȥ��ȴ��������ɿ����ٴ���Ӧ
//               AdKeyLock   =  1;          //�˴���Ӧ������
//			   PcbKeyValue =  0xff;		  //���߰����������,ȥ����
//			 }
//			 else
//			 {
//		        switch(UpDatabuff)
//		        {
//			       case 1:BiGuangCon = 1;        break;
////			       case 2:                       break;
//			       case 3:TempSwFlashTimerCon= 0;break;	//���Ǽ��ȼ��˳��±��л�������֮
////		           case 4:                       break;
////		           case 5:                       break;
//			       default  :                    break;
//		        }
//			    //-------------
//		        if(!BiGuangCon)
//		        {
//		          if(Standby)
//			      {
//			        AdKeyLock    = 1;//����û�е���������Ӧ�������˴���Ӧ������
//					BiGuangCon   = 1;
//					PcbKeyValue  = 0;
//			      }
//		        }else
//				{ //�����������⣬��Ӧ����
//				  PcbKeyValue = UpDatabuff; //�˼�ȷ��������
//				}
//
//			    UpPcbKeyValue = PcbKeyValue; //�����������쳣
//			 }
//	         if(PcbKeyValue == 5)
//	         TempFlashTimerCon=0;
//             break;
//           }
//         }
//	   }
//	 }
//   }
//}