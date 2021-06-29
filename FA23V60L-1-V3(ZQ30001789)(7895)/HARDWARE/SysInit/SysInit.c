/***********************************************************
*  �ļ���: main.H
************************************************************
*  ����:
*
*  ����:
*  ����˵����ϵͳ�����ļ�
*
************************************************************
*  Ӳ����  MB95F204K
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
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
	               |   ��������	   |
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
	               |   ��������	   |
              GND--|5			 16|--P4.0/FLA_Y
		           |   SH79F083	   |
         DIO/P3.7--|6			 15|--VDD
                   |			   |
       DOW_B/P1.0--|7			 14|--P1.7/SDL_B
		       	   |			   |
       DOW_O/P1.1--|8			 13|--P1.6/SDL_Y
			       |			   |
          IR/P1.2--|9			 12|--P1.5/DWL_R
			       |			   |
         NTC/P1.3--|10			 11|--P1.4/DWL_G
			       |_ _ _ _ _ _ _ _|
******************************************************************/
#include "HARDWARE/main/SysInc.h"
#include "HARDWARE\Lib\inc\epwm.h"
#include "HARDWARE\Lib\inc\adc.h"
#include "HARDWARE\Lib\inc\gpio.h"
#include "HARDWARE\Lib\inc\timer.h"
#include "HARDWARE\Lib\inc\system.h"
#include "HARDWARE\Lib\inc\wdt.h"
#include "HARDWARE\Lib\inc\extint.h"

