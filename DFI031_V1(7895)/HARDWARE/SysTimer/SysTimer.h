#ifndef __SYS_TIMER_H__
#define __SYS_TIMER_H__
//--------------------
extern bit   HeaterSec;
//--------------------
extern bit   HeatTest;
extern U8 TestNtcTimer;
//----------------------
extern bit  AdNtcNew;
extern U16  AdNtcValue;
//-----------------------
#if (IO_AD_KEY_OTP == 0)
extern bit  KeyNew;
#else
extern bit  AdKeyNew;
extern U8   AdKeyValue;
#endif
//----------------------
extern bit  AdVrNew;
extern U8   AdVrValue;
//-----------------------
extern bit   LockWoodCon;	  //加执上锁试图加热闪烁温度单位
extern bit   LockWoodFah;
//--------------------
extern bit   GoErrCon;
extern U8  GoErrCount;

extern void LookFlhWood(void);
extern void KeySaveDat(void);
extern void SysTimer50ms(void);
extern void GoErrTestInit(void);
//-----------------------
#endif
