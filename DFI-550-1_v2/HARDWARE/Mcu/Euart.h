#ifndef __EUART_H__
#define __EUART_H__
//--------------------
#ifdef EUART_EN
extern bit RxFinish;
extern u8 data RxDat;
//--------------------
extern u8 TxTimer; 
extern u8 TxErrTimer;
extern u8 xdata DatBuf[16];
//--------------------
extern void EuartInit(void);
extern void UartTxDat(void);
#endif
//--------------------
#endif