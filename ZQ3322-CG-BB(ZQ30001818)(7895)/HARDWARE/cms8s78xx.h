/*******************************************************************************
* Copyright (C) 2019 China Micro Semiconductor Limited Company. All Rights Reserved.
*
* This software is owned and published by:
* CMS LLC, No 2609-10, Taurus Plaza, TaoyuanRoad, NanshanDistrict, Shenzhen, China.
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with CMS
* components. This software is licensed by CMS to be adapted only
* for use in systems utilizing CMS components. CMS shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. CMS is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

/*****************************************************************************/
/** \file cms8s78xx.h
**
**
**
** History:
**
*****************************************************************************/
#ifndef _CMS8S78XX_H_
#define _CMS8S78XX_H_
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "intrins.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/
typedef   signed            char int8_t;
typedef   signed short      int int16_t;
typedef   signed            long  int32_t;

typedef unsigned            char uint8_t;
typedef unsigned short      int  uint16_t;
typedef unsigned  			long uint32_t;

typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t   s8;

typedef uint32_t  u32;
typedef uint16_t  u16;
typedef uint8_t   u8;


/*----------BYTE Register------------------*/
/*-----------SFR(?¡ë???????¨¨???????????-------*/
/*-----------BANK0---------------------*/
sfr  P0	= 0x80;
sfr  SP = 0x81;
sfr  DPL0 = 0x82;
sfr  DPH0 = 0x83;
sfr  DPL1 = 0x84;
sfr  DPH1 = 0x85;
sfr  DPS  = 0x86;
sfr  PCON = 0x87;
sfr  TCON = 0x88;
sfr  TMOD = 0x89;
sfr  TL0  = 0x8a;
sfr  TL1  = 0x8b;
sfr  TH0  = 0x8c;
sfr  TH1  = 0x8d;
sfr  CKCON = 0x8e;
sfr  CLKDIV = 0x8f;

sfr	  P1 = 0x90;
sfr   FUNCCR = 0x91;
sfr   TA   = 0x96;
sfr   WDCON = 0x97;
sfr   SCON0 = 0x98;
sfr   SBUF0  = 0x99;
sfr   P0TRIS = 0x9a;

sfr   P2  = 0xa0;
sfr   P1TRIS = 0xa1;
sfr   P2TRIS = 0xa2;
sfr   P3TRIS = 0xa3;

sfr   IE  = 0xa8;
sfr   EIE2 = 0xaa;
sfr   P0EXTIE = 0xac;
sfr   P1EXTIE = 0xad;
sfr   P2EXTIE = 0xae;
sfr   P3EXTIE = 0xaf;

sfr   P3 = 0xb0;
sfr   EIF2 = 0xb2;
sfr   P0EXTIF = 0xb4;
sfr   P1EXTIF = 0xb5;
sfr   P2EXTIF = 0xb6;
sfr   P3EXTIF = 0xb7;

sfr   IP = 0xb8;
sfr   EIP1 = 0xb9;
sfr   EIP2 = 0xba;
sfr   EIP3 = 0xbb;
sfr	  WUTCRL = 0xbc;
sfr   WUTCRH = 0xbd;
sfr   BUZDIV = 0xbe;
sfr   BUZCON = 0xbf;

sfr   CCL1 = 0xc2;
sfr   CCH1 = 0xc3;
sfr   CCL2 = 0xc4;
sfr   CCH2 = 0xc5;
sfr   CCL3 = 0xc6;
sfr   CCH3 = 0xc7;

sfr   T2CON = 0xc8;
sfr   T2IF = 0xc9;
sfr   RLDL = 0xca;
sfr   RLDH = 0xcb;
sfr   TL2 = 0xcc;
sfr   TH2 = 0xcd;
sfr   CCEN = 0xce;
sfr   T2IE = 0xcf;

sfr   PSW = 0xd0;
sfr   ADCMPC = 0xd1;
sfr   T34MOD = 0xd2;
sfr   ADDLYL = 0xd3;
sfr   ADCMPL = 0xd4;
sfr   ADCMPH = 0xd5;
sfr   SCKSEL = 0xd6;
sfr   SCKSTAU = 0xd7;

sfr	  ADCCHS = 0xd9;
sfr   TL3 = 0xda;
sfr   TH3 = 0xdb;
sfr   ADRESL = 0xdc;
sfr   ADRESH = 0xdd;
sfr   ADCON1 = 0xde;
sfr   ADCON0 = 0xdf;

sfr   ACC = 0xe0;
sfr   TL4 = 0xe2;
sfr   TH4 = 0xe3;

sfr   ADCON2 = 0xe9;
sfr   SPCR  = 0xec;
sfr   SPSR  = 0xed;
sfr   SPDR  = 0xee;
sfr   SSCR  = 0xef;

sfr   B = 0xf0;
sfr   I2CSADR = 0xf1;
sfr   I2CSCR = 0xf2;
sfr   I2CSSR = 0xf2;
sfr   I2CSBUF = 0xf3;
sfr   I2CMSA = 0xf4;
sfr   I2CMCR = 0xf5;
sfr   I2CMSR = 0xf5;
sfr   I2CMBUF = 0xf6;
sfr   I2CMTP = 0xf7;

sfr   PCRCDL = 0xf9;
sfr   PCRCDH = 0xfa;
sfr   MLOCK = 0xfb;
sfr   MADRL = 0xfc;
sfr   MADRH = 0xfd;
sfr   MDATA = 0xfe;
sfr   MCTRL = 0xff;


/*-----------XSFR(?¡ë???????¨¨???????????-------*/
#define P00CFG 	*(volatile unsigned char xdata *) 0xF000
#define P01CFG 	*(volatile unsigned char xdata *) 0xF001
#define P02CFG 	*(volatile unsigned char xdata *) 0xF002
#define P03CFG 	*(volatile unsigned char xdata *) 0xF003
#define P04CFG 	*(volatile unsigned char xdata *) 0xF004
#define P05CFG 	*(volatile unsigned char xdata *) 0xF005
#define P06CFG 	*(volatile unsigned char xdata *) 0xF006
#define P07CFG 	*(volatile unsigned char xdata *) 0xF007

#define P0OD 	*(volatile unsigned char xdata *) 0xF009
#define P0UP 	*(volatile unsigned char xdata *) 0xF00A
#define P0RD	*(volatile unsigned char xdata *) 0xF00B
#define P0DR	*(volatile unsigned char xdata *) 0xF00C
#define P0SR	*(volatile unsigned char xdata *) 0xF00D
#define P0DS	*(volatile unsigned char xdata *) 0xF00E

#define P10CFG 	*(volatile unsigned char xdata *) 0xF010
#define P11CFG 	*(volatile unsigned char xdata *) 0xF011
#define P12CFG 	*(volatile unsigned char xdata *) 0xF012
#define P13CFG 	*(volatile unsigned char xdata *) 0xF013
#define P14CFG 	*(volatile unsigned char xdata *) 0xF014
#define P15CFG 	*(volatile unsigned char xdata *) 0xF015
#define P16CFG 	*(volatile unsigned char xdata *) 0xF016
#define P17CFG 	*(volatile unsigned char xdata *) 0xF017

#define P1OD 	*(volatile unsigned char xdata *) 0xF019
#define P1UP 	*(volatile unsigned char xdata *) 0xF01A
#define P1RD	*(volatile unsigned char xdata *) 0xF01B
#define P1DR	*(volatile unsigned char xdata *) 0xF01C
#define P1SR	*(volatile unsigned char xdata *) 0xF01D
#define P1DS	*(volatile unsigned char xdata *) 0xF01E

#define P20CFG 	*(volatile unsigned char xdata *) 0xF020
#define P21CFG 	*(volatile unsigned char xdata *) 0xF021
#define P22CFG 	*(volatile unsigned char xdata *) 0xF022
#define P23CFG 	*(volatile unsigned char xdata *) 0xF023
#define P24CFG 	*(volatile unsigned char xdata *) 0xF024
#define P25CFG	*(volatile unsigned char xdata *) 0xF025

#define P2OD 	*(volatile unsigned char xdata *) 0xF029
#define P2UP 	*(volatile unsigned char xdata *) 0xF02A
#define P2RD	*(volatile unsigned char xdata *) 0xF02B
#define P2DR	*(volatile unsigned char xdata *) 0xF02C
#define P2SR	*(volatile unsigned char xdata *) 0xF02D
#define P2DS	*(volatile unsigned char xdata *) 0xF02E


#define P30CFG 	*(volatile unsigned char xdata *) 0xF030
#define P31CFG 	*(volatile unsigned char xdata *) 0xF031
#define P32CFG 	*(volatile unsigned char xdata *) 0xF032
#define P33CFG 	*(volatile unsigned char xdata *) 0xF033


#define P3OD 	*(volatile unsigned char xdata *) 0xF039
#define P3UP 	*(volatile unsigned char xdata *) 0xF03A
#define P3RD	*(volatile unsigned char xdata *) 0xF03B
#define P3DR	*(volatile unsigned char xdata *) 0xF03C
#define P3SR	*(volatile unsigned char xdata *) 0xF03D
#define P3DS	*(volatile unsigned char xdata *) 0xF03E


#define P00EICFG 	*(volatile unsigned char xdata *) 0xF080
#define P01EICFG 	*(volatile unsigned char xdata *) 0xF081
#define P02EICFG 	*(volatile unsigned char xdata *) 0xF082
#define P03EICFG 	*(volatile unsigned char xdata *) 0xF083
#define P04EICFG 	*(volatile unsigned char xdata *) 0xF084
#define P05EICFG 	*(volatile unsigned char xdata *) 0xF085
#define P06EICFG 	*(volatile unsigned char xdata *) 0xF086
#define P07EICFG 	*(volatile unsigned char xdata *) 0xF087

