/***********************************************************
*
************************************************************
*  日期:
*
*  作者:
*
************************************************************
*  硬件：  SH79F1622
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\include\SysInc.h"

#define  NC  0xff
//-------------------------------
bit KeyProc;
u8  KeyLongTimer;
bit IrBalance , PcBbalance;
//u8 KeyLinkTimer;
//长按，连加选择			     POW   UFL  DFL  HEA
//u8 code ShortPressList[ ]={  0 ,  0 ,  1 ,  1 ,  1 };
//u8 code LinkPressList [ ]={  0 ,  0 ,  0 ,  0 ,  0 };
u8 code LongPressList [ ]={  NC,  0 ,  NC,  NC, 100};
/************************************************************
* 函数名: KeyCall
* 功能说明:  按键调用
************************************************************/
void KeyCall(u8 KeyData)
{
  if(!Standby && (KeyData != 1) && (KeyData <= 20))
  return;//待机只有电源键起作用
  switch(KeyData)
  {
    case  1   :PowerKey()   ;break;
    case  2   :FlaUpKey()   ;break;
	case  3   :FlaDoKey()   ;break;	//
    case  4   :HeatKey()    ;break;
    case 21   :HeatLockKey();break;
	case 24   :SysRest();    break;
    default  :break;
  }
}
/************************************************************
* 函数名:    SysKey
* 功能说明:  按键分离
*            此函数包括了，按键
*            的短按，长按，连加的处理
*            或许这样写不怎么科学，但为了AD键和摇控的模块化，
*            这可能是应当负出的代价
************************************************************/
void SysKey(void)
{
  u8 KeyBuf;
  bit Psw;
  static u8  KeyValue;
  static bit LongPressFlag;
  KeyBuf = PcbKeyValue;
  if(KeyBuf > 4)
  {
    KeyBuf   = 0;
	KeyValue = 0;
	KeyProc = 1;
  }
  //----------------------------
  if(!KeyBuf)
  {
    Psw     = 1;
	KeyBuf	= IrValue;
	if(KeyBuf>4)
	{
	  KeyBuf   = 0;
	  KeyValue = 0;
	  KeyProc = 1;
	}
	if(KeyBuf)
    IrBalance   = 1;
  }else
  {
    Psw        = 0;
	IrValue    = 0;
	PcBbalance = 1;
  }
  //-------------------------
  if(PcBbalance && IrBalance)
  {
    KeyProc = 1;
	KeyBuf  = 0;
	IrValue = 0;
  }
  if(!KeyBuf)
  {
    if(!KeyProc && KeyValue)
    KeyCall(KeyValue);	 //短按调用处理
	//-----------------
	KeyValue      = 0;
	KeyProc       = 0;
	LongPressFlag = 0;
	//-------------------------
	IrBalance   = 0;
	PcBbalance  = 0;
	//-------------------------
	return;
  }
//  if(!Standby)//待机只有电源键起作用
//  {
//    if(KeyBuf != 1)// && (KeyBuf != 4 || Psw))//屏蔽其它键
//    return;
//  }
  KeyValue = KeyBuf;
  if(!LongPressFlag)
  {
    if(Psw)
	{
	  KeyCall(KeyValue);	 //短按调用处理
	  KeyProc = 1;
	  IrValue = 0;
	}
    LongPressFlag = 1;
	KeyLongTimer  = 200;//50ms*200=10s
  }else
  {
	if(LongPressList[KeyValue]!=NC)
	{
	  if(KeyLongTimer <= LongPressList[KeyValue])
	  {
	    KeyLongTimer = 200;
	    KeyProc = 1;
	    KeyCall(KeyValue+20);
	  }
	}
  }
}