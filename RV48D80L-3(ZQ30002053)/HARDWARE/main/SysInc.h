/***********************************************************
*  文件名:
************************************************************
*  日期:
*
*  作者:
*  功能说明：系统配置文件
*
************************************************************
*  硬件：
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
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
          NC/P3.2--|1		     20|--P4.2/TXAL1 \
    	           |			   |			   X = 32768
          NC/P3.3--|2			 19|--P4.1/TAXL2 /
   	               |			   |
         STB/P3.4--|3			 18|--P3.1/MOT
	               |    RLP-36BL   |
         CLK/P3.5--|4			 17|--P3.0/HOT
	               |   引脚配置	   |
              GND--|5			 16|--P4.0/DWL1
		           |   SH79F083	   |
         DIO/P3.7--|6			 15|--VDD
                   |			   |
          NC/P1.0--|7			 14|--P1.7/DWL2
		       	   |			   |
          NC/P1.1--|8			 13|--P1.6/NC
			       |			   |
          IR/P1.2--|9			 12|--P1.5/DOT
			       |			   |
         NTC/P1.3--|10			 11|--P1.4/FLA
			       |_ _ _ _ _ _ _ _|
******************************************************************/
#ifndef __SysInc_H__
#define __SysInc_H__

#include "cms8s78xx.h"
#include <INTRINS.H>
#include <math.h>

#define  uint8  unsigned char
#define  uint16 unsigned int

//--------------------------
#define u8  unsigned char
#define s8  signed   char
#define u16 unsigned int
#define s16 signed   int
//--------------------------
#define  TK6_G23K_OTP 0  // 0: TOUCH_6KEY  1：G23K08_KEY(14寸)

#define  CT_YY_EN     1  // 0: 长条遥控    1：弧形遥控

#define  LUM_EN       1  // 0：火焰，底灰亮度关  1：火焰底灰亮度开

#define  HOT_DELAY_TIME   4   //风机提前5S
#define  FAN_DELAY_TIME   7   //风机延时8S
/************************************************************
*
* 功能说明:IO定义,如需修改MCU引脚在这里进行
************************************************************/
#define UART_TEST			0
#define CONFIG_ZERO_CHECK	1
#define WDT_SWITCH			1

#if UART_TEST
#define IR_TEST				0
#else
#define IR_TEST	0
#endif

#define  FLA_Y	  P05//P1_0
#define  FLA_B	  P03//P3_7
#define  FLA_R	  P17//P1_7
//--------------------
#define  DOW_R	  P20//P1_6
#define  DOW_B	  P21//P1_5
#define  DOW_G    P23//P4_0
//--------------------
#define  MOT      P24//P3_0
#define  FAN      P25//P3_1
#define  HOT      P33//P4_1
//--------------------
#define  IR       P30//P1_2
//--------------------
#define  NTC      P12//P1_3
//--------------------
#define  STB      P04//P3_3
#define  CLK      P00//P3_4
#define  DIO      P02//P3_5
//--------------------
#define  SHOWKEY  P32//P4_2
/************************************************************
* 功能说明:如果显示发数据改变了,在这里也是可以修改的
*
************************************************************/
#define  DISP_LED1 0
#define  DISP_LED2 1
#define  DISP_LED3 2

#define  A        10  //	10	//	A
#define  B        11  //	11	//	B
#define  C        12  //	12	//	C
#define  D        13  //	13	//	D
#define  E        14  //	14	//	E
#define  F        15  //	15	//	F
#define  DISP_OFF 16
#define  H        17
#define  L        18
#define  N        19
/************************************************************
* 功能说明:按键击活
*
************************************************************/
#define  K2_POW   0X0001
#define  K2_FLA   0X0002
#define  K2_HEA   0X0004
#define  K2_DWL   0X0008
#define  K2_SDL   0X0010
#define  K2_TIM   0X0020
#define  K2_DOW   0X0040
#define  K2_DAO   0X0080
#define  K2_FAO   0X0100

#define  LED_POW   0X40
#define  LED_FLA   0X20
#define  LED_HEA   0X04
#define  LED_DWL   0X01
#define  LED_TIM   0X08
#define  LED_SDL   0X02
#define  ALL_LED   0XfF
/************************************************************
* 功能说明:ADC通道更换
*
**************************************** ********************/
/*ADC */
//	      bit7   bit6    bit5   bit4   bit3   bit2	 bit1   bit0
//ADCON   ADON   ADCIF   EC     --     SCH2   SCH1   SCH0   GO/DONE
//ADT     TADC2  TADC1   TADC0  --     TS3    TS2    TS1    TS0
//ADCH    CH7    CH6     CH5	CH4	   CH3    CH2    CH1    CH0
//IO      P17	 P16	 P15	P14	   P13	  P12	 P11	P10
//-------------------------------------------------------------
#define  AD_NTC	   0x87 //P1_3 AN3			P12 an10

#define  AD_KEY	   0x83	//P1_1 AN1			P11 an9
/************************************************************
* 功能说明:中断向量表
*
************************************************************/
#define d_MODEVALUE_T0      65536     //MODE1 16bit 65536
#define d_RELOADVALUE_T0    120      //User Define Reload Value
#define d_MODEVALUE_T1      65536    //MODE1 16bit 65536
#define d_RELOADVALUE_T1    100      //User Define Reload Value
#define d_MODEVALUE_T2      65536
#define d_RELOADVALUE_T2    2000 //User Define Reload Value
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
//
#include "HARDWARE\ADC\ad.h"
//
#include "HARDWARE\Ir\Ir.h"
#include "HARDWARE\Key\SysKey.h"
#include "HARDWARE\Key\PowerKey.h"
#include "HARDWARE\Key\TimerKey.h"
#include "HARDWARE\Key\TempKye.h"
#include "HARDWARE\Key\FlaKey.h"
//#include "HARDWARE\Key\DwlKey.h"
//#include "HARDWARE\Key\SdlKey.h"
#include "HARDWARE\Key\DowKey.h"
#include "HARDWARE\Key\upKey.h"
//
#include "HARDWARE\Key\GainAdKeyValue.h"
//
#include "HARDWARE\HeatCon\HeatCon.h"
//
#include "HARDWARE\Tm1638\Tm1638.h"
//
#include "HARDWARE\SysTimer\SysTimer.h"
//
#include "HARDWARE\Disp\Disp.h"
//
#include "HARDWARE\SysInit\SysInit.h"
//
#include "HARDWARE\LedAutoCon\LedAutoCon.h"
//
#include "HARDWARE\ErrTest\ErrTest.h"
//
#define DOW_MAX     9
#define DOW_AU_MAX  6

#define FLA_MAX     8
#define FLA_AU_MAX  6

#if WDT_SWITCH
#include "HARDWARE\Lib\inc\wdt.h"
#endif
#if UART_TEST
extern unsigned long Sys_Time;
#endif

#endif
