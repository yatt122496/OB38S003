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
#include "HARDWARE\Lib\inc\epwm.h"
#include "HARDWARE\Lib\inc\adc.h"
#include "HARDWARE\Lib\inc\gpio.h"
#include "HARDWARE\Lib\inc\timer.h"
#include "HARDWARE\Lib\inc\system.h"
#include "HARDWARE\Lib\inc\wdt.h"
#include "HARDWARE\Lib\inc\extint.h"

extern void (*DispDataSet)();

static void sEPWMInit(void)
{

	//设置EPWM运行模式
	EPWM_ConfigRunMode(EPWM_WFG_INDEPENDENT|EPWM_OC_INDEPENDENT|EPWM_OCU_SYMMETRIC|EPWM_COUNT_DOWN); //互补模式+输出独立模式+对称计数模式+上下计数(中心对齐)模式
	//设置EPWM运行时钟
	EPWM_ConfigChannelClk(EPWM0, EPWM_CLK_DIV_32);
	EPWM_ConfigChannelClk(EPWM1, EPWM_CLK_DIV_32);
	EPWM_ConfigChannelClk(EPWM3, EPWM_CLK_DIV_32);
	//设置EPWM 周期以及占空比
	EPWM_ConfigChannelPeriod(EPWM0, PWM_MAX);
	EPWM_ConfigChannelPeriod(EPWM1, PWM_MAX);
	EPWM_ConfigChannelPeriod(EPWM3, PWM_MAX);
	EPWM_ConfigChannelSymDuty(EPWM0, 0);
	EPWM_ConfigChannelSymDuty(EPWM1, 0);
	EPWM_ConfigChannelSymDuty(EPWM3, 0);
	//设置EPWM的加载方式为自动加载
	EPWM_EnableAutoLoadMode(EPWM_CH_0_MSK | EPWM_CH_1_MSK | EPWM_CH_3_MSK);
	//设置EPWM的输出极性
	EPWM_DisableReverseOutput(EPWM_CH_0_MSK | EPWM_CH_1_MSK|EPWM_CH_3_MSK); //反向输出
//	//设置EPWM输出
	EPWM_EnableOutput(EPWM_CH_0_MSK|EPWM_CH_1_MSK|EPWM_CH_3_MSK);		//开启输出
	//设置EPWM死区
	EPWM_DisableDeadZone(EPWM0);
	EPWM_DisableDeadZone(EPWM1);
	EPWM_DisableDeadZone(EPWM3);
	//设置EPWM输出IO复用
	GPIO_SET_MUX_MODE(P17CFG, GPIO_P17_MUX_PG0);
	GPIO_SET_MUX_MODE(P21CFG, GPIO_P21_MUX_PG1);
	GPIO_SET_MUX_MODE(P23CFG, GPIO_P23_MUX_PG3);

	//开启EPWM
	EPWM_Start(EPWM_CH_0_MSK | EPWM_CH_1_MSK|EPWM_CH_3_MSK);
}

