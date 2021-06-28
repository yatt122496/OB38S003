#ifndef __POWER_KEY_H__
#define __POWER_KEY_H__

extern bit   Standby;
extern uint8 KeyAct;

extern void  PowerDisp( void );
extern void  SysRst(void);
extern void  PowKey( void );

#endif