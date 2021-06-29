#ifndef __Disp_H__
#define __Disp_H__

extern bit   BiGuangCon;

extern uint8 DispSensFreq;
extern uint8 DispDct1;
extern uint8 DispDct2;
extern uint8 DispLed;
extern void (*DispDataSet)();
extern void  Disp( void );
extern void  ClrDisp( void );


#endif