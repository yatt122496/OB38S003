#ifndef __SYS_INC_H__
#define __SYS_INC_H__
/*****************************************************************
                   |``````:_:``````|
        INT0/P3.2--|1		     20|--P4.2/TXAL1
    	           |			   |
        INT1/P3.3--|2			 19|--P4.1/TAXL2
   	               |               |
          T0/P3.4--|3			 18|--P3.1/TXD
	               |			   |
      PWM/T1/P3.5--|4			 17|--P3.0/RXD
	               |    引脚配置	   |
              GND--|5			 16|--P4.0/RESET
		           |   SH79F083	   |
             P3.7--|6			 15|--VDD
                   |			   |
         AN0/P1.0--|7			 14|--P1.7/T2/AN7
		       	   |			   |
         AN1/P1.1--|8			 13|--P1.6/T2EX/AN6
			       |			   |
TDD/AN2/INT2/P1.2--|9			 12|--P1.5/AN5/TCK
			       |			   |
TMS/AN3/VLPD/P1.3--|10			 11|--P1.4/AN4/TDI
			       |_ _ _ _ _ _ _ _|

                   |``````:_:``````|
GO_TEST/INT0/P3.2--|1		     20|--P4.2/TXAL1 \
    	           |			   |               32768
         DWL/P3.3--|2			 19|--P4.1/TAXL2 /
   	               |               |
         FOT/P3.4--|3			 18|--P3.1/TX
	               |			   |
          BZ/P3.5--|4			 17|--P3.0/RX
	               |    引脚配置	   |
              GND--|5			 16|--P4.0/NC
		           |   SH79F083	   |
         DOT/P3.7--|6			 15|--VDD
                   |			   |
         MOT/P1.0--|7			 14|--P1.7/NC
		       	   |			   |
         FAN/P1.1--|8			 13|--P1.6/NC
			       |			   |
     IR/INT2/P1.2--|9			 12|--P1.5/NC
			       |			   |
         HOT/P1.3--|10			 11|--P1.4/NTC
			       |_ _ _ _ _ _ _ _|
******************************************************************/
/************************************************************
*函数名:
*功能说明:
************************************************************/
#include "cms8s78xx.h"
#include <INTRINS.H>
#include <math.h>

#include "type.h"
#include "EF_II033_Inc.h"
#include "IncError.h"

#define  _A_  10
#define  _B_  11
#define  _C_  12
#define  _D_  13
#define  _E_  14
#define  _F_  15
#define  DOFF 16

#define  DISP_OFF	16
#define  _h_		17
#define  _N_		18
#define  _I_		19
#define  _H_		20
/************************************************************
*函数名:
*功能说明:  I/O引脚备置
************************************************************/
#define UART_TEST			0
#define CONFIG_ZERO_CHECK	1
#define WDT_SWITCH			1

#if UART_TEST
#define IR_TEST				1
#else
#define IR_TEST	0
#endif
//-----------------------
#define  MOT      P24//P3_0
#define  FAN      P25//P3_1
#define  HOT      P33//P4_1
//-----------------------
#define  DOT   P05//P1_0
#define  DOT1  P23//P4_0
#define  FOT   P17//P1_7
#define  DWL   P20//P1_6

#define  TEST  P20//P1_6
//-----------------------
#define  IR    P30//P1_2
//
//#define  BZ    P3_5
//#define	 BZ_ON()  {P3M0&=~Bin(00100000);P3M1|= Bin(00100000);}
//#define	 BZ_OF()  {P3M0|= Bin(00100000);P3M1&=~Bin(00100000);}
//-----------------------
//	IIC 通讯
#define  STB      P04//P3_3
#define  CLK      P00//P3_4
#define  DIO      P01//P3_5
//-----------------------
#define  AD_NTC	   0x87 //P1_3 AN3			P12 an10
#define  AD_KEY	   0x83	//P1_1 AN1			P11 an9
//-----------------------
/************************************************************
*函数名:
*功能说明:
************************************************************/
#define FOSC     16600000L
#define SCLK	 (FOSC)
//-----------------------------
#define T0_FD    12
#define T0_FREQ	 5000	//200us
//-----------------------------
#define T1_FD    12
#define T1_FREQ	 100	//10ms
//-----------------------------
#define T2_FD    12
#define T2_FREQ	 1000  	//1ms
//-----------------------------
//#define PWM_FD   8
//#define PWM_FREQ 4000   //250us
/************************************************************
*函数名:
*功能说明:  I/O引脚备置
************************************************************/
#define  K2_POW        0x01
#define  K2_HEA        0x02
#define  K2_FLA		   0x04
#define  K2_TIM		   0x08
#define  K2_DWL        0x10
/************************************************************
*函数名:
*功能说明:  I/O引脚备置
************************************************************/
#define  LED_F	    0x02
#define  LED_C	    0x04
//LED1
#define  POW_LED	0x01
//LED
#define  TMR_LED	0x10
#define  HEA_LED	0x04
#define  FLA_LED	0x08
#define  DWL_LED	0x01
/************************************************************
*函数名:
*功能说明:  中断向量表
************************************************************/
#define d_MODEVALUE_T0      65536     //MODE1 16bit 65536
#define d_RELOADVALUE_T0    120      //User Define Reload Value
#define d_MODEVALUE_T1      65536    //MODE1 16bit 65536
#define d_RELOADVALUE_T1    20000      //User Define Reload Value
#define d_MODEVALUE_T2      65536
#define d_RELOADVALUE_T2    2000 //User Define Reload Value
// #define   INT0    interrupt  0
// #define	  TIMER0  interrupt  1
// #define	  INT1    interrupt  2
// #define	  TIMER1  interrupt  3
// #define	  EUART   interrupt  4
// #define	  TIMER2  interrupt  5
// #define	  ADC     interrupt  6
// #define	  INT2	  interrupt	 9
// #define	  SCM	  interrupt	 11
// #define	  PWM	  interrupt	 12
// #define	  LPD     interrupt	 13
/************************************************************
*函数名:
*功能说明:
************************************************************/
//-----------------------
#include "HARDWARE\Initial\Initial.h"
//-----------------------
#include "HARDWARE\Ir\Ir.h"
//-----------------------
#include "HARDWARE\Key\Key.h"
#include "HARDWARE\Key\PowerKey.h"
#include "HARDWARE\Key\FlaKey.h"
#include "HARDWARE\Key\HeatKey.h"
#include "HARDWARE\Key\TimerKey.h"
#include "HARDWARE\Key\TempProcKye.h"
#if (DWL_EN==1)
#include "HARDWARE\Key\DwlKey.h"
#endif
//
#include "HARDWARE\Tm1638\Tm1638.h"
//-----------------------
#include "HARDWARE\Disp\Disp.h"
//-----------------------
#include "HARDWARE\SysTimer\SysTimer.h"
//-----------------------
#include "HARDWARE\FlaCon\FalCon.h"
#include "HARDWARE\HeatCon\HeatCon.h"
//-----------------------
#include "HARDWARE\Ad\Ad.h"
//-----------------------
#include "HARDWARE\ErrTest\ErrTest.h"
//-----------------------
#include "HARDWARE\Key\GainAdKeyValue.h"
/************************************************************
*函数名:
*功能说明:
************************************************************/
extern uint8 TestKeyBuf;
extern uint8 UpPowerTest;
extern uint8 Test0x5a;
extern bit   DBugBit;
extern bit   CancelErrDispEc;


extern uint8 Disturb0xAA;
extern uint8 Disturb0x55;

#if WDT_SWITCH
#include "HARDWARE\Lib\inc\wdt.h"
#endif

#endif