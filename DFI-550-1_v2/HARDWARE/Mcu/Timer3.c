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
#ifdef TIMER3_EN
//-------------------------------
void Timer3Init(void)
{
  //-----------------------------
  #define T3_FD      4000
  #define T3_FREQ	 64	//200us
  //-----------------------------
  /*Timer   3   */
  //   	  bit7   bit6    bit5     bit4	  bit3    bit2	  bit1   bit0
  //T3CON   TF3     --    T3PS.1   T3PS.0    --     TR3   T3CLKS.1 T3CLKS.0
  //TL3
  //TH3
  T3CON = Bin(00100000);
  TL3   = (65536-(SCLK/T3_FD/T3_FREQ))%256;
  TH3   = (65536-(SCLK/T3_FD/T3_FREQ))/256;
  IntSet(TIMER3,0,1);
  TR3   = 1;
}

void Timer3Isr(void) interrupt TIMER3
{
  static u8 Timer1ms;
  TF3 = 0;
  TouchStartIsr();

  Timer1ms++;
  if(Timer1ms > 39)
  {
    Timer1ms = 0;
	Autio1s = 1;
//	if(TxTimer)
//	TxTimer--;
//	if(TxErrTimer)
//	TxErrTimer--;
  }
}
#endif