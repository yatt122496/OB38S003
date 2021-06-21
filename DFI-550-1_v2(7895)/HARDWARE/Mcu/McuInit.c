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
#include "HARDWARE\Lib\inc\epwm.h"
#include "HARDWARE\Lib\inc\adc.h"
#include "HARDWARE\Lib\inc\gpio.h"
#include "HARDWARE\Lib\inc\timer.h"
#include "HARDWARE\Lib\inc\system.h"
#include "HARDWARE\Lib\inc\wdt.h"
#include "HARDWARE\Lib\inc\extint.h"
//--------------------
void McuInit(void)
{
	SysClkInit();
#if WDT_SWITCH
	// 开启WDT溢出时间,Fsys=24Mhz -> Twdt = 4194304/24 = 174.76ms
	WDT_ConfigOverflowTime(WDT_CLK_4194304);
	//设置WDT溢出中断
	WDT_EnableOverflowInt();
	SYS_EnableWDTReset(); //开启看门狗复位功能,CONFIG中设置SOFTWARECONTROL(软件控制)
#endif
	P0TRIS = 0;
	P1TRIS = 0;
	P2TRIS = 0;
	P3TRIS = 0;
	/*  IO  */
	//   	  bit7   bit6    bit5     bit4	  bit3    bit2	  bit1   bit0
	//P0
	//P1
	//P2
	//P3
	//---------
#ifdef REG79F1622_H
	P0 = Bin(00000000);	   //P0口
	P0CR = Bin(00000000);  //方向控制，1：输出，0：输入，
	P0PCR = Bin(00000000); //上拉电阻，1：上拉，0：不拉
	//---------
	P1 = Bin(00000000);	   //P1口
	P1CR = Bin(00000000);  //方向控制，1：输出，0：输入，
	P1PCR = Bin(00000000); //上拉电阻，1：上拉，0：不拉
	//---------
	P2 = Bin(00000000);	   //P2口
	P2CR = Bin(00000000);  //方向控制，1：输出，0：输入，
	P2PCR = Bin(00000000); //上拉电阻，1：上拉，0：不拉
	//---------
	P3 = Bin(00000000);	   //P3口
	P3CR = Bin(00000000);  //方向控制，1：输出，0：输入，
	P3PCR = Bin(00000000); //上拉电阻，1：上拉，0：不拉
#endif
	//---------
#ifdef REG79F083A_H
	// P1 = Bin(00000000);
	P05 = 0; P11 = 0; P30 = 0; P12 = 0;
	P22 = 0; P21 = 0; P20 = 0; P17 = 0;
	// P1M0 = Bin(11111111);
	// P1M1 = Bin(00000000);
	P05CFG = GPIO_MUX_GPIO;
	P11CFG = GPIO_P11_MUX_AN9;
	P30CFG = GPIO_MUX_GPIO;
	P12CFG = GPIO_P12_MUX_AN10;
	P22CFG = GPIO_MUX_GPIO;
	P21CFG = GPIO_MUX_GPIO;
	P20CFG = GPIO_MUX_GPIO;
	P17CFG = GPIO_MUX_GPIO;//P06外部中断IR
	P0TRIS = (P0TRIS & ~((1 << 5))) | ((0));
	P1TRIS = (P1TRIS & ~((1 << 1) | (1 << 2) | (1 << 7))) | (0);
	P2TRIS = (P2TRIS & ~((1 << 0) | (1 << 1) | (1 << 2))) | (0);
	P3TRIS = (P3TRIS & ~((1 << 0))) | (0);
	//
	// P3 = Bin(00000100);
	P24 = 0; P25 = 0; P31 = 0; P04 = 0;
	P00 = 0; P02 = 0;	 	   P03 = 0;
	// P3M0 = Bin(11111111);
	// P3M1 = Bin(00000000);
	P24CFG = GPIO_MUX_GPIO;
	P25CFG = GPIO_MUX_GPIO;
	P31CFG = GPIO_MUX_GPIO;
	P04CFG = GPIO_MUX_GPIO;
	P00CFG = GPIO_MUX_GPIO;
	P02CFG = GPIO_MUX_GPIO;

	P03CFG = GPIO_MUX_GPIO;
	P0TRIS = (P0TRIS & ~((1 << 0) | (1 << 2) | (1 << 3) | (1 << 4))) | (0);
	// P1TRIS = (P1TRIS & ~((0))) | ((0));
	P2TRIS = (P2TRIS & ~((1 << 4) | (1 << 5))) | ((0));
	P3TRIS = (P3TRIS & ~((1 << 1))) | ((0));
	//
	// P4 = Bin(00000000);
	P23 = 0; P33 = 0; P32 = 0;
	// P4M0 = Bin(11111111);
	// P4M1 = Bin(00000000);
	P23CFG = GPIO_MUX_GPIO;
	P33CFG = GPIO_MUX_GPIO;
	P32CFG = GPIO_MUX_GPIO;

	// P0TRIS = (P0TRIS & ~((0))) | ((0));
	// P1TRIS = (P1TRIS & ~((0))) | ((0));
	P2TRIS = (P2TRIS & ~((1 << 3))) | (0);
	P3TRIS = (P3TRIS & ~((1 << 2) | (1 << 3))) | (0);
#endif
	//---------
#ifdef REG79F084A_H
	P1 = Bin(00000000);
	P1M0 = Bin(11111111);
	P1M1 = Bin(00000000);
	//
	P3 = Bin(00000000);
	P3M0 = Bin(11111111);
	P3M1 = Bin(00000000);
	//
	P4 = Bin(00000000);
	P4M0 = Bin(11111111);
	P4M1 = Bin(00000000);
#endif
//
#ifdef TIMER0_EN
	Timer0Init();
#endif
//---------
#ifdef TIMER1_EN
	Timer1Init();
#endif
//---------
#ifdef TIMER2_EN
	Timer2Init();
#endif
//---------
#ifdef TIMER3_EN
	Timer3Init();
#endif
//---------
#ifdef TIMER4_EN
	Timer4Init();
#endif
//---------
#ifdef EUART_EN
	EuartInit();
#endif
//---------
#ifdef INT0_EN
	Int0Init();
#endif
//---------
#ifdef INT1_EN
	Int1Init();
#endif
//---------
#ifdef INT2_EN
	Int2Init();
#endif
//---------
#ifdef PWM_EN
	PwmInit();
#endif
	// IRQ_ALL_ENABLE();							 //开启总中断
	TMR_Start(TMR0);
	// TMR_Start(TMR1);
	TMR2_Start();
	ADC_Start();
	ADC_GO();
	//  EA = 1;
}