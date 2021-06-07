/***********************************************************
*  文件名: main.H
************************************************************
*  日期:
*
*  作者:
*  功能说明：
*
************************************************************
*  硬件：  SH79F083
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
	        TEST/P3.2--|1		     20|--P4.2/TXAL1
	    	           |			   |			  X = 32768
	          NC/P3.3--|2			 19|--P4.1/TAXL2
	   	               |			   |
	         DIO/P3.4--|3			 18|--P3.1/HOT
		               |   红外火炉    |
	         CLK/P3.5--|4			 17|--P3.0/FAN
		               |   引脚配置	   |
	              GND--|5			 16|--P4.0/MOT
			           |   SH79F083	   |
	         STB/P3.7--|6			 15|--VDD
	                   |			   |
	      AD_NTC/P1.0--|7			 14|--P1.7/LED2/DWL3
			       	   |			   |
	      AD_KEY/P1.1--|8			 13|--P1.6/DWL/DWL2
				       |			   |
	          IR/P1.2--|9			 12|--P1.5/BOT/DWL1
				       |			   |
	         FOT/P1.3--|10			 11|--P1.4/DOT
				       |_ _ _ _ _ _ _ _|
******************************************************************/
#include "HARDWARE\main\SysInc.h"
#include "ADC.h"
#include "PWM.h"

#define TIMER0_VECTOR  1    //TIMER0 Interrupt Vevtor
#define TIMER1_VECTOR  3    //TIMER1 Interrupt Vevtor
#define TIMER2_VECTOR   5      //TIMER0 Interrupt Vevtor
#define d_T2PS          0x05      //T2CON[7:5] TIMER2 Prescaler select 0~7
#define d_T2R           0x02      //T2CON[4:3] TIMER2 Reload mode select 0~3
#define d_T2I           0x01      //T2CON[1:0] TIMER2 Input select 0~3
#define d_T0MOD        0x01 //TMOD[3:0] TIMER0 Mode setting
#define d_T1MOD        0x01 //TMOD[7:4] TIMER1 Mode setting
#define ET2            0x01 //TIMER2 overflow Interrupt Enable (Default 0 Disable)
#define ET1            0x01 //TIMER1 overflow Interrupt Enable (Default 0 Disable)
#define ET0            0x01 //TIMER0 overflow Interrupt Enable (Default 0 Disable)

#define d_MODEVALUE_T0      65536     //MODE1 16bit 65536
#define d_RELOADVALUE_T0    200      //User Define Reload Value
#define d_MODEVALUE_T1      65536    //MODE1 16bit 65536
#define d_RELOADVALUE_T1    333      //User Define Reload Value
#define d_MODEVALUE_T2      65536
#define d_RELOADVALUE_T2    3333 //User Define Reload Value


extern void (*DispDataSet)();

void	InitSys(void)
{
//    uint8 Dey;
//    //--------------------
//    for(Dey=0xff;Dey;Dey--);
//	//--------------------
	Disturb0xAA = 0XAA;
//	//--------------------
//	//
//	/*CLKCON   0 , 1   */
//    //   	  bit7        bit6    bit5     bit4	   bit3    bit2	  bit1   bit0
//    //TMOD  32K_SPDUP    CLKS1    CLKS0    SCMIF   RCON     FS    --     --
//	CLKCON =Bin(00101000);
	// CKCON = 0x10;
	CKCON = 0;
	if ((RSTS&0x08))            //Decision WDT Occur (WDTF=1)
    {
        RSTS = RSTS&0xF7;       //Clear WDTF (WDT Timer Reset Flag)
        WDT_CountClear();       //Clear WDT Count Subroutine
        // WDT_Disable();
        // while(1);
    }
    WDT_initialize();           //Call WDT Initial Subroutine
//    //
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//    for(Dey=0xff;Dey;Dey--);
    //
	// CLKCON =Bin(00100000);
	//CLKCON =Bin(00000000);
    //
	// P1 	  = Bin(00000100);

	P0 &= (1 << 3);
	P1_4 = 1;

	// P1M0  = Bin(11110000);
	// P1M1  = Bin(00001011);
	P0M1  = (P0M1 & ~((1 << 0) | (1 << 1) | (1 << 2))) | ((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));
	P0M0  = (P0M0 & ~((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))) | ((1 << 0) | (1 << 1) | (1 << 2));

	P1M1  |= (1 << 4);
	P1M0  &= ~(1 << 4);

		   //     111
	// P3 	  = Bin(00000111);
	P1 = (P1 | ((1 << 0) | (1 << 1) | (1 << 3))) & ~((1 << 2) | (1 << 6) | (1 << 7));
	P0_3 = 0;
#if (DWL_EN==1)
	P3M0  = Bin(01100000);
	P3M1  = Bin(10011000);
#else
	// P3M0  = Bin(01101000);
	// P3M1  = Bin(10010000);
	P0M1  = P0M1 | ((1 << 3));
	P0M0  = (P0M0 & ~((1 << 3)));

	P1M1  = (P1M1 & ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 7))) | ((1 << 6));
	P1M0  = (P1M0 & ~((1 << 0) | (1 << 1) | (1 << 3) | (1 << 6))) | ((1 << 2) | (1 << 7));

