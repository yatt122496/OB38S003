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

/****************************************************************************/
/** \file timer.c
**
**  
**
**	History:
**	
****************************************************************************/
/***************************************************************************/
/*	include files
****************************************************************************/
#include "timer.h"

/***************************************************************************/
/*	Local pre-processor symbols/macros('#define')
****************************************************************************/

/***************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
****************************************************************************/

/***************************************************************************/
/*	Local type definitions('typedef')
****************************************************************************/

/***************************************************************************/
/*	Local variable  definitions('static')
****************************************************************************/

/***************************************************************************/
/*	Local function prototypes('static')
****************************************************************************/

/***************************************************************************/
/*	Function implementation - global ('extern') and local('static')
****************************************************************************/
/****************************************************************************
 ** \brief	TMR_ConfigRunMode
 **			配置定时器运行模�?
 ** \param [in] Timern	�?	TMR0,TMR1,TMR3,TMR4
 **				TimerMode 	�?1)TMR_MODE_TIMING	:定时模式
 **							  (2)TMR_MODE_COUNT		:计数模式
 **				TimerModeBranch	：模式的分支
 **								(1)TMR_TIM_13BIT 	:13位定�?计数模式
 **								(2)TMR_TIM_16BIT 	:16位定�?计数模式		
 **								(3)TMR_TIM_AUTO_8BIT :8位自动重载定�?计数模式
 **								(4)TMR_TIM_TWO_INDEPENDENT_8BIT	:两个独立�?位定�?计数模式
 ** \return  none
 ** \note    此函数不支持TMR2
 *****************************************************************************/
void TMR_ConfigRunMode(uint8_t Timern, uint8_t TimerMode, uint8_t TimerModeBranch)
{
	switch (Timern)
	{
		case TMR0:
			TMOD &= ~(TMR_TMOD_T0Mn_Msk | TMR_TMOD_CT0_Msk);
			TMOD |= (TimerMode<< TMR_TMOD_CT0_Pos) | TimerModeBranch;
			break;
		case TMR1:
			TMOD &= ~(TMR_TMOD_T1Mn_Msk | TMR_TMOD_CT1_Msk);
			TMOD |= (TimerMode<< TMR_TMOD_CT1_Pos) | (TimerModeBranch<< TMR_TMOD_T1Mn_Pos);
			break;	
		case TMR3:
			T34MOD &= ~(TMR_T34MOD_T3Mn_Msk);
			T34MOD |= TimerModeBranch;
			break;
		case TMR4:
			T34MOD &= ~(TMR_T34MOD_T4Mn_Msk);
			T34MOD |= (TimerModeBranch<< TMR_T34MOD_T4Mn_Pos);	
			break;	
		default:
			break;
	}		
}
/***************************************************************************
 ** \brief	TMR_ConfigTimerClk
 **			配置定时器运行时�?
 ** \param [in] Timern	�?	TMR0,TMR1,TMR3,TMR4
 **				TimerClkDiv	�?1)TMR_CLK_DIV_4 
 **							  (2)TMR_CLK_DIV_12
 ** \return  none
 ** \note   
*****************************************************************************/
void TMR_ConfigTimerClk(uint8_t Timern,uint8_t TimerClkDiv)
{
	switch (Timern)
	{
		case TMR0:
			CKCON &= ~(TMR_CKCON_T0M_Msk);
			CKCON |= (TimerClkDiv << TMR_CKCON_T0M_Pos);
			break;
		case TMR1:
			CKCON &= ~(TMR_CKCON_T1M_Msk);
			CKCON |= (TimerClkDiv << TMR_CKCON_T1M_Pos);
			break;	
		case TMR3:
			T34MOD &= ~(TMR_T34MOD_T3M_Msk);
			T34MOD |= (TimerClkDiv << TMR_T34MOD_T3M_Pos);
			break;
		case TMR4:
			T34MOD &= ~(TMR_T34MOD_T4M_Msk);
			T34MOD |= (TimerClkDiv << TMR_T34MOD_T4M_Pos);
			break;	
		default:
			break;
	}	
}
/***************************************************************************
 ** \brief	TMR_ConfigTimerPeriod
 **			配置定时器定时周�?
 ** \param [in] Timern	�?	TMR0,TMR1,TMR3,TMR4
 **				TimerPeriodH:(1)TH0 (2)TH1 (3)TH3 (4)TH4
 **				TimerPeriodL:(1)TL0 (2)TL1 (3)TL3 (4)TL4
 ** \return  none
 ** \note    13位定时器 ：THx[7:0],TLx[4:0]
*****************************************************************************/
void TMR_ConfigTimerPeriod(uint8_t Timern , uint8_t TimerPeriodHigh, uint8_t TimerPeriodLow)
{
	switch (Timern)
	{
		case TMR0:
			TH0 = TimerPeriodHigh;
			TL0 = TimerPeriodLow;
			break;
		case TMR1:
			TH1 = TimerPeriodHigh;
			TL1 = TimerPeriodLow;
			break;	
		case TMR3:
			TH3 = TimerPeriodHigh;
			TL3 = TimerPeriodLow;
			break;
		case TMR4:
			TH4 = TimerPeriodHigh;
			TL4 = TimerPeriodLow;
			break;	
		default:
			break;
	}		
}