void	InitSys(void)
{
	/*CLKCON   0 , 1   */
    //   	  bit7        bit6    bit5     bit4	   bit3    bit2	  bit1   bit0
    //TMOD  32K_SPDUP    CLKS1    CLKS0    SCMIF   RCON     FS    --     --
	// CLKCON=Bin(00000000);
#if WDT_SWITCH
	// ����WDT���ʱ��,Fsys=24Mhz -> Twdt = 4194304/24 = 174.76ms
	WDT_ConfigOverflowTime(WDT_CLK_4194304);
	//����WDT����ж�
	WDT_EnableOverflowInt();
	SYS_EnableWDTReset(); //�������Ź���λ����,CONFIG������SOFTWARECONTROL(�������)
#endif
	// RSTSTAT=Bin(00000000);
	P0TRIS = 0;
	P1TRIS = 0;
	P2TRIS = 0;
	P3TRIS = 0;

	// P1 	  = Bin(00000100);
	P05 = 0; P11 = 0; P30 = 0; P12 = 0;
	P22 = 0; P21 = 0; P20 = 0; P17 = 0;
  #if (FA23V60_EN==1)
	// P1M0  = Bin(01011111);
	// P1M1  = Bin(10100000);	// P1M1.0 P1M0.0
	P05CFG = GPIO_MUX_GPIO;
	P11CFG = GPIO_P11_MUX_AN9;
	P30CFG = GPIO_MUX_GPIO;
	P12CFG = GPIO_P12_MUX_AN10;
	P22CFG = GPIO_MUX_GPIO;
	P21CFG = GPIO_MUX_GPIO;
	P20CFG = GPIO_MUX_GPIO;
	P17CFG = GPIO_MUX_GPIO;//P06�ⲿ�ж�IR
	P0TRIS = (P0TRIS & ~((1 << 5))) | ((0));
	P1TRIS = (P1TRIS & ~((1 << 1) | (1 << 2))) | ((1 << 7));
	P2TRIS = (P2TRIS & ~((1 << 0) | (1 << 2))) | ((1 << 1));
	P3TRIS = (P3TRIS & ~((1 << 0))) | (0);
  #else
    P1M0  = Bin(01011110);
	P1M1  = Bin(10100001);	// P1M1.0 P1M0.0
  #endif
		   //     111		//  0	   0		 ׼˫���ģʽ
	// P3 	  = Bin(00000000);	//  0      1         ����    ģʽ
	P24 = 0; P25 = 0; P31 = 0; P04 = 0;
	P00 = 0; P02 = 0;	 	   P03 = 0;
	// P3M0  = Bin(01000100);	//  1      0    	 ���    ģʽ
	// P3M1  = Bin(10111011);	//  1      1         ��©���ģʽ
	P24CFG = GPIO_MUX_GPIO;
	P25CFG = GPIO_MUX_GPIO;
	P31CFG = GPIO_MUX_GPIO;
	P04CFG = GPIO_MUX_GPIO;
	P00CFG = GPIO_MUX_GPIO;
	P02CFG = GPIO_MUX_GPIO;

	P03CFG = GPIO_MUX_GPIO;
	P0TRIS = (P0TRIS & ~(0)) | ((1 << 0) | (1 << 2) | (1 << 3) | (1 << 4));
	// P1TRIS = (P1TRIS & ~((0))) | ((0));
	P2TRIS = (P2TRIS & ~(0)) | ((1 << 4) | (1 << 5));
	P3TRIS = (P3TRIS & ~((1 << 1))) | ((0));

	// P4 	  = Bin(00000000);
	P23 = 0; P33 = 0; P32 = 0;
	// P4M0  = Bin(00000100);
	// P4M1  = Bin(00000011);
	P23CFG = GPIO_MUX_GPIO;
	P33CFG = GPIO_MUX_GPIO;
	P32CFG = GPIO_MUX_GPIO;

	// P0TRIS = (P0TRIS & ~((0))) | ((0));
	// P1TRIS = (P1TRIS & ~((0))) | ((0));
	P2TRIS = (P2TRIS & ~(0)) | ((1 << 3));
	P3TRIS = (P3TRIS & ~((1 << 2))) | ((1 << 3));
	/*Timer   0 , 1   */
    //   	  bit7   bit6    bit5     bit4	  bit3    bit2	  bit1   bit0
    //TMOD    GATE1  C/T1    M11      M10     GATE0   C/T0    M01    M00
    //TCON    TF1    TR1     TF0      TR0     IE1     IT1     IE0    IT0
    //TCON1   --     TCLKS1  TCLKS0   --	  TCLKP1  TCLKP0  TC1    TC0
    // TMOD  = Bin(00100001);
    // TCON  = Bin(00000001);
    // TCON1 = Bin(00000000);
  	// TH0   =	0XFA;				//1ms
  	// TL0   =	0X99;
	// TH1   = 0;
	// TH0   = 0;
	TMR_ConfigRunMode(TMR0, TMR_MODE_TIMING,TMR_TIM_16BIT);
	TMR_ConfigTimerClk(TMR0, TMR_CLK_DIV_4);					/*Fsys = 8Mhz��Ftimer = 2Mhz,Ttmr=0.5us*/
	TMR_ConfigTimerPeriod(TMR0, (d_MODEVALUE_T0-d_RELOADVALUE_T0) >> 8, (d_MODEVALUE_T0-d_RELOADVALUE_T0)); 		// 10us,��������
	TMR_EnableOverflowInt(TMR0);
	IRQ_SET_PRIORITY(IRQ_TMR0,IRQ_PRIORITY_HIGH);
	//----------------------
	// T2MOD = Bin(00000000);
	// T2CON = Bin(00000000);
    // RCAP2H= 0xC9;
	// RCAP2L= 0xF7;
    // TH2   = 0XC9;
	// TL2   = 0XF7;
	//Time2 1ms
	TMR2_ConfigRunMode(TMR2_MODE_TIMING, TMR2_AUTO_LOAD);
	TMR2_ConfigTimerClk(TMR2_CLK_DIV_12);			/*Fsys = 8Mhz��Ftimer = 2Mhz, Ttmr=0.5us*/
	TMR2_ConfigTimerPeriod((d_MODEVALUE_T2 - d_RELOADVALUE_T2));      	/* Ttimer 5ms, ���ϼ������*/
	TMR2_EnableOverflowInt();
	IRQ_SET_PRIORITY(IRQ_TMR2,IRQ_PRIORITY_LOW);
	TMR2_AllIntEnable();
    //----------------------
    // PWMP  = 0xce;
    // PWMD  = 0xce;
	//----------------------
	/*ADC interrupt*/
   //	     bit7   bit6    bit5   bit4	  bit3   bit2	bit1   bit0
   //ADCON   ADON   ADCIF   EC     --     SCH2   SCH1   SCH0   GO/DONE
   //ADT     TADC2  TADC1   TADC0  --     TS3    TS2    TS1    TS0
   //ADCH    CH7    CH6     CH5	   CH4	  CH3    CH2    CH1    CH0
	ADC_ConfigRunMode(ADC_CLK_DIV_64, ADC_RESULT_RIGHT);//ADCʱ��256��Ƶ,�����ģʽ
	//ʹ��ADCͨ��5
	ADC_EnableChannel(ADC_CH_9);
	ADC_DisableLDO();					//�����ڲ�ADC LDO
	// ADCON = AD_KEY;
	// ADT   = Bin(11101111);
    // ADCH  = Bin(00001010);
	/*no interrupt*/
	//	 		 Bit7	Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
	//IEN0		 EA 	EADC  ET2   ES0   ET1   EX1   ET0   EX0
	//IEN1	  	 ELPD   --    EPWM  ESCM  --    EX2   --    --
	//EXF0		 --    --     --    --    IT2.1 IT2.0 --	IE2
	// EXF0 = Bin(00001000);
	P30CFG = GPIO_MUX_GPIO;
	P3TRIS &= ~(1 << 0);
	P30EICFG = 0x02;
	P31CFG = GPIO_MUX_GPIO;
	P3TRIS &= ~(1 << 1);
	P31EICFG = 0x02;
	P3EXTIE = 1;
	IRQ_SET_PRIORITY(IRQ_P3,IRQ_PRIORITY_HIGH);

	// IPH0 = Bin(00000010);
	// IPL0 = Bin(00000010);

	// IPH1 = Bin(00000000);
	// IPL1 = Bin(00100100);

	// IEN0 = Bin(00101010);
	// IEN1 = Bin(00100100);

	DispDataSet  = &ClrDisp;

	// TR0  = 1;
//	TR1  = 1;
	// TR2  = 1;

	// PWMCON= Bin(10110000);

	IRQ_ALL_ENABLE();							 //�������ж�
	TMR_Start(TMR0);
	// TMR_Start(TMR1);
	TMR2_Start();
	ADC_Start();
	ADC_GO();
}