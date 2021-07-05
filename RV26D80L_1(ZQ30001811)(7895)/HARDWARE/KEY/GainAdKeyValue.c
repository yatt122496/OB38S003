/***********************************************************
*  TM1638驱动
************************************************************
*  日期:
*
*  作者:  cuoiszf
*
************************************************************
*  硬件：MCS51
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
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
* 函数名:
* 功能说明:AD键值分离
************************************************************/
void GainAdKeyValue(void)
{
   unsigned char Databuff;
   unsigned char KeyValueSize;
   unsigned char KeySize,MaxAdKey,AdKeyConstValue;
   if(AdKeyNew)
   {
	 AdKeyNew = 0;		   //有新的按键值
	 Databuff = AdKeyValue;//新按键值
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
     if(Databuff >= MaxAdKey)   //如果大于240说明没有键按下
     {
       AdKeyLock        = 0;//没有键按下
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
          {              		   //成功获得键值
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
			   UpDatabuff = Databuff;		//两次比较去抖，除干扰
			 }
			 else
			 {
				//-----------------------------------------------
		        if(!UpPcbKeyValue || (UpDatabuff == UpPcbKeyValue))
		        {
		           UpPcbKeyValue = UpDatabuff; //按键处理无异常
		           switch(UpDatabuff)
		           {
			         case 1:if(!Standby)BiGuangCon = 1;break;
//			         case 2:                       break;
//			         case 3:                       break;	//不是加热键退出温标切换，是则反之
//		             case 4:                       break;
//		             case 5:                       break;
			         default  :                    break;
		           }
				   //-------------
		           if(!BiGuangCon)
		           {
		             if(Standby)
			         {
			           AdKeyLock    = 1;//背光没有点亮，不响应按键，此次响应被锁定
					   BiGuangCon   = 1;
					   PcbKeyValue  = 0;
			         }
		           }else
				   { //己经点亮背光，响应按键
					  PcbKeyValue = UpDatabuff; //此键确定被按下
				   }
		        }else
				{ //比较两次是不是同键按下，不是，去错等待按键被松开才再次响应
                  AdKeyLock   =  1;   //此次响应被锁定
			      PcbKeyValue =  0xff;//告诉按键处理程序,去错了
				}//-------
			 }
			 break;	//按键己处理，结束搜索键值循环
          }
	   }
	 }
   }
}

///************************************************************
//* 函数名:
//* 功能说明:AD键值分离
//************************************************************/
//bit                  AdKeyLock;
//unsigned char        UpDatabuff;
//unsigned char        PcbKeyValue;
//unsigned char        UpPcbKeyValue;
////									 VOD TIM SDL DWL HEA FLA POW
//unsigned char code AdKeyConst[7]   ={92, 52, 33, 12,  0};
//unsigned char code KeyValueTable[7]={ 0,  4,  5,  2,  1};
///************************************************************
//* 函数名:
//* 功能说明:AD键值分离
//************************************************************/
//void GainAdKeyValue(void)
//{
//   unsigned char Databuff;
//   unsigned char KeyValueSize;
//   if(AdKeyNew)
//   {
//	 AdKeyNew = 0;		           //有新的按键值
//	 Databuff = AdKeyValue;		   //新按键值
//     if(Databuff >= 92)           //如果大于240说明没有键按下
//     {
//       AdKeyLock        = 0;	   //没有键按下
//	   PcbKeyValue      = 0;
//	   UpPcbKeyValue    = 0;
//       return;
//     }
//     if(!AdKeyLock)
//     {
//	   if(UpDatabuff != Databuff)
//	   UpDatabuff     = Databuff;  //两次比较去抖，除干扰
//	   else
//	   { 						   //此键确定被按下
//         for(KeyValueSize = 0; KeyValueSize <= 5; KeyValueSize++)
//         {						   //
//           if(Databuff >= AdKeyConst[KeyValueSize])
//           {              		   //成功获得键值
//             PcbKeyValue      =  KeyValueTable[KeyValueSize];
//	         if(UpPcbKeyValue && (UpPcbKeyValue != PcbKeyValue))
//			 {//比较两次是不是同键按下，不是，去错等待按键被松开才再次响应
//               AdKeyLock   =  1;          //此次响应被定锁
//			   PcbKeyValue =  0xff;		  //告诉按键处理程序,去错了
//			 }
//			 else
//			 {
//		        switch(UpDatabuff)
//		        {
//			       case 1:BiGuangCon = 1;        break;
////			       case 2:                       break;
//			       case 3:TempSwFlashTimerCon= 0;break;	//不是加热键退出温标切换，是则反之
////		           case 4:                       break;
////		           case 5:                       break;
//			       default  :                    break;
//		        }
//			    //-------------
//		        if(!BiGuangCon)
//		        {
//		          if(Standby)
//			      {
//			        AdKeyLock    = 1;//背光没有点亮，不响应按键，此次响应被锁定
//					BiGuangCon   = 1;
//					PcbKeyValue  = 0;
//			      }
//		        }else
//				{ //己经点亮背光，响应按键
//				  PcbKeyValue = UpDatabuff; //此键确定被按下
//				}
//
//			    UpPcbKeyValue = PcbKeyValue; //按键处理无异常
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