#define P10EICFG 	*(volatile unsigned char xdata *) 0xF088
#define P11EICFG 	*(volatile unsigned char xdata *) 0xF089
#define P12EICFG 	*(volatile unsigned char xdata *) 0xF08A
#define P13EICFG 	*(volatile unsigned char xdata *) 0xF08B
#define P14EICFG 	*(volatile unsigned char xdata *) 0xF08C
#define P15EICFG 	*(volatile unsigned char xdata *) 0xF08D
#define P16EICFG 	*(volatile unsigned char xdata *) 0xF08E
#define P17EICFG 	*(volatile unsigned char xdata *) 0xF08F

#define P20EICFG 	*(volatile unsigned char xdata *) 0xF090
#define P21EICFG 	*(volatile unsigned char xdata *) 0xF091
#define P22EICFG 	*(volatile unsigned char xdata *) 0xF092
#define P23EICFG 	*(volatile unsigned char xdata *) 0xF093
#define P24EICFG 	*(volatile unsigned char xdata *) 0xF094
#define P25EICFG 	*(volatile unsigned char xdata *) 0xF095

#define P30EICFG 	*(volatile unsigned char xdata *) 0xF098
#define P31EICFG 	*(volatile unsigned char xdata *) 0xF099
#define P32EICFG 	*(volatile unsigned char xdata *) 0xF09A
#define P33EICFG 	*(volatile unsigned char xdata *) 0xF09B


#define PS_INT0		*(volatile unsigned char xdata *) 0xF0C0
#define PS_INT1		*(volatile unsigned char xdata *) 0xF0C1
#define PS_T0		*(volatile unsigned char xdata *) 0xF0C2
#define PS_T0G		*(volatile unsigned char xdata *) 0xF0C3
#define PS_T1		*(volatile unsigned char xdata *) 0xF0C4
#define PS_T1G		*(volatile unsigned char xdata *) 0xF0C5
#define PS_T2		*(volatile unsigned char xdata *) 0xF0C6
#define PS_T2EX		*(volatile unsigned char xdata *) 0xF0C7
#define PS_CAP0		*(volatile unsigned char xdata *) 0xF0C8
#define PS_CAP1		*(volatile unsigned char xdata *) 0xF0C9
#define PS_CAP2		*(volatile unsigned char xdata *) 0xF0CA
#define PS_CAP3		*(volatile unsigned char xdata *) 0xF0CB
#define PS_ADET		*(volatile unsigned char xdata *) 0xF0CC
#define PS_FB0		*(volatile unsigned char xdata *) 0xF0CD
#define PS_FB1		*(volatile unsigned char xdata *) 0xF0CE

#define PWMCON		*(volatile unsigned char xdata *) 0xF120
#define PWMOE		*(volatile unsigned char xdata *) 0xF121
#define PWMPINV		*(volatile unsigned char xdata *) 0xF122
#define PWM01PSC	*(volatile unsigned char xdata *) 0xF123
#define PWM23PSC	*(volatile unsigned char xdata *) 0xF124

#define PWMCNTE		*(volatile unsigned char xdata *) 0xF126
#define PWMCNTM		*(volatile unsigned char xdata *) 0xF127
#define PWMCNTCLR	*(volatile unsigned char xdata *) 0xF128
#define PWMLOADEN	*(volatile unsigned char xdata *) 0xF129

#define PWM0DIV		*(volatile unsigned char xdata *) 0xF12A
#define PWM1DIV		*(volatile unsigned char xdata *) 0xF12B
#define PWM2DIV		*(volatile unsigned char xdata *) 0xF12C
#define PWM3DIV		*(volatile unsigned char xdata *) 0xF12D

#define PWMP0L		*(volatile unsigned char xdata *) 0xF130
#define PWMP0H		*(volatile unsigned char xdata *) 0xF131
#define PWMP1L		*(volatile unsigned char xdata *) 0xF132
#define PWMP1H		*(volatile unsigned char xdata *) 0xF133
#define PWMP2L		*(volatile unsigned char xdata *) 0xF134
#define PWMP2H		*(volatile unsigned char xdata *) 0xF135
#define PWMP3L		*(volatile unsigned char xdata *) 0xF136
#define PWMP3H		*(volatile unsigned char xdata *) 0xF137

#define PWMD0L		*(volatile unsigned char xdata *) 0xF140
#define PWMD0H		*(volatile unsigned char xdata *) 0xF141
#define PWMD1L		*(volatile unsigned char xdata *) 0xF142
#define PWMD1H		*(volatile unsigned char xdata *) 0xF143
#define PWMD2L		*(volatile unsigned char xdata *) 0xF144
#define PWMD2H		*(volatile unsigned char xdata *) 0xF145
#define PWMD3L		*(volatile unsigned char xdata *) 0xF146
#define PWMD3H		*(volatile unsigned char xdata *) 0xF147

#define PWMDD0L		*(volatile unsigned char xdata *) 0xF150
#define PWMDD0H		*(volatile unsigned char xdata *) 0xF151
#define PWMDD1L		*(volatile unsigned char xdata *) 0xF152
#define PWMDD1H		*(volatile unsigned char xdata *) 0xF153
#define PWMDD2L		*(volatile unsigned char xdata *) 0xF154
#define PWMDD2H		*(volatile unsigned char xdata *) 0xF155
#define PWMDD3L		*(volatile unsigned char xdata *) 0xF156
#define PWMDD3H		*(volatile unsigned char xdata *) 0xF157

#define PWMBRKC		*(volatile unsigned char xdata *) 0xF15C
#define PWMBRKRDTL	*(volatile unsigned char xdata *) 0xF15D
#define PWMBRKRDTH	*(volatile unsigned char xdata *) 0xF15E


#define PWMDTE		*(volatile unsigned char xdata *) 0xF160
#define PWM01DT		*(volatile unsigned char xdata *) 0xF161
#define PWM23DT		*(volatile unsigned char xdata *) 0xF162

#define PWMMASKE	*(volatile unsigned char xdata *) 0xF164
#define PWMMASKD	*(volatile unsigned char xdata *) 0xF165
#define PWMFBKC		*(volatile unsigned char xdata *) 0xF166
#define PWMFBKD		*(volatile unsigned char xdata *) 0xF167
#define PWMPIE		*(volatile unsigned char xdata *) 0xF168
#define PWMZIE		*(volatile unsigned char xdata *) 0xF169
#define PWMUIE		*(volatile unsigned char xdata *) 0xF16A
#define PWMDIE		*(volatile unsigned char xdata *) 0xF16B
#define PWMPIF		*(volatile unsigned char xdata *) 0xF16C
#define PWMZIF		*(volatile unsigned char xdata *) 0xF16D
#define PWMUIF		*(volatile unsigned char xdata *) 0xF16E
#define PWMDIF		*(volatile unsigned char xdata *) 0xF16F

#define C0CON0   	*(volatile unsigned char xdata *) 0xF500
#define C0CON1   	*(volatile unsigned char xdata *) 0xF501
#define C0CON2   	*(volatile unsigned char xdata *) 0xF502
#define C1CON0   	*(volatile unsigned char xdata *) 0xF503
#define C1CON1   	*(volatile unsigned char xdata *) 0xF504
#define C1CON2   	*(volatile unsigned char xdata *) 0xF505

#define CNVRCON   	*(volatile unsigned char xdata *) 0xF506
#define CNFBCON   	*(volatile unsigned char xdata *) 0xF507
#define CNIE	   	*(volatile unsigned char xdata *) 0xF508
#define CNIF   		*(volatile unsigned char xdata *) 0xF509
#define C0ADJE   	*(volatile unsigned char xdata *) 0xF50A
#define C1ADJE   	*(volatile unsigned char xdata *) 0xF50B
#define C0HYS   	*(volatile unsigned char xdata *) 0xF50C
#define C1HYS   	*(volatile unsigned char xdata *) 0xF50D


#define BRTCON		*(volatile unsigned char xdata *) 0xF5C0
#define BRTDL		*(volatile unsigned char xdata *) 0xF5C1
#define BRTDH		*(volatile unsigned char xdata *) 0xF5C2


#define UID0		*(volatile unsigned char xdata *) 0xF5E0
#define UID1		*(volatile unsigned char xdata *) 0xF5E1
#define UID2		*(volatile unsigned char xdata *) 0xF5E2
#define UID3		*(volatile unsigned char xdata *) 0xF5E3
#define UID4		*(volatile unsigned char xdata *) 0xF5E4
#define UID5		*(volatile unsigned char xdata *) 0xF5E5
#define UID6		*(volatile unsigned char xdata *) 0xF5E6
#define UID7		*(volatile unsigned char xdata *) 0xF5E7
#define UID8		*(volatile unsigned char xdata *) 0xF5E8
#define UID9		*(volatile unsigned char xdata *) 0xF5E9
#define UID10		*(volatile unsigned char xdata *) 0xF5EA
#define UID11		*(volatile unsigned char xdata *) 0xF5EB


#define LCDCON0		*(volatile unsigned char xdata *) 0xF650
#define LCD_S0		*(volatile unsigned char xdata *) 0xF651
#define LCD_S1		*(volatile unsigned char xdata *) 0xF652
#define LCD_S2		*(volatile unsigned char xdata *) 0xF653
#define LCDEN0		*(volatile unsigned char xdata *) 0xF654
#define LCDEN1		*(volatile unsigned char xdata *) 0xF655
#define LCDEN2		*(volatile unsigned char xdata *) 0xF656

#define LVDCON		*(volatile unsigned char xdata *) 0xF690
#define BOOTCON		*(volatile unsigned char xdata *) 0xF691
#define ADCLDO		*(volatile unsigned char xdata *) 0xF692

#define TS_REG		*(volatile unsigned char xdata *) 0xF693

#define LSECRL		*(volatile unsigned char xdata *) 0xF694
#define LSECRH		*(volatile unsigned char xdata *) 0xF695
#define LSECON		*(volatile unsigned char xdata *) 0xF696

#define XT_SCM		*(volatile unsigned char xdata *) 0xF697

