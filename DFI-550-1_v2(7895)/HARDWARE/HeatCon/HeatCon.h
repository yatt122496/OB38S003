#ifndef __HEAT_CON_H__
#define __HEAT_CON_H__
//
extern bit HotOnOff;
extern bit MotDelayOff;

extern void HeatInit(void);

extern void HeatCon( void );

extern void Hot3min(void);
extern void HotWait(void);
extern void TsetHot(void);
//
#endif