/*****************************************************************************
 ** \brief	TMR_EnableGATE
 **			使能定时器门控功�?
 ** \param [in] Timern	�?TMR0,TMR1
 ** \return  none
 ** \note   
 *****************************************************************************/
void TMR_EnableGATE(uint8_t Timern)
{
	if(TMR0 == Timern)
	{
		TMOD |= TMR_TMOD_GATE0_Msk;
	}
	if(TMR1 == Timern)
	{
		TMOD |= TMR_TMOD_GATE1_Msk;
	}
}
/*****************************************************************************
 ** \brief	TMR_DisableGATE
 **			关闭定时器门�?
 ** \param [in] Timern	�?TMR0,TMR1
 ** \return  none
 ** \note   
 *****************************************************************************/
void TMR_DisableGATE(uint8_t Timern)
{
	if(TMR0 == Timern)
	{
		TMOD &= ~(TMR_TMOD_GATE0_Msk);
	}
	if(TMR1 == Timern)
	{
		TMOD &= ~(TMR_TMOD_GATE1_Msk);
	}
}
/*****************************************************************************
 ** \brief	TMR_GetCountValue
 **			获取定时器计数模式的计数�?
 ** \param [in] Timern	�?TMR0,TMR1
 ** \return  16bits的计数值：[THn:TLn]
 ** \note   模式2/3: 请酌情使�?
 *****************************************************************************/
uint16_t  TMR_GetCountValue(uint8_t Timern)
{
	if(	TMR0 == Timern)
	{	
		if( TMR_TIM_13BIT == (TMOD & TMR_TMOD_T0Mn_Msk))
		{
			return(((TH0<< 5) | TL0));
		}
		return(((TH0<< 8) | TL0));		
	}	
	if(	TMR1 == Timern)
	{
		if( TMR_TIM_13BIT == (TMOD & TMR_TMOD_T1Mn_Msk))
		{
			return(((TH1<< 5) | TL1));		
		}
		return(((TH1<< 8) | TL1));			
	}
	return 0;
}

/*****************************************************************************
 ** \brief	TMR_EnableOverflowInt
 **			使能定时器溢出中�?
 ** \param [in] Timern	�?TMR0,TMR1,TMR3,TMR4
 ** \return   none
 ** \note   
 *****************************************************************************/
