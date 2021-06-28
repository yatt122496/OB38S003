#ifndef __TempKey_H__
#define __TempKey_H__

extern bit     TcTf;
extern bit     SetTemp;
extern bit     HeaOnOff; 
extern bit     HeatLock; 
extern uint8   HeatGears;

extern uint8 code  SetTcTable[];

extern void HeatDisp(void); 
extern void HeatKey(bit PcbIr);
extern void GainHeaterPsw(void);
extern void HeatSetAndLook(void);
extern void TempSw(void);
extern void TempSetKey(void);

#endif