#define PS_SCLK		*(volatile unsigned char xdata *) 0xF698
#define PS_MOSI		*(volatile unsigned char xdata *) 0xF699
#define PS_MISO		*(volatile unsigned char xdata *) 0xF69A
#define PS_NSS		*(volatile unsigned char xdata *) 0xF69B
#define PS_SCL		*(volatile unsigned char xdata *) 0xF69C
#define PS_SDA		*(volatile unsigned char xdata *) 0xF69D
#define PS_RXD		*(volatile unsigned char xdata *) 0xF69F

#define LEDSDRP0L	*(volatile unsigned char xdata *) 0xF710
#define LEDSDRP0H	*(volatile unsigned char xdata *) 0xF711
#define LEDSDRP1L	*(volatile unsigned char xdata *) 0xF712
#define LEDSDRP1H	*(volatile unsigned char xdata *) 0xF713
#define LEDSDRP2L	*(volatile unsigned char xdata *) 0xF714
#define LEDSDRP2H	*(volatile unsigned char xdata *) 0xF715
#define LEDSDRP3L	*(volatile unsigned char xdata *) 0xF716

/*--------------------------------------------------------------- --------
  BIT Register
-------------------------------------------------------------------------*/
/*  P0  */
  sbit P07     = P0^7;
  sbit P06     = P0^6;
  sbit P05     = P0^5;
  sbit P04     = P0^4;
  sbit P03     = P0^3;
  sbit P02     = P0^2;
  sbit P01     = P0^1;
  sbit P00     = P0^0;
/*  P1  */
  sbit P17     = P1^7;
  sbit P16     = P1^6;
  sbit P15     = P1^5;
  sbit P14     = P1^4;
  sbit P13     = P1^3;
  sbit P12     = P1^2;
  sbit P11     = P1^1;
  sbit P10     = P1^0;
/*  P2  */
  sbit P25     = P2^5;
  sbit P24     = P2^4;
  sbit P23     = P2^3;
  sbit P22     = P2^2;
  sbit P21     = P2^1;
  sbit P20     = P2^0;

/*  P3  */
  sbit P33     = P3^3;
  sbit P32     = P3^2;
  sbit P31     = P3^1;
  sbit P30     = P3^0;
/*  TCON  */
  sbit IT0      = TCON^0;
  sbit IE0      = TCON^1;
  sbit IT1      = TCON^2;
  sbit IE1      = TCON^3;
  sbit TR0      = TCON^4;
  sbit TF0      = TCON^5;
  sbit TR1      = TCON^6;
  sbit TF1      = TCON^7;
/*  SCON0 */
  sbit RI0      = SCON0^0;
  sbit TI0      = SCON0^1;
  sbit U0RB8    = SCON0^2;
  sbit U0TB8    = SCON0^3;
  sbit U0REN    = SCON0^4;
  sbit U0SM2    = SCON0^5;
  sbit U0SM1    = SCON0^6;
  sbit U0SM0    = SCON0^7;
/*  IE */
  sbit EX0     	= IE^0;
  sbit ET0     	= IE^1;
  sbit EX1     	= IE^2;
  sbit ET1     	= IE^3;
  sbit ES0     	= IE^4;
  sbit ET2     	= IE^5;
  sbit ES1     	= IE^6;
  sbit EA      	= IE^7;
 /*  IP */
  sbit PX0     	= IP^0;
  sbit PT0     	= IP^1;
  sbit PX1     	= IP^2;
  sbit PT1     	= IP^3;
  sbit PS0     	= IP^4;
  sbit PT2     	= IP^5;
  sbit PS1     	= IP^6;
 /*  T2CON */
  sbit T2I0     = T2CON^0;
  sbit T2I1     = T2CON^1;
  sbit T2CM     = T2CON^2;
  sbit T2R0     = T2CON^3;
  sbit T2R1     = T2CON^4;
  sbit I3FR     = T2CON^6;
  sbit T2PS     = T2CON^7;
 /* PSW  */
  sbit  P     	=PSW^0;
  sbit  OV    	=PSW^2;
  sbit  RS0   	=PSW^3;
  sbit  RS1    	=PSW^4;
  sbit  F0    	=PSW^5;
  sbit  AC    	=PSW^6;
  sbit  CY    	=PSW^7;

/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/

/*-----------------------------------------------------------------
**	Peripheral memory map
------------------------------------------------------------------*/

/*-----------------------------------------------------------------
**IRQ ????¨C?
------------------------------------------------------------------*/
/*------IE--------------------------------------------------------*/
#define IRQ_IE_EA_Pos			(7)
#define IRQ_IE_EA_Msk			(0x1 << IRQ_IE_EA_Pos)
#define IRQ_IE_ES1_Pos			(6)
#define IRQ_IE_ES1_Msk			(0x1 << IRQ_IE_ES1_Pos)
#define IRQ_IE_ET2_Pos			(5)
#define IRQ_IE_ET2_Msk			(0x1 << IRQ_IE_ET2_Pos)
#define IRQ_IE_ES0_Pos			(4)
#define IRQ_IE_ES0_Msk			(0x1 << IRQ_IE_ES0_Pos)
#define IRQ_IE_ET1_Pos			(3)
#define IRQ_IE_ET1_Msk			(0x1 << IRQ_IE_ET1_Pos)
#define IRQ_IE_EX1_Pos			(2)
#define IRQ_IE_EX1_Msk			(0x1 << IRQ_IE_EX1_Pos)
#define IRQ_IE_ET0_Pos			(1)
#define IRQ_IE_ET0_Msk			(0x1 << IRQ_IE_ET0_Pos)
#define IRQ_IE_EX0_Pos			(0)
#define IRQ_IE_EX0_Msk			(0x1 << IRQ_IE_EX0_Pos)
/*------EIE2------------------------------------------------------*/
#define IRQ_EIE2_SPIIE_Pos		(7)
#define IRQ_EIE2_SPIIE_Msk		(0x1 << IRQ_EIE2_SPIIE_Pos)
#define IRQ_EIE2_I2CIE_Pos		(6)
#define IRQ_EIE2_I2CIE_Msk		(0x1 << IRQ_EIE2_I2CIE_Pos)
#define IRQ_EIE2_WDTIE_Pos		(5)
#define IRQ_EIE2_WDTIE_Msk		(0x1 << IRQ_EIE2_WDTIE_Pos)
#define IRQ_EIE2_ADCIE_Pos		(4)
#define IRQ_EIE2_ADCIE_Msk		(0x1 << IRQ_EIE2_ADCIE_Pos)
#define IRQ_EIE2_PWMIE_Pos		(3)
#define IRQ_EIE2_PWMIE_Msk		(0x1 << IRQ_EIE2_PWMIE_Pos)
#define IRQ_EIE2_ET4IE_Pos		(1)
#define IRQ_EIE2_ET4IE_Msk		(0x1 << IRQ_EIE2_ET4IE_Pos)
#define IRQ_EIE2_ET3IE_Pos		(0)
#define IRQ_EIE2_ET3IE_Msk		(0x1 << IRQ_EIE2_ET3IE_Pos)
/*------EIE3------------------------------------------------------*/
#define IRQ_EIE3_ES3_Pos		(1)
#define IRQ_EIE3_ES3_Msk		(0x1 << IRQ_EIE3_ES3_Pos)
#define IRQ_EIE3_ES2_Pos		(0)
#define IRQ_EIE3_ES2_Msk		(0x1 << IRQ_EIE3_ES2_Pos)

/*------EIF2------------------------------------------------------*/
#define IRQ_EIF2_SPIIF_Pos		(7)
#define IRQ_EIF2_SPIIF_Msk		(0x1 << IRQ_EIF2_SPIIF_Pos)
#define IRQ_EIF2_I2CIF_Pos		(6)
#define IRQ_EIF2_I2CIF_Msk		(0x1 << IRQ_EIF2_I2CIF_Pos)
#define IRQ_EIF2_ADCIF_Pos		(4)
#define IRQ_EIF2_ADCIF_Msk		(0x1 << IRQ_EIF2_ADCIF_Pos)
#define IRQ_EIF2_PWMIF_Pos		(3)
#define IRQ_EIF2_PWMIF_Msk		(0x1 << IRQ_EIF2_PWMIF_Pos)
#define IRQ_EIF2_TF4_Pos		(1)
#define IRQ_EIF2_TF4_Msk		(0x1 << IRQ_EIF2_TF4_Pos)
#define IRQ_EIF2_TF3_Pos		(0)
#define IRQ_EIF2_TF3_Msk		(0x1 << IRQ_EIF2_TF3_Pos)

/*------T2IE------------------------------------------------------*/
#define IRQ_T2IE_T2OVIE_Pos		(7)
#define IRQ_T2IE_T2OVIE_Msk		(0x1 << IRQ_T2IE_T2OVIE_Pos)
#define IRQ_T2IE_T2EXIE_Pos		(6)
#define IRQ_T2IE_T2EXIE_Msk		(0x1 << IRQ_T2IE_T2EXIE_Pos)
#define IRQ_T2IE_T2C3IE_Pos		(3)
#define IRQ_T2IE_T2C3IE_Msk		(0x1 << IRQ_T2IE_T2C3IE_Pos)
#define IRQ_T2IE_T2C2IE_Pos		(2)
#define IRQ_T2IE_T2C2IE_Msk		(0x1 << IRQ_T2IE_T2C2IE_Pos)
#define IRQ_T2IE_T2C1IE_Pos		(1)
#define IRQ_T2IE_T2C1IE_Msk		(0x1 << IRQ_T2IE_T2C1IE_Pos)
#define IRQ_T2IE_T2C0IE_Pos		(0)
#define IRQ_T2IE_T2C0IE_Msk		(0x1 << IRQ_T2IE_T2C0IE_Pos)
/*------T2IF------------------------------------------------------*/
#define IRQ_T2IF_T2F_Pos		(7)
#define IRQ_T2IF_T2F_Msk		(0x1 << IRQ_T2IF_T2F_Pos)
#define IRQ_T2IF_T2EXIF_Pos		(6)
#define IRQ_T2IF_T2EXIF_Msk		(0x1 << IRQ_T2IF_T2EXIF_Pos)
#define IRQ_T2IF_T2C3IF_Pos		(3)
#define IRQ_T2IF_T2C3IF_Msk		(0x1 << IRQ_T2IF_T2C3IF_Pos)
#define IRQ_T2IF_T2C2IF_Pos		(2)
#define IRQ_T2IF_T2C2IF_Msk		(0x1 << IRQ_T2IF_T2C2IF_Pos)
#define IRQ_T2IF_T2C1IF_Pos		(1)
#define IRQ_T2IF_T2C1IF_Msk		(0x1 << IRQ_T2IF_T2C1IF_Pos)
#define IRQ_T2IF_T2C0IF_Pos		(0)
#define IRQ_T2IF_T2C0IF_Msk		(0x1 << IRQ_T2IF_T2C0IF_Pos)






