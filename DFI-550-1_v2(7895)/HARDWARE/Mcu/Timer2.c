/***********************************************************
*
************************************************************
*  日期:2014-1-3 9:10
*
*  作者:
*
************************************************************
*  硬件：  SH79F1622
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\include\SysInc.h"
#include "HARDWARE\Lib\inc\timer.h"
#include "HARDWARE\Lib\inc\adc.h"
//-------------------------------
#ifdef TIMER2_EN
//-------------------------------
u8 BitList[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

u8 UpKeyDat, UpKeyValue, KeySize;
bit KeySta;

void Timer2Init(void)
{
	//   //-----------------------------
	//   #define T2_FD      12
	//   #define T2_FREQ	 500  	//100Ms
	//   //-----------------------------
	//   //   	    bit7   bit6    bit5     bit4	bit3    bit2  bit1   bit0
	//   //T2MOD   TCLKP2 -       -        -       -       -     T2OE   DCEN
	//   //T2CON   TF2    EXF2    RCLK     TCLK    EXEN2   TR2   C/T2   CP/RL2
	//   //-----------------------------
	// #ifdef  REG79F083A_H
	//   T2MOD = Bin(00000000);
	// #endif
	//   //-----------------------------
	// #ifdef  REG79F084A_H
	//   T2MOD = Bin(00000000);
	// #endif
	//   //-----------------------------
	//   T2CON = Bin(00000000);
	//   //-----------------------------
	//   RCAP2H= (65536-(SCLK/T2_FD/T2_FREQ))/256;
	//   RCAP2L= (65536-(SCLK/T2_FD/T2_FREQ))%256-1;
	//   TH2   = (65536-(SCLK/T2_FD/T2_FREQ))/256;
	//   TL2   = (65536-(SCLK/T2_FD/T2_FREQ))%256-1;
	//   IntSet(TIMER2,1,1);
	// TR2   = 1;
	//Time2 1ms
	TMR2_ConfigRunMode(TMR2_MODE_TIMING, TMR2_AUTO_LOAD);
	TMR2_ConfigTimerClk(TMR2_CLK_DIV_12);						 /*Fsys = 8Mhz，Ftimer = 2Mhz, Ttmr=0.5us*/
	TMR2_ConfigTimerPeriod((d_MODEVALUE_T2 - d_RELOADVALUE_T2)); /* Ttimer 5ms, 向上计数溢出*/
	TMR2_EnableOverflowInt();
	IRQ_SET_PRIORITY(IRQ_TMR2, IRQ_PRIORITY_LOW);
	TMR2_AllIntEnable();
	// TMR2_Start();
	//--------------------
	//   P1M0 &=~Bin(00000001);
	//   P1M1 |= Bin(00000001);
	GPIO_SET_PXDS(P0DS,GPIO_PIN_0);
	GPIO_SET_PXDS(P0DS,GPIO_PIN_2);
	GPIO_SET_PXDS(P0DS,GPIO_PIN_3);
	GPIO_SET_PXDS(P0DS,GPIO_PIN_4);
	GPIO_SET_PXDS(P0DS,GPIO_PIN_5);
	GPIO_DISABLE_OD(P0OD, GPIO_PIN_0);
	GPIO_DISABLE_OD(P0OD, GPIO_PIN_2);
	GPIO_DISABLE_OD(P0OD, GPIO_PIN_3);
	GPIO_DISABLE_OD(P0OD, GPIO_PIN_4);
	GPIO_DISABLE_OD(P0OD, GPIO_PIN_5);
	GPIO_SET_MUX_MODE(P00CFG, GPIO_MUX_GPIO);
	GPIO_SET_MUX_MODE(P02CFG, GPIO_MUX_GPIO);
	GPIO_SET_MUX_MODE(P03CFG, GPIO_MUX_GPIO);
	GPIO_SET_MUX_MODE(P04CFG, GPIO_MUX_GPIO);
	GPIO_SET_MUX_MODE(P05CFG, GPIO_MUX_GPIO);
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_0);
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_2);
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_3);
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_4);
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_5);
	// P05 = 1;
	// P05CFG = GPIO_MUX_GPIO;
	// P0TRIS = (P0TRIS & ~(0)) | ((1 << 5));
	// 							P04 = 1;
	// P00 = 0; P02 = 0;			P03 = 0;
	// P04CFG = GPIO_MUX_GPIO;
	// P00CFG = GPIO_MUX_GPIO;
	// P02CFG = GPIO_MUX_GPIO;

	// P03CFG = GPIO_MUX_GPIO;
	// P0TRIS = (P0TRIS & ~(0)) | ((1 << 0) | (1 << 2) | (1 << 3) | (1 << 4));
	// P0DS = 0xff;
	// P11CFG = GPIO_MUX_GPIO;
	// P30CFG = GPIO_MUX_GPIO;
	// P12CFG = GPIO_MUX_GPIO;
	// P22CFG = GPIO_P22_MUX_AN18;
	// P21CFG = GPIO_MUX_GPIO;
	// P20CFG = GPIO_MUX_GPIO;
	// P17CFG = GPIO_MUX_GPIO;//P06外部中断IR
	// P1TRIS = (P1TRIS & ~((1 << 1) | (1 << 2))) | ((1 << 7));
	// P2TRIS = (P2TRIS & ~((1 << 0) | (1 << 2))) | ((1 << 1));
	// P3TRIS = (P3TRIS & ~((1 << 0))) | (0);
	//----------------------
	//   ADCH  = Bin(00001010);
	//   ADT   = Bin(11101111);
	//   ADCON = AD_VR;
	ADC_ConfigRunMode(ADC_CLK_DIV_64, ADC_RESULT_RIGHT); //ADC时钟256分频,左对齐模式
	//使能ADC通道5
	ADC_EnableChannel(ADC_CH_9);
	GPIO_SET_MUX_MODE(P11CFG, GPIO_P11_MUX_AN9);
	ADC_DisableLDO(); //开启内部ADC LDO
	//----------------------
	UpKeyDat = 0xff;
	KeySize = 0;
	KeySta = 0;
	//----------------------
}
bit NewDis;
//------------------
u8 bdata SEG;
sbit DSEG1 = SEG^0;
sbit DSEG2 = SEG^1;
sbit DSEG3 = SEG^2;
sbit DSEG4 = SEG^3;
sbit DSEG5 = SEG^4;
//------------------
u8 bdata DKEY;
sbit DKEY1 = DKEY^0;
sbit DKEY2 = DKEY^1;
sbit DKEY3 = DKEY^2;
sbit DKEY4 = DKEY^3;
//------------------
//u8 bdata CKEY;
//sbit CKEY1 = CKEY^0;
//sbit CKEY2 = CKEY^1;
//sbit CKEY3 = CKEY^2;
//sbit CKEY4 = CKEY^3;
//------------------
u8 PcbKeyValue;
//-----------------------
//
//
//-----------------------
bit HeaterSec;
u16 HotWaitModeTimer;
//-----------------------
u8 code AdCh[2] = {AD_VR, AD_NTC};
//-----------------------
//bit HeatTest;
//u8  TestNtcTimer;
//----------------------
bit AdNtcNew;
u16 AdNtcValue;
//----------------------
bit AdVrNew;
u8 AdVrValue;
//------------------------
u8 AdSensFreq;
u8 AdSize;
//------------------------
u8 T1MotTimer, T1MotTimer1;
u8 AdErrTim;
/********************************************************
*
*
*
*
********************************************************/
unsigned long Sys_Time = 0;
void Timer2Isr(void) interrupt TMR2_VECTOR //2ms中断一次
{
	//------------------
	static u8 DispBuf[2], DispSize = 0;
	//------------------
	static u8 Timer50Ms;
	//------------------
	u8 dat;
	//------------------
	if (TMR2_GetOverflowIntFlag())
	{
		//   TF2 = 0;
		//------------------
		Sys_Time++;
		BzTime50ms = 1;
		//***********************************************
		AdSensFreq++;
		if (AdSensFreq > 4) //10ms
		{
			AdSensFreq = 0;
			if (0 == ADC_IS_BUSY) { //ADC????????????/???é????????
				if (ADCCHS == ADC_CH_10) {
					AdNtcNew    = 1;
					// AdNtcValue  = (((ADRESH & 0x0f) << 8) | ADRESL) >> 2;
					AdNtcValue  = ADC_GetADCResult() >> 2;
					// ADCON       = AD_KEY  ;//Bin(10000011);
					ADC_EnableChannel(ADC_CH_9);
					ADC_GO();
					// FLA_Y = !FLA_Y;
					AdErrTim = 0;
				} else if (ADCCHS == ADC_CH_9) {
					AdVrNew    = 1;
					// AdVrValue  = (((ADRESH & 0x0f) << 8) | ADRESL) >> 4;
					AdVrValue  = ADC_GetADCResult() >> 4;
					// ADCON       = AD_KEY  ;//Bin(10000011);
					ADC_EnableChannel(ADC_CH_10);
					ADC_GO();
					AdErrTim = 0;
				}
			} else {
				AdErrTim++;
				if (AdErrTim > 2) {
					AdErrTim = 0;
					//	   ADT   = Bin(11101111);	//????????°?AD?§?§??100MS?ó×???????
					//       ADCH  = Bin(01000000);
					//	   ADCON = AD_NTC;
					ADCCHS = ADC_CH_9;
					ADCON1 = 0xF0;
					ADC_GO();
				}
			}
			// if ((ADCON & 0X01) == 0)
			// {
			// 	switch (AdSize)
			// 	{
			// 	case 0:
			// 		AdVrValue = ADDH;
			// 		AdVrNew = 1;
			// 		break;
			// 	case 1:
			// 		AdNtcValue = (ADDH << 2) | (ADDL & 0x03);
			// 		AdNtcNew = 1;
			// 		break;
			// 	default:
			// 		break;
			// 	}
			// 	AdSize++;
			// 	if (AdSize > 1)
			// 		AdSize = 0;
			// 	ADCON = AdCh[AdSize];
			// }
			//-------------------------
			if (!HotOnOff && MotDelayOff)
			{
				//-----------------------
				T1MotTimer++;
				if (T1MotTimer > 99)
				{ //1s
					T1MotTimer = 0;
					T1MotTimer1++;
					if (T1MotTimer1 > 19)
					{ //20S
						T1MotTimer1 = 0;
						MotDelayOff = 0;
					}
				}
			}
			else
			{
				T1MotTimer = 0;
				T1MotTimer1 = 0;
			}
			//***********************************************
			HotWaitModeTimer++;
			if (HotWaitModeTimer > 99)
			{
				HotWaitModeTimer = 0;
				HeaterSec = 1;
				//      if(HeatTest)		 //Hot Test Timer 1mim
				//      {
				//	    TestNtcTimer++;
				//        if(TestNtcTimer > 59)
				//        {
				//          TestNtcTimer = 0;
				//          HeatTest     = 0;		//Test cancel
				//        }
				//      }
			}
		}
		//------------------
		Timer50Ms++;
		if (Timer50Ms > 24)
		{
			Timer50Ms = 0;
			if (KeyLongTimer)
				KeyLongTimer--;
		}
		if (DispTime)
			DispTime--;
		//------------------
		if (NewDis && !DispSize)
		{
			NewDis = 0;
			DispBuf[0] = DispDat[0];
			DispBuf[1] = DispDat[1];
		}
		if (DispSize == 0)
		{
			//--------------
			// COM1 = 1;
			//--------------
			// P3 |= Bin(10111000);
			// P3M1 &= ~Bin(10111000);
			// P3M0 &= ~Bin(10111000);
			// P24CFG = GPIO_MUX_GPIO;
			// P25CFG = GPIO_MUX_GPIO;
			// P31CFG = GPIO_MUX_GPIO;
			// /*P24 = 0; P25 = 0; P31 = 0; */P04 = 1;
			// P00 = 1; P02 = 1;	 	   P03 = 1;
			// P04CFG = GPIO_MUX_GPIO;
			// P00CFG = GPIO_MUX_GPIO;
			// P01CFG = GPIO_MUX_GPIO;

			// P03CFG = GPIO_MUX_GPIO;
			P0TRIS &= ~((1 << 0) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5));
			P0UP |= ((1 << 0) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5));
			// P1TRIS = (P1TRIS & ~((0))) | ((0));
			// P2TRIS = (P2TRIS & ~((1 << 4) | (1 << 5))) | ((0));
			// P3TRIS = (P3TRIS & ~((1 << 1))) | ((0));
			// GPIO_ENABLE_UP(P0UP, GPIO_PIN_0);				//开启上拉
			// GPIO_ENABLE_UP(P0UP, GPIO_PIN_1);				//开启上拉
			// GPIO_ENABLE_UP(P0UP, GPIO_PIN_3);				//开启上拉
			// GPIO_ENABLE_UP(P0UP, GPIO_PIN_4);				//开启上拉
			//--------------
			KeySta = 1;
			if (KeySize > 1)
			{
				KeySize = 0;
				dat = DKEY & 0x0f;
				if (dat)
				{
					if (UpKeyDat != dat)
						UpKeyDat = dat;
					else
					{
						if (!UpKeyValue || UpKeyValue == dat)
						{
							UpKeyValue = dat;
							switch (dat)
							{
							case 1:
								dat = 1;
								break;
							case 2:
								dat = 2;
								break;
							case 4:
								dat = 3;
								break; //
							case 8:
								dat = 4;
								break;
							default:
								goto KeyErr;
							}
							PcbKeyValue = dat;
						}
						else
						{
						KeyErr:
							UpKeyValue = 0xff;
							PcbKeyValue = 0xff;
						}
					}
				}
				else
				{
					UpKeyDat = 0xff;
					PcbKeyValue = 0;
					UpKeyValue = 0;
				}
			}
			else
				KeySize++;
		}
		else
		{
			if (KeySta)
			{
				KeySta = 0;
				//--------------
				DKEY = 0;
				if (!SEG1)
					DKEY1 = 1;
				if (!SEG2)
					DKEY2 = 1;
				if (!SEG3)
					DKEY3 = 1;
				if (!SEG4)
					DKEY4 = 1;
			}
			//---------------------
			// P3 &= ~Bin(10111000);
			// P3M1 &= ~Bin(10111000);
			// P3M0 |= Bin(10111000);
			// GPIO_DISABLE_UP(P0UP, GPIO_PIN_0);				//关闭上拉
			// GPIO_DISABLE_UP(P0UP, GPIO_PIN_1);				//关闭上拉
			// GPIO_DISABLE_UP(P0UP, GPIO_PIN_3);				//关闭上拉
			// GPIO_DISABLE_UP(P0UP, GPIO_PIN_4);				//关闭上拉
			// /*P24 = 0; P25 = 0; P31 = 0; */P04 = 0;
			// P00 = 0; P02 = 0;	 	   P03 = 0;
			P0TRIS &= ~((1 << 0) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5));
			P0UP &= ~((1 << 0) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5));
			// P24CFG = GPIO_MUX_GPIO;
			// P25CFG = GPIO_MUX_GPIO;
			// P31CFG = GPIO_MUX_GPIO;
			// P04CFG = GPIO_MUX_GPIO;
			// P00CFG = GPIO_MUX_GPIO;
			// P01CFG = GPIO_MUX_GPIO;

			// P03CFG = GPIO_MUX_GPIO;
			// P0TRIS = (P0TRIS & ~(0)) | ((1 << 0) | (1 << 2) | (1 << 3) | (1 << 4));
			// P1TRIS = (P1TRIS & ~((0))) | ((0));
			// P2TRIS = (P2TRIS & ~((1 << 4) | (1 << 5))) | ((0));
			// P3TRIS = (P3TRIS & ~((1 << 1))) | ((0));
			//--------------------
			SEG = DispBuf[0];
			// COM1 = 1;
			if (DispSize == 1)
			{
				if (DSEG1 && (!DKEY1 || !(DKEY & 0x0e)))
				{
					GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_4);
					GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_5);
					SEG1 = DSEG1;
					// P3M0 &= ~Bin(00001000);
					// P3M1 |= Bin(00001000); //推挽输出
					COM1 = 0;
				}
			}
			else if (DispSize == 2)
			{
				if (DSEG2 && (!DKEY2 || !(DKEY & 0x0d)))
				{
					GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_0);
					GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_5);
					SEG2 = DSEG2;
					// P3M0 &= ~Bin(00010000);
					// P3M1 |= Bin(00010000); //推挽输出
					COM1 = 0;
				}
			}
			else if (DispSize == 3)
			{
				if (DSEG3 && (!DKEY3 || !(DKEY & 0x0b)))
				{
					GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_2);
					GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_5);
					SEG3 = DSEG3;
					// P3M0 &= ~Bin(00100000);
					// P3M1 |= Bin(00100000); //推挽输出
					COM1 = 0;
				}
			}
			else if (DispSize == 4)
			{
				if (DSEG4 && (!DKEY4 || !(DKEY & 0x07)))
				{
					GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_3);
					GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_5);
					SEG4 = DSEG4;
					// P3M0 &= ~Bin(10000000);
					// P3M1 |= Bin(10000000); //推挽输出
					COM1 = 0;
				}
			}
		}
		// --------------
		DispSize++;
		if (DispSize > 4)
		{
			DispSize = 0;
			if (InitKeyTime)
				InitKeyTime--;
		}
		TMR2_ClearOverflowIntFlag();
	}
}
#endif