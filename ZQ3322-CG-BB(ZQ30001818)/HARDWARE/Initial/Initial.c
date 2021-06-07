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
#include "HARDWARE\Lib\inc\adc.h"
#include "HARDWARE\Lib\inc\gpio.h"
#include "HARDWARE\Lib\inc\timer.h"
#include "HARDWARE\Lib\inc\system.h"
#include "HARDWARE\Lib\inc\wdt.h"
#include "HARDWARE\Lib\inc\extint.h"

extern void (*DispDataSet)();

void	InitSys(void)
{
	Disturb0xAA = 0XAA;
	//--------------------
	//
	/*CLKCON   0 , 1   */
    //   	  bit7        bit6    bit5     bit4	   bit3    bit2	  bit1   bit0
    //TMOD  32K_SPDUP    CLKS1    CLKS0    SCMIF   RCON     FS    --     --
	// CLKCON=Bin(00000000);

#if WDT_SWITCH
	// 开启WDT溢出时间,Fsys=24Mhz -> Twdt = 4194304/24 = 174.76ms
	WDT_ConfigOverflowTime(WDT_CLK_4194304);
	//设置WDT溢出中断
	WDT_EnableOverflowInt();
	SYS_EnableWDTReset();   //开启看门狗复位功能,CONFIG中设置SOFTWARECONTROL(软件控制)
#endif
	// RSTSTAT=Bin(00000000);

	P0TRIS = 0;
	P1TRIS = 0;
	P2TRIS = 0;
	P3TRIS = 0;

	// P1 	  = Bin(00000000);
	// P1M0  = Bin(00111110);
	// P1M1  = Bin(11000001);	// P1M1.0 P1M0.0
	P05 = 0; P11 = 0; P30 = 0; P12 = 0;
	P22 = 0; P21 = 0; P20 = 0; P17 = 0;

	// P1M0  = Bin(00010001);
	// P1M1  = Bin(11100000);
	//配置为GPIO或者模拟输入
	P05CFG = GPIO_MUX_GPIO;
	P11CFG = GPIO_P11_MUX_AN9;
	P30CFG = GPIO_MUX_GPIO;
	P12CFG = GPIO_P12_MUX_AN10;
	P22CFG = GPIO_MUX_GPIO;
	P21CFG = GPIO_MUX_GPIO;
	P20CFG = GPIO_MUX_GPIO;
	P17CFG = GPIO_MUX_GPIO;
	P0TRIS = (P0TRIS & ~(0)) | ((1 << 5));
	P1TRIS = (P1TRIS & ~((1 << 1) | (1 << 2))) | ((1 << 7));
	P2TRIS = (P2TRIS & ~((1 << 1) | (1 << 2))) | ((1 << 0));
	P3TRIS = (P3TRIS & ~((1 << 0))) | (0);

	// 	   //     111		//  0	   0		 准双向口模式
	// P3 	  = Bin(00000000);	//  0      1         输入    模式
	// P3M0  = Bin(00000100);	//  1      0    	 输出    模式
	// P3M1  = Bin(00111011);	//  1      1         开漏输出模式
	P24 = 0; P25 = 0; P31 = 0; P04 = 0;
	P00 = 0; P01 = 0;	 	   P03 = 0;
	P24CFG = GPIO_MUX_GPIO;
	P25CFG = GPIO_MUX_GPIO;
	P31CFG = GPIO_MUX_GPIO;
	P04CFG = GPIO_MUX_GPIO;
	P00CFG = GPIO_MUX_GPIO;
	P01CFG = GPIO_MUX_GPIO;

	P03CFG = GPIO_MUX_GPIO;
	P0TRIS = (P0TRIS & ~((1 << 3))) | ((1 << 0) | (1 << 1) | (1 << 4));
	// P1TRIS = (P1TRIS & ~((0))) | ((0));
	P2TRIS = (P2TRIS & ~(0)) | ((1 << 4) | (1 << 5));
	P3TRIS = (P3TRIS & ~((1 << 1))) | ((0));

	// P4 	  = Bin(00000000);
	// P4M0  = Bin(00000100);
	// P4M1  = Bin(00000011);
	P23 = 0; P33 = 0; P32 = 0;
	P23CFG = GPIO_MUX_GPIO;
	P33CFG = GPIO_MUX_GPIO;
	P32CFG = GPIO_MUX_GPIO;

	// P0TRIS = (P0TRIS & ~((0))) | ((0));
	// P1TRIS = (P1TRIS & ~((0))) | ((0));
	P2TRIS = (P2TRIS & ~((0))) | ((1 << 3));
	P3TRIS = (P3TRIS & ~((1 << 2))) | ((1 << 3));
    //----------------------
	/*Timer   0 , 1   */
    //   	  bit7   bit6    bit5     bit4	  bit3    bit2	  bit1   bit0
    //TMOD    GATE1  C/T1    M11      M10     GATE0   C/T0    M01    M00
    //TCON    TF1    TR1     TF0      TR0     IE1     IT1     IE0    IT0
    //TCON1   --     TCLKS1  TCLKS0   --	  TCLKP1  TCLKP0  TC1    TC0
    // TMOD  = Bin(00010001);
    // TCON  = Bin(00000001);
    // TCON1 = Bin(00000000);
	// //----------------------
    // TH0   =	(65536-(SCLK/T0_FD/T0_FREQ))/256;
    // TL0   =	(65536-(SCLK/T0_FD/T0_FREQ))%256-1;
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
	TMR_ConfigRunMode(TMR0, TMR_MODE_TIMING,TMR_TIM_16BIT);
	TMR_ConfigTimerClk(TMR0, TMR_CLK_DIV_4);					/*Fsys = 8Mhz，Ftimer = 2Mhz,Ttmr=0.5us*/
	TMR_ConfigTimerPeriod(TMR0, (d_MODEVALUE_T0-d_RELOADVALUE_T0) >> 8, (d_MODEVALUE_T0-d_RELOADVALUE_T0)); 		// 10us,递增计数
	TMR_EnableOverflowInt(TMR0);
	IRQ_SET_PRIORITY(IRQ_TMR0,IRQ_PRIORITY_HIGH);

	TMR_ConfigRunMode(TMR1, TMR_MODE_TIMING,TMR_TIM_16BIT);
	TMR_ConfigTimerClk(TMR1, TMR_CLK_DIV_12);				/*Fsys = 8Mhz，Ftimer = 2Mhz,Ttmr=0.5us*/
	TMR_ConfigTimerPeriod(TMR1, (d_MODEVALUE_T1-d_RELOADVALUE_T1) >> 8, (d_MODEVALUE_T1-d_RELOADVALUE_T1)); // 50us,递增计数
	TMR_EnableOverflowInt(TMR1);
	IRQ_SET_PRIORITY(IRQ_TMR1,IRQ_PRIORITY_LOW);

	//Time2 1ms
	TMR2_ConfigRunMode(TMR2_MODE_TIMING, TMR2_AUTO_LOAD);
	TMR2_ConfigTimerClk(TMR2_CLK_DIV_12);			/*Fsys = 8Mhz，Ftimer = 2Mhz, Ttmr=0.5us*/
	TMR2_ConfigTimerPeriod((d_MODEVALUE_T2 - d_RELOADVALUE_T2));      	/* Ttimer 5ms, 向上计数溢出*/
	TMR2_EnableOverflowInt();
	IRQ_SET_PRIORITY(IRQ_TMR2,IRQ_PRIORITY_LOW);
	TMR2_AllIntEnable();
	//----------------------
	/*ADC interrupt*/
    //	     bit7   bit6    bit5   bit4	  bit3   bit2	bit1   bit0
    //ADCON   ADON   ADCIF   EC     --     SCH2   SCH1   SCH0   GO/DONE
    //ADT     TADC2  TADC1   TADC0  --     TS3    TS2    TS1    TS0
    //ADCH    CH7    CH6     CH5	   CH4	  CH3    CH2    CH1    CH0
    //----------------------
	// ADCON = AD_KEY;
	// ADT   = Bin(11101111);
    // ADCH  = Bin(00001010);
	ADC_ConfigRunMode(ADC_CLK_DIV_64, ADC_RESULT_RIGHT);//ADC时钟256分频,左对齐模式
	//使能ADC通道5
	ADC_EnableChannel(ADC_CH_9);
	ADC_DisableLDO();					//开启内部ADC LDO
	//----------------------
	/*no interrupt*/
	//	 		 Bit7	Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
	//IEN0		 EA 	EADC  ET2   ES0   ET1   EX1   ET0   EX0
	//IEN1	  	 ELPD   --    EPWM  ESCM  --    EX2   --    --
	//EXF0		 --    --     --    --    IT2.1 IT2.0 --	IE2
	//----------------------
	P30CFG = GPIO_MUX_GPIO;
	P3TRIS &= ~(1 << 0);
	P30EICFG = 0x02;
	P31CFG = GPIO_MUX_GPIO;
	P3TRIS &= ~(1 << 1);
	P31EICFG = 0x02;
	P3EXTIE = 1;
	IRQ_SET_PRIORITY(IRQ_P3,IRQ_PRIORITY_HIGH);
	// EXF0 = Bin(00001000);
	// //----------------------
	// IPH0 = Bin(00001001);
	// IPL0 = Bin(00100001);
	// //----------------------
	// IPH1 = Bin(00000000);
	// IPL1 = Bin(00000000);
	// //----------------------
	// IEN0 = Bin(00101010);
	// IEN1 = Bin(00000100);
	//----------------------
	IRQ_ALL_ENABLE();							 //开启总中断
	TMR_Start(TMR0);
	TMR_Start(TMR1);
	TMR2_Start();
	ADC_Start();
	ADC_GO();
    // TR0  = 1;
	// TR1  = 1;
	// TR2  = 1;
    // //----------------------
	// EA   = 1;
	// //----------------------
	// RSTSTAT=Bin(00000010); //170ms
}

bit  PowerOn;
void SysInit(void)
{
	Standby = 0;
	//--------------
	PowerOn = 1; //机器上电
	//--------------
	//
	FlaGears = 0;
	//
	TcTf = 0;
	HeatLock = 0;
	HeatOnOff = 0;
	HeatGears = 0;
	GearWidth1F_En = 0;
	Set5FGears = 0;
	Set1CGears = 0;
//
//  HeaInit = 1;
//
#if (DWL_EN == 1)
	DwlGears = 0;
#endif
	//
	ClrTmr();
}
