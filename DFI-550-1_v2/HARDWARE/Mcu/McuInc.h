#ifndef __MCU_INC_H__
#define __MCU_INC_H__
//--------------------------
#include "cms8s78xx.h"
#include "HARDWARE\include\Type.h"
#define REG79F083A_H
/************************************************************
*函数名:
*功能说明:  中断向量表
************************************************************/
#ifdef  REG79F1622_H
#define  INT0      0
#define  TK        1
#define  INT1      2
#define  EUART     4
#define  TIMER2	   5
#define  TIMER4    7
#define  INT2      8
#define  INT4 	   9
#define  TWI       10
#define  TIMER3    11
//--------------------------
//#define TIMER2_EN
//#define TIMER3_EN
//#define TIMER4_EN
//#define EUART_EN
//#define  SH_EEPROM
//--------------------------
#define FOSC     27000000L
#define FOSC_FD  4
#define SCLK     (FOSC / FOSC_FD)
//--------------------------
#endif

#ifdef  REG79F083A_H
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
	          ZO/P3.2--|1		     20|--P4.2/HOT
	    	           |			   |
	        SEG4/P3.3--|2			 19|--P4.1/FAN
	   	               |			   |
	        SEG3/P3.4--|3			 18|--P3.1/MOT
		               |    DFI020     |
	        SEG2/P3.5--|4			 17|--P3.0/NC
		               |   引脚配置	   |
	              GND--|5			 16|--P4.0/NC
			           |   SH79F083	   |
	        SEG1/P3.7--|6			 15|--VDD
	                   |			   |
	        COM1/P1.0--|7			 14|--P1.7/BZ
			       	   |			   |
	          Vr/P1.1--|8			 13|--P1.6/NC
				       |			   |
	          IR/P1.2--|9			 12|--P1.5/NC
				       |			   |
	         NTC/P1.3--|10			 11|--P1.4/FLA
				       |_ _ _ _ _ _ _ _|
******************************************************************/
//--------------------------
#define UART_TEST			0
#define CONFIG_ZERO_CHECK	1
#define WDT_SWITCH			1

