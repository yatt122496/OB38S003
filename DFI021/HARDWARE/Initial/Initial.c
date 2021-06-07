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
	        DOT1/P3.2--|1		     20|--P4.2/NC
	    	           |			   |
	        DOT2/P3.3--|2			 19|--P4.1/NC
	   	               |			   |
	          NC/P3.4--|3			 18|--P3.1/HOT
		               |   红外火炉    |
	          NC/P3.5--|4			 17|--P3.0/NC
		               |   引脚配置	   |
	              GND--|5			 16|--P4.0/NC
			           |   SH79F083	   |
	          NC/P3.7--|6			 15|--VDD
	                   |			   |
	         FLA/P1.0--|7			 14|--P1.7/NC
			       	   |			   |
	      AD_KEY/P1.1--|8			 13|--P1.6/NC
				       |			   |
	          IR/P1.2--|9			 12|--P1.5/MOT
				       |			   |
	          VR/P1.3--|10			 11|--P1.4/NTC
				       |_ _ _ _ _ _ _ _|
******************************************************************/
#include "HARDWARE\main\SysInc.h"
#include "MYADC.h"
#include "PWM.h"

extern void (*DispDataSet)();

void	InitSys(void)
{
    unsigned char Del;
	/*CLKCON   0 , 1   */
    //   	  bit7        bit6    bit5     bit4	   bit3    bit2	  bit1   bit0
    //TMOD  32K_SPDUP    CLKS1    CLKS0    SCMIF   RCON     FS    --     --
	// CLKCON =Bin(00100000);
	CKCON = 0x10;
#if WDT_SWITCH
	if ((RSTS&0x08))            //Decision WDT Occur (WDTF=1)
    {
        RSTS = RSTS&0xF7;       //Clear WDTF (WDT Timer Reset Flag)
        WDT_CountClear();       //Clear WDT Count Subroutine
        // WDT_Disable();
    }
    WDT_initialize();           //Call WDT Initial Subroutine
#endif
	Del=255;
    while(Del--);
	//----------------------
	// P1 	  = Bin(00001110);
	P0 = (P0 & ~((1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))) | ((1 << 0) | (1 << 2));
	P1_4 = 1;

	// P1M0  = Bin(00010001);
	// P1M1  = Bin(11100000);

	P0M1  = (P0M1 & ~((1 << 0) | (1 << 2) | (1 << 5) | (1 << 7))) | ((1 << 1) | (1 << 4) | (1 << 6));
	P0M0  = (P0M0 & ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 4) | (1 << 6))) | ((1 << 5) | (1 << 7));
	// P0_6 = 1;

	P1M1  &= ~(1 << 4);
	P1M0  &= ~(1 << 4);
	//----------------------
	// P3 	  = Bin(10000000);
	P1 = (P1 & ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 5) | (1 << 6))) | ((1 << 7));
	P0_3 = 0;

	// P3M0  = Bin(01111111);
	// P3M1  = Bin(00000000);
	P0M1  |= (1 << 3);
	P0M0  &= ~(1 << 3);
	P1M1  = (P1M1 & ~((1 << 6) | (1 << 7))) | ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3));
	P1M0  = (P1M0 & ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 6) | (1 << 7))) | (0);
	//----------------------
	// P4 	  = Bin(00000000);
	P1_5 = 0;
	P3_0 = 0;
	P3_1 = 0;

	// P4M0  = Bin(11111001);
	// P4M1  = Bin(00000110);
	P1M1  |= (1 << 5);
	P1M0  &= ~(1 << 5);
	P3M1 = (P3M1 & ~((1 << 0) | (1 << 1)));
	P3M0 = (P3M0 | (1 << 0) | (1 << 1));

	PWM_initialize();     //Call PWM Initial Subroutine
    // PWM_Output(0, 0, 0, 0);

	/*Timer   0 , 1   */
    //   	  bit7   bit6    bit5     bit4	  bit3    bit2	  bit1   bit0
    //TMOD    GATE1  C/T1    M11      M10     GATE0   C/T0    M01    M00
    //TCON    TF1    TR1     TF0      TR0     IE1     IT1     IE0    IT0
    //TCON1   --     TCLKS1  TCLKS0   --	  TCLKP1  TCLKP0  TC1    TC0
    // TMOD  = Bin(00000001);
    // TCON  = Bin(00000000);
    // TCON1 = Bin(00000000);
	PFCON = 1;
	IEN0 |= (ET2<<5)|(ET1<<3)|(ET0<<1); //IE=IEN0
    TMOD  = (d_T1MOD<<4)|(d_T0MOD);
	// IT0 = 1;
	//----------------------
    // TH0   = 0Xf2;			    //5ms
    // TL0   = 0X7e;
	TH0   = (d_MODEVALUE_T0-d_RELOADVALUE_T0)/256;
    TL0   = (d_MODEVALUE_T0-d_RELOADVALUE_T0)%256;
	TH1   = (d_MODEVALUE_T1-d_RELOADVALUE_T1)/256;
    TL1   = (d_MODEVALUE_T1-d_RELOADVALUE_T1)%256;
	//----------------------
	// T2MOD = Bin(00000000);		//500us
	// T2CON = Bin(00000000);
    // RCAP2H= 0xff;
	// RCAP2L= 0xdd;
    // TH2   = 0Xff;
	// TL2   = 0Xdd;
	T2CON  = (d_T2PS<<5)|(d_T2R<<3)|(d_T2I);
    TH2    = (d_MODEVALUE_T2-d_RELOADVALUE_T2)/256;
    TL2    = (d_MODEVALUE_T2-d_RELOADVALUE_T2)%256;
    CRCH   = (d_MODEVALUE_T2-d_RELOADVALUE_T2)/256; //reload velue high
    CRCL   = (d_MODEVALUE_T2-d_RELOADVALUE_T2)%256; //reload velue low
    //----------------------
    // PWMP  = 0x67;			   //200us
    // PWMD  = 0x67;
	//----------------------
	/*ADC interrupt*/
    //	     bit7   bit6    bit5   bit4	  bit3   bit2	bit1   bit0
    //ADCON   ADON   ADCIF   EC     --     SCH2   SCH1   SCH0   GO/DONE
    //ADT     TADC2  TADC1   TADC0  --     TS3    TS2    TS1    TS0
    //ADCH    CH7    CH6     CH5	   CH4	  CH3    CH2    CH1    CH0
    //----------------------
	// ADCH  = Bin(00010001);
	// ADT   = Bin(11101111);
	// ADCON = AD_VR;
	ADC_Init();
	ADC_Start(d_ADC_CH1_IN);
	//----------------------
	/*no interrupt*/
	//	 		 Bit7	Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
	//IEN0		 EA 	EADC  ET2   ES0   ET1   EX1   ET0   EX0
	//IEN1	  	 ELPD   --    EPWM  ESCM  --    EX2   --    --
	//EXF0		 --    --     --    --    IT2.1 IT2.0 --	IE2
	//----------------------
	// EXF0 = Bin(00000100);
	IT1 = 1;
	EX1 = 1;
	//----------------------
	// IPH0 = Bin(00100010);
	// IPL0 = Bin(00100000);
	// //----------------------
	// IPH1 = Bin(00000000);
	// IPL1 = Bin(00100100);
	IP0 |= (1 << 1) | (1 << 2);
	IP1 |= (1 << 1) | (1 << 2);
	// //----------------------
	// IEN0 = Bin(00100010);
	// IEN1 = Bin(00100100);
	//----------------------
	// TR0  = 1;
	TR1  = 1;

	// TR2  = 1;
	// PWMCON= Bin(10110000);	  //200us
	//----------------------
	EA   = 1;

	//----------------------
}