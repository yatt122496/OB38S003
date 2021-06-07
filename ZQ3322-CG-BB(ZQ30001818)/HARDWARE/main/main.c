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
#include "SysInc.h"
//------------------------------------------
uint8 KeyTestSize;
//------------------------------------------
bit CancelErrDispEc;
//------------------------------------------
uint8 TestKeyBuf;
uint8 UpPowerTest;
uint8 Test0x5a;
bit   DBugBit;
//------------------------------------------
uint8 Disturb0xAA;
uint8 Disturb0x55;
//------------------------------------------
void main(void)
{   
  //--------------------------   
  DBugBit        = 0;
  CancelErrDispEc= 0; 
  //------------
  SysInit();  
  InitSys(); 
  //--------------------------
  _nop_(); 
  _nop_();  
  _nop_(); 
  _nop_();  
  _nop_(); 
  if(Disturb0x55 != 0x55 || Disturb0xAA != 0xaa)
  while(1);
  //--------------------------
  TM1638_Init();
  DispInit();
  GoErrTestInit();
  //---------------------------  
//  if(HeatGears) 
//  FirstHeat = 1;
  while(1){
	RSTSTAT=Bin(00000000); //170ms 
	TimerOff();	
	SysTimer50ms();
	KeyValueApart(); 
	_nop_();  
	_nop_(); 
	_nop_();  
	_nop_(); 
	if(Disturb0xAA != 0xaa || Disturb0x55 != 0x55)
	while(1);
	AdNtc();
    HeatCon();	
	//---------------
	ErrTest();
	Disp();
#if (DWL_EN==1)	
    DwlCon();
#endif
	//--------------
	_nop_();  
	_nop_(); 
	_nop_();  
	_nop_(); 
	_nop_();  
	_nop_();     
  }
  while(1);
}