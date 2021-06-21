#include "HARDWARE\main\SysInc.h"
#include "HARDWARE\Lib\inc\epwm.h"

bit SaveSet;
U8  idata SysMemBuff[8];
/************************************************************
*
* 		  ÎÂ¶È×ª»»ÉÁ
************************************************************/
void EepromInit( unsigned char PowerErase )
{
   U8 DataBuf;
   SysSaveErr:
   if(EepRomBoot(PowerErase))
   {
	  //-----------------------------
      ReadEepromLike(&SysMemBuff[0]);
//*************************************
//*
	  if(SysMemBuff[0] != SysMemBuff[1] || SysMemBuff[2] != 0x55 || SysMemBuff[3] != 0xaa)
	  {
	    PowerErase = 1;
        goto SysSaveErr;
	  }
//*
//*************************************
	  //-----------------------------
	  DataBuf = SysMemBuff[0];
	  if(DataBuf & 0x80)
	  Standby    = 1;
	  if(DataBuf & 0x40)
	  HeatOnOff  = 1;
	  if(DataBuf & 0x20) {
		  DotAotoCon = 1;
		  EPWM_ConfigChannelPeriod(EPWM0, PWM_MAX);
		EPWM_ConfigChannelPeriod(EPWM3, PWM_MAX);
		EPWM_ConfigChannelSymDuty(EPWM0, 0);
		EPWM_ConfigChannelSymDuty(EPWM3, 0);
	  }
	  if(DataBuf & 0x10)
	  HeatLock   = 1;
	  FlaGears   = DataBuf & 0x07;
	  //-----------------------------
   }
   else
   {
      //-----------------------------
      Standby    = 0;
	  HeatOnOff  = 0;
	  DotAotoCon = 0;
	  EPWM_ConfigChannelPeriod(EPWM0, PWM_MAX / 2);
		EPWM_ConfigChannelPeriod(EPWM3, PWM_MAX / 2);
		EPWM_ConfigChannelSymDuty(EPWM0, 0);
		EPWM_ConfigChannelSymDuty(EPWM3, 0);
	  FlaGears   = 5;
	  HeatLock   = 0;
	  //-----------------------------
//*************************************
//*
	  SysMemBuff[0]=0;
	  SysMemBuff[1]=0;
      SysMemBuff[2] = 0x55;
      SysMemBuff[3] = 0xaa;
//*
//*************************************
	  SysMemBuff[4]=0;
	  SysMemBuff[5]=0;
	  SysMemBuff[6]=0;
	  SysMemBuff[7]=0;
	  WriteEepromLike(&SysMemBuff[0]);
	  //-----------------------------
   }
}
/************************************************************
*
*
************************************************************/
void SaveSetCall( void )
{
  U8 DataBuf;
  //-----------------------------
  SysMemBuff[0]=0;
  SysMemBuff[1]=0;
  SysMemBuff[2]=0;
  SysMemBuff[3]=0;
  SysMemBuff[4]=0;
  SysMemBuff[5]=0;
  SysMemBuff[6]=0;
  SysMemBuff[7]=0;
  //-------------------------
  /*********************************/
  DataBuf    = FlaGears & 0x07;
  if(Standby)
  DataBuf   |= 0x80;
  if(HeatOnOff)
  DataBuf   |= 0x40;
  if(DotAotoCon)
  DataBuf   |= 0x20;
  if(HeatLock)
  DataBuf   |= 0x10;
//*************************************
//*
  SysMemBuff[0] = DataBuf;
  SysMemBuff[1] = DataBuf;
  SysMemBuff[2] = 0x55;
  SysMemBuff[3] = 0xaa;
//*
//*************************************
  /*********************************/
  //-------------------------
  WriteEepromLike(&SysMemBuff[0]);
  //-------------------------
}