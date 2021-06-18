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
#ifdef TIMER0_EN
//-------------------------------
void Timer0Init(void)
{
//   //-----------------------------
//   #define T0_FD      12
//   #define T0_FREQ	 5000  	//200us
//   //-----------------------------
//   //   	  bit7   bit6    bit5     bit4	  bit3    bit2	  bit1   bit0
//   //TMOD    GATE1  C/T1    M11      M10     GATE0   C/T0    M01    M00
//   //TCON    TF1    TR1     TF0      TR0     IE1     IT1     IE0    IT0
//   //TCON1   --     TCLKS1  TCLKS0   --	    TCLKP1  TCLKP0  TC1    TC0

//   TMOD &= Bin(11110000);
//   TCON &= Bin(11001111);
//   //-----------------------------
// #ifdef  REG79F083A_H
//   TCON1&=~Bin(00100000);
// #endif
//   //-----------------------------
// #ifdef  REG79F084A_H
//   TCON1&=~Bin(00100000);
// #endif
//   //-----------------------------
//   TMOD |= Bin(00000010);
//   //-----------------------------
//   TH0   = ((65536-(SCLK/T0_FD/T0_FREQ)))%256;
//   TL0   = ((65536-(SCLK/T0_FD/T0_FREQ)))%256;
//   //-----------------------------
//   IntSet(TIMER0,0,1);
//   //-----------------------------
//   TCON |= Bin(00010000);
  	TMR_ConfigRunMode(TMR0, TMR_MODE_TIMING,TMR_TIM_16BIT);
	TMR_ConfigTimerClk(TMR0, TMR_CLK_DIV_4);					/*Fsys = 8Mhz，Ftimer = 2Mhz,Ttmr=0.5us*/
	TMR_ConfigTimerPeriod(TMR0, (d_MODEVALUE_T0-d_RELOADVALUE_T0) >> 8, (d_MODEVALUE_T0-d_RELOADVALUE_T0)); 		// 10us,递增计数
	TMR_EnableOverflowInt(TMR0);
	IRQ_SET_PRIORITY(IRQ_TMR0,IRQ_PRIORITY_HIGH);
}

void Timer0Isr(void)  interrupt TMR0_VECTOR
{
  TH0   = (d_MODEVALUE_T0-d_RELOADVALUE_T0) >> 8;
	TL0   = (d_MODEVALUE_T0-d_RELOADVALUE_T0);
  IrCnt();
}
#endif