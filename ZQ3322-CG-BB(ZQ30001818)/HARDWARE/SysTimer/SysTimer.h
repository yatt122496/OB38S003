#ifndef __SYS_TIMER_H__
#define __SYS_TIMER_H__
//--------------------
extern bit   Hidden;
extern uint8 HiddenTimer;
//extern uint8 TempSwFlashTimerCon;
//-----------------------
//extern bit   LockWoodCon;	  //加执上锁试图加热闪烁温度单位
//extern bit   LockWoodFah;

extern bit   BiGuangCon;
//--------------------
//extern bit   TempSwFlash;
extern bit   FunEndFlash;
//--------------------	
extern bit   HeaterSec;
//--------------------
extern bit   HeatTest;
extern uint8 TestNtcTimer;
//-----------------------
extern bit   AdKeyNew;
extern uint8 AdKeyValue;
//-----------------------
extern bit    AdNtcNew;
extern uint16 AdNtcValue; 
//-----------------------
extern bit    ErrFlashCon;
//-----------------------
extern void CancelAllFlash(bit NoFlhWood);
extern void FunEndFlashSet(void);
extern void LookFlhWood(void);
//extern void TempSwFlashSet(void);
extern void SysTimer50ms(void);
//-----------------------
extern bit   ErrDisCon,ErrDisFlh;
extern void ErrDisIni(void);
extern void ErrDis(void);
//-----------------------
//extern void BzSet(void);
extern void TestClrMin(void);
//-----------------------
#endif
