/***********************************************************
*
************************************************************
*  日期:2015-1-8 10:51
*
*  作者:
*
************************************************************
*  硬件：  SH79F1622
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\include\SysInc.h"
//-------------------------------
u8 idata SysMemBuff[8];
/************************************************************
*
* 		  温度转换闪
************************************************************/
void EepromInit(u8 Init)
{
  u8 DataBuf;
  if(Init == 0x55) goto SaveErr;else
  if(Init == 0x99) goto SaveErr;else
  if(Init != 0xaa) return;
  if(ReadEepromLike(&SysMemBuff[0]))
  {
	  DataBuf = SysMemBuff[0]+SysMemBuff[1];
	  //-----------------------------
	  if(DataBuf != SysMemBuff[6] || SysMemBuff[7] != 0x55)
      goto SaveErr;
	  //-----------------------------
	  HeatLock     = 0;
	  Standby      = 0;
	  HeatOnOff    = 0;
	  DataBuf       = SysMemBuff[0];
	  if(DataBuf&0x80)
	  Standby      = 1;
	  if(DataBuf&0x40)
	  HeatLock     = 1;
	  if(DataBuf&0x20)
	  HeatOnOff    = 1;
	  //-----------------------------
	  FlaGears	   = SysMemBuff[1] & 0x07;
	  //-----------------------------
	  if(FlaGears>6)
	  goto SaveErr;
	  BzSet(1);
  }
  else
  {
    SaveErr:
	EraseEepromMsg();
//*************************************
//*
	if(Init != 0x99)
	Standby      = 0;
	HeatLock     = 0;
	HeatOnOff    = 0;
	FlaGears     = 0;
//*
//*************************************
    SaveSetCall();
	BzSet(3);
  }
}
/************************************************************
*
*
************************************************************/
void SaveSetCall( void )
{
  u8 ReadBuf[8];
  u8 SaveTO;
  if(EEPROM_Error != 0X55)
  {
	SysMemBuff[0]= 0;
	if(Standby)
	SysMemBuff[0]|= 0x80;
	if(HeatLock)
	SysMemBuff[0]|= 0x40;
	if(HeatOnOff)
	SysMemBuff[0]|= 0x20;
	//-------------------------
	SysMemBuff[1] = FlaGears;
	//-------------------------
	SysMemBuff[2]=0;
    SysMemBuff[3]=0;
    SysMemBuff[4]=0;
    SysMemBuff[5]=0;
	//-------------------------
	SysMemBuff[6] = SysMemBuff[0]+SysMemBuff[1];
	SysMemBuff[7] = 0x55;
    //-------------------------
	SaveTO = 0;
	ErrRestWrite:
	if(EEPROM_Error != 0X55)
	{
      WriteEepromLike(&SysMemBuff[0],&ReadBuf[0]);
	  if(SysMemBuff[0] != ReadBuf[0] || SysMemBuff[1] != ReadBuf[1]
	  || SysMemBuff[2] != ReadBuf[2] || SysMemBuff[3] != ReadBuf[3]
	  || SysMemBuff[4] != ReadBuf[4] || SysMemBuff[5] != ReadBuf[5]
	  || SysMemBuff[6] != ReadBuf[6] || SysMemBuff[7] != ReadBuf[7])
	  {
	    SaveTO++;
	    if(SaveTO > 3)
	    {
	      SaveTO = 4;	   //3次擦写读不正确说明EEPROM坏了
		  EEPROM_Error = 0X55;
		  return;
	    }else
		if(SaveTO == 2)
		EraseEepromMsg();
		goto ErrRestWrite;
	  }
	}
    //-------------------------
  }
}
