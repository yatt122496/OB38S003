

#ifndef     __UART_H__
#define     __UART_H__

extern u8 idata TxDatTim;
extern u8 idata CfgTim;
extern bit TxNewDat;
//=============================================================================
// 
//=============================================================================
// ´®¿Ú³õÊ¼»¯
extern void UartInit(void);
extern u8   TxSetDat(u8 Len,u8 *pDat);
extern u8 PcbKeyValue;
extern void UartTo(void);
extern void TxClrLead(void);

#endif // end of __UART_H__





