#ifndef __FlaKey_H__
#define __FlaKey_H__

extern uint8   FlaGears;
#if (LUM_EN==1)
extern uint8   FlaLum;
#endif

extern void    FlaKey(void);
#if (LUM_EN==1)
extern void    FlaAutoKey(void);
#endif
extern void    GinFlaPsw(void);
extern void    FlaDisp(void); 

#endif