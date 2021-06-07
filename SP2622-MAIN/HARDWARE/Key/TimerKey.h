#ifndef __TIMER_KEY_H__
#define __TIMER_KEY_H__
//--------------------
extern bit   TimerCon;
extern uint8 MsTimer;
extern uint8 clk[3]; //时间缓存  ： clk[2]小时，clk[1]分钟，clk[0]秒，
//--------------------
extern void TimDisp( void );
extern void TimKey( void );
extern void TimerOff(void);
//--------------------
extern void ClrTmr(void);
//--------------------
#endif