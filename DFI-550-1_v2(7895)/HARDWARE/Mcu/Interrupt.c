/***********************************************************
*
************************************************************
*  日期:
*
*  作者:
*
************************************************************
*  硬件：  SH79F1622
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\include\SysInc.h"
//-------------------------------
#ifdef  REG79F1622_H
u8  code IntList[]=
{
  0x01,	 //INT0		0
  0x02,	 //TK		1
  0x04,	 //INT1		2
  0x00,	 // --		3
  0x10,	 //EUART	4
  0x20,	 //TIMER2	5
  0x00,	 // --		6
  0x01,	 //TIMER4	7
  0x02,	 //INT2		8
  0x04,	 //INT4		9
  0x08,	 //TWI		10
  0x10,	 //TIMER3	11
};
#endif
#ifdef  REG79F083A_H
u8  code IntList[]=
{
  0x01,	 //INT0		0
  0x02,	 //TIMER0	1
  0x04,	 //INT1		2
  0x08,	 //TIMER1   3
  0x10,	 //EUART	4
  0x20,	 //TIMER2	5
  0x40,	 //ADC		6
  0x00,	 //-- 	    7
  0x00,	 //-- 	    8
  0x04,	 //INT2		9
  0x00,	 //--		10
  0x10,	 //SCM		11
  0x20,	 //PWM		12
  0x00,	 //--		13
  0x80,	 //LPD   	14
};
#endif
#ifdef  REG79F084A_H
u8  code IntList[]=
{
  0x01,	 //INT0		0
  0x02,	 //TIMER0	1
  0x04,	 //INT1		2
  0x08,	 //TIMER1   3
  0x10,	 //EUART	4
  0x20,	 //TIMER2	5
  0x40,	 //ADC		6
  0x00,	 //-- 	    7
  0x00,	 //-- 	    8
  0x04,	 //INT2		9
  0x00,	 //--		10
  0x10,	 //SCM		11
  0x20,	 //PWM		12
  0x00,	 //--		13
  0x80,	 //LPD   	14
};
#endif
/*no interrupt
	  	 		 Bit7	Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
  IEN0       EA     --    ET2   ES    --    EX1   TKIE  EX0
  IEN1       --     --    --    ET3   ETWI  EX4   EX2   ET4
  IENC       EXS47  EXS46 EXS45 EXS44 EXS43 EXS42 EXS41 EXS40
  EXF0		 IT4.1  IT4.0 --    --    IT2.1 IT2.0 --	IE2
  EXF1       --     --    --    --    IF43  IF42  IF41  IF40
*/
// void IntSet(u8 IntOtp,u8 Prio,u8 En)
// {
//   u8 DatBuf;
//   u8 IpHbuf,IpLbuf;
// #ifdef  REG79F1622_H
//   if(Prio < 4 && IntOtp < 12)
// #endif
// #ifdef  REG79F083A_H
//   if(Prio < 4 && IntOtp < 15)
// #endif
// #ifdef  REG79F084A_H
//   if(Prio < 4 && IntOtp < 15)
// #endif
//   {
//     DatBuf = IntList[IntOtp];
// 	if(IntOtp < 7){IpHbuf = IPH0;IpLbuf = IPL0;}
// 	else          {IpHbuf = IPH1;IpLbuf = IPL1;}
// 	//
// 	if(Prio == 0)
// 	{
// 	  IpHbuf &= ~DatBuf;
// 	  IpLbuf &= ~DatBuf;
// 	}else
// 	if(Prio == 1)
// 	{
// 	  IpHbuf &= ~DatBuf;
// 	  IpLbuf |=  DatBuf;
// 	}else
// 	if(Prio == 2)
// 	{
// 	  IpHbuf |=  DatBuf;
// 	  IpLbuf &= ~DatBuf;
// 	}else
//     if(Prio == 3)
// 	{
// 	  IpHbuf |=  DatBuf;
// 	  IpLbuf |=  DatBuf;
// 	}
// 	//------------
// 	if(IntOtp < 7)
// 	{
// 	  IPH0  = IpHbuf;
// 	  IPL0  = IpLbuf;
// 	  IEN0 &= ~DatBuf;
// 	  if(En)
// 	  IEN0 |=  DatBuf;
// 	}else
// 	{
// 	  IPH1  = IpHbuf;
// 	  IPL1  = IpLbuf;
// 	  IEN1 &= ~DatBuf;
// 	  if(En)
// 	  IEN1 |=  DatBuf;
// 	}
// 	//------------
//   }
// }