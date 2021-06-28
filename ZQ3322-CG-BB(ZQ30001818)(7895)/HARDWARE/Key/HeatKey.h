#ifndef __HEAT_KEY_H__
#define __HEAT_KEY_H__
//----------------------------
extern bit   TcTf;
//extern bit   FirstHeat;
extern bit   HeatLock;
extern bit   HeatOnOff;
extern uint8 HeatGears;
extern bit GearWidth1F_En;   //µµÎ»5F/2C 1F/1C
extern uint8 Set5FGears;
extern uint8 Set1CGears;
extern uint8 code SetTcTable[];
//----------------------------
extern void TempDisp(void);
extern bit  GainHeaterPsw(void);
//extern void HeatKey(void);
extern void HeaKey(void);
extern void HeatKey(bit Opt);
extern void GearsWidthKey(void);
//----------------------------
extern void HeatDownKey(void);
//----------------------------
extern bit  TempSwCon;
extern void HeaLockSw( void );
extern void HeaClrCnt(void);
extern void CfDisp(void);
extern void ClrErrTmr(void);
//----------------------------
#endif