#ifndef __TIMER_KEY_H__
#define __TIMER_KEY_H__
//--------------------
extern bit   TimerCon;
extern uint8 MsTimer;
extern uint8 clk[3]; //ʱ�仺��  �� clk[2]Сʱ��clk[1]���ӣ�clk[0]�룬
//--------------------
extern void TimDisp( void );
extern void TimKey( void );
extern void TimerOff(void);
//--------------------
extern void ClrTmr(void);
//--------------------
#endif