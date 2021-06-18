#ifndef __TIMER2_H__
#define __TIMER2_H__
//--------------------------
#ifdef TIMER2_EN
//--------------------
extern bit   HeaterSec;
//--------------------
//extern bit   HeatTest;
//extern u8 TestNtcTimer;
//----------------------
extern bit  AdNtcNew;
extern u16  AdNtcValue;
//-----------------------
extern bit  KeyNew;
extern u8   AdKeyValue;
//----------------------
extern bit  AdVrNew;
extern u8   AdVrValue;
//-----------------------
extern bit NewDis;
extern u8 UpKeyValue;
extern u8 PcbKeyValue;
extern u8 InitKeyTime;
extern unsigned long Sys_Time;

extern void Timer2Init(void);
#endif
//--------------------------
#endif