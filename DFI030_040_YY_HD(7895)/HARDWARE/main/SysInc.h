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
#include "cms8s78xx.h"
#include <INTRINS.H>
#include <math.h>
#include "HARDWARE/main/type.h"
#include "HARDWARE/main/E22Inc.h"

/************************************************************
*函数名:
*功能说明:  I/O引脚备置
************************************************************/
//-----------------
#define UART_TEST			0
#define CONFIG_ZERO_CHECK	0
#define WDT_SWITCH			0

#if UART_TEST
#define IR_TEST				0
#else
#define IR_TEST	0
#endif
#define PWM_MAX		7500u
#define PWM_PRE		75u
#define PWM_PRE10	750u

#define  HOT   P32//P4_2
#define  FAN   P33//P4_1
#define  MOT   P24//P3_0

#define  VTX   P25
#define  cVTX_Time	52       //19200
//-----------------
#define  FOT   P21//P1_5		 PG1
#define  DOT1  P23//P1_6	p1.6 PG3
#define  DOT2  P17//P17//P1_7	 PG0	//改线
//-----------------
#define  IR    P30//P1_2
//-----------------
#define  ADVR  P22//P1_4
#define  ADNTC P05//P1_0
//-----------------
#define  KEY1  P12//P1_3
//-----------------
#if (IO_AD_KEY_OTP == 0)
  #define  KEY2  P1_1
  #define  KEY3  P3_7
#endif
/************************************************************
*函数名:
*功能说明:  I/O引脚备置
************************************************************/
#define   AD_NTC  0X81		//an0 p10	an5 p05
#define   AD_VR   0X89		//an4 p14	an18 p22
#define   AD_KEY  0X87		//an3 p13	an10 p12
/************************************************************
*函数名:
*功能说明:  中断向量表
************************************************************/
#define d_MODEVALUE_T0      65536     //MODE1 16bit 65536
#define d_RELOADVALUE_T0    120      //User Define Reload Value
#define d_MODEVALUE_T1      65536    //MODE1 16bit 65536
#define d_RELOADVALUE_T1    280      //User Define Reload Value
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
//-----------------------
#include "HARDWARE\Euart\MP3_680_681 .h"
/*/-----------------------

#include "HARDWARE\Key\Key.h"



#include "HARDWARE\Key\TimerKey.h"
#include "HARDWARE\Key\UpDown.h"
#include "HARDWARE\Key\TempProcKye.h"

//-----------------------
#include "HARDWARE\Disp\Disp.h"


//-----------------------

//-----------------------


#include "HARDWARE\ErrTest\ErrTest.h"   */
/************************************************************
*函数名:
*功能说明:
************************************************************/
#if WDT_SWITCH
#include "HARDWARE\Lib\inc\wdt.h"
#endif

#if UART_TEST
// #include "UART0.h"
extern unsigned long Sys_Time;
#endif
#endif