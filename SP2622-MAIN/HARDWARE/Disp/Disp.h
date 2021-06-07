#ifndef __DISP_H__
#define __DISP_H__
//--------------------------
extern uint8       DispDct1;
extern uint8       DispDct2;
extern uint8       DispDct3;
extern uint8 bdata DispLed;
//--------------------------
extern bit LedPow;
extern bit LedFla;
extern bit LedHea;
extern bit LedTmr;
extern bit LedTc;
extern bit LedTf;
extern bit LedSec;
//--------------------------
extern void (*DispDataSet)();
//--------------------------
extern uint8 PcbKeyValue;
extern uint8 DispSensFreq;
//--------------------------
extern void Disp( void );
extern void ClrDisp(void);
extern void DispInit(void);
//--------------------------
#endif