/*-----------------------------------------------------------------
**EPWM
------------------------------------------------------------------*/
/*------PWMCON----------------------------------------------------*/
#define EPWM_PWMCON_PWMRUN_Pos			(6)
#define EPWM_PWMCON_PWMRUN_Msk			(0x1 << EPWM_PWMCON_PWMRUN_Pos)
/*------PWMDTE----------------------------------------------------*/
#define EPWM_PWMDTE_PWM23DTE_Pos		(1)
#define EPWM_PWMDTE_PWM23DTE_Msk		(0x1 << EPWM_PWMDTE_PWM23DTE_Pos)
#define EPWM_PWMDTE_PWM01DTE_Pos		(0)
#define EPWM_PWMDTE_PWM01DTE_Msk		(0x1 << EPWM_PWMDTE_PWM01DTE_Pos)

/*------PWMFBKC----------------------------------------------------*/
#define EPWM_PWMFBKC_PWMFBIE_Pos		(7)
#define EPWM_PWMFBKC_PWMFBIE_Msk		(0x1 << EPWM_PWMFBKC_PWMFBIE_Pos)
#define EPWM_PWMFBKC_PWMFBF_Pos			(6)
#define EPWM_PWMFBKC_PWMFBF_Msk			(0x1 << EPWM_PWMFBKC_PWMFBF_Pos)
#define EPWM_PWMFBKC_BRKAF_Pos			(5)
#define EPWM_PWMFBKC_BRKAF_Msk			(0x1 << EPWM_PWMFBKC_BRKAF_Pos)
#define EPWM_PWMFBKC_PWMFBKSW_Pos		(4)
#define EPWM_PWMFBKC_PWMFBKSW_Msk		(0x1 << EPWM_PWMFBKC_PWMFBKSW_Pos)
#define EPWM_PWMFBKC_PWMFB1ES_Pos		(3)
#define EPWM_PWMFBKC_PWMFB1ES_Msk		(0x1 << EPWM_PWMFBKC_PWMFB1ES_Pos)
#define EPWM_PWMFBKC_PWMFB0ES_Pos		(2)
#define EPWM_PWMFBKC_PWMFB0ES_Msk		(0x1 << EPWM_PWMFBKC_PWMFB0ES_Pos)
#define EPWM_PWMFBKC_PWMFB1EN_Pos		(1)
#define EPWM_PWMFBKC_PWMFB1EN_Msk		(0x1 << EPWM_PWMFBKC_PWMFB1EN_Pos)
#define EPWM_PWMFBKC_PWMFB0EN_Pos		(0)
#define EPWM_PWMFBKC_PWMFB0EN_Msk		(0x1 << EPWM_PWMFBKC_PWMFB0EN_Pos)

/*------PWMFBRKC----------------------------------------------------*/
#define EPWM_PWMBRKC_BRKOSF_Pos			(7)
#define EPWM_PWMBRKC_BRKOSF_Msk			(0x1 << EPWM_PWMBRKC_BRKOSF_Pos)
#define EPWM_PWMBRKC_BRKRCS_Pos			(4)
#define EPWM_PWMBRKC_BRKRCS_Msk			(0x7 << EPWM_PWMBRKC_BRKRCS_Pos)
#define EPWM_PWMBRKC_BRKRCLR_Pos		(3)
#define EPWM_PWMBRKC_BRKRCLR_Msk		(0x1 << EPWM_PWMBRKC_BRKRCLR_Pos)
#define EPWM_PWMBRKC_BRKEN_Pos			(2)
#define EPWM_PWMBRKC_BRKEN_Msk			(0x1 << EPWM_PWMBRKC_BRKEN_Pos)
#define EPWM_PWMBRKC_BRKMS_Pos			(0)
#define EPWM_PWMBRKC_BRKMS_Msk			(0x3 << EPWM_PWMBRKC_BRKMS_Pos)


/*-----------------------------------------------------------------
**ACMP
------------------------------------------------------------------*/
/*------C0CON0----------------------------------------------------*/
#define ACMP_C0CON0_C0EN_Pos		(7)
#define ACMP_C0CON0_C0EN_Msk		(0x1 << ACMP_C0CON0_C0EN_Pos)
#define ACMP_C0CON0_C0COFM_Pos		(6)
#define ACMP_C0CON0_C0COFM_Msk		(0x1 << ACMP_C0CON0_C0COFM_Pos)
#define ACMP_C0CON0_C0N2G_Pos		(5)
#define ACMP_C0CON0_C0N2G_Msk		(0x1 << ACMP_C0CON0_C0N2G_Pos)
#define ACMP_C0CON0_C0NS_Pos		(3)
#define ACMP_C0CON0_C0NS_Msk		(0x3 << ACMP_C0CON0_C0NS_Pos)
#define ACMP_C0CON0_C0PS_Pos		(0)
#define ACMP_C0CON0_C0PS_Msk		(0x7 << ACMP_C0CON0_C0PS_Pos)
/*------C0CON1----------------------------------------------------*/
#define ACMP_C0CON1_C0OUT_Pos		(7)
#define ACMP_C0CON1_C0OUT_Msk		(0x1 << ACMP_C0CON1_C0OUT_Pos)
#define ACMP_C0CON1_C0CRS_Pos		(5)
#define ACMP_C0CON1_C0CRS_Msk		(0x3 << ACMP_C0CON1_C0CRS_Pos)
#define ACMP_C0CON1_C0ADJ_Pos		(0)
#define ACMP_C0CON1_C0ADJ_Msk		(0x1F<< ACMP_C0CON1_C0ADJ_Pos)
/*------C0CON2----------------------------------------------------*/
#define ACMP_C0CON2_C0POS_Pos		(5)
#define ACMP_C0CON2_C0POS_Msk		(0x1 << ACMP_C0CON2_C0POS_Pos)
#define ACMP_C0CON2_C0FE_Pos		(4)
#define ACMP_C0CON2_C0FE_Msk		(0x1 << ACMP_C0CON2_C0FE_Pos)
#define ACMP_C0CON2_C0FS_Pos		(0)
#define ACMP_C0CON2_C0FS_Msk		(0xF << ACMP_C0CON2_C0FS_Pos)
/*------C1CON0----------------------------------------------------*/
#define ACMP_C1CON0_C1EN_Pos		(7)
#define ACMP_C1CON0_C1EN_Msk		(0x1 << ACMP_C1CON0_C1EN_Pos)
#define ACMP_C1CON0_C1COFM_Pos		(6)
#define ACMP_C1CON0_C1COFM_Msk		(0x1 << ACMP_C1CON0_C1COFM_Pos)
#define ACMP_C1CON0_C1N2G_Pos		(5)
#define ACMP_C1CON0_C1N2G_Msk		(0x1 << ACMP_C1CON0_C1N2G_Pos)
#define ACMP_C1CON0_C1NS_Pos		(3)
#define ACMP_C1CON0_C1NS_Msk		(0x3 << ACMP_C1CON0_C1NS_Pos)
#define ACMP_C1CON0_C1PS_Pos		(0)
#define ACMP_C1CON0_C1PS_Msk		(0x7 << ACMP_C1CON0_C1PS_Pos)
/*------C1CON1----------------------------------------------------*/
#define ACMP_C1CON1_C1OUT_Pos		(7)
#define ACMP_C1CON1_C1OUT_Msk		(0x1 << ACMP_C1CON1_C1OUT_Pos)
#define ACMP_C1CON1_C1CRS_Pos		(5)
#define ACMP_C1CON1_C1CRS_Msk		(0x3 << ACMP_C1CON1_C1CRS_Pos)
#define ACMP_C1CON1_C1ADJ_Pos		(0)
#define ACMP_C1CON1_C1ADJ_Msk		(0x1F<< ACMP_C1CON1_C1ADJ_Pos)
/*------C1CON2----------------------------------------------------*/
#define ACMP_C1CON2_C1POS_Pos		(5)
#define ACMP_C1CON2_C1POS_Msk		(0x1 << ACMP_C1CON2_C1POS_Pos)
#define ACMP_C1CON2_C1FE_Pos		(4)
#define ACMP_C1CON2_C1FE_Msk		(0x1 << ACMP_C1CON2_C1FE_Pos)
#define ACMP_C1CON2_C1FS_Pos		(0)
#define ACMP_C1CON2_C1FS_Msk		(0xF << ACMP_C1CON2_C1FS_Pos)
/*------CNVRCON---------------------------------------------------*/
#define ACMP_CNVRCON_CNDIVS_Pos		(7)
#define ACMP_CNVRCON_CNDIVS_Msk		(0x1 << ACMP_CNVRCON_CNDIVS_Pos)
#define ACMP_CNVRCON_CNSVR_Pos		(6)
#define ACMP_CNVRCON_CNSVR_Msk		(0x1 << ACMP_CNVRCON_CNSVR_Pos)
#define ACMP_CNVRCON_CNSVS_Pos		(0)
#define ACMP_CNVRCON_CNSVS_Msk		(0x3F << ACMP_CNVRCON_CNSVS_Pos)
/*------CNFBCON---------------------------------------------------*/
#define ACMP_CNFBCON_C1FBPEN_Pos	(7)
#define ACMP_CNFBCON_C1FBPEN_Msk	(0x1 << ACMP_CNFBCON_C1FBPEN_Pos)
#define ACMP_CNFBCON_C0FBPEN_Pos	(6)
#define ACMP_CNFBCON_C0FBPEN_Msk	(0x1 << ACMP_CNFBCON_C0FBPEN_Pos)
#define ACMP_CNFBCON_C1FBPS_Pos		(5)
#define ACMP_CNFBCON_C1FBPS_Msk		(0x1 << ACMP_CNFBCON_C1FBPS_Pos)
#define ACMP_CNFBCON_C0FBPS_Pos		(4)
#define ACMP_CNFBCON_C0FBPS_Msk		(0x1 << ACMP_CNFBCON_C0FBPS_Pos)
#define ACMP_CNFBCON_C1FBEEN_Pos	(3)
#define ACMP_CNFBCON_C1FBEEN_Msk	(0x1 << ACMP_CNFBCON_C1FBEEN_Pos)
#define ACMP_CNFBCON_C0FBEEN_Pos	(2)
#define ACMP_CNFBCON_C0FBEEN_Msk	(0x1 << ACMP_CNFBCON_C0FBEEN_Pos)
#define ACMP_CNFBCON_C1FBES_Pos		(1)
#define ACMP_CNFBCON_C1FBES_Msk		(0x1 << ACMP_CNFBCON_C1FBES_Pos)
#define ACMP_CNFBCON_C0FBES_Pos		(0)
#define ACMP_CNFBCON_C0FBES_Msk		(0x1 << ACMP_CNFBCON_C0FBES_Pos)
/*------CNIE-------------------------------------------------------*/
#define ACMP_CNIE_C1IE_Pos			(1)
#define ACMP_CNIE_C1IE_Msk			(0x1 << ACMP_CNIE_C1IE_Pos)
#define ACMP_CNIE_C0IE_Pos			(0)
#define ACMP_CNIE_C0IE_Msk			(0x1 << ACMP_CNIE_C0IE_Pos)
/*------CNIF-------------------------------------------------------*/
#define ACMP_CNIF_C1IF_Pos			(1)
#define ACMP_CNIF_C1IF_Msk			(0x1 << ACMP_CNIF_C1IF_Pos)
#define ACMP_CNIF_C0IF_Pos			(0)
#define ACMP_CNIF_C0IF_Msk			(0x1 << ACMP_CNIF_C0IF_Pos)

