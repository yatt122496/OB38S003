#ifndef __DOW_KEY_H__
#define __DOW_KEY_H__

extern u8 DowGears;
#if (LUM_EN==1)
extern u8 DowLum;
//extern u8 DowAS;
#endif

extern void    DowKey(void);
extern void    DowDisp(void); 
#if (LUM_EN==1)
extern void    DowLumDisp(void);
//extern void    DowASDisp(void);
#endif
extern void    DowAutoKey(void);

#endif