void  TMR_EnableOverflowInt(uint8_t Timern)
{
	switch (Timern)
	{
		case TMR0:
			ET0 = 1;
			break;
		case TMR1:
			ET1 = 1;
			break;	
		case TMR3:
			EIE2 |= IRQ_EIE2_ET3IE_Msk;
			break;
		case TMR4:
			EIE2 |= IRQ_EIE2_ET4IE_Msk;
			break;	
		default:
			break;
	}		
}

/*****************************************************************************
 ** \brief	TMR_DisableOverflowInt
 **			关闭定时器溢出中�?
 ** \param [in] Timern	�?TMR0,TMR1,TMR3,TMR4
 ** \return   none
 ** \note   
 *****************************************************************************/
void  TMR_DisableOverflowInt(uint8_t Timern)
{
	switch (Timern)
	{
		case TMR0:
			ET0 = 0;
			break;
		case TMR1:
			ET1 = 0;
			break;	
		case TMR3:
			EIE2 &= ~(IRQ_EIE2_ET3IE_Msk);
			break;
		case TMR4:
			EIE2 &= ~(IRQ_EIE2_ET4IE_Msk);
			break;	
		default:
			break;
	}	
}
/*****************************************************************************
 ** \brief	TMR_GetOverflowIntFlag
 **			获取定时器中断标�?
 ** \param [in] Timern	�?TMR0,TMR1,TMR3,TMR4
 ** \return   0：无中断�?1：有中断
 ** \note   定时�?�?使用模式3时，其中TLn的溢出中断使用TMR0�?中断标志
 **									   THn的溢出中断使用TMR1�?中断标志 
 *****************************************************************************/
uint8_t TMR_GetOverflowIntFlag(uint8_t Timern)
{
	uint8_t IntFlag =0;
	switch (Timern)
	{
		case TMR0:
			IntFlag = TCON & TMR_TCON_TF0_Msk;
			break;
		case TMR1:
			IntFlag = TCON & TMR_TCON_TF1_Msk;
			break;	
		case TMR3:
			IntFlag = EIF2 & IRQ_EIF2_TF3_Msk;
			break;
		case TMR4:
			IntFlag = EIF2 & IRQ_EIF2_TF4_Msk;
			break;	
		default:
			break;
	}
	return (IntFlag ? 1:0);
}
/*****************************************************************************
 ** \brief	TMR_ClearOverflowIntFlag
 **			清除定时器溢出中断标�?
 ** \param [in] Timern	�?TMR0,TMR1,TMR3,TMR4
 ** \return  none
 ** \note   
 *****************************************************************************/
void  TMR_ClearOverflowIntFlag(uint8_t Timern)
{
	switch (Timern)
	{
		case TMR0:
			TF0 = 0;
			break;
		case TMR1:
			TF1 = 0;
			break;	
		case TMR3:
			EIF2 = 0xFF & (~(IRQ_EIF2_TF3_Msk));
			break;
		case TMR4:
			EIF2 = 0xFF & (~(IRQ_EIF2_TF4_Msk));
			break;	
		default:
			break;
	}	
}
/*****************************************************************************
 ** \brief	TMR_Start
 **			开启定时器
 ** \param [in] Timern	�?TMR0,TMR1,TMR3,TMR4
 ** \return  none
 ** \note   
 *****************************************************************************/
void TMR_Start(uint8_t Timern)
{
	switch (Timern)
	{
		case TMR0:
			TCON |= TMR_TCON_TR0_Msk;
			break;
		case TMR1:
			TCON |= TMR_TCON_TR1_Msk;
			break;	
		case TMR3:
			T34MOD |= TMR_T34MOD_TR3_Msk;
			break;
		case TMR4:
			T34MOD |= TMR_T34MOD_TR4_Msk;
			break;	
		default:
			break;
	}		
}
/*****************************************************************************
 ** \brief	TMR_Stop
 **			关闭定时�?
 ** \param [in] Timern	�?TMR0,TMR1,TMR3,TMR4
 ** \return  none
 ** \note   
 *****************************************************************************/