/*------C0HYS-------------------------------------------------------*/
#define ACMP_C0HYS_PNS_Pos			(2)
#define ACMP_C0HYS_PNS_Msk			(0x3 << ACMP_C0HYS_PNS_Pos)
#define ACMP_C0HYS_S_Pos			(0)
#define ACMP_C0HYS_S_Msk			(0x3 << ACMP_C0HYS_S_Pos)
/*------C1HYS-------------------------------------------------------*/
#define ACMP_C1HYS_PNS_Pos			(2)
#define ACMP_C1HYS_PNS_Msk			(0x3 << ACMP_C1HYS_PNS_Pos)
#define ACMP_C1HYS_S_Pos			(0)
#define ACMP_C1HYS_S_Msk			(0x3 << ACMP_C1HYS_S_Pos)

/*-----------------------------------------------------------------
**ADC
------------------------------------------------------------------*/
/*------ADCON0----------------------------------------------------*/
#define ADC_ADCON0_ADFM_Pos			(6)
#define ADC_ADCON0_ADFM_Msk			(0x1 << ADC_ADCON0_ADFM_Pos)
#define ADC_ADCON0_ANACH_Pos		(2)
#define ADC_ADCON0_ANACH_Msk		(0xF << ADC_ADCON0_ANACH_Pos)
#define ADC_ADCON0_ADGO_Pos			(1)
#define ADC_ADCON0_ADGO_Msk			(0x1 << ADC_ADCON0_ADGO_Pos)
/*------ADCON1----------------------------------------------------*/
#define ADC_ADCON1_ADEN_Pos			(7)
#define ADC_ADCON1_ADEN_Msk			(0x1 << ADC_ADCON1_ADEN_Pos)
#define ADC_ADCON1_ADCKS_Pos		(4)
#define ADC_ADCON1_ADCKS_Msk		(0x7 << ADC_ADCON1_ADCKS_Pos)
/*------ADCON2----------------------------------------------------*/
#define ADC_ADCON2_ADCEX_Pos		(7)
#define ADC_ADCON2_ADCEX_Msk		(0x1 << ADC_ADCON2_ADCEX_Pos)
#define ADC_ADCON2_ADTGS_Pos		(4)
#define ADC_ADCON2_ADTGS_Msk		(0x3 << ADC_ADCON2_ADTGS_Pos)
#define ADC_ADCON2_ADEGS_Pos		(2)
#define ADC_ADCON2_ADEGS_Msk		(0x3 << ADC_ADCON2_ADEGS_Pos)
/*------ADCMPC----------------------------------------------------*/
#define ADC_ADCMPC_ADFBEN_Pos		(7)
#define ADC_ADCMPC_ADFBEN_Msk		(0x1 << ADC_ADCMPC_ADFBEN_Pos)
#define ADC_ADCMPC_ADCMPPS_Pos		(6)
#define ADC_ADCMPC_ADCMPPS_Msk		(0x1 << ADC_ADCMPC_ADCMPPS_Pos)
#define ADC_ADCMPC_ADCMPO_Pos		(4)
#define ADC_ADCMPC_ADCMPO_Msk		(0x1 << ADC_ADCMPC_ADCMPO_Pos)
#define ADC_ADCMPC_ADDLY_Pos		(0)
#define ADC_ADCMPC_ADDLY_Msk		(0x3 << ADC_ADCMPC_ADDLY_Pos)
/*------ADCLDO----------------------------------------------------*/
#define ADC_ADCLDO_LDOEN_Pos		(7)
#define ADC_ADCLDO_LDOEN_Msk		(0x1 << ADC_ADCLDO_LDOEN_Pos)
#define ADC_ADCLDO_VSEL_Pos			(5)
#define ADC_ADCLDO_VSEL_Msk			(0x3 << ADC_ADCLDO_VSEL_Pos)
#define ADC_ADCLDO_OUTEN_Pos		(4)
#define ADC_ADCLDO_OUTEN_Msk		(0x1 << ADC_ADCLDO_OUTEN_Pos)
/*-----------------------------------------------------------------
**Timer
------------------------------------------------------------------*/
/*------TMOD------------------------------------------------------*/
#define TMR_TMOD_GATE1_Pos				(7)
#define TMR_TMOD_GATE1_Msk				(0x1 << TMR_TMOD_GATE1_Pos)
#define TMR_TMOD_CT1_Pos				(6)
#define TMR_TMOD_CT1_Msk				(0x1 << TMR_TMOD_CT1_Pos)
#define TMR_TMOD_T1Mn_Pos				(4)
#define TMR_TMOD_T1Mn_Msk				(0x3 << TMR_TMOD_T1Mn_Pos)
#define TMR_TMOD_GATE0_Pos				(3)
#define TMR_TMOD_GATE0_Msk				(0x1 << TMR_TMOD_GATE0_Pos)
#define TMR_TMOD_CT0_Pos				(2)
#define TMR_TMOD_CT0_Msk				(0x1 << TMR_TMOD_CT0_Pos)
#define TMR_TMOD_T0Mn_Pos				(0)
#define TMR_TMOD_T0Mn_Msk				(0x3 << TMR_TMOD_T0Mn_Pos)
/*------TCON------------------------------------------------------*/
#define TMR_TCON_TF1_Pos				(7)
#define TMR_TCON_TF1_Msk				(0x1 << TMR_TCON_TF1_Pos)
#define TMR_TCON_TR1_Pos				(6)
#define TMR_TCON_TR1_Msk				(0x1 << TMR_TCON_TR1_Pos)
#define TMR_TCON_TF0_Pos				(5)
#define TMR_TCON_TF0_Msk				(0x1 << TMR_TCON_TF0_Pos)
#define TMR_TCON_TR0_Pos				(4)
#define TMR_TCON_TR0_Msk				(0x1 << TMR_TCON_TR0_Pos)
#define TMR_TCON_IE1_Pos				(3)
#define TMR_TCON_IE1_Msk				(0x1 << TMR_TCON_IE1_Pos)
#define TMR_TCON_IT1_Pos				(2)
#define TMR_TCON_IT1_Msk				(0x1 << TMR_TCON_IT1_Pos)
#define TMR_TCON_IE0_Pos				(1)
#define TMR_TCON_IE0_Msk				(0x1 << TMR_TCON_IE0_Pos)
#define TMR_TCON_IT0_Pos				(0)
#define TMR_TCON_IT0_Msk				(0x1 << TMR_TCON_IT0_Pos)
/*------CKCON-----------------------------------------------------*/
#define TMR_CKCON_WTSn_Pos				(5)
#define TMR_CKCON_WTSn_Msk				(0x7 << TMR_CKCON_WTSn_Pos)
#define TMR_CKCON_T1M_Pos				(4)
#define TMR_CKCON_T1M_Msk				(0x1 << TMR_CKCON_T1M_Pos)
#define TMR_CKCON_T0M_Pos				(3)
#define TMR_CKCON_T0M_Msk				(0x1 << TMR_CKCON_T0M_Pos)
/*------T2CON-----------------------------------------------------*/
#define TMR_T2CON_T2PS_Pos				(7)
#define TMR_T2CON_T2PS_Msk				(0x1 << TMR_T2CON_T2PS_Pos)
#define TMR_T2CON_I3FR_Pos				(6)
#define TMR_T2CON_I3FR_Msk				(0x1 << TMR_T2CON_I3FR_Pos)
#define TMR_T2CON_CAPES_Pos				(5)
#define TMR_T2CON_CAPES_Msk				(0x1 << TMR_T2CON_CAPES_Pos)
#define TMR_T2CON_T2Rn_Pos				(3)
#define TMR_T2CON_T2Rn_Msk				(0x3 << TMR_T2CON_T2Rn_Pos)
#define TMR_T2CON_T2CM_Pos				(2)
#define TMR_T2CON_T2CM_Msk				(0x1 << TMR_T2CON_T2CM_Pos)
#define TMR_T2CON_T2In_Pos				(0)
#define TMR_T2CON_T2In_Msk				(0x3 << TMR_T2CON_T2In_Pos)

