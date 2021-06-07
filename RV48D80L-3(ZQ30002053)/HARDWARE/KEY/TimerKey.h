#ifndef __TimerKey_H__
#define __TimerKey_H__


extern bit     TimerCon;
extern uint8   clk[3];
//extern uint8   TimerGears;
extern bit T1s;
extern uint8   Tim1s;

extern void TimDisp(void);
extern void TimKey(void);
extern void TimerUp(void);
extern void TimerOff(void);
extern void TimerFun( void );

#endif