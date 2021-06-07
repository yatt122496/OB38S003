/***********************************************************
*  �ļ�˵����                                            
************************************************************
*  ����:
*									                                                                                                                                            
*  ����:                                                                                           
*                                                          
************************************************************
*  Ӳ����sh79f083a                                                
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���                           
* ��������                                
***********************************************************/
#include "HARDWARE\main\SysInc.h"

bit     Standby;
uint8   KeyAct;
/************************************************************
* 
* 		Power��ʾ
************************************************************/
void PowerDisp( void )
{    
  if(Standby){		
    //----------
    if(HeatGears && !HeatLock && !ErrCon)
    TempDisp();   
    else
	if(FlaGears)
	FlaDisp();
#if (DWL_EN==1)
    else
    if(DwlGears)    
    DwlDisp(); 
#endif	
    else{
      LedPow     =  1;   
	  DispDct1   =  0;
	  DispDct2   = _N_;
//	  DispDct3   = _F_;           
    }
	//----------
  }else{
    DispDct1 = 0; //"0000"   
    DispDct2 = 0;    
    DispDct3 = 0;    
    DispLed  = 0;  
  }
}
/************************************************************
*  
*        Power��
************************************************************/
void PowKey( void )
{
   CancelAllFlash(0);
   //----------
   ClrTmr();
   //----------       
   Standby = ~Standby;
   if(!Standby){     
	 KeyAct   = K2_POW;
     DispDataSet = &ClrDisp;
      Hidden     = 0;
      BiGuangCon = 0; 
   }else{    
	 if(HeatGears && !HeatLock && !ErrCon){   		   	
       HeaClr1min(); 
       KeyAct  = K2_HEA;        
	 }else
	 if(FlaGears)
	 KeyAct  = K2_FLA;
     DispDataSet = &PowerDisp; 
   } 
}
/************************************************************
*  
*        Power��
************************************************************/
void SysRst(void)
{
   SysInit(); 
   //-----------    
   FunEndFlashSet();    
   DispDataSet = &PowerDisp;  
}