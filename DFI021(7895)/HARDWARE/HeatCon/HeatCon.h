#ifndef __HEATER_CONTROL_H__
#define __HEATER_CONTROL_H__

extern bit HotOnOff;
extern bit MotDelayOff;

extern void HeatCon( void );

extern void Hot3min(void);
extern void HotWait(void);
extern void TsetHot(void);

#endif