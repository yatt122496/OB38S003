/***********************************************************
*  �ļ�˵����
************************************************************
*  ����:
*
*  ����:  cuoiszf
*
************************************************************
*  Ӳ����sh79f083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE\main\SysInc.h"
//-----------------------
bit KeyLock;
bit IrBalance , PcBbalance;
bit  KeyProcLock;
U8  KeySwitchTimer;
U8  KeyValue;
//-----------------------
//����������ѡ��			  POW FLA HEA TIM
U8 code ShortPressList[]={0 , 1 , 1 , 0 , 1 , 1};
/************************************************************
* ������: UpKey()
* ����˵��:  ��������
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
* ������: UpKey()
* ����˵��:  ��������
*            �˺��������ˣ�����
*            �Ķ̰������������ӵĴ���
*            ��������д����ô��ѧ����Ϊ��AD����ҡ�ص�ģ�黯��
*            �������Ӧ�������Ĵ���
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
  if(PcBbalance && IrBalance)	  //�����ٲ�
  {
	SaveKeyData = 0;
	IrValue     = 0;
  }
  //-------------------------
  if(!SaveKeyData)
  {
     if(!KeyProcLock && KeyValue)
	 {
	   KeyCall(KeyValue);	 //�̰������ô���
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
 	  KeyCall(KeyValue);	 //�̰������ô���
	  KeyProcLock    = 1;
	}
	KeyLock        = 1;
	KeySwitchTimer = 200;	  //10�밴�����ܼ��л�
  }else
  {
    if(!ShortPressList[KeyValue] && Standby)
    {
	  if(!KeySwitchTimer)
      {
	    KeySwitchTimer = 200;	  //10�밴�����ܼ��л�
        KeyCall(KeyValue + 20);
		KeyProcLock = 1;
	  }
    }
  }
  //-------------------------
}