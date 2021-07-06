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

/**
  * @brief Delay
  * @param nCount
  * @retval None
  */
void main(void)
{  
  InitSys();
  //--------------------------
  RSTSTAT=Bin(00000000);
  EA   = 1;
  //--------------------------
  UpKeyValue   = 0x55; 
  KeyTestSize  = 4;
  while(KeyTestSize)
  {
#if  (IO_AD_KEY_OTP == 0)       
    if(KeyNew)
#else        
    if(AdKeyNew)
#endif        
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
  GoErrTestInit( );
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