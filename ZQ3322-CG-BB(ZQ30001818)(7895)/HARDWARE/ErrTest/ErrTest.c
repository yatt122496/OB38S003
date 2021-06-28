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
#include "HARDWARE\main\SysInc.h"
//----------------------------
bit    GoErrCon;
//----------------------------
uint8  GoErrCount;
//----------------------------
uint16  NtcErrDat;
//----------------------------
uint8  ErrCon;
//----------------------------
void GoErrTestInit(void)
{
  GoErrCon   = 0;
  GoErrCount = 0;
}
bit    ErrLock;
uint8  UpErr;
/************************************************************
*
* 功能说明:
************************************************************/
void ErrDis(void)
{
  if(!ErrCon){
    DispDataSet = &ClrDisp;
    CancelAllFlash(0);
  }
  if(!ErrDisFlh){
    DispDct1  = _E_;
    DispDct2  = ErrCon;
  }
  DispLed = 0;
}
/************************************************************
*
* 功能说明:  错误分离检测
************************************************************/
void ErrTest(void)
{
  uint8 ErrBuf;
 if(Standby){
  if(AdReady){
    ErrBuf = 0;
    if(HeatLock){ErrBuf |= 1;}
	if(GoErrCon){ErrBuf |= 2;}
	if(NtcErr)  {ErrBuf |= 4;}
    if(ErrBuf){
      if(!(UpErr&ErrBuf)){
        UpErr = ErrBuf;
        if(ErrBuf & 0x01){ErrCon = 3;}else
        if(ErrBuf & 0x02){ErrCon = 1;}else
        if(ErrBuf & 0x04){ErrCon = 2;}
        ErrDisIni();
        Hidden = 1;
        DispDataSet = &ErrDis;
      }
    }else{
      UpErr  = 0;
      ErrCon = 0;
    }
  }else
  ErrCon = 0;
 }
}
/************************************************************
*
* 		  跳制保护检测
************************************************************/
// void Int1Isr_ErrTest(void) INT0
// {
//   IE0  = 0;
//   GoErrCount++;
//   if(GoErrCount > 80)
//   GoErrCount    = 90;
// }
