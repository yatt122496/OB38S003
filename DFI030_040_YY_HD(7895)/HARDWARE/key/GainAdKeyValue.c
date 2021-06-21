/***********************************************************
*
************************************************************
*  日期:
*
*  作者:
*
************************************************************
*  硬件：
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\main\SysInc.h"

bit KeyNew;

#if (IO_AD_KEY_OTP == 0)
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
U8 PcbKeyValue;
U8 UpPcbKeyValue;
U8 UpKeyBuff;
/************************************************************
* 函数名:
* 功能说明:
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
* 函数名:
* 功能说明:
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
* 函数名:
* 功能说明:
************************************************************/
void GainAdKeyValue(void)
{
   U8 Databuff;
   U8 KeyValueSize;
   if(AdKeyNew)
   {
	   AdKeyNew = 0;		           //有新的按键值
	   Databuff = AdKeyValue;		   //新按键值
     if(Databuff >= AD_KEY_MAX)   //如果大于240说明没有键按下
     {
       AdKeyLock        = 0;	   //没有键按下
	   UpPcbKeyValue    = 0;
	   PcbKeyValue      = 0;
       return;
     }
     if(!AdKeyLock)
     {
       for(KeyValueSize = 0; KeyValueSize < KEY_SIZE; KeyValueSize++)
       {						   //
         if(Databuff >= AdKeyConst[KeyValueSize])
         {              		   //成功获得键值
            Databuff    =  KeyValueTable[KeyValueSize];
			if(UpDatabuff != Databuff)
			UpDatabuff = Databuff;		//两次比较去抖，除干扰
			else
			{
			  PcbKeyValue = UpDatabuff; //此键确定被按下
	          if(UpPcbKeyValue && (UpPcbKeyValue != PcbKeyValue))
			  {//比较两次是不是同键按下，不是，去错等待按键被松开才再次响应
                AdKeyLock   =  1;          //此次响应被锁定
			    PcbKeyValue =  0xff;		  //告诉按键处理程序,去错了
			  }
			  else
			  UpPcbKeyValue = PcbKeyValue; //按键处理无异常
			}
			break;
         }
       }
	 }
   }
}
#endif