#if UART_TEST
#define IR_TEST				0
#else
#define IR_TEST	0
#endif
//DISP
#define	COM1  P05//P1_0
#define	SEG1  P04//P3_3
#define	SEG2  P00//P3_4
#define	SEG3  P02//P3_5
#define	SEG4  P03//P3_7
//HEAT
#define	HOT   P32//P4_2
#define	FAN   P33//P4_1
//FLA
#define	MOT   P25//P3_1
#define	FLA   P22//P1_4
//zo
//#define	ZO    P3_2
//BUZZ
#define	BZ    P17//P1_7
//ad
//#define	Vr    P1_1
//#define	NTC   P1_3
//ir
//#define	IR    P1_2
/************************************************************
*函数名:
*功能说明:
************************************************************/
#define   AD_NTC  0X87	//an3 p13		an10 p12
#define   AD_VR   0X83	//an1 p11		an9 p11
/************************************************************
*函数名:
*功能说明:  中断向量表
************************************************************/
#define d_MODEVALUE_T0      65536     //MODE1 16bit 65536
#define d_RELOADVALUE_T0    120      //User Define Reload Value
#define d_MODEVALUE_T1      65536    //MODE1 16bit 65536
#define d_RELOADVALUE_T1    300      //User Define Reload Value
#define d_MODEVALUE_T2      65536
#define d_RELOADVALUE_T2    4000 //User Define Reload Value
// #define   INT0      0
// #define	  TIMER0    1
// #define	  INT1      2
// #define	  TIMER1    3
// #define	  EUART     4
// #define	  TIMER2	5
// #define	  ADC       6
// #define	  INT2		9
// #define	  SCM		11
// #define	  PWM		12
// #define	  LPD    	13
//--------------------------
#define INT0_EN
//#define INT1_EN
#define INT2_EN
#define TIMER0_EN
#define TIMER1_EN
#define TIMER2_EN
#define PWM_EN
//#define EUART_EN
#define  SH_EEPROM
//--------------------------
#define FOSC     16600000L
#define FOSC_FD  2
#define SCLK     (FOSC / FOSC_FD)
//--------------------------
#endif
#ifdef  REG79F084A_H//SH79F084A
/*****************************************************************
                   |``````:_:``````|
       RESET/P4.0--|1		     16|--VDD
    	           |			   |
         RXD/P3.0--|2			 15|--P1.7/T2/AN7
   	               |			   |
         TXD/P3.1--|3			 14|--P1.6/T2EX/AN6
	               |   引脚配置	   |
       XTAL2/P4.1--|4			 13|--P1.5/AN5/TCK
	               |   	           |
       XTAL1/P4.2--|5			 12|--P1.4/AN4/TDI
		           |   SH79F084A   |
        INT0/P3.2--|6			 11|--P1.3/VLPD/AN3/TMS
                   |			   |
        INT1/P3.3--|7			 10|--P1.2/INT2/AN2/TDO
		       	   |			   |
              GND--|8			  9|--P3.7/T1/PWM
			       |_ _ _ _ _ _ _ _|

                   |``````:_:``````|
         FAN/P4.0--|1		     16|--VDD
    	           |			   |
        HEA1/P3.0--|2			 15|--P1.7/COM1
   	               |			   |
        HEA2/P3.1--|3			 14|--P1.6/SEG1
	               |   引脚配置	   |
       XTAL2/P4.1--|4			 13|--P1.5/SEG2
	NC             |   	           |
       XTAL1/P4.2--|5			 12|--P1.4/SEG3
		           |   SH79F084A   |
         FLA/P3.2--|6			 11|--P1.3/SEG4
                   |			   |
          ZO/P3.3--|7			 10|--P1.2/INT2/IR
		       	   |			   |
              GND--|8			  9|--P3.7/PWM/BZ
			       |_ _ _ _ _ _ _ _|
******************************************************************/
////DISP
//#define	COM1  P1_7
//#define	SEG1  P1_3
//#define	SEG2  P1_4
//#define	SEG3  P1_5
//#define	SEG4  P1_6
////HEAT
//#define KEY   P1
////HEAT
//#define	MOT   P4_0
//#define	HEA1  P3_1
//#define	HEA2  P4_1
//#define	FAN   P3_0
////FLA
//#define	FLA   P3_2
//#define	ZO    P3_3
////BUZZ
//#define	BZ    P3_7
/************************************************************
*函数名:
*功能说明:  中断向量表
************************************************************/
#define   INT0      0
#define	  TIMER0    1
#define	  INT1      2
#define	  TIMER1    3
#define	  EUART     4
#define	  TIMER2	5
#define	  ADC       6
#define	  INT2		9
#define	  SCM		11
#define	  PWM		12
#define	  LPD    	13
//--------------------------
//#define INT0_EN
#define INT1_EN
#define INT2_EN
#define TIMER0_EN
#define TIMER1_EN
#define TIMER2_EN
#define PWM_EN
//#define EUART_EN
#define  SH_EEPROM
//--------------------------
#define FOSC     16600000L
#define FOSC_FD  2
#define SCLK     (FOSC / FOSC_FD)
//--------------------------
#endif

#include "HARDWARE\Mcu\McuInit.h"
#include "HARDWARE\Mcu\SysClkInit.h"
#include "HARDWARE\Mcu\Interrupt.h"
#include "HARDWARE\Mcu\Timer0.h"
#include "HARDWARE\Mcu\Timer1.h"
#include "HARDWARE\Mcu\Timer2.h"
#include "HARDWARE\Mcu\Timer3.h"
#include "HARDWARE\Mcu\Timer4.h"
#include "HARDWARE\MCU\Euart.h"
#include "HARDWARE\Mcu\Interrupt.h"
#include "HARDWARE\Mcu\Int0.h"
#include "HARDWARE\Mcu\Int1.h"
#include "HARDWARE\Mcu\Int2.h"
#include "HARDWARE\Mcu\pwm.h"
#include "HARDWARE\Mcu\SH_EEPROM.H"
//--------------------------
#include "HARDWARE\FlaCon\FlaCon.h"
//--------------------------
#endif