void	InitSys(void)
{
    unsigned char Del;
	/*CLKCON   0 , 1   */
    //   	  bit7        bit6    bit5     bit4	   bit3    bit2	  bit1   bit0
    //TMOD  32K_SPDUP    CLKS1    CLKS0    SCMIF   RCON     FS    --     --
	// CLKCON =Bin(00000000);
#if WDT_SWITCH
	// 开启WDT溢出时间,Fsys=24Mhz -> Twdt = 4194304/24 = 174.76ms
	WDT_ConfigOverflowTime(WDT_CLK_67108864);
	//设置WDT溢出中断
	WDT_EnableOverflowInt();
	SYS_EnableWDTReset();   //开启看门狗复位功能,CONFIG中设置SOFTWARECONTROL(软件控制)
#endif
	P0TRIS = 0;
	P1TRIS = 0;
	P2TRIS = 0;
	P3TRIS = 0;
	Del=255;
    while(Del--);
	//----------------------
#if (IO_AD_KEY_OTP==0)
	// P1 	  = Bin(00001110);
	// P1M0  = Bin(00010001);
	// P1M1  = Bin(11100000);
	P05 = 0; P11 = 0; P30 = 0; P12 = 0;
	P22 = 0; P21 = 0; P20 = 0; P17 = 0;
	//配置为GPIO或者模拟输入
	P05CFG = GPIO_P05_MUX_AN5;
	P11CFG = GPIO_MUX_GPIO;
	P30CFG = GPIO_MUX_GPIO;
	P12CFG = GPIO_MUX_GPIO;
	P22CFG = GPIO_P22_MUX_AN18;
	P21CFG = GPIO_MUX_GPIO;
	P20CFG = GPIO_MUX_GPIO;
	P17CFG = GPIO_MUX_GPIO;//P06外部中断IR
	P0TRIS = (P0TRIS & ~((1 << 5))) | ((0));
	P1TRIS = (P1TRIS & ~((1 << 1) | (1 << 2))) | ((1 << 7));
	P2TRIS = (P2TRIS & ~((1 << 0) | (1 << 2))) | ((1 << 1));
	P3TRIS = (P3TRIS & ~((1 << 0))) | (0);
	GPIO_ENABLE_UP(P1UP, GPIO_PIN_1);
	GPIO_ENABLE_UP(P1UP, GPIO_PIN_2);
#else
	P1 	  = Bin(00000100);
	P1M0  = Bin(00011011);
	P1M1  = Bin(11100000);
#endif
	//----------------------
#if (IO_AD_KEY_OTP==0)
	// P3 	  = Bin(10000010);
	// P3M0  = Bin(01111100);
	// P3M1  = Bin(00000001);
	P24 = 0; P25 = 1; P31 = 0; P04 = 0;
	P00 = 0; P02 = 0;	 	   P03 = 0;
	P24CFG = GPIO_MUX_GPIO;
	P25CFG = GPIO_MUX_GPIO;
	P31CFG = GPIO_MUX_GPIO;
	P04CFG = GPIO_MUX_GPIO;
	P00CFG = GPIO_MUX_GPIO;
	P02CFG = GPIO_MUX_GPIO;

	P03CFG = GPIO_MUX_GPIO;
	P0TRIS = (P0TRIS & ~((1 << 0) | (1 << 2) | (1 << 3) | (1 << 4))) | (0);
	// P1TRIS = (P1TRIS & ~((0))) | ((0));
	P2TRIS = (P2TRIS & ~(0)) | ((1 << 4) | (1 << 5));
	P3TRIS = (P3TRIS & ~((1 << 1))) | ((0));
	GPIO_ENABLE_UP(P0UP, GPIO_PIN_3);
#else
	P3 	  = Bin(00000010);
	P3M0  = Bin(11111100);
	P3M1  = Bin(00000001);
#endif
	//----------------------
	// P4 	  = Bin(00000000);
	// P4M0  = Bin(11111001);
	// P4M1  = Bin(00000110);
	P23 = 0; P33 = 0; P32 = 0;
	P23CFG = GPIO_MUX_GPIO;
	P33CFG = GPIO_MUX_GPIO;
	P32CFG = GPIO_MUX_GPIO;

	// P0TRIS = (P0TRIS & ~((0))) | ((0));
	// P1TRIS = (P1TRIS & ~((0))) | ((0));
	P2TRIS = (P2TRIS & ~(0)) | ((1 << 3));
	P3TRIS = (P3TRIS & ~((0))) | ((1 << 2) | (1 << 3));

	sEPWMInit();     //Call PWM Initial Subroutine
	/*Timer   0 , 1   */
    //   	  bit7   bit6    bit5     bit4	  bit3    bit2	  bit1   bit0
    //TMOD    GATE1  C/T1    M11      M10     GATE0   C/T0    M01    M00
    //TCON    TF1    TR1     TF0      TR0     IE1     IT1     IE0    IT0
    //TCON1   --     TCLKS1  TCLKS0   --	  TCLKP1  TCLKP0  TC1    TC0
    // TMOD  = Bin(00100001);
    // TCON  = Bin(00000000);
    // TCON1 = Bin(00000000);
	// //----------------------
    // TH0   = 0Xfa;			    //5ms
    // TL0   = 0X99;
	TMR_ConfigRunMode(TMR0, TMR_MODE_TIMING,TMR_TIM_16BIT);
	TMR_ConfigTimerClk(TMR0, TMR_CLK_DIV_4);					/*Fsys = 8Mhz，Ftimer = 2Mhz,Ttmr=0.5us*/
	TMR_ConfigTimerPeriod(TMR0, (d_MODEVALUE_T0-d_RELOADVALUE_T0) >> 8, (d_MODEVALUE_T0-d_RELOADVALUE_T0)); 		// 10us,递增计数
	TMR_EnableOverflowInt(TMR0);
	IRQ_SET_PRIORITY(IRQ_TMR0,IRQ_PRIORITY_HIGH);

	TMR_ConfigRunMode(TMR1, TMR_MODE_TIMING,TMR_TIM_16BIT);
	TMR_ConfigTimerClk(TMR1, TMR_CLK_DIV_4);				/*Fsys = 8Mhz，Ftimer = 2Mhz,Ttmr=0.5us*/
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
//    TH1   = 0Xdd;			    //5ms
//    TL1   = 0Xdd;

//    T2MOD = Bin(00000000);		//50us
//    T2CON = Bin(00000000);
//    RCAP2H= 0xff;
//    RCAP2L= 0XBB;
//    TH2   = 0xff;
//    TL2   = 0XBB;
//     //----------------------
//     PWMP  = 0xCE;			   //200us
//     PWMD  = 0xCE;
	//----------------------
	/*ADC interrupt*/
    //	     bit7   bit6    bit5   bit4	  bit3   bit2	bit1   bit0
    //ADCON   ADON   ADCIF   EC     --     SCH2   SCH1   SCH0   GO/DONE
    //ADT     TADC2  TADC1   TADC0  --     TS3    TS2    TS1    TS0
    //ADCH    CH7    CH6     CH5	   CH4	  CH3    CH2    CH1    CH0
    //----------------------
#if (IO_AD_KEY_OTP==0)
	// ADCH  = Bin(00010001);
#else
    // ADCH  = Bin(00011001);
#endif
	// ADT   = Bin(11101111);
	// ADCON = AD_VR;
	ADC_ConfigRunMode(ADC_CLK_DIV_64, ADC_RESULT_RIGHT);//ADC时钟256分频,左对齐模式
	//使能ADC通道5
	ADC_EnableChannel(ADC_CH_18);
	ADC_DisableLDO();					//开启内部ADC LDO

	//----------------------
	/*no interrupt*/
	//	 		 Bit7	Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
	//IEN0		 EA 	EADC  ET2   ES0   ET1   EX1   ET0   EX0
	//IEN1	  	 ELPD   --    EPWM  ESCM  --    EX2   --    --
	//EXF0		 --    --     --    --    IT2.1 IT2.0 --	IE2
	//----------------------
	// EXF0 = Bin(00000100);
	// //----------------------
	// IPH0 = Bin(00100010);
	// IPL0 = Bin(00100000);
	// //----------------------
	// IPH1 = Bin(00000000);
	// IPL1 = Bin(00100100);
	// //----------------------
	// IEN0 = Bin(00100010);
	// IEN1 = Bin(00100100);
	// //----------------------
	// TR0  = 1;
	P30CFG = GPIO_MUX_GPIO;
	P3TRIS &= ~(1 << 0);
	P30EICFG = 0x02;
	P3EXTIE = 1;
	IRQ_SET_PRIORITY(IRQ_P3,IRQ_PRIORITY_HIGH);
	// TR2  = 1;
	// PWMCON= Bin(10110000);	  //200us
	//----------------------
//	EA   = 1;
	//----------------------
	// IRQ_ALL_ENABLE();							 //开启总中断
	TMR_Start(TMR0);
	TMR_Start(TMR1);
	TMR2_Start();
	ADC_Start();
	ADC_GO();
}