void TMR_Stop(uint8_t Timern)
{
	switch (Timern)
	{
		case TMR0:
			TCON &= ~(TMR_TCON_TR0_Msk);
			break;
		case TMR1:
			TCON &= ~(TMR_TCON_TR1_Msk);
			break;	
		case TMR3:
			T34MOD &= ~(TMR_T34MOD_TR3_Msk);
			break;
		case TMR4:
			T34MOD &= ~(TMR_T34MOD_TR4_Msk);
			break;	
		default:
			break;
	}		
}


/****************************************************************************/
/*****************************************************************************
 ** \brief	TMR2_ConfigRunMode
 **			配置Timer2运行模式
 ** \param [in]	Timer2Mode 	:	(1)TMR2_MODE_TIMING	:定时模式
 **								(2)TMR2_MODE_COUNT	:计数模式
 **			   Timer2LoadMode	�?
 **								(1)TMR2_AUTO_LOAD	:定时�?自动重载模式
 **								(2)TMR2_T2EX_LOAD	:定时�?外部触发重载模式
**								(3)TMR2_LOAD_DISBALE: 禁止重载
 ** \return  none
 ** \note    
*****************************************************************************/
void TMR2_ConfigRunMode(  uint8_t Timer2Mode, uint8_t Timer2LoadMode)
{
	T2CON &= ~(TMR_T2CON_T2Rn_Msk | TMR_TMOD_T0Mn_Msk);
	T2CON |= Timer2Mode | Timer2LoadMode ;		
}
/*****************************************************************************
 ** \brief	TMR2_ConfigTimerClk
 **			配置定时器运行时�?
 ** \param [in]	TimerClkDiv	：TMR2_CLK_DIV_12 、TMR2_CLK_DIV_24
 ** \return  none
 ** \note   
 *****************************************************************************/
void TMR2_ConfigTimerClk(uint8_t TimerClkDiv)
{
	T2CON &= ~(TMR_T2CON_T2PS_Msk);
	T2CON |= (TimerClkDiv);
}
/***************************************************************************
 ** \brief	TMR2_ConfigTimerPeriod
 **			配置定时�?定时周期
 ** \param [in] TimerPeriod；定时器2定时周期
 ** \return  none
 ** \note   
*****************************************************************************/
void TMR2_ConfigTimerPeriod(uint16_t TimerPeriod)
{
	TL2 = (uint8_t)TimerPeriod;
	TH2 = (uint8_t)(TimerPeriod >>8);
	if((TMR2_AUTO_LOAD == (T2CON & TMR_T2CON_T2Rn_Msk)) || (TMR2_T2EX_LOAD == (T2CON & TMR_T2CON_T2Rn_Msk)))
	{
		RLDL = (uint8_t)TimerPeriod;			//自动重载或T2EX下降沿加�?
		RLDH = (uint8_t)(TimerPeriod >>8);		
	}
}
/*****************************************************************************
 ** \brief	TMR2_EnableGATE
 **			使能定时�?门控功能
 ** \param [in] none
 ** \return  none
 ** \note   
 *****************************************************************************/
void TMR2_EnableGATE(void)
{
	T2CON |= TMR_T2CON_T2In_Msk;
}
/*****************************************************************************
 ** \brief	TMR2_DisableGATE
 **			关闭定时�?门控功能
 ** \param [in] none
 ** \return  none
 ** \note   
 *****************************************************************************/
void TMR2_DisableGATE(void)
{
	T2CON &= ~(TMR_T2CON_T2In_Msk);	
	T2CON |= (0x1 << TMR_T2CON_T2In_Pos);
}

/*****************************************************************************
 ** \brief	TMR2_EnableCompare
 **			使能比较模式
 ** \param [in]	Timer2CCn:  TMR2_CC0 ~ TMR2_CC3
 **				CompareMode :(1)TMR2_CMP_MODE_0
 **							 (2)TMR2_CMP_MODE_1
 ** \return  none
 ** \note   
 *****************************************************************************/
