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
#ifdef TIMER4_EN
//-------------------------------
void Timer4Init(void)
{
  //-----------------------------
  #define T4_FD      12
  #define T4_FREQ	 200	//5ms
  //-----------------------------
  /*Timer   0 , 1   */
  //   	    bit7   bit6    bit5     bit4	bit3    bit2	 bit1  bit0
  //T4CON    TF4    TC4    T4PS1    T4PS0   T4M1    T4M0     TR4   T4CLKS
  //TL4
  //TH4
  T4CON = Bin(00100010);
  TL4   = (65536-(SCLK/T4_FD/T4_FREQ))%256-1;
  TH4   = (65536-(SCLK/T4_FD/T4_FREQ))/256;
  IntSet(TIMER4,0,1);
}


void Timer4Isr(void) interrupt TIMER4
{
  T4CON &= ~Bin(10000000);

}
#endif