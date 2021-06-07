/***********************************************************
*  文件说明：                                            
************************************************************
*  日期:
*									                                                                                                                                            
*  作者:                                                                                           
*                                                          
************************************************************
*  硬件：sh79f083a                                                
************************************************************
* 【版权】 Copyright(C)鹏林电子                           
* 【声明】                                
***********************************************************/
#include "HARDWARE\main\SysInc.h"

bit     Standby;
uint8   KeyAct;
/************************************************************
* 
* 		Power显示
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
*        Power键
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
*        Power键
************************************************************/
void SysRst(void)
{
   SysInit(); 
   //-----------    
   FunEndFlashSet();    
   DispDataSet = &PowerDisp;  
}