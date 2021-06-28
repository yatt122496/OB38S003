#ifndef __HEAT_CON_H__
#define __HEAT_CON_H__

//extern bit   WaitDisp_F0_;
extern bit   HotOnOff;
extern bit   MotDelayOff;

extern void HeatCon( void );
//extern void Heat3min(void);
//extern void TsetHeat(void);
extern uint16 OnfHeaTmr;
extern void HeaClr1min(void);

extern bit HeaInit;//≈–∂œ≥ı¥Œ…œµÁ

#endif