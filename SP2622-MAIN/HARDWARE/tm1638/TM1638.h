#ifndef __tm1638_H__
#define __tm1638_H__




extern void TM1638_Init( void );
//1638 DISP
extern void  WriteTm1638Data(uint8 Len,uint8 *PData);

//1638 ON OR OFF
extern void OnOrOff(uint8 OnOffDat);

extern void ReadKey(uint8 *PKeyDat);



#endif







