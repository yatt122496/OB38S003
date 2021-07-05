/***********************************************************
*  TM1638����
************************************************************
*  ����:2011.9.21 5:00
*
*  ����:
*
************************************************************
*  Ӳ����SH79F083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE/main/SysInc.h"
#define  KNC   0XFF
//����������ѡ���						     POW FLA HEA DWL SDL TUP
unsigned char code ShortPressList  [8] ={ 0 , 0 , 1 , 1 , 1 , 1 , 0  };
unsigned char code LongPressList   [8] ={KNC,100,KNC,KNC,KNC,KNC,100};

unsigned char KeySwitchTimer;

bit IrBalance,PcBbalance;

bit           KeyLock;
bit           KeyProcLock;
unsigned char KeyValue;
/************************************************************
* ������: UpKey()
* ����˵��:  ��������
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
  GainAdKeyValue();
  SaveKeyData = PcbKeyValue;
  //-------------------------
  if(SaveKeyData == 0xff){
    KeyProcLock = 1;//��ֵ��������ü���Ϊ������
	SaveKeyData = 0;//��ֵ��������
  }
  //----------------------------
  if(!SaveKeyData){//�����ް�������
	SaveKeyData	= IrValue;//�洢ң�ؼ�ֵ
	if(SaveKeyData)//�м�����
    IrBalance   = 1;//��־��1
	Psw         = 1;
  }else{//�����а�������
	IrValue       = 0;//ң�ؼ�ֵ����
	PcBbalance    = 1;//��־��1
	Psw           = 0;
  }
  //-------------------------
  if(PcBbalance && IrBalance){//���ң�ض��м�����
    KeyProcLock = 1;//�ü���Ϊ������
	SaveKeyData = 0;//��������
	IrValue     = 0;//ң�ؼ�ֵ����
  }
  //-------------------------
  if(!SaveKeyData){//����Ч��ֵ
	 if(!KeyProcLock && KeyValue && (KeySwitchTimer>160))//��ֵδ�����Ҽ�ֵ��Ч
	 KeyCall(KeyValue);//��ֵ����
	 KeyLock     = 0;
	 KeyValue    = 0;
	 KeyProcLock = 0;
	 //-------------------------
	 IrBalance   = 0;
	 PcBbalance  = 0;
	 //-------------------------
	 return;
  }
  if(Standby==0){//����ֻ�е�Դ��������
    if(SaveKeyData!=1)//����������
    return;
  }
  KeyValue = SaveKeyData;
  if(!KeyLock){
	if(ShortPressList[KeyValue] || Psw){ //�б𳤰������л���
	  KeyCall(KeyValue);	 //�̰������ô���
      KeyProcLock  =  1;	   //�ü���Ϊ������
	  IrValue      =  0;//ң�ؼ�ֵ����
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
	    KeySwitchTimer = 200;	  //10�밴�����ܼ��л�
        KeyCall(KeyValue + 20);
		KeyProcLock = 1;
	  }
	}
  }
}