#endif

	// P4 	  = Bin(00000000);
	P1_5 = 0;
	P1M1  = P1M1 | ((1 << 5));
	P1M0  = (P1M0 & ~((1 << 5)));
	// P4M0  = Bin(00000111);
	// P4M1  = Bin(00000000);
    //----------------------
	/*Timer   0 , 1   */
    //   	  bit7   bit6    bit5     bit4	  bit3    bit2	  bit1   bit0
    //TMOD    GATE1  C/T1    M11      M10     GATE0   C/T0    M01    M00
    //TCON    TF1    TR1     TF0      TR0     IE1     IT1     IE0    IT0
    //TCON1   --     TCLKS1  TCLKS0   --	  TCLKP1  TCLKP0  TC1    TC0
    // TMOD  = Bin(00010001);
    // TCON  = Bin(00000101);
    // TCON1 = Bin(00000000);
	// //----------------------
	// TL0 = 0;
	// TH0 = 0;
    // //----------------------
    // TH1   =	(65536-(SCLK/T1_FD/T1_FREQ))/256;
    // TL1   =	(65536-(SCLK/T1_FD/T1_FREQ))%256-1;
	// //----------------------
    // //T
    // //T2CON TF2 EXF2 RCLK TCLK EXEN2 TR2 C/---- T---- 2 CP/- RL2 ----------
    // T2MOD = Bin(00000000);//1ms
	// T2CON = Bin(00000000);
    // RCAP2H= (65536-(SCLK/T2_FD/T2_FREQ))/256;
    // RCAP2L= (65536-(SCLK/T2_FD/T2_FREQ))%256-1;
    // TH2   = (65536-(SCLK/T2_FD/T2_FREQ))/256;
    // TL2   = (65536-(SCLK/T2_FD/T2_FREQ))%256-1;
	PFCON &= 0xf0;
	PFCON |= 0x1;
	IEN0 |= (ET2<<5)|(ET1<<3)|(ET0<<1); //IE=IEN0
    TMOD  = (d_T1MOD<<4)|(d_T0MOD);

    // TH0   = (d_MODEVALUE_T0-d_RELOADVALUE_T0)/256;
    // TL0   = (d_MODEVALUE_T0-d_RELOADVALUE_T0)%256;


	TH1   = (d_MODEVALUE_T1-d_RELOADVALUE_T1)/256;
    TL1   = (d_MODEVALUE_T1-d_RELOADVALUE_T1)%256;
    //TR0   = 1;    //Timer0 Start bit

    T2CON  = (d_T2PS<<5)|(d_T2R<<3)|(d_T2I);
    TH2    = (d_MODEVALUE_T2-d_RELOADVALUE_T2)/256;
    TL2    = (d_MODEVALUE_T2-d_RELOADVALUE_T2)%256;
    CRCH   = (d_MODEVALUE_T2-d_RELOADVALUE_T2)/256; //reload velue high
    CRCL   = (d_MODEVALUE_T2-d_RELOADVALUE_T2)%256; //reload velue low
	//----------------------
	/*ADC interrupt*/
    //	     bit7   bit6    bit5   bit4	  bit3   bit2	bit1   bit0
    //ADCON   ADON   ADCIF   EC     --     SCH2   SCH1   SCH0   GO/DONE
    //ADT     TADC2  TADC1   TADC0  --     TS3    TS2    TS1    TS0
    //ADCH    CH7    CH6     CH5	   CH4	  CH3    CH2    CH1    CH0
    //----------------------
	ADC_Init();

	// ADT   = AD_TIME;
	// ADCH  = AD_CH;
	// ADCON = AD_CH_OTP;
	//----------------------
	PWM_initialize();
	PWM_Output(PWMD0, PWMD1, PWMD2, PWMD3);
    // PWMP  = (SCLK/PWM_FD/PWM_FREQ)%256;//250us
    // PWMD  = (SCLK/PWM_FD/PWM_FREQ)%256;;
	/*no interrupt*/
	//	 		 Bit7	Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
	//IEN0		 EA 	EADC  ET2   ES0   ET1   EX1   ET0   EX0
	//IEN1	  	 ELPD   --    EPWM  ESCM  --    EX2   --    --
	//EXF0		 --    --     --    --    IT2.1 IT2.0 --	IE2
	//----------------------
    // EXF0 = Bin(00000100);
	IT0 = 1;
	IT1 = 1;
	//----------------------
	// IPH0 = Bin(00001000);
	// IPL0 = Bin(00100000);
	// //----------------------
	// IPH1 = Bin(00100000);
	// IPL1 = Bin(00100000);
	//----------------------
	// IEN0 = Bin(00101000);
	// IEN1 = Bin(00100100);
	IEN0 |= (1 << 2);
	// //----------------------
	TR1  = 1;
    // //----------------------
    // PWMCON= Bin(10100000);
	//----------------------
	EA   = 1;
	//----------------------
	// RSTSTAT=Bin(00000010); //170ms
}

bit  PowerOn;
void SysInit(void)
{
  Standby  = 0;
  //--------------
  PowerOn  = 1; //机器上电
  //--------------
  //
  FlaGears = 0;
  //
  TcTf     = 0;
  HeatLock = 0;
//  HeatOnOff= 0;
  HeatGears=0;
  GearWidth1F_En=0;
  Set5FGears = 0;
  Set1CGears = 0;
//
//  HeaInit = 1;
//
#if (DWL_EN==1)
  DwlGears = 0;
#endif
  //
  ClrTmr();
}