/*------CCEN------------------------------------------------------*/
#define TMR_CCEN_CMn3_Pos				(6)
#define TMR_CCEN_CMn3_Msk				(0x3 << TMR_CCEN_CMn3_Pos)
#define TMR_CCEN_CMn2_Pos				(4)
#define TMR_CCEN_CMn2_Msk				(0x3 << TMR_CCEN_CMn2_Pos)
#define TMR_CCEN_CMn1_Pos				(2)
#define TMR_CCEN_CMn1_Msk				(0x3 << TMR_CCEN_CMn1_Pos)
#define TMR_CCEN_CMn0_Pos				(0)
#define TMR_CCEN_CMn0_Msk				(0x3 << TMR_CCEN_CMn0_Pos)

/*------T34MOD----------------------------------------------------*/
#define TMR_T34MOD_TR4_Pos				(7)
#define TMR_T34MOD_TR4_Msk				(0x1 << TMR_T34MOD_TR4_Pos)
#define TMR_T34MOD_T4M_Pos				(6)
#define TMR_T34MOD_T4M_Msk				(0x1 << TMR_T34MOD_T4M_Pos)
#define TMR_T34MOD_T4Mn_Pos				(4)
#define TMR_T34MOD_T4Mn_Msk				(0x3 << TMR_T34MOD_T4Mn_Pos)
#define TMR_T34MOD_TR3_Pos				(3)
#define TMR_T34MOD_TR3_Msk				(0x1 << TMR_T34MOD_TR3_Pos)
#define TMR_T34MOD_T3M_Pos				(2)
#define TMR_T34MOD_T3M_Msk				(0x1 << TMR_T34MOD_T3M_Pos)
#define TMR_T34MOD_T3Mn_Pos				(0)
#define TMR_T34MOD_T3Mn_Msk				(0x3 << TMR_T34MOD_T3Mn_Pos)

/*-----------------------------------------------------------------
**UART
------------------------------------------------------------------*/
/*------SCON0------------------------------------------------------*/
#define UART_SCON0_U0SMn_Pos			(6)
#define UART_SCON0_U0SMn_Msk			(0x3 << UART_SCON0_U0SMn_Pos)
#define UART_SCON0_U0SM2_Pos			(5)
#define UART_SCON0_U0SM2_Msk			(0x1 << UART_SCON0_U0SM2_Pos)
#define UART_SCON0_U0REN_Pos			(4)
#define UART_SCON0_U0REN_Msk			(0x1 << UART_SCON0_U0REN_Pos)
#define UART_SCON0_U0TB8_Pos			(3)
#define UART_SCON0_U0TB8_Msk			(0x1 << UART_SCON0_U0TB8_Pos)
#define UART_SCON0_U0RB8_Pos			(2)
#define UART_SCON0_U0RB8_Msk			(0x1 << UART_SCON0_U0RB8_Pos)
#define UART_SCON0_TI0_Pos				(1)
#define UART_SCON0_TI0_Msk				(0x1 << UART_SCON0_TI0_Pos)
#define UART_SCON0_RI0_Pos				(0)
#define UART_SCON0_RI0_Msk				(0x1 << UART_SCON0_RI0_Pos)

/*------SCON2------------------------------------------------------*/
#define UART_SCON2_U2SMn_Pos			(6)
#define UART_SCON2_U2SMn_Msk			(0x3 << UART_SCON2_U2SMn_Pos)
#define UART_SCON2_U2SM2_Pos			(5)
#define UART_SCON2_U2SM2_Msk			(0x1 << UART_SCON2_U2SM2_Pos)
#define UART_SCON2_U2REN_Pos			(4)
#define UART_SCON2_U2REN_Msk			(0x1 << UART_SCON2_U2REN_Pos)
#define UART_SCON2_U2TB8_Pos			(3)
#define UART_SCON2_U2TB8_Msk			(0x1 << UART_SCON2_U2TB8_Pos)
#define UART_SCON2_U2RB8_Pos			(2)
#define UART_SCON2_U2RB8_Msk			(0x1 << UART_SCON2_U2RB8_Pos)
#define UART_SCON2_TI2_Pos				(1)
#define UART_SCON2_TI2_Msk				(0x1 << UART_SCON2_TI2_Pos)
#define UART_SCON2_RI2_Pos				(0)
#define UART_SCON2_RI2_Msk				(0x1 << UART_SCON2_RI2_Pos)
/*------SCON3------------------------------------------------------*/
#define UART_SCON3_U3SMn_Pos			(6)
#define UART_SCON3_U3SMn_Msk			(0x3 << UART_SCON3_U3SMn_Pos)
#define UART_SCON3_U3SM2_Pos			(5)
#define UART_SCON3_U3SM2_Msk			(0x1 << UART_SCON3_U3SM2_Pos)
#define UART_SCON3_U3REN_Pos			(4)
#define UART_SCON3_U3REN_Msk			(0x1 << UART_SCON3_U3REN_Pos)
#define UART_SCON3_U3TB8_Pos			(3)
#define UART_SCON3_U3TB8_Msk			(0x1 << UART_SCON3_U3TB8_Pos)
#define UART_SCON3_U3RB8_Pos			(2)
#define UART_SCON3_U3RB8_Msk			(0x1 << UART_SCON3_U3RB8_Pos)
#define UART_SCON3_TI3_Pos				(1)
#define UART_SCON3_TI3_Msk				(0x1 << UART_SCON3_TI3_Pos)
#define UART_SCON3_RI3_Pos				(0)
#define UART_SCON3_RI3_Msk				(0x1 << UART_SCON3_RI3_Pos)





/*------BRTCON-----------------------------------------------------*/
#define UART_BRTCON_BRTEN_Pos			(7)
#define UART_BRTCON_BRTEN_Msk			(0x1 << UART_BRTCON_BRTEN_Pos)
#define UART_BRTCON_BRTCKDIV_Pos		(0)
#define UART_BRTCON_BRTCKDIV_Msk		(0x7 << UART_BRTCON_BRTCKDIV_Pos)


/*-----------------------------------------------------------------
**System
------------------------------------------------------------------*/
/*-----------------------------------------------------------------
**System CLK
------------------------------------------------------------------*/
/*------SCKSEL----------------------------------------------------*/
#define SYS_SCKSEL_SEL_Pos				(4)
#define SYS_SCKSEL_SEL_Msk				(0x1 << SYS_SCKSEL_SEL_Pos)
#define SYS_SCKSEL_WRITE_Pos			(3)
#define SYS_SCKSEL_WRITE_Msk			(0x1 << SYS_SCKSEL_WRITE_Pos)
#define SYS_SCKSEL_CKSEL_Pos			(0)
#define SYS_SCKSEL_CKSEL_Msk			(0x7 << SYS_SCKSEL_CKSEL_Pos)

/*------SCKSTAU---------------------------------------------------*/
#define SYS_SCKSTAU_LSIF_Pos			(7)
#define SYS_SCKSTAU_LSIF_Msk			(0x1 << SYS_SCKSTAU_LSIF_Pos)
#define SYS_SCKSTAU_LSEF_Pos			(6)
#define SYS_SCKSTAU_LSEF_Msk			(0x1 << SYS_SCKSTAU_LSEF_Pos)
#define SYS_SCKSTAU_HSEF_Pos			(5)
#define SYS_SCKSTAU_HSEF_Msk			(0x1 << SYS_SCKSTAU_HSEF_Pos)
#define SYS_SCKSTAU_HSIF_Pos			(4)
#define SYS_SCKSTAU_HSIF_Msk			(0x1 << SYS_SCKSTAU_HSIF_Pos)

/*------PCON------------------------------------------------------*/
#define SYS_PCON_SMOD0_Pos			(7)
#define SYS_PCON_SMOD0_Msk			(0x1 << SYS_PCON_SMOD0_Pos)
#define SYS_PCON_SWE_Pos			(2)
#define SYS_PCON_SWE_Msk			(0x1 << SYS_PCON_SWE_Pos)
#define SYS_PCON_STOP_Pos			(1)
#define SYS_PCON_STOP_Msk			(0x1 << SYS_PCON_STOP_Pos)
#define SYS_PCON_IDLE_Pos			(0)
#define SYS_PCON_IDLE_Msk			(0x1 << SYS_PCON_IDLE_Pos)

/*------FUNCCR----------------------------------------------------*/
#define SYS_FUNCCR_UART0_CKS_Pos	(0)
#define SYS_FUNCCR_UART0_CKS_Msk	(0x7 << SYS_FUNCCR_UART0_CKS_Pos)

