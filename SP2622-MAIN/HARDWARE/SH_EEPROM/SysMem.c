
#include "../code/main/SysInc.h"

bit    SaveSet;
uint8  SysMemBuff[8];
/************************************************************
* 
* 		  温度转换闪
************************************************************/
void EepromInit( unsigned char PowerErase )
{
   uint8 DataBuf;
   uint8 AddBuff;    
   //------------------
   SysSaveErr:
   //----------------------
   if(EepRomBoot(PowerErase))
   {
      ReadEepromLike(&SysMemBuff[0]);
//*************************************
//*		
      AddBuff = 0;
	  AddBuff  = SysMemBuff[0]; 
      AddBuff += SysMemBuff[1]; 
      AddBuff += SysMemBuff[2]; 
      AddBuff += SysMemBuff[3]; 
	  //-----------------------------
	  if(AddBuff != SysMemBuff[4] || SysMemBuff[5] != 0x55 || SysMemBuff[6] != 0xaa)
	  {
	    PowerErase = 1;
        goto SysSaveErr;
	  }
//*
//*************************************
      DataBuf = SysMemBuff[0];
	  //-----------------------------
//	  if(DataBuf & 0x80)
//	  FlaOnOff = 1;
//	  else
//	  FlaOnOff = 0;
	  //-----------------------------
	  DataBuf = (DataBuf >> 4) & 0x07;
	  if(DataBuf < 7)
      FlaGears = DataBuf;
	  else
	  goto SaveErr;
/**************************************************/
	  //-----------------------------
	  DataBuf = SysMemBuff[1] & 0x0f;
	  if(DataBuf < 13)
      HeatGears = DataBuf;
	  else
	  goto SaveErr;
	  //-----------------------------
      DataBuf = SysMemBuff[1];
	  //-----------------------------
	  if(DataBuf&0x80)	   //电源是否开起
	  Standby = 1;		   //电源开
	  else
	  Standby = 0;		   //电源关
	  //-----------------------------
	  if(DataBuf&0x40)	   //加热锁
	  HeatLock = 1;		   //上锁
	  else
	  HeatLock = 0;		   //没锁
	  //-----------------------------
	  if(DataBuf&0x20)	  //温标
	  TcTf     = 1;		  //摄氏度
	  else
	  TcTf     = 0;		  //华氏度
	  //-----------------------------
	  if(DataBuf&0x10)	  //发热是否开起
	  HeatOnOff = 1;	  //开启
	  else
	  HeatOnOff = 0;	  //关闭
	  //-----------------------------
/**************************************************/
	  TimerCon   = 0; 
	  DataBuf = SysMemBuff[3] & 0x0f;
	  if((SysMemBuff[2] != 0)||(DataBuf != 0)) 
	  {
	    //-----------------------------
		if(DataBuf <= 9)
		clk[2]  = DataBuf; 
		else
	    goto SaveErr; 
		//-----------------------------
	  	DataBuf = SysMemBuff[3] & 0xf0;
		if(DataBuf == 0xa0)
		goto SaveErr;	
		//-----------------------------					
		DataBuf	= SysMemBuff[2] & 0x3f;
		if(DataBuf <= 60)
		clk[1]  = DataBuf;  
		else
	    goto SaveErr;
		//-----------------------------
	    clk[0]     = 59;
		TimerEnd   = 0;
		TimerCon   = 1;   		              
	  }else
	  {
	  	DataBuf = SysMemBuff[3] & 0xf0;
		if(DataBuf == 0xa0)
		{
	      clk[0]     = 99;
		  TimerEnd   = 1;
		  TimerCon   = 1;
		}   		
	  }        	  	  	  
   }
   else
   {
      SaveErr:	  
	  Standby   = 0;
	  //-----------	
      TcTf      = FC_EN; 
	  HeatLock  = 0;
	  HeatOnOff = 0;
	  HeatGears = 6;
	  //-----------
//	  FlaOnOff  = 1;
	  FlaGears  = 6;
	  //-----------	
	  //-----------  
	  TimerCon  = 0;  
	  clk[0]    = 0;
	  clk[1]    = 0;
	  clk[2]    = 0;
	  TimerEnd  = 0; 	   
	  //----------- 
      SaveSetCall();
   }
}
/************************************************************
* 
* 		  
************************************************************/
void SaveSetCall( void )
{          
  uint8 AddBuff; 
  SysMemBuff[0]=0;
  SysMemBuff[1]=0;
  SysMemBuff[2]=0;
  SysMemBuff[3]=0;	
  SysMemBuff[4]=0;
  SysMemBuff[5]=0;
  SysMemBuff[6]=0;
  SysMemBuff[7]=0;
  //-------------------------
  SysMemBuff[0] |= (FlaGears << 4) & 0x70; 
//  if(FlaOnOff)
//  SysMemBuff[0] |= 0x80;
  //-------------------------
  SysMemBuff[1]  = HeatGears & 0x0f;
  //-------------------------
  if(Standby)
  SysMemBuff[1] |= 0x80;
  //-------------------------		
  if(HeatLock)
  SysMemBuff[1] |= 0x40;
  //-------------------------
  if(TcTf)
  SysMemBuff[1] |= 0x20;
  //-------------------------
  if(HeatOnOff)
  SysMemBuff[1] |= 0x10;
  //-------------------------
  EA = 0;
  if(TimerCon){
    SysMemBuff[2]  = clk[1];    
	if(TimerEnd)
	SysMemBuff[3]  = 0xa0;
	else
    SysMemBuff[3]  = clk[2];
  }
  EA = 1;
//*************************************
//*
  AddBuff  = 0;
  AddBuff  = SysMemBuff[0]; 
  AddBuff += SysMemBuff[1]; 
  AddBuff += SysMemBuff[2]; 
  AddBuff += SysMemBuff[3]; 
  SysMemBuff[4] = AddBuff;
  SysMemBuff[5] = 0x55;
  SysMemBuff[6] = 0xaa;	
//*
//*************************************
  //-------------------------
  WriteEepromLike(&SysMemBuff[0]); 	
  //-------------------------
}