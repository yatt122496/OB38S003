#ifndef __SysTimer_H__
#define __SysTimer_H__
//----------------------------
extern bit    LockWoodCon;
extern bit    LockWoodFalsh; 
extern void   LookFlhWood(uint8 Otp);
//----------------------------
extern bit    AdKeyNew;
extern uint8  AdKeyValue; 
//----------------------------
extern bit    AdNtcNew;
extern uint16 AdNtcValue; 
//----------------------------
extern bit    Hidden;
extern uint8  HiddenTimer;
//----------------------------
extern bit    HeatTest;
extern bit    HeaterSec;
//----------------------------
extern bit    TempSwFah;
//----------------------------
extern bit    TempFlash;
extern uint8  idata TempFlashTimerCon;
//----------------------------
extern bit    ShowCon;
extern bit    ShowOnCon;
extern uint16 idata ShowTim;
//----------------------------
extern void   SysTimer(void);
//----------------------------
extern void   CancelAllFlash(uint8 Otp);
extern void   TempSwFahSet(void);
//----------------------------
#endif
