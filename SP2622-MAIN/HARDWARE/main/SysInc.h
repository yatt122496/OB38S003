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
#include "OB38S003.h"
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
//-----------------------
#define  HOT   P0_0//P1_3
#define  FAN   P0_2//P1_1
//-----------------------
#define  MOT   P0_1//P1_0
//#define  NC    P1_4
//#define  NC    P1_5
//#define  YLOT  P1_5
#define  DOT   P1_7//P3_7
#define  FOT   P1_2//P3_4
#define  DWL   P0_3//P3_3
//-----------------------
#define  IR    P1_4//P1_2
//
#define  BZ    P1_6//P3_5
#define	 BZ_ON()  {PWMC |= 0x1;}
#define	 BZ_OF()  {PWMC &= 0xfe;}
//-----------------------
//	IIC 通讯
#define UART_TEST 0
#if UART_TEST
#define IR_TEST 1
#else
#define IR_TEST 0
#endif
#if UART_TEST
#define  SCL    P1_7//P3_0	//TM1638总线时钟
#define  SDA    P1_7//P3_1	//TM1638总线数据
#define  SDA_PIN_IN()  P1_7 = 1;
#define  SDA_PIN_OUT() P1_7 = 1;
#else
#define  SCL    P1_1//P3_0	//TM1638总线时钟
#define  SDA    P1_0//P3_1	//TM1638总线数据
#define  SDA_PIN_IN()  P1_0 = 1;
#define  SDA_PIN_OUT() P1_0 = 1;
#endif

//-----------------------
//#define  NC     P3_3
//#define  NC     P3_4
//-----------------------
//#define  NTC   P1_4
#define AN0   0
#define AN1   1
#define AN2   2
#define AN3   3
#define AN4   4
#define AN5   5
#define AN6   6
#define AN7   7
//-----------------------
#define NTC   AN4
//-----------------------
#define AD_CH     (1<<NTC)
#define AD_CH_OTP ((NTC << 1) | 0X81)
#define AD_TIME 0XEF
//-----------------------
/************************************************************
*函数名:
*功能说明:
************************************************************/
#define FOSC     8000000L
#define SCLK	 (FOSC / 2)
//-----------------------------
#define T0_FD    12
#define T0_FREQ	 5000	//200us
//-----------------------------
#define T1_FD    12
#define T1_FREQ	 100	//1ms
//-----------------------------
#define T2_FD    12
#define T2_FREQ	 1000  	//10ms
//-----------------------------
#define PWM_FD   8
#define PWM_FREQ 4000   //250us
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
#define INT0		   0
#define TIMER0_VECTOR  1    //TIMER0 Interrupt Vevtor
#define	INT1 		   2
#define TIMER1_VECTOR  3    //TIMER1 Interrupt Vevtor
#define TIMER2_VECTOR  5      //TIMER0 Interrupt Vevtor

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
#include "WDT.h"
#include "HARDWARE\Initial\Initial.h"
//-----------------------
#include "HARDWARE\Ir\Ir.h"
//-----------------------
#include "HARDWARE\Key\Key.h"
#include "HARDWARE\Key\PowerKey.h"
#include "HARDWARE\Key\FlaKey.h"
#include "HARDWARE\Key\HeatKey.h"
#include "HARDWARE\Key\TimerKey.h"
//#include "HARDWARE\Key\SysRest.h"
#include "HARDWARE\Key\TempProcKye.h"
#if (DWL_EN==1)
#include "HARDWARE\Key\DwlKey.h"
#endif
#include "HARDWARE\IIC\IIC.h"
//#include "HARDWARE\Uart\Uart.h"
//#include "HARDWARE\Key\GainKeyValue.h"
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
#if UART_TEST
#include "UART0.h"
#endif
//-----------------------
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

extern unsigned int n_data;
extern bit          ADCfinish;

extern unsigned long Sys_Time;
// extern unsigned short wIr_time;
// extern unsigned char indx;
// extern xdata unsigned short wData[40];

#endif