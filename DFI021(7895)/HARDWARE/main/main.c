/***********************************************************
*  �ļ�˵����                                            
************************************************************
*  ����: 
*									                                                                                                                                            
*  ����:                                                                                           
*                                                          
************************************************************
*  Ӳ����sh79f083                                                
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���                           
* ��������                                
***********************************************************/
#include "SysInc.h"

U8 KeyTestSize;
U8 UpKeyValue;

void main(void)
{  
  FlaInit();
  InitSys();
  //--------------------------
  UpKeyValue   = 0x55; 
  KeyTestSize  = 4;
  while(KeyTestSize)
  {
    if(KeyNew)
    {    
      GainAdKeyValue  ();
      if(PcbKeyValue != UpKeyValue)
      UpKeyValue = PcbKeyValue;
	  else
	  {		//���αȽϽ����ͬ��ֵȷ��
        switch(PcbKeyValue)
        {
          case 1    :EepRomBoot(1);KeyTestSize = 0;break;  //�ϵ簴POWER����λϵͳ��                              
          default   :              KeyTestSize = 0;break;		
        } 
	  }
	  if(KeyTestSize)
	  KeyTestSize--;
    }
  }
  //--------------------------
  EepromInit(0);
  //--------------------------
  while(1)
  {
	RSTSTAT=Bin(00000010); 	
	KeyValueApart();
	AdNtc();
	ArAd();
    HeatCon();	
	SysTimer50ms();
  }
}