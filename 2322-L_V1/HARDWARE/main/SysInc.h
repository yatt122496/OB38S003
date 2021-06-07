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

#include <OB38S003.h>
#include <INTRINS.H>
#include <math.h>

#define  uint8  unsigned char
#define  uint16 unsigned int

//--------------------------
#define u8  unsigned char
#define s8  signed   char
#define u16 unsigned int
#define s16 signed   int

/************************************************************
*
* 机型选择：
************************************************************/
#define  L2322_EN       1   //
//--------------------------------------------
#define  KEY_BG_EN      0   //
#define  TOCH_ANKEY     0   //0 触摸   1：轻触
//0：直接按按键有效   1：背景等亮起，按按键才有效
//--------------------------------------------
#define  SYS_ERROT   (L2322_EN)

#if (SYS_ERROT > 1)
   #define TK6_G23K_OTP 0
   //-------------------
	#error  "错误:你不能同时选择033.UL或UK,你只能选择其中的一种......"
   //-------------------
#endif

#if (SYS_ERROT == 0)
   #define TK6_G23K_OTP 0
   //-------------------
	#error  "错误:你没有选择033.UL或UK系列机型"
   //-------------------
#endif

#define TK6_G23K_OTP  1       //0：TOUCH_6KEY  1：G23K08_KEY(14寸)
//--------------------------
#define FAN_DELAY_TIME   59   //风机延时60S
/************************************************************
*
* 功能说明:IO定义,如需修改MCU引脚在这里进行
************************************************************/
#define UART_TEST			0
#define CONFIG_ZERO_CHECK	1
#define WDT_SWITCH			1

#if UART_TEST
#define IR_TEST				1
#else
#define IR_TEST	0
#endif

#define  DWL1	  P0_5//P1_5
#define  DWL2	  P0_1//P1_0
//--------------------
#define  FOT	  P1_5//P4_0
#define  DOT	  P0_7//P1_7
#define  DOT1     P1_7//P3_7
//------------------------
#if UART_TEST
#define  MOT      FOT//P3_0
#define  FAN      FOT//P3_1
#else
#define  MOT      P1_1//P3_0
#define  FAN      P1_0//P3_1
#endif
#define  HOT      P3_0//P4_1
//--------------------
#define  IR       P1_4//P1_2
//--------------------
#define  NTC      P0_0//P1_3
//--------------------
#define  STB      P0_3//P3_3
#define  CLK      P1_2//P3_4
#define  DIO      P1_6//P3_5
//--------------------
#define  SHOWKEY  P3_1//P4_2
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
#define  K2_POW   0X01
#define  K2_FLA   0X02
#define  K2_HEA   0X04
#define  K2_DWL   0X08
#define  K2_SDL   0X10
#define  K2_TIM   0X20

#if (TK6_G23K_OTP==0)
  #define  LED_POW   0X40
  #define  LED_FLA   0X20
  #define  LED_HEA   0X04
  #define  LED_DWL   0X01
  #define  LED_TIM   0X08
  #define  LED_SDL   0X02
#else
  #define  LED_POW   0X02
  #define  LED_FLA   0X08
  #define  LED_HEA   0X04
  #define  LED_DWL   0X20
  #define  LED_TIM   0X10
  #define  LED_SDL   0X40
#endif
/************************************************************
* 功能说明:ADC通道更换
*
**************************************** ********************/
#define  AD_NTC	   0x87 //AN3	ADC0

#define  AD_KEY	   0x83	//P1_1 AN1 ADC2

/************************************************************
* 功能说明:中断向量表
*
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
#include "HARDWARE\ADC\ADC.h"
//
#include "HARDWARE\Ir\Ir.h"
#include "HARDWARE\Key\SysKey.h"
#include "HARDWARE\Key\PowerKey.h"
#include "HARDWARE\Key\TimerKey.h"
#include "HARDWARE\Key\TempKye.h"
#include "HARDWARE\Key\FlaKey.h"
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
#include "HARDWARE\LedAutoCon\LedAutoCon.h"
//
#include "HARDWARE\ErrTest\ErrTest.h"

#if WDT_SWITCH
#include "WDT.h"
#endif

#if UART_TEST
#include "UART0.h"
extern xdata unsigned long Sys_Time;
#endif

#endif
