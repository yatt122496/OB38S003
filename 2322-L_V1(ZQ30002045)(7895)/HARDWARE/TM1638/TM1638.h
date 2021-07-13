#ifndef __tm1638_H__
#define __tm1638_H__
extern void TM1638_Init( void );
//1638 DISP
extern void  WriteTm1638Data(unsigned char *PData);
//1638 ON OR OFF
extern void OnOrOff(unsigned char OnOffDat);
//extern void ReadKey(unsigned char *PKeyDat);
#endif
