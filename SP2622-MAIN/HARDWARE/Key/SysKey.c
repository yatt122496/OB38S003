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
//����������ѡ��			         POW   FLA  HEA  TIM  DWL  Width TEST
//uint8 code ShortPressList[ ]={ 0  , 0  ,  0 ,  0 ,  1 ,  1 ,  1 };
//uint8 code LinkPressList [ ]={ 0  , 0  ,  0 ,  0 ,  0 ,  0 ,  1 ,  1 ,  0 };
uint8 code LongPressList [ ]={ LNC,   0  , LNC, 100, LNC,  0, 100, LNC};
//-----------------------
/************************************************************
* ������: UpKey()
* ����˵��:  ��������
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
* ������: UpKey()
* ����˵��:  ��������
*            �˺��������ˣ�����
*            �Ķ̰������������ӵĴ���
*            ��������д����ô��ѧ����Ϊ��AD����ҡ�ص�ģ�黯��
*            �������Ӧ�������Ĵ���
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
		if(Psw){ //�б𳤰������л���
			KeyCall(KeyValue);	              //�̰������ô���
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
	//        KeyProcLock  =  1;	 //�ü���Ϊ������
	//	  }
	//	}else
		if((LongPressList[SaveKeyData] != LNC) && Standby){
			if(KeySwitchTimer <= LongPressList[SaveKeyData]){
			KeySwitchTimer = 200;	  //10�밴�����ܼ��л�
			KeyProcLock    =  1 ;
			KeyCall(KeyValue + 20);	  //
			}
		}
	}
}