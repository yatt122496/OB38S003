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
#include "HARDWARE\Lib\inc\timer.h"
//-------------------------------
#ifdef TIMER1_EN
//-------------------------------
void Timer1Init(void)
{
  //-----------------------------
  #define T1_FD      12
  #define T1_FREQ	 10  	//100Ms
//   //-----------------------------
//   //   	  bit7   bit6    bit5     bit4	  bit3    bit2	  bit1   bit0
//   //TMOD    GATE1  C/T1    M11      M10   GATE0   C/T0    M01    M00
//   //TCON    TF1    TR1     TF0      TR0   IE1     IT1     IE0    IT0
//   //TCON1   --     TCLKS1  TCLKS0   --	  TCLKP1  TCLKP0  TC1    TC0
//   TMOD &= Bin(00001111);
//   TCON &= Bin(00111111);
//   //-----------------------------
// #ifdef  REG79F083A_H
//   TCON1&=~Bin(01000000);
// #endif
//   //-----------------------------
// #ifdef  REG79F084A_H
//   TCON1&=~Bin(01000000);
// #endif
//   //-----------------------------
//   TMOD |= Bin(00010000);
// //  TCON1|= Bin(00000000);
// //  TCON |= Bin(00000000);
// //  //-----------------------------
// //  TH1   = ((65536-(SCLK/T1_FD/T1_FREQ)-1))/256;
// //  TL1   = ((65536-(SCLK/T1_FD/T1_FREQ)-1))%256;
// //  //-----------------------------
//   IntSet(TIMER1,2,1);
	TMR_ConfigRunMode(TMR1, TMR_MODE_TIMING,TMR_TIM_16BIT);
	TMR_ConfigTimerClk(TMR1, TMR_CLK_DIV_4);				/*Fsys = 8Mhz，Ftimer = 2Mhz,Ttmr=0.5us*/
	// TMR_ConfigTimerPeriod(TMR1, (d_MODEVALUE_T1-d_RELOADVALUE_T1) >> 8, (d_MODEVALUE_T1-d_RELOADVALUE_T1)); // 50us,递增计数
	// TMR_EnableOverflowInt(TMR1);
	IRQ_SET_PRIORITY(IRQ_TMR1,IRQ_PRIORITY_LOW);
}

void Timer1Isr(void)  interrupt TMR1_VECTOR
{
//   TF1 = 0;
  FlaOff();
}
#endif