/*------SCKSEL----------------------------------------------------*/
#define SYS_SCKSEL_SEL_Pos			(4)
#define SYS_SCKSEL_SEL_Msk			(0x1 << SYS_SCKSEL_SEL_Pos)
#define SYS_SCKSEL_WRITE_Pos		(3)
#define SYS_SCKSEL_WRITE_Msk		(0x1 << SYS_SCKSEL_WRITE_Pos)
#define SYS_SCKSEL_CKSEL_Pos		(0)
#define SYS_SCKSEL_CKSEL_Msk		(0x7 << SYS_SCKSEL_CKSEL_Pos)
/*------CKSTAU----------------------------------------------------*/
#define SYS_CKSTAU_LSI_F_Pos		(7)
#define SYS_CKSTAU_LSI_F_Msk		(0x1 << SYS_CKSTAU_LSI_F_Pos)
#define SYS_CKSTAU_LSE_F_Pos		(6)
#define SYS_CKSTAU_LSE_F_Msk		(0x1 << SYS_CKSTAU_LSE_F_Pos)
#define SYS_CKSTAU_HSE_F_Pos		(5)
#define SYS_CKSTAU_HSE_F_Msk		(0x1 << SYS_CKSTAU_HSE_F_Pos)
#define SYS_CKSTAU_HSI_F_Pos		(4)
#define SYS_CKSTAU_HSI_F_Msk		(0x1 << SYS_CKSTAU_HSI_F_Pos)
#define SYS_CKSTAU_LSI_E_Pos		(3)
#define SYS_CKSTAU_LSI_E_Msk		(0x1 << SYS_CKSTAU_LSI_E_Pos)
#define SYS_CKSTAU_LSE_E_Pos		(2)
#define SYS_CKSTAU_LSE_E_Msk		(0x1 << SYS_CKSTAU_LSE_E_Pos)
#define SYS_CKSTAU_HSE_E_Pos		(1)
#define SYS_CKSTAU_HSE_E_Msk		(0x1 << SYS_CKSTAU_HSE_E_Pos)
#define SYS_CKSTAU_HSI_E_Pos		(0)
#define SYS_CKSTAU_HSI_E_Msk		(0x1 << SYS_CKSTAU_HSI_E_Pos)
/*------WKTSET----------------------------------------------------*/
#define SYS_WKTSET_WUEN_Pos			(7)
#define SYS_WKTSET_WUEN_Msk			(0x1 << SYS_WKTSET_WUEN_Pos)
#define SYS_WKTSET_XTCNTEN_Pos		(6)
#define SYS_WKTSET_XTCNTEN_Msk		(0x1 << SYS_WKTSET_XTCNTEN_Pos)
#define SYS_WKTSET_XTSEL_Pos		(5)
#define SYS_WKTSET_XTSEL_Msk		(0x1 << SYS_WKTSET_XTSEL_Pos)
#define SYS_WKTSET_XTINE_Pos		(1)
#define SYS_WKTSET_XTINE_Msk		(0x1 << SYS_WKTSET_XTINE_Pos)
#define SYS_WKTSET_XTINF_Pos		(0)
#define SYS_WKTSET_XTINF_Msk		(0x1 << SYS_WKTSET_XTINF_Pos)
/*------XT_SCM----------------------------------------------------*/
#define SYS_XTSCM_SCMEN_Pos			(7)
#define SYS_XTSCM_SCMEN_Msk			(0x1 << SYS_XTSCM_SCMEN_Pos)
#define SYS_XTSCM_SCMIE_Pos			(6)
#define SYS_XTSCM_SCMIE_Msk			(0x1 << SYS_XTSCM_SCMIE_Pos)
#define SYS_XTSCM_SCMIF_Pos			(1)
#define SYS_XTSCM_SCMIF_Msk			(0x1 << SYS_XTSCM_SCMIF_Pos)
#define SYS_XTSCM_SCMSTA_Pos		(0)
#define SYS_XTSCM_SCMSTA_Msk		(0x1 << SYS_XTSCM_SCMSTA_Pos)

/*-----------------------------------------------------------------
**WDT
------------------------------------------------------------------*/
/*------WDCON-----------------------------------------------------*/
#define WDT_WDCON_SWRST_Pos			(7)
#define WDT_WDCON_SWRST_Msk			(0x1 << WDT_WDCON_SWRST_Pos)
#define WDT_WDCON_PORF_Pos			(6)
#define WDT_WDCON_PORF_Msk			(0x1 << WDT_WDCON_PORF_Pos)
#define WDT_WDCON_WDTIF_Pos			(3)
#define WDT_WDCON_WDTIF_Msk			(0x1 << WDT_WDCON_WDTIF_Pos)
#define WDT_WDCON_WDTRF_Pos			(2)
#define WDT_WDCON_WDTRF_Msk			(0x1 << WDT_WDCON_WDTRF_Pos)
#define WDT_WDCON_WDTRE_Pos			(1)
#define WDT_WDCON_WDTRE_Msk			(0x1 << WDT_WDCON_WDTRE_Pos)
#define WDT_WDCON_WDTCLR_Pos		(0)
#define WDT_WDCON_WDTCLR_Msk		(0x1 << WDT_WDCON_WDTCLR_Pos)
/*-----------------------------------------------------------------
**I2C
------------------------------------------------------------------*/
/*------I2CMCR----------------------------------------------------*/
#define I2C_I2CMCR_RSTS_Pos			(7)
#define I2C_I2CMCR_RSTS_Msk			(0x1 << I2C_I2CMCR_RSTS_Pos)
#define I2C_I2CMCR_ACK_Pos			(3)
#define I2C_I2CMCR_ACK_Msk			(0x1 << I2C_I2CMCR_ACK_Pos)
#define I2C_I2CMCR_STOP_Pos			(2)
#define I2C_I2CMCR_STOP_Msk			(0x1 << I2C_I2CMCR_STOP_Pos)
#define I2C_I2CMCR_START_Pos		(1)
#define I2C_I2CMCR_START_Msk		(0x1 << I2C_I2CMCR_START_Pos)
#define I2C_I2CMCR_RUN_Pos			(0)
#define I2C_I2CMCR_RUN_Msk			(0x1 << I2C_I2CMCR_RUN_Pos)
/*------I2CMSR----------------------------------------------------*/
#define I2C_I2CMSR_I2CMIF_Pos		(7)
#define I2C_I2CMSR_I2CMIF_Msk		(0x1 << I2C_I2CMSR_I2CMIF_Pos)
#define I2C_I2CMSR_BUS_BUSY_Pos		(6)
#define I2C_I2CMSR_BUS_BUSY_Msk		(0x1 << I2C_I2CMSR_BUS_BUSY_Pos)
#define I2C_I2CMSR_IDLE_Pos			(5)
#define I2C_I2CMSR_IDLE_Msk			(0x1 << I2C_I2CMSR_IDLE_Pos)
#define I2C_I2CMSR_ARB_LOST_Pos		(4)
#define I2C_I2CMSR_ARB_LOST_Msk		(0x1 << I2C_I2CMSR_ARB_LOST_Pos)
#define I2C_I2CMSR_DATA_ACK_Pos		(3)
#define I2C_I2CMSR_DATA_ACK_Msk		(0x1 << I2C_I2CMSR_DATA_ACK_Pos)
#define I2C_I2CMSR_ADD_ACK_Pos		(2)
#define I2C_I2CMSR_ADD_ACK_Msk		(0x1 << I2C_I2CMSR_ADD_ACK_Pos)
#define I2C_I2CMSR_ERROR_Pos		(1)
#define I2C_I2CMSR_ERROR_Msk		(0x1 << I2C_I2CMSR_ERROR_Pos)
#define I2C_I2CMSR_BUSY_Pos			(0)
#define I2C_I2CMSR_BUSY_Msk		(0x1 << I2C_I2CMSR_BUSY_Pos)
/*------I2CMSA----------------------------------------------------*/
#define I2C_I2CMSA_SAn_Pos			(1)
#define I2C_I2CMSA_SAn_Msk			(0x7F << I2C_I2CMSA_SAn_Pos)
#define I2C_I2CMSA_RS_Pos			(0)
#define I2C_I2CMSA_RS_Msk			(0x1 << I2C_I2CMSA_RS_Pos)
/*------I2CSCR----------------------------------------------------*/
#define I2C_I2CSCR_RSTS_Pos			(7)
#define I2C_I2CSCR_RSTS_Msk			(0x1 << I2C_I2CSCR_RSTS_Pos)
#define I2C_I2CSCR_DA_Pos			(0)
#define I2C_I2CSCR_DA_Msk			(0x1 << I2C_I2CSCR_DA_Pos)
/*------I2CSSR----------------------------------------------------*/
#define I2C_I2CSSR_SENDFIN_Pos		(2)
#define I2C_I2CSSR_SENDFIN_Msk		(0x1 << I2C_I2CSCR_RSTS_Pos)
#define I2C_I2CSSR_TREQ_Pos			(1)
#define I2C_I2CSSR_TREQ_Msk			(0x1 << I2C_I2CSSR_TREQ_Pos)
#define I2C_I2CSSR_RREQ_Pos			(0)
#define I2C_I2CSSR_RREQ_Msk			(0x1 << I2C_I2CSSR_RREQ_Pos)
/*-----------------------------------------------------------------
**BUZZER
------------------------------------------------------------------*/
/*------BUZCON----------------------------------------------------*/
#define BUZZER_BUZCON_BUZEN_Pos		(7)
#define BUZZER_BUZCON_BUZEN_Msk		(0x1 << BUZZER_BUZCON_BUZEN_Pos)
#define BUZZER_BUZCON_BUZCKS_Pos	(0)
#define BUZZER_BUZCON_BUZCKS_Msk	(0x3 << BUZZER_BUZCON_BUZCKS_Pos)
/*-----------------------------------------------------------------
**FLASH
------------------------------------------------------------------*/
/*------FLASH----------------------------------------------------*/
#define FLASH_MCTRL_MERR_Pos		(5)
#define FLASH_MCTRL_MERR_Msk		(0x1 << FLASH_MCTRL_MERR_Pos)
#define FLASH_MCTRL_MREG_Pos		(4)
#define FLASH_MCTRL_MREG_Msk		(0x1 << FLASH_MCTRL_MREG_Pos)
#define FLASH_MCTRL_MMODE_Pos		(2)
#define FLASH_MCTRL_MMODE_Msk		(0x3 << FLASH_MCTRL_MMODE_Pos)
#define FLASH_MCTRL_CRCADR_Pos		(1)
#define FLASH_MCTRL_CRCADR_Msk		(0x1 << FLASH_MCTRL_CRCADR_Pos)
#define FLASH_MCTRL_MSTART_Pos		(0)
#define FLASH_MCTRL_MSTART_Msk		(0x1 << FLASH_MCTRL_MSTART_Pos)


