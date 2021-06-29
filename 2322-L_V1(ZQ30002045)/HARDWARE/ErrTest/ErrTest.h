#ifndef __ERR_TEST_H__
#define __ERR_TEST_H__
//----------------------
extern bit    GoErrCon;
//----------------------------
extern uint8  GoErrCount;
//----------------------
extern uint16 NtcErrDat;
//----------------------
extern uint8  ErrCon;
//----------------------
extern void ErrTest(void);
extern void GoErrTestInit(void);
//----------------------
#endif