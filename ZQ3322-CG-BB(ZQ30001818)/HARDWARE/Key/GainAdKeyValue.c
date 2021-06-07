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
* 函数名:
* 功能说明:AD键值分离
************************************************************/
void GainAdKeyValue(void)
{
  unsigned char Databuff;
  unsigned char KeyValueSize;
  unsigned char KeySize,MaxAdKey,AdKeyConstValue;
  if(AdKeyNew&&!TouchKeyTim){
	 AdKeyNew = 0;		          //有新的按键值
	 Databuff = AdKeyValue;		  //新按键值
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
     if(Databuff >= MaxAdKey){  //如果大于240说明没有键按下
       AdKeyLock        = 0;	  //没有键按下
	   UpPcbKeyValue    = 0;
	   PcbKeyValue      = 0;
	   UpDatabuff       = 0;
       return;
     }
     if(!AdKeyLock){//此键确定被按下
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
         if(Databuff >= AdKeyConstValue){//成功获得键值
           if(TouchKeyOpt==0)
           {
			 Databuff =  KeyValueTable0[KeyValueSize];
		   }else
           {
			 Databuff =  KeyValueTable1[KeyValueSize];
		   }
	       if(UpDatabuff != Databuff)
		   UpDatabuff = Databuff;		//两次比较去抖，除干扰
		   else{
             if(UpDatabuff==3 || UpDatabuff==4){
				if(++CompoundKeyCnt>3){
				  CompoundKeyCnt = 3;
				  PcbKeyValue = UpDatabuff; //此键确定被按下
				  if(UpDatabuff==3)ClrErrTmr();
				}
			 }else{
			    CompoundKeyCnt = 0;
                PcbKeyValue = UpDatabuff; //此键确定被按下
			 }
	          if(UpPcbKeyValue && (UpPcbKeyValue != PcbKeyValue)) {//比较两次是不是同键按下，不是，去错等待按键被松开才再次响应
                 AdKeyLock   =  1;          //此次响应被锁定
			     PcbKeyValue =  0xff;		  //告诉按键处理程序,去错了
			  }else{
			     UpPcbKeyValue = PcbKeyValue; //按键处理无异常
			  }
		   }
		   break;
         }
	   }
	 }
  }
}
