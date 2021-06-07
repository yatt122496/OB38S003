/***********************************************************
*  文件说明：
************************************************************
*  日期:
*
*  作者:  cuoiszf
*
************************************************************
*  硬件：sh79f083
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\main\SysInc.h"
//
#define LNC      0XFF
//-----------------------
bit  KeyLock;
bit  KeyLinkProc;
bit  KeyProcLock;
bit  IrBalance , PcBbalance;
//-----------------------
uint8 KeyValue;
uint8 KeyLinkTimer;
uint8 KeySwitchTimer;
//长按，连加选择			         POW   FLA  HEA  TIM  DWL  Width TEST
//uint8 code ShortPressList[ ]={ 0  , 0  ,  0 ,  0 ,  1 ,  1 ,  1 };
//uint8 code LinkPressList [ ]={ 0  , 0  ,  0 ,  0 ,  0 ,  0 ,  1 ,  1 ,  0 };
uint8 code LongPressList [ ]={ LNC,   0  , LNC, 100, LNC,  0, 100, LNC};
//-----------------------
/************************************************************
* 函数名: UpKey()
* 功能说明:  按键调用
************************************************************/
void KeyCall(unsigned char KeyData)
{
  HiddenTimer = 0;
  Hidden      = 1;
  switch(KeyData){
	case 0x01:PowKey()        ;break;
	case 0x02:FlaKey()        ;break;
	case 0x03:HeatKey()       ;break;
    case 0x04:TimKey()        ;break;
	//-----------------------------
#if (DWL_EN==1)
    case 0x05:DwlKey()        ;break;
#endif
    //-----------------------------
	case 0x07:TempProcKey()   ;break;
	//-----------------------------
    case   21:SysRst()        ;break;
    case   23:HeaLockSw()     ;break;
    //-----------------------------
#if (DWL_EN==1)
    case   25:TestEnter()     ;break;
#endif
	//-----------------------------
	case   26:GearsWidthKey() ;break;
	default  :                 break;
  }
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
	SaveKeyData = PcbKeyValue;
	//-------------------------
	if(SaveKeyData > 7){
		KeyProcLock = 1;
		SaveKeyData = 0;
	}
	//----------------------------
	if(!SaveKeyData){
		Psw         = 1;
		SaveKeyData	= IrValue;
		if(SaveKeyData)
			IrBalance   = 1;
	}else{
		Psw           = 0;
		IrValue       = 0;
		PcBbalance    = 1;
	}
	//-------------------------
	if(PcBbalance && IrBalance){
		KeyProcLock = 1;
		SaveKeyData = 0;
		IrValue     = 0;
	}
	//-------------------------
	if(!SaveKeyData){
		if(!KeyProcLock && KeyValue)
			KeyCall(KeyValue);
		KeyLock     = 0;
		KeyValue    = 0;
		KeyProcLock = 0;
		//-------------------------
		IrBalance   = 0;
		PcBbalance  = 0;
		KeyLinkProc     = 0;
		//-------------------------
		return;
	}
	//-----------
	if(!BiGuangCon){
		BiGuangCon   = 1;
		KeyLock     = 1;
		KeyProcLock = 1;
		KeySwitchTimer    = 200;//50Ms*200=10S
	}
	KeyValue=SaveKeyData;
	if(KeyLock==0){
		if(Psw){ //判别长按功能切换键
			KeyCall(KeyValue);	              //短按键调用处理
			KeyProcLock  =  1;
			IrValue      =  0;
		}
		HeaClrCnt();
		//
		KeyLock           = 1;
		//	KeyLinkTimer      = 20; //50Ms*20 =1S
		KeySwitchTimer    = 200;//50Ms*200=10S
	}else{
	//    if(LinkPressList[KeyValue]){
	//	  if(!KeyLinkTimer){
	//		KeyLinkTimer = 	6;	 //50Ms* 6 =300mS
	//        KeyProcLock  =  1;	 //该键设为己处理
	//	  }
	//	}else
		if((LongPressList[SaveKeyData] != LNC) && Standby){
			if(KeySwitchTimer <= LongPressList[SaveKeyData]){
			KeySwitchTimer = 200;	  //10秒按键功能键切换
			KeyProcLock    =  1 ;
			KeyCall(KeyValue + 20);	  //
			}
		}
	}
}