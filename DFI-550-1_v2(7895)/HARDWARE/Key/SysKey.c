/***********************************************************
*
************************************************************
*  ����:
*
*  ����:
*
************************************************************
*  Ӳ����  SH79F1622
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE\include\SysInc.h"

#define  NC  0xff
//-------------------------------
bit KeyProc;
u8  KeyLongTimer;
bit IrBalance , PcBbalance;
//u8 KeyLinkTimer;
//����������ѡ��			     POW   UFL  DFL  HEA
//u8 code ShortPressList[ ]={  0 ,  0 ,  1 ,  1 ,  1 };
//u8 code LinkPressList [ ]={  0 ,  0 ,  0 ,  0 ,  0 };
u8 code LongPressList [ ]={  NC,  0 ,  NC,  NC, 100};
/************************************************************
* ������: KeyCall
* ����˵��:  ��������
************************************************************/
void KeyCall(u8 KeyData)
{
  if(!Standby && (KeyData != 1) && (KeyData <= 20))
  return;//����ֻ�е�Դ��������
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
* ������:    SysKey
* ����˵��:  ��������
*            �˺��������ˣ�����
*            �Ķ̰������������ӵĴ���
*            ��������д����ô��ѧ����Ϊ��AD����ҡ�ص�ģ�黯��
*            �������Ӧ�������Ĵ���
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
    KeyCall(KeyValue);	 //�̰����ô���
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
//  if(!Standby)//����ֻ�е�Դ��������
//  {
//    if(KeyBuf != 1)// && (KeyBuf != 4 || Psw))//����������
//    return;
//  }
  KeyValue = KeyBuf;
  if(!LongPressFlag)
  {
    if(Psw)
	{
	  KeyCall(KeyValue);	 //�̰����ô���
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