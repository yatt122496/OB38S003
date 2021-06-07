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
//-----------------------
bit KeyLock;
bit IrBalance , PcBbalance;
bit  KeyProcLock;
U8  KeySwitchTimer;
U8  KeyValue;
//-----------------------
//长按，连加选择			  POW FLA HEA TIM
U8 code ShortPressList[]={0 , 1 , 1 , 0 , 1 , 1};
/************************************************************
* 函数名: UpKey()
* 功能说明:  按键调用
************************************************************/
void KeyCall(unsigned char KeyData)
{
  switch(KeyData)
  {
	case 0x01:PowerKey()         ;break;
	case 0x02:FlaKey()           ;break;
	case 0x03:HeatKey()          ;break;
    case 0x04:FlaUKey()          ;break;
    case 0x05:FlaDKey()          ;break;
	case   23:HeatLook()         ;break;
	default  :                    break;
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
  U8 SaveKeyData;
  bit Psw;
  GainAdKeyValue();
  SaveKeyData = PcbKeyValue;
  //-------------------------
  if(SaveKeyData == 0xff)
  SaveKeyData = 0;
  //----------------------------
  if(!SaveKeyData)
  {
	SaveKeyData	= IrValue;
	if(SaveKeyData)
    IrBalance   = 1;
	Psw = 1;
  }else
  {
	IrValue       = 0;
	PcBbalance    = 1;
	Psw = 0;
  }
  //-------------------------
  if(PcBbalance && IrBalance)	  //按键仲裁
  {
	SaveKeyData = 0;
	IrValue     = 0;
  }
  //-------------------------
  if(!SaveKeyData)
  {
     if(!KeyProcLock && KeyValue)
	 {
	   KeyCall(KeyValue);	 //短按键调用处理
	 }
	 KeyLock     = 0;
	 KeyProcLock = 0;
	 KeyValue    = 0;
	 //-------------------------
	 IrBalance   = 0;
	 PcBbalance  = 0;
	 //-------------------------
	 return;
  }
  if(!Standby){
    if(SaveKeyData != 1){
      return;
    }
  }
  //-------------------------
  KeyValue = SaveKeyData;
  if(KeyLock==0)
  {
    if(ShortPressList[KeyValue] || Psw)
	{
 	  KeyCall(KeyValue);	 //短按键调用处理
	  KeyProcLock    = 1;
	}
	KeyLock        = 1;
	KeySwitchTimer = 200;	  //10秒按键功能键切换
  }else
  {
    if(!ShortPressList[KeyValue] && Standby)
    {
	  if(!KeySwitchTimer)
      {
	    KeySwitchTimer = 200;	  //10秒按键功能键切换
        KeyCall(KeyValue + 20);
		KeyProcLock = 1;
	  }
    }
  }
  //-------------------------
}