void TMR2_EnableCompare(uint8_t Timer2CCn, uint8_t CompareMode)
{
	T2CON &= ~(TMR_T2CON_T2CM_Msk);
	T2CON |= CompareMode;
	if( Timer2CCn == TMR2_CC0)
	{
		CCEN &= ~(TMR_CCEN_CMn0_Msk);
		CCEN |= (TMR2_MODE_COMPARE << TMR_CCEN_CMn0_Pos);
	}
	if( Timer2CCn == TMR2_CC1)
	{
		CCEN &= ~(TMR_CCEN_CMn1_Msk);
		CCEN |= (TMR2_MODE_COMPARE << TMR_CCEN_CMn1_Pos);
	}
	if( Timer2CCn == TMR2_CC2)
	{
		CCEN &= ~(TMR_CCEN_CMn2_Msk);
		CCEN |= (TMR2_MODE_COMPARE << TMR_CCEN_CMn2_Pos);	
	}
	if( Timer2CCn == TMR2_CC3)
	{
		CCEN &= ~(TMR_CCEN_CMn3_Msk);
		CCEN |= (TMR2_MODE_COMPARE << TMR_CCEN_CMn3_Pos);	
	}			
}
/*****************************************************************************
 ** \brief	TMR2_DisableCompare
 **			关闭比较模式
 ** \param [in]	Timer2CCMask:  TMR2_CC0 ~ TMR2_CC3
 ** \return  none
 ** \note   
 *****************************************************************************/
void TMR2_DisableCompare(uint8_t Timer2CCn)
{
	if( Timer2CCn == TMR2_CC0)
	{
		CCEN &= ~(TMR_CCEN_CMn0_Msk);
	}
	if( Timer2CCn == TMR2_CC1)
	{
		CCEN &= ~(TMR_CCEN_CMn1_Msk);
	}
	if( Timer2CCn == TMR2_CC2)
	{
		CCEN &= ~(TMR_CCEN_CMn2_Msk);
	}
	if( Timer2CCn == TMR2_CC3)
	{
		CCEN &= ~(TMR_CCEN_CMn3_Msk);
	}			
}

/*****************************************************************************
 ** \brief	TMR2_ConfigCompareValue
 **			配置比较通道比较�?
 ** \param [in]	Timer2CCMask:  TMR2_CC0 ~ TMR2_CC3
 **				CompareValue:  0x0 ~ 0xFFFF;
 ** \return  none
 ** \note   
 *****************************************************************************/
void TMR2_ConfigCompareValue(uint8_t Timer2CCn, uint16_t CompareValue)
{
	if( TMR2_CC0 == Timer2CCn)
	{
		RLDL = (uint8_t)CompareValue;
		RLDH = (uint8_t)(CompareValue >>8);
	}
	if( TMR2_CC1 == Timer2CCn)
	{
		CCL1 = (uint8_t)CompareValue;
		CCH1 = (uint8_t)(CompareValue >>8);	
	}
	if( TMR2_CC2 == Timer2CCn)
	{
		CCL2 = (uint8_t)CompareValue;
		CCH2 = (uint8_t)(CompareValue >>8);		
	}
	if( TMR2_CC3 == Timer2CCn)
	{
		CCL3 = (uint8_t)CompareValue;
		CCH3 = (uint8_t)(CompareValue >>8);		
	}
}
/*****************************************************************************
 ** \brief	TMR2_ConfigCompareIntMode
 **			配置比较通道比较中断模式
 ** \param [in]	Timer2CompareIntMode:	(1)TMR2_CMP_INT_MODE0   
 **										(2)TMR2_CMP_INT_MODE1	  
 ** \return  none
 ** \note   
 **						 
 *****************************************************************************/
