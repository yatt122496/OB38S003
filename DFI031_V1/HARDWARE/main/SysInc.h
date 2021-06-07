#ifndef __SYS_INC_H__
#define __SYS_INC_H__
/*****************************************************************
	                   |``````:_:``````|
	        INT0/P3.2--|1		     20|--P4.2/TXAL1
	    	           |			   |
	        INT1/P3.3--|2			 19|--P4.1/TAXL2
	   	               |			   |
	          T0/P3.4--|3			 18|--P3.1/TXD
		               |			   |
	      PWM/T1/P3.5--|4			 17|--P3.0/RXD
		               |   引脚配置	   |
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
	          NC/P3.2--|1		     20|--P4.2/HOT
	    	           |			   |
	          NC/P3.3--|2			 19|--P4.1/FAN
	   	               |			   |
	          NC/P3.4--|3			 18|--P3.1/TXD
		               |    DFI020     |
	          NC/P3.5--|4			 17|--P3.0/MOT
		               |   引脚配置	   |
	              GND--|5			 16|--P4.0/
			           |   SH79F083	   |
	        KEY3/P3.7--|6			 15|--VDD
	                   |			   |
	         NTC/P1.0--|7			 14|--P1.7/DOT1
			       	   |			   |
	        KEY2/P1.1--|8			 13|--P1.6/DOT2
				       |			   |
	          IR/P1.2--|9			 12|--P1.5/FOT
				       |			   |
	        KEY1/P1.3--|10			 11|--P1.4/VR
				       |_ _ _ _ _ _ _ _|
******************************************************************/
/************************************************************
*函数名:		FAN	20S
*功能说明:
************************************************************/
#include "OB38S003.h"
#include <INTRINS.H>
#include <math.h>
#include "type.h"
#include "E22Inc.h"

/************************************************************
*函数名:
*功能说明:  I/O引脚备置
************************************************************/
//-----------------
#define UART_TEST 0
#if UART_TEST
#define IR_TEST 1
#else
#define IR_TEST 0
#endif
#define CONFIG_ZERO_CHECK 1

#define  HOT   P3_1//P4_2
#define  FAN   P3_0//P4_1
#if UART_TEST
#define  MOT   P0_5//P3_0
#else
#define  MOT   P1_1//P3_0
#endif
//-----------------
#define  FOT   P0_5//P1_5
#define  DOT1  P0_6//P1_6
#define  DOT2  P0_7//P1_7
//-----------------
#define  IR    P1_4//P1_2
//-----------------
#define  ADVR  P0_4//P1_4
#define  ADNTC P0_1//P1_0
//-----------------
#define  KEY1  P0_0//P1_3
//-----------------
#if (IO_AD_KEY_OTP == 0)
  #define  KEY2  P0_2//P1_1
  #define  KEY3  P1_7//P3_7
#endif
/************************************************************
*函数名:
*功能说明:  I/O引脚备置
************************************************************/
#define   AD_NTC  0X81
#define   AD_VR   0X89
#define   AD_KEY  0X87
/************************************************************
*函数名:
*功能说明:  中断向量表
************************************************************/
#define	INT0			0
#define TIMER0_VECTOR	1    //TIMER0 Interrupt Vevtor
#define	INT1			2
#define TIMER1_VECTOR	3    //TIMER1 Interrupt Vevtor
#define TIMER2_VECTOR   5      //TIMER0 Interrupt Vevtor
#define PWM_VECTOR		8           //PWM Interrupt Vevtor

#define d_T2PS          0x05      //T2CON[7:5] TIMER2 Prescaler select 0~7
#define d_T2R           0x02      //T2CON[4:3] TIMER2 Reload mode select 0~3
#define d_T2I           0x01      //T2CON[1:0] TIMER2 Input select 0~3
#define d_T0MOD			0x01 //TMOD[3:0] TIMER0 Mode setting
#define d_T1MOD			0x01 //TMOD[7:4] TIMER1 Mode setting
#define ET2				0x01 //TIMER2 overflow Interrupt Enable (Default 0 Disable)
#define ET1				0x00 //TIMER1 overflow Interrupt Enable (Default 0 Disable)
#define ET0				0x01 //TIMER0 overflow Interrupt Enable (Default 0 Disable)

#define d_MODEVALUE_T0      65536     //MODE1 16bit 65536
#define d_RELOADVALUE_T0    160      //User Define Reload Value
#define d_MODEVALUE_T1      65536    //MODE1 16bit 65536
#define d_RELOADVALUE_T1    66      //User Define Reload Value
#define d_MODEVALUE_T2      65536
#define d_RELOADVALUE_T2    1333 //User Define Reload Value

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
#include "WDT.h"
//-----------------------
#include "HARDWARE\Ir\Ir.h"
#include "HARDWARE\Key\GainAdKeyValue.h"
#include "HARDWARE\Key\SysKey.h"
#include "HARDWARE\Key\PowerKey.h"
#include "HARDWARE\Key\FlaKey.h"
#include "HARDWARE\Key\HaetKey.h"
//-----------------------
#include "HARDWARE\Ad\Ad.h"
//-----------------------
#include "HARDWARE\HeatCon\HeatCon.h"
//-----------------------
#include "HARDWARE\FlaCon\FalCon.h"
//-----------------------
#include "HARDWARE\SysTimer\SysTimer.h"
//-----------------------
#include "HARDWARE\VrAd\VrAd.h"
//-----------------------
#include "HARDWARE\SH_EEPROM\SH_EEPROM.h"
#if UART_TEST
#include "UART0.h"
#endif
//-----------------------
/************************************************************
*函数名:
*功能说明:
************************************************************/
#if UART_TEST
extern xdata unsigned long Sys_Time;
#endif

#endif
