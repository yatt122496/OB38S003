#ifndef __PWM_H__
#define __PWM_H__
//--------------------------
#ifdef PWM_EN
extern bit BzTime50ms;
extern void PwmInit(void);
extern void BzSet(u8 Set);
extern void Bz(void);
#endif
//--------------------------
#endif
