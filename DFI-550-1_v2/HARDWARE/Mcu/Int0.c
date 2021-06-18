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
#ifdef INT0_EN
//-------------------------------
void Int0Init(void)
{
  //-----------------------------
  //   	  bit7   bit6    bit5     bit4	  bit3    bit2	  bit1   bit0
  //TCON    --     --      --       --      --      --     IE0    IT0
  //-----------------------------
//   TCON &=~Bin(00000011);
//   TCON |= Bin(00000001);
//   //-----------------------------
//   IntSet(INT0,2,1);
//   //-----------------------------
//   P3    |= Bin(00000100);
//   P3M0  &=~Bin(00000100);
	P31CFG = GPIO_MUX_GPIO;
	P3TRIS &= ~(1 << 1);
	P31EICFG = 0x02;
	P3EXTIE |= 2;
	IRQ_SET_PRIORITY(IRQ_P3,IRQ_PRIORITY_HIGH);
  //
}

// void Int0Isr(void) interrupt INT0
// {
//   IE0 = 0;
//   FlaZoOn();
// }
#endif