/*-----------------------------------------------------------------
**SPI
------------------------------------------------------------------*/
/*------SPCR------------------------------------------------------*/
#define SPI_SPCR_SPEN_Pos			(6)
#define SPI_SPCR_SPEN_Msk			(0x1 << SPI_SPCR_SPEN_Pos)
#define SPI_SPCR_SPR2_Pos			(5)
#define SPI_SPCR_SPR2_Msk			(0x1 << SPI_SPCR_SPR2_Pos)
#define SPI_SPCR_MSTR_Pos			(4)
#define SPI_SPCR_MSTR_Msk			(0x1 << SPI_SPCR_MSTR_Pos)
#define SPI_SPCR_CPOL_Pos			(3)
#define SPI_SPCR_CPOL_Msk			(0x1 << SPI_SPCR_CPOL_Pos)
#define SPI_SPCR_CPHA_Pos			(2)
#define SPI_SPCR_CPHA_Msk			(0x1 << SPI_SPCR_CPHA_Pos)
#define SPI_SPCR_SPRn_Pos			(0)
#define SPI_SPCR_SPRn_Msk			(0x3 << SPI_SPCR_SPRn_Pos)

/*------SPSR------------------------------------------------------*/
#define SPI_SPSR_SPISIF_Pos			(7)
#define SPI_SPSR_SPISIF_Msk			(0x1 << SPI_SPSR_SPISIF_Pos)
#define SPI_SPSR_WCOL_Pos			(6)
#define SPI_SPSR_WCOL_Msk			(0x1 << SPI_SPSR_WCOL_Pos)
#define SPI_SPSR_SSCEN_Pos			(0)
#define SPI_SPSR_SSCEN_Msk			(0x1 << SPI_SPSR_SSCEN_Pos)

/*-----------------------------------------------------------------
**LSE
------------------------------------------------------------------*/
/*------LSE------------------------------------------------------*/
#define LSE_LSECON_LSEEN_Pos		(7)
#define LSE_LSECON_LSEEN_Msk		(0x1 << LSE_LSECON_LSEEN_Pos)
#define LSE_LSECON_LSEWUEN_Pos		(6)
#define LSE_LSECON_LSEWUEN_Msk		(0x1 << LSE_LSECON_LSEWUEN_Pos)
#define LSE_LSECON_LSECNTEN_Pos		(5)
#define LSE_LSECON_LSECNTEN_Msk		(0x1 << LSE_LSECON_LSECNTEN_Pos)
#define LSE_LSECON_LSESTA_Pos		(4)
#define LSE_LSECON_LSESTA_Msk		(0x1 << LSE_LSECON_LSESTA_Pos)
#define LSE_LSECON_LSEIE_Pos		(3)
#define LSE_LSECON_LSEIE_Msk		(0x1 << LSE_LSECON_LSEIE_Pos)
#define LSE_LSECON_LSEIF_Pos		(0)
#define LSE_LSECON_LSEIF_Msk		(0x1 << LSE_LSECON_LSEIF_Pos)

/*-----------------------------------------------------------------
**LVD
------------------------------------------------------------------*/
/*------LVDCON----------------------------------------------------*/
#define LVD_LVDCON_LVDSEL_Pos		(4)
#define LVD_LVDCON_LVDSEL_Msk		(0xF << LVD_LVDCON_LVDSEL_Pos)
#define LVD_LVDCON_LVDEN_Pos		(3)
#define LVD_LVDCON_LVDEN_Msk		(0x1 << LVD_LVDCON_LVDEN_Pos)
#define LVD_LVDCON_LVDINTE_Pos		(1)
#define LVD_LVDCON_LVDINTE_Msk		(0x1 << LVD_LVDCON_LVDINTE_Pos)
#define LVD_LVDCON_LVDINTF_Pos		(0)
#define LVD_LVDCON_LVDINTF_Msk		(0x1 << LVD_LVDCON_LVDINTF_Pos)

/*-----------------------------------------------------------------
**WUT
------------------------------------------------------------------*/
/*------WUTCRH----------------------------------------------------*/
#define WUT_WUTCRH_WUTEN_Pos		(7)
#define WUT_WUTCRH_WUTEN_Msk		(0x1 << WUT_WUTCRH_WUTEN_Pos)
#define WUT_WUTCRH_WUTPS_Pos		(4)
#define WUT_WUTCRH_WUTPS_Msk		(0x3 << WUT_WUTCRH_WUTPS_Pos)
#define WUT_WUTCRH_WUTD_Pos			(0)
#define WUT_WUTCRH_WUTD_Msk			(0xF << WUT_WUTCRH_WUTD_Pos)

/*-----------------------------------------------------------------
**LCD
------------------------------------------------------------------*/
/*------LCDCON0----------------------------------------------------*/
#define LCD_LCDCON0_EN_Pos			(7)
#define LCD_LCDCON0_EN_Msk			(0x1 << LCD_LCDCON0_EN_Pos)
#define LCD_LCDCON0_FRAME_Pos		(6)
#define LCD_LCDCON0_FRAME_Msk		(0x1 << LCD_LCDCON0_FRAME_Pos)
#define LCD_LCDCON0_ISEL_Pos		(0)
#define LCD_LCDCON0_IESL_Msk		(0x3 << LCD_LCDCON0_ISEL_Pos)

/*-----------------------------------------------------------------
**????¨C?????¡­???¡ì?¡§???¡ª??¨C???Priority Module Number
------------------------------------------------------------------*/
typedef enum  en_Priority_Module{
	IRQ_INT0	=0,
	IRQ_TMR0	=1,
	IRQ_INT1	=2,
	IRQ_TMR1	=3,
	IRQ_UART0	=4,
	IRQ_TMR2	=5,
	IRQ_P0		=8,
	IRQ_P1		=9,
	IRQ_P2		=10,
	IRQ_P3		=13,
	IRQ_ACMP	=15,
	IRQ_TMR3	=16,
	IRQ_TMR4	=17,
	IRQ_EPWM	=19,
	IRQ_ADC 	=20,
	IRQ_WDT  	=21,
	IRQ_I2C  	=22,
	IRQ_SPI  	=23,
	IRQ_LSE_SCM =26,
	IRQ_LVD	    =27,

}en_Priority_Module_t;

/*-----------------------------------------------------------------
**????¨C?????¡­????IRQPriority
------------------------------------------------------------------*/
#define  IRQ_PRIORITY_LOW		(0x00)
#define  IRQ_PRIORITY_HIGH		(0x01)

/********************************************************************************
 ** \brief	 IRQ_SET_PRIORITY
 **			 ¨¨?????????¨C?????¡­????
 ** \param [in] none
 ** \return  none
 ******************************************************************************/
#define  IRQ_SET_PRIORITY(IRQ_Module, IRQPriority)  do{\
														if(IRQ_Module <8)\
														{\
															IP &= ~(1<< IRQ_Module);\
															IP |=(IRQPriority<< IRQ_Module);\
														}\
														else if(IRQ_Module <16)\
														{\
															EIP1 &= ~(1<< (IRQ_Module-8));\
															EIP1 |= (IRQPriority<< (IRQ_Module-8));\
														}\
														else if(IRQ_Module <24)\
														{\
															EIP2 &= ~(1<< (IRQ_Module-16));\
															EIP2 |=(IRQPriority<< (IRQ_Module-16));\
														}\
														else if(IRQ_Module <32)\
														{\
															EIP3 &= ~(1<< (IRQ_Module-24));\
															EIP3 |=(IRQPriority<< (IRQ_Module-24));\
														}\
													}while(0)

/********************************************************************************
 ** \brief	 IRQ_ALL_ENABLE
 **			 ???¨¨???€?????¨C?
 ** \param [in] none
 ** \return  none
 ******************************************************************************/
#define  IRQ_ALL_ENABLE()		do{\
									EA =1;\
								  }while(0)
/********************************************************************************
 ** \brief	 IRQ_ALL_DISABLE
 **			 ?¡­?¨¦¡ª??€?????¨C?
 ** \param [in] none
 ** \return  none
 ******************************************************************************/
#define  IRQ_ALL_DISABLE()		do{\
									EA =0;\
								  }while(0)

/*---------????¨C???¡®¨¦??¨¨??--------------------------------------------------------
 **   interrupt vector all 28
------------------------------------------------------------------------------*/
 #define         INT0_VECTOR		0
 #define         TMR0_VECTOR		1
 #define         INT1_VECTOR		2
 #define         TMR1_VECTOR   		3
 #define         UART0_VECTOR    	4
 #define         TMR2_VECTOR		5
 #define         P0EI_VECTOR		7
 #define         P1EI_VECTOR		8
 #define         P2EI_VECTOR		9
 #define         P3EI_VECTOR		10
 #define         ACMP_VECTOR		14
 #define         TMR3_VECTOR		15
 #define         TMR4_VECTOR		16
 #define         EPWM_VECTOR		18
 #define         ADC_VECTOR   		19
 #define         WDT_VECTOR         20
 #define         I2C_VECTOR			21
 #define         SPI_VECTOR			22
 #define         LSE_SCM_VECTOR		25
 #define         LVD_VECTOR			26


/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/
extern  uint32_t  SystemClock;
/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/
#include "system.h"
#include "gpio.h"
#include "wdt.h"
#include "acmp.h"
#include "adc.h"
#include "buzzer.h"
#include "epwm.h"
#include "extint.h"
#include "flash.h"
#include "i2c.h"
#include "lse.h"
#include "spi.h"
#include "timer.h"
#include "uart.h"
#include "lcd.h"

#endif /* _CMS8S78XX_H_ */