void TMR2_ConfigCompareIntMode(uint8_t Timer2CompareIntMode)
{
	T2CON &= ~(TMR_T2CON_I3FR_Msk);
	T2CON |= Timer2CompareIntMode;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************
 ** \brief	TMR2_EnableCapture
 **			使能捕获模式
 ** \param [in]	Timer2CCMask:  TMR2_CC0 ~ TMR2_CC3
 **				Timer2CaptureMode: (1)TMR2_CAP_WRITE_REGISTER   捕获通道在写寄存器时捕获
 **								   (2)TMR2_CAP_EDGE_FALLING		捕获通道下降沿捕�?		  	
 **								   (3)TMR2_CAP_EDGE_RISING		捕获通道上升沿捕�?
 **								   (4)TMR2_CAP_EDGE_BOTH		捕获通道在上升和下降边沿都可捕获							   
 ** \return  none
 ** \note  
 *****************************************************************************/
void TMR2_EnableCapture(uint8_t Timer2CCn, uint8_t Timer2CaptureMode)
{
	if( TMR2_CC0 == Timer2CCn)
	{
		T2CON &= ~(TMR_T2CON_I3FR_Msk);
		T2CON |= ( (0x1 & Timer2CaptureMode)<<TMR_T2CON_I3FR_Pos);		
		CCEN &= ~(TMR_CCEN_CMn0_Msk);
		CCEN |= ( (0x1 | Timer2CaptureMode)<< TMR_CCEN_CMn0_Pos);
	}
	if( TMR2_CC1 == Timer2CCn)
	{
		T2CON &= ~(TMR_T2CON_CAPES_Msk);
		if(TMR2_CAP_EDGE_FALLING == Timer2CaptureMode)
		{
			T2CON |= ( (0x1)<<TMR_T2CON_CAPES_Pos);			
		}	
		CCEN &= ~(TMR_CCEN_CMn1_Msk);
		CCEN |= ((0x1 | Timer2CaptureMode)<< TMR_CCEN_CMn1_Pos);
		
	}
	if( TMR2_CC2 == Timer2CCn)
	{
		T2CON &= ~(TMR_T2CON_CAPES_Msk);
		if(TMR2_CAP_EDGE_FALLING == Timer2CaptureMode)
		{
			T2CON |= ( (0x1)<<TMR_T2CON_CAPES_Pos);			
		}		
		CCEN &= ~(TMR_CCEN_CMn2_Msk);
		CCEN |= ((0x1 | Timer2CaptureMode)<< TMR_CCEN_CMn2_Pos);	
	}
	if( TMR2_CC3 == Timer2CCn)
	{
		T2CON &= ~(TMR_T2CON_CAPES_Msk);
		if(TMR2_CAP_EDGE_FALLING == Timer2CaptureMode)
		{
			T2CON |= ( (0x1)<<TMR_T2CON_CAPES_Pos);			
		}			
		CCEN &= ~(TMR_CCEN_CMn3_Msk);
		CCEN |= ((0x1 | Timer2CaptureMode)<< TMR_CCEN_CMn3_Pos);	
	}	
}

/*****************************************************************************
 ** \brief	TMR2_DisableCapture
 **			关闭捕获模式
 ** \param [in]	Timer2CCn:  TMR2_CC0 ~ TMR2_CC3
 ** \return  none
 ** \note   
*****************************************************************************/
void TMR2_DisableCapture(uint8_t Timer2CCn)
{
	if( Timer2CCn == TMR2_CC0)
	{
		CCEN &= ~(TMR_CCEN_CMn0_Msk);
	}
	if( Timer2CCn == TMR2_CC1)
	{
		CCEN &= ~(TMR_CCEN_CMn1_Msk);
	}
	if( Timer2CCn == TMR2_CC2)
	{
		CCEN &= ~(TMR_CCEN_CMn2_Msk);
	}
	if( Timer2CCn == TMR2_CC3)
	{
		CCEN &= ~(TMR_CCEN_CMn3_Msk);
	}	
}

/*****************************************************************************
 ** \brief	TMR2_GetCaptureValue
 **			获取捕获�?
 ** \param [in]	Timer2CCn:  TMR2_CC0 ~ TMR2_CC3			
 ** \return  16bit value
 ** \note   
 *****************************************************************************/
uint16_t TMR2_GetCaptureValue(uint8_t Timer2CCn)
{
	uint16_t  CaputerValue = 0;
	switch(Timer2CCn)
	{
		case TMR2_CC0:
			CaputerValue = RLDH;
			CaputerValue = (CaputerValue <<8) | RLDL;
			break;
		case TMR2_CC1:
			CaputerValue = CCH1;
			CaputerValue = (CaputerValue <<8) | CCL1;
			break;	
		case TMR2_CC2:
			CaputerValue = CCH2;
			CaputerValue = (CaputerValue <<8) | CCL2;
			break;		
		case TMR2_CC3:
			CaputerValue = CCH3;
			CaputerValue = (CaputerValue <<8) | CCL3;
			break;	
		default:
			break;
	}		
	return CaputerValue;	
}

/*****************************************************************************
 ** \brief	TMR2_EnableOverflowInt
 **			使能定时�?溢出中断
 ** \param [in] none
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_EnableOverflowInt(void)
{
	T2IE |= IRQ_T2IE_T2OVIE_Msk;
}

/*****************************************************************************
 ** \brief	TMR2_DisableOverflowInt
 **			关闭定时�?溢出中断
 ** \param [in] none
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_DisableOverflowInt(void)
{
	T2IE &= ~(IRQ_T2IE_T2OVIE_Msk);
}

/*****************************************************************************
 ** \brief	TMR2_GetOverflowIntFlag
 **			获取定时�?溢出中断标志
 ** \param [in] none
 ** \return   0：无中断�?1：有中断
 ** \note   
 *****************************************************************************/
uint8_t TMR2_GetOverflowIntFlag(void)
{
	return((T2IF & IRQ_T2IF_T2F_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	TMR2_ClearOverflowIntFlag
 **			清除定时�?溢出中断标志
 ** \param [in] none
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_ClearOverflowIntFlag(void)
{
	T2IF =  0xff & (~(IRQ_T2IF_T2F_Msk));
}

/*****************************************************************************
 ** \brief	TMR2_EnableT2EXInt
 **			使能定时�?外部加载T2EX中断
 ** \param [in] none
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_EnableT2EXInt(void)
{
	T2IE |= IRQ_T2IE_T2EXIE_Msk;
}

/*****************************************************************************
 ** \brief	TMR2_DisableT2EXInt
 **			关闭定时�?外部加载T2EX中断
 ** \param [in] none
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_DisableT2EXInt(void)
{
	T2IE &= ~(IRQ_T2IE_T2EXIE_Msk);
}
/*****************************************************************************
 ** \brief	TMR_GetT2EXIntFlag
 **			获取定时�?外部加载T2EX中断标志
 ** \param [in] none
 ** \return   0：无中断�?1：有中断
 ** \note   
 *****************************************************************************/
uint8_t TMR2_GetT2EXIntFlag(void)
{
	return((T2IF & IRQ_T2IF_T2EXIF_Msk)? 1:0);
}

/*****************************************************************************
 ** \brief	TMR2_ClearT2EXIntFlag
 **			清除定时�?外部加载T2EX中断标志
 ** \param [in] none
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_ClearT2EXIntFlag(void)
{
	T2IF =  0xff & (~(IRQ_T2IF_T2EXIF_Msk));
}

/*****************************************************************************
 ** \brief	TMR2_EnableCompareInt
 **			使能定时�?通道比较中断
 ** \param [in]Timer2CCn:  TMR2_CC0 ~ TMR2_CC3
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_EnableCompareInt(uint8_t Timer2CCn)
{
	T2IE |= (0x1<<Timer2CCn);
}

/*****************************************************************************
 ** \brief	TMR2_DisableCompareInt
 **			关闭定时�?通道比较中断
 ** \param [in] Timer2CCn:  TMR2_CC0 ~ TMR2_CC3
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_DisableCompareInt(uint8_t Timer2CCn)
{
	T2IE &= ~(0x1<<Timer2CCn);
}

/*****************************************************************************
 ** \brief	TMR2_GetCompareIntFlag
 **			获取定时�?通道比较中断标志
 ** \param [in]Timer2CCn:  TMR2_CC0 ~ TMR2_CC3
 ** \return   0：无中断�?1：有中断
 ** \note   
 *****************************************************************************/
uint8_t TMR2_GetCompareIntFlag(uint8_t Timer2CCn)
{
	return ((T2IF & (0x1<< Timer2CCn))? 1:0);
}
/*****************************************************************************
 ** \brief	TMR2_ClearCompareIntFlag
 **			清除定时�?通道比较中断标志
 ** \param [in]Timer2CCn:  TMR2_CC0 ~ TMR2_CC3
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_ClearCompareIntFlag(uint8_t Timer2CCn)
{
	T2IF = 0xff & (~(0x1<< Timer2CCn));
}

/*****************************************************************************
 ** \brief	TMR2_EnableCaptureInt
 **			使能定时�?通道捕获中断
 ** \param [in]Timer2CCn:  TMR2_CC0 ~ TMR2_CC3
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_EnableCaptureInt(uint8_t Timer2CCn)
{
	T2IE |= (0x1<<Timer2CCn);
}
/*****************************************************************************
 ** \brief	TMR2_DisableCaptureInt
 **			关闭定时�?通道捕获中断
 ** \param [in]Timer2CCn:  TMR2_CC0 ~ TMR2_CC3
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_DisableCaptureInt(uint8_t Timer2CCn)
{
		T2IE &= ~(0x1<<Timer2CCn);
}
/*****************************************************************************
 ** \brief	TMR2_GetCaptureIntFlag
 **			获取定时�?通道捕获中断标志
 ** \param [in]Timer2CCn:  TMR2_CC0 ~ TMR2_CC3
 ** \return   0：无中断�?1：有中断
 ** \note   
 *****************************************************************************/
uint8_t TMR2_GetCaptureIntFlag(uint8_t Timer2CCn)
{
	return ((T2IF & (0x1<< Timer2CCn))? 1:0);
}
/*****************************************************************************
 ** \brief	TMR2_ClearCaptureIntFlag
 **			清除定时�?通道捕获中断标志
 ** \param [in]Timer2CCn:  TMR2_CC0 ~ TMR2_CC3
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_ClearCaptureIntFlag(uint8_t Timer2CCn)
{
	T2IF = 0xff & (~(0x1<< Timer2CCn));
}

/*****************************************************************************
 ** \brief	TMR2_AllIntEnable
 **			使能定时�?总中�?
 ** \param [in] none
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_AllIntEnable(void)
{
	ET2 = 1;
}

/*****************************************************************************
 ** \brief	TMR2_AllIntDisable
 **			关闭定时�?总中�?
 ** \param [in] none
 ** \return   none
 ** \note   
 *****************************************************************************/
void TMR2_AllIntDisable(void)
{
	ET2 = 0;
}
/*****************************************************************************
 ** \brief	TMR2_Start
 **			开启定时器2
 ** \param [in] none
 ** \return  none
 ** \note   
 *****************************************************************************/
void TMR2_Start(void)
{
	if(0x0 == (T2CON & TMR_T2CON_T2In_Msk))
	{
		T2CON |= (0x1 <<TMR_T2CON_T2In_Pos);	
	}
}
/*****************************************************************************
 ** \brief	TMR2_Stop
 **			关闭定时�?
 ** \param [in] none
 ** \return  none
 ** \note   
 *****************************************************************************/
void TMR2_Stop(void)
{
	T2CON &= ~(TMR_T2CON_T2In_Msk);
}

