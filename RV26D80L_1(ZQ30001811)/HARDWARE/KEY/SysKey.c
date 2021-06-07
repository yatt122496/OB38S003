/***********************************************************
*  TM1638驱动
************************************************************
*  日期:2011.9.21 5:00
*
*  作者:
*
************************************************************
*  硬件：SH79F083
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE/main/SysInc.h"
#define  KNC   0XFF
//长按，连加选择表						     POW FLA HEA DWL SDL TUP
unsigned char code ShortPressList  [8] ={ 0 , 0 , 1 , 1 , 1 , 1 , 0  };
unsigned char code LongPressList   [8] ={KNC,100,KNC,KNC,KNC,KNC,100};

unsigned char KeySwitchTimer;

bit IrBalance,PcBbalance;

bit           KeyLock;
bit           KeyProcLock;
unsigned char KeyValue;
/************************************************************
* 函数名: UpKey()
* 功能说明:  按键调用
************************************************************/
void KeyCall(unsigned char KeyData)
{
  switch(KeyData)
  {
	case 0x01:PowKey()         ;break;
	case 0x02:FlaKey()         ;break;
    case 0x03:HeatKey(0)       ;break;
	case 0x04:TimKey()         ;break;
	case 0x05:DowKey()         ;break;
	case 0x06:HeatKey(1)       ;break;
    case 0x07:TempSetKey()     ;break;
    case   21:TempSw()         ;break;
//	case   22:FlaLockKey()     ;break;
	case   26:HeatSetAndLook() ;break;
	default  :                  break;
  }

  Hidden            = 1;
  HiddenTimer       = 0;
  TempFlashTimerCon = 0;
}
/************************************************************
* 函数名: UpKey()
* 功能说明:  按键分离
*            此函数包括了，按键
*            的短按，长按，连加的处理
*            或许这样写不怎么科学，但为了AD键和摇控的模块化，
*            这可能是应当负出的代价
************************************************************/
void KeyValueApart( void )
{
  bit   Psw;
  uint8 SaveKeyData;
  GainAdKeyValue();
  SaveKeyData = PcbKeyValue;
  //-------------------------
  if(SaveKeyData == 0xff){
    KeyProcLock = 1;//键值处理出错，该键设为己处理
	SaveKeyData = 0;//键值缓存清零
  }
  //----------------------------
  if(!SaveKeyData){//板上无按键按下
	SaveKeyData	= IrValue;//存储遥控键值
	if(SaveKeyData)//有键按下
    IrBalance   = 1;//标志置1
	Psw         = 1;
  }else{//板上有按键按下
	IrValue       = 0;//遥控键值清零
	PcBbalance    = 1;//标志置1
	Psw           = 0;
  }
  //-------------------------
  if(PcBbalance && IrBalance){//板和遥控都有键按下
    KeyProcLock = 1;//该键设为己处理
	SaveKeyData = 0;//缓存清零
	IrValue     = 0;//遥控键值清零
  }
  //-------------------------
  if(!SaveKeyData){//有有效键值
	 if(!KeyProcLock && KeyValue && (KeySwitchTimer>160))//键值未处理，且键值有效
	 KeyCall(KeyValue);//键值处理
	 KeyLock     = 0;
	 KeyValue    = 0;
	 KeyProcLock = 0;
	 //-------------------------
	 IrBalance   = 0;
	 PcBbalance  = 0;
	 //-------------------------
	 return;
  }
  if(Standby==0){//待机只有电源键起作用
    if(SaveKeyData!=1)//屏蔽其它键
    return;
  }
  KeyValue = SaveKeyData;
  if(!KeyLock){
	if(ShortPressList[KeyValue] || Psw){ //判别长按功能切换键
	  KeyCall(KeyValue);	 //短按键调用处理
      KeyProcLock  =  1;	   //该键设为己处理
	  IrValue      =  0;//遥控键值清零
	}else{
      switch(KeyValue){
	    case 0x02:GinFlaPsw()      ;break;
	    case 0x06:GainHeaterPsw()  ;break;
	    default  :                  break;
      }
	  Hidden        =  1;
	  HiddenTimer   =  0;
	}
    KeyLock         = 1;
    KeySwitchTimer  = 200;		//50Ms*60=3S
  }else{
	if((LongPressList[KeyValue] != KNC) && Standby){
	  if(KeySwitchTimer <= LongPressList[KeyValue]){
	    KeySwitchTimer = 200;	  //10秒按键功能键切换
        KeyCall(KeyValue + 20);
		KeyProcLock = 1;
	  }
	}
  }
}