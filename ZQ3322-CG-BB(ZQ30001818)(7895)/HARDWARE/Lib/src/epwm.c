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
/** \file epwm.c
**
** 
**
**	History:
**	
*****************************************************************************/

/****************************************************************************/
/*	include files
*****************************************************************************/
#include "epwm.h"
/****************************************************************************/
/*	Local pre-processor symbols/macros ('#define')
*****************************************************************************/

/****************************************************************************/
/*	Global variable definitions (declared in header file with 'extern')
*****************************************************************************/

/****************************************************************************/
/*	Local type definitions ('typedef')
*****************************************************************************/

/****************************************************************************/
/*	Local variable  definitions ('static')
*****************************************************************************/

/****************************************************************************/
/*	Local function prototypes ('static')
*****************************************************************************/

/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
*****************************************************************************/
/********************************************************************************
 ** \brief	 EPWM_ConfigRunMode
 **			 设置EPWM的运行模式
 ** \param [in] EpwmRunModeMask: (1)EPWM_COUNT_MODE_UP_DOWN_MASK
							   (2)EPWM_COUNT_MODE_DOWN_MASK
							   (3)EPWM_OCU_MODE_ASYMMETRIC_MASK
							   (4)EPWM_OCU_MODE_SYMMETRIC_MASK
							   (5)EPWM_WFG_MODE_INDEPENDENT_MASK
							   (6)EPWM_WFG_MODE_COMPLEMENTARY_MASK
							   (7)EPWM_WFG_MODE_SYNCHRONIZED_MASK
							   (8)EPWM_OC_MODE_GROUP_MASK
							   (9)EPWM_OC_INDEPENDENT_MASK
 ** \return  none
 ** \note    以上9种摸式可组合成不同的运行模式，且共用一个8位寄存器
 ******************************************************************************/
void EPWM_ConfigRunMode( uint8_t EpwmRunModeMask)
{
	PWMCON = EpwmRunModeMask; 			/*注：直接赋值*/
}
/*****************************************************************************
 ** \brief	 EPWM_ConfigChannelClk	
** \param [in] ChannelNum : EPWM0,EPWM1,EPWM2,EPWM3
 **				ClkDiv: (1)EPWM_CLK_DIV_1 
 **						(2)EPWM_CLK_DIV_2
 **						(3)EPWM_CLK_DIV_4
 **						(4)EPWM_CLK_DIV_8
 **						(5)EPWM_CLK_DIV_16
 **						(6)EPWM_CLK_DIV_32
 ** \return  none	
 ** \note 
 **	(1)PWM01PSC共同控制PWM0、PWM1通道 ，所以此函数统一设置PWMxxPSC=0x01
 **	若需要其他的分频，请酌情对寄存器赋值
 **	(2)EPWM 分频分为两级：PWMxPSC PWMnDIV 
 **	第一级分频(PWMxPSC)：0x00 预分频停止并且计数器停止; 其他值：系统时钟分频系数PWMxPSC+1
 **	第二级分频（PWMnDIV): 0x00 FEPWMPSC/2; 0x01 FEPWMPSC/4；0x02:FEPWMPSC/8；0x3 FEPWMPSC/16
 **	0x04 FEPWMPSC ; 其他 Fsys 
 ** 分频级数：1~4096，例Fsys=8M，EPWM的频率范围：1.95k ~ 8M	
*****************************************************************************/
void EPWM_ConfigChannelClk(uint8_t ChannelNum,uint8_t ClkDiv)
{
	switch(ChannelNum)
	{
		case EPWM0:
			 PWM01PSC = 0x01;
			 PWM0DIV = ClkDiv;
			break;
		case EPWM1:
			PWM01PSC = 0x01;
			PWM1DIV = ClkDiv;
			break;
		case EPWM2:
			 PWM23PSC = 0x01;
			 PWM2DIV = ClkDiv;
			 break;
		case EPWM3:
			 PWM23PSC = 0x01;
			 PWM3DIV = ClkDiv;
			 break;		
		default:
			break;
	}
}
/*****************************************************************************
 ** \brief	 EPWM_ConfigChannelPeriod
 **			 设置EPWM通道的频率以及占空比
 ** \param [in] ChannelNum : EPWM0,EPWM1,EPWM2,EPWM3
 **				Period: 16位周期值
 ** \return none
 ** \note    
 ****************************************************************************/
void EPWM_ConfigChannelPeriod(uint8_t ChannelNum,uint16_t Period)
{	
	switch(ChannelNum)
	{
		case EPWM0:
			PWMP0H = Period>>8;
			PWMP0L = Period;
			PWMLOADEN |= EPWM_CH_0_MSK;
			break;
		case EPWM1:
			PWMP1H = Period>>8;
			PWMP1L = Period;
			PWMLOADEN |= EPWM_CH_1_MSK;
			break;
		case EPWM2:
			PWMP2H = Period>>8;
			PWMP2L = Period;
			PWMLOADEN |= EPWM_CH_2_MSK;
			break;
		case EPWM3:
			PWMP3H = Period>>8;
			PWMP3L = Period;
			PWMLOADEN |= EPWM_CH_3_MSK;
			break;		
		default:
			break;
	}	
}
/*****************************************************************************
 ** \brief	 EPWM_ConfigChannelSymDuty
 **			 设置EPWM通道对称模式占空比
 ** \param [in] ChannelNum  :EPWM0,EPWM1,EPWM2,EPWM3
 **				Duty: 16位占空比
 ** \return none
 ** \note   
 ****************************************************************************/
void EPWM_ConfigChannelSymDuty(uint8_t ChannelNum,uint16_t Duty)
{
	switch(ChannelNum)
	{
		case EPWM0:
			PWMD0H = Duty>>8;
			PWMD0L = Duty;
			PWMLOADEN |= EPWM_CH_0_MSK;
			break;
		case EPWM1:
			PWMD1H = Duty>>8;
			PWMD1L = Duty;
			PWMLOADEN |= EPWM_CH_1_MSK;
			break;
		case EPWM2:
			PWMD2H = Duty>>8;
			PWMD2L = Duty;
			PWMLOADEN |= EPWM_CH_2_MSK;
			break;
		case EPWM3:
			PWMD3H = Duty>>8;
			PWMD3L = Duty;
			PWMLOADEN |= EPWM_CH_3_MSK;
			break;			
		default:
			break;
	}		
}
 /*****************************************************************************
 ** \brief	 EPWM_ConfigChannelAsymDuty
 **			 设置EPWM通道非对称模式占空比
 ** \param [in] ChannelNum  :EPWM0,EPWM1,EPWM2,EPWM3
 **				DownCmp: 16 bit 向下比较值
 ** \return none
 ** \note    只适用于中心对齐计数(上下计数)模式
 ****************************************************************************/
void EPWM_ConfigChannelAsymDuty(uint8_t ChannelNum,uint16_t UpCmp, uint16_t DowmCmp)
{
	switch(ChannelNum)
	{
		case EPWM0:
			PWMD0H = UpCmp>>8;
			PWMD0L = UpCmp;
			PWMDD0H = DowmCmp>>8;
			PWMDD0L = DowmCmp;	
			PWMLOADEN |= EPWM_CH_0_MSK;		
			break;
		case EPWM1:
			PWMD1H = UpCmp>>8;
			PWMD1L = UpCmp;
			PWMDD1H = DowmCmp>>8;
			PWMDD1L = DowmCmp;	
			PWMLOADEN |= EPWM_CH_1_MSK;
			break;
		case EPWM2:
			PWMD2H = UpCmp>>8;
			PWMD2L = UpCmp;
			PWMDD2H = DowmCmp>>8;
			PWMDD2L = DowmCmp;
			PWMLOADEN |= EPWM_CH_2_MSK;		
			break;
		case EPWM3:
			PWMD3H = UpCmp>>8;
			PWMD3L = UpCmp;
			PWMDD3H = DowmCmp>>8;
			PWMDD3L = DowmCmp;
			PWMLOADEN |= EPWM_CH_3_MSK;		
			break;		
		default:
			break;
	}		
}
/****************************************************************************
 ** \brief	 EPWM_EnableOneShotMode
 **			 开启One-Shot模式
 ** \param [in]  ChannelMask   EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void EPWM_EnableOneShotMode(uint8_t ChannelMask)
{			
	PWMCNTM &= ~ChannelMask;	
}
/****************************************************************************
 ** \brief	 EPWM_EnableAutoLoadMode
 **			 开启自动加载模式
 ** \param [in]  ChannelMask   EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void EPWM_EnableAutoLoadMode(uint8_t ChannelMask)
{			
	PWMCNTM |= ChannelMask;	
}

/****************************************************************************
 ** \brief	 EPWM_EnableSynCount	
 **			使能PWMn同步计数
 ** \param [in]  none
 ** \return  none
 ** \note	
 ****************************************************************************/
void EPWM_EnableSynCount( void)
{			
	PWMCON |= EPWM_PWMCON_PWMRUN_Msk;	
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	PWMCON &= ~(EPWM_PWMCON_PWMRUN_Msk);	
}

/****************************************************************************
 ** \brief	 EPWM_Start		
 ** \param [in]  ChannelMask   EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note	
 ****************************************************************************/
void EPWM_Start( uint8_t ChannelMask)
{			
	PWMCNTE |= ChannelMask;		/*使能PWMn计数器*/
}
/*****************************************************************************
 ** \brief	 EPWM_Stop
 **
 ** \param [in] ChannelMask  : EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note    
*****************************************************************************/
void EPWM_Stop( uint8_t ChannelMask)
{
	PWMCNTE &= ~ ChannelMask;		/*停止计数*/
}


/*****************************************************************************
 ** \brief	 EPWM_EnableOutput
 **			 开启EPWM输出
 ** \param [in]  ChannelMask   EPWM_CH_0_MSK ~ EPWM_CH_3_MSK   
 ** \return  none
 ** \note   
*****************************************************************************/
void EPWM_EnableOutput( uint8_t ChannelMask)
{
	PWMOE |= ChannelMask;		/*使能PWM输出*/	
}
/*****************************************************************************
 ** \brief	 EPWM_DisableOutput
 **			 关闭EPWM输出
 ** \param [in]  ChannelMask   EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note    
*****************************************************************************/
void EPWM_DisableOutput( uint8_t ChannelMask)
{
	PWMOE &= ~(ChannelMask);		
}


/*****************************************************************************
 ** \brief	 EPWM_ConfigBrakeMode
 **			 设置EPWM刹车模式
 ** \param [in] BrakeMode: (1)EPWM_BRK_STOP		停止模式
 **						   (2)EPWM_BRK_SUSPEND	暂停模式
 **						   (3)EPWM_BRK_RECOVER	恢复模式
 **						   (4)EPWM_BRK_DELAY_RECOVER	延时恢复模式
 **			 	Relaod:	   (1)EPWM_BRK_LOAD_EPWM0		EPWM0的加载点恢复
 **						   (2)EPWM_BRK_LOAD_EPWM1		EPWM1的加载点恢复
 **						   (3)EPWM_BRK_LOAD_EPWM2		EPWM2的加载点恢复
 **						   (4)EPWM_BRK_LOAD_EPWM3		EPWM3的加载点恢复
 ** \return  none
 ** \note  	 
*****************************************************************************/
void EPWM_ConfigBrakeMode( uint8_t BrakeMode , uint8_t Relaod)
{
	PWMBRKC &= ~(EPWM_PWMBRKC_BRKRCS_Msk | EPWM_PWMBRKC_BRKMS_Msk);
	PWMBRKC |= BrakeMode | Relaod;
}

/*****************************************************************************
 ** \brief	 EPWM_ConfigBrakeRecoverDelay
 **			 配置刹车恢复延时模式的延时
 ** \param [in] time : 0~0x3ff
 ** \return  none
 ** \note  刹车恢复延时时间 = time * Tsys(系统时钟)  
*****************************************************************************/
void EPWM_ConfigBrakeRecoverDelay( uint16_t time)
{
	PWMBRKRDTH = 0x3 & (time>>8);
	PWMBRKRDTL = 0xff & time;
}

/*****************************************************************************
 ** \brief	 EPWM_EnableFaultBrake
 **			 使能EPWM刹车模式
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void EPWM_EnableFaultBrake( void)
{
	PWMBRKC |= EPWM_PWMBRKC_BRKEN_Msk;
}
/*****************************************************************************
 ** \brief	 EPWM_DisableFaultBrake
 **			 关闭EPWM刹车
 ** \param [in] none
 ** \return  none
 ** \note    
*****************************************************************************/
void EPWM_DisableFaultBrake(void)
{
	PWMBRKC &= ~(EPWM_PWMBRKC_BRKEN_Msk);
}


/****************************************************************************
 ** \brief	 EPWM_ConfigChannelBrakeLevel
 **			 设置EPWM通道刹车电平
 ** \param [in]  ChannelMask： EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 **		   		 BrakeLevel: FaultBreake后的EPWM通道电平 ：0/1(低/高)
 ** \return  none
 ** \note   
*****************************************************************************/
void EPWM_ConfigChannelBrakeLevel( uint8_t ChannelMask, uint8_t BrakeLevel)
{	
	if(1 == BrakeLevel)
	{
		PWMFBKD  |= ChannelMask;		
	}
	else
	{
		PWMFBKD  &= ~(ChannelMask);		
	}
}
/****************************************************************************
 ** \brief	 EPWM_EnableDeadZone
 **			 开启死区
 ** \param [in] Channel: EPWM0、EPWM1....EPWM3		
 **			DeadTime : 死区时间( 0~0xFF) = DeadTime * Tepwm
 ** \return  none
 ** \note  
*****************************************************************************/
void EPWM_EnableDeadZone( uint8_t Channel, uint8_t DeadTime)
{
	switch(Channel)
	{
		case EPWM0:
		case EPWM1:
			PWMDTE  |= EPWM_PWMDTE_PWM01DTE_Msk;
			PWM01DT = DeadTime;
			break;
		case EPWM2:
		case EPWM3:
			PWMDTE  |= EPWM_PWMDTE_PWM23DTE_Msk;
			PWM23DT = DeadTime;
			break;
		default:
			break;		
	}	
}
/*****************************************************************************
 ** \brief	 EPWM_DisableDeadZone
 **			 关闭EPWM死区
 ** \param [in] Channel: EPWM0、EPWM1....EPWM3	
 ** \return  none
 ** \note  
*****************************************************************************/
void EPWM_DisableDeadZone( uint8_t Channel)
{
	switch(Channel)
	{
		case EPWM0:
		case EPWM1:
			PWMDTE  &= ~(EPWM_PWMDTE_PWM01DTE_Msk);
			break;
		case EPWM2:
		case EPWM3:
			PWMDTE  &= ~(EPWM_PWMDTE_PWM23DTE_Msk);
			break;
		default:
			break;		
	}	
}
/*****************************************************************************
 ** \brief	 EPWM_EnableMaskControl
 **			 掩码控制开启
 ** \param [in] ChannelMask:  EPWM_CH_0_MSK ~ EPWM_CH_3_MSK	 	
 ** 	    	MaskLevel: 掩码的数据 :0/1(低/高)
 ** \return  none
 ** \note   
*****************************************************************************/
void EPWM_EnableMaskControl( uint8_t ChannelMask, uint8_t MaskLevel)
{
	if(1 == MaskLevel)
	{
		PWMMASKD  |= ChannelMask;		
	}
	else
	{
		PWMMASKD  &= ~(ChannelMask);		
	}
	
	PWMMASKE  |= ChannelMask;			/*使能控制位*/	
}
/*****************************************************************************
 ** \brief	 EPWM_DisableMaskControl
 **			 掩码控制关闭
 ** \param [in] ChannelMask:  EPWM_CH_0_MSK ~ EPWM_CH_3_MSK	 		
 ** \return  none
 ** \note   
*****************************************************************************/
void EPWM_DisableMaskControl( uint8_t ChannelMask)
{	
	PWMMASKE  &=~(ChannelMask);		
}
/*****************************************************************************
 ** \brief	 EPWM_EnableUpCmpInt
 **			 开启向上比较中断
 ** \param [in]  ChannelMask： EPWM_CH_0_MSK ~ EPWM_CH_3_MSK		
 ** \return  none
 ** \note   
*****************************************************************************/
void EPWM_EnableUpCmpInt( uint8_t ChannelMask)
{
	PWMUIE |= ChannelMask ;
}
/*****************************************************************************
 ** \brief	 EPWM_DisableUpCmptInt
 **			 关闭向上比较中断
 ** \param [in]  ChannelMask ：EPWM_CH_0_MSK ~ EPWM_CH_3_MSK	
 ** \return  none
 ** \note   
*****************************************************************************/
void EPWM_DisableUpCmpInt( uint8_t ChannelMask)
{
	PWMUIE &= ~ChannelMask ;
}
/*****************************************************************************
 ** \brief	 EPWM_GetUpCmpIntFlag
 **			 获取向上比较中断标志位
 ** \param [in] ChannelNum:EPWM0,EPWM1,EPWM2,EPWM3
 ** \return  0: 无中断产生
 **          1：有中断产生
 ** \note   
*****************************************************************************/
uint8_t EPWM_GetUpCmpIntFlag( uint8_t ChannelNum)
{
	return(PWMUIF & (1<<ChannelNum)? 1:0);

}
/*****************************************************************************
 ** \brief	 EPWM_ClearUpCmpIntFlag
 **			 清除向上比较中断标志位
 ** \param [in] ChannelNum:EPWM0,EPWM1,EPWM2,EPWM3
 ** \return  none
 ** \note   
*****************************************************************************/
void EPWM_ClearUpCmpIntFlag( uint8_t ChannelNum)
{
	PWMUIF = 0xff & (~(1<<ChannelNum));
}
/*****************************************************************************
 ** \brief	 EPWM_EnableDownCmpInt
 **			 开启向下比较中断
 ** \param [in]ChannelMask : EPWM_CH_0_MSK ~ EPWM_CH_3_MSK	
 ** \return  none
 ** \note   
*****************************************************************************/
void EPWM_EnableDownCmpInt( uint8_t ChannelMask)
{
	PWMDIE  |= ChannelMask;
}
/*****************************************************************************
 ** \brief	 EPWM_DisableDownCmpInt
 **			 关闭向下比较中断
 ** \param [in]  ChannelMask : EPWM_CH_0_MSK ~ EPWM_CH_3_MSK	
 ** \return  none
 ** \note   
*****************************************************************************/
void EPWM_DisableDownCmpInt( uint8_t ChannelMask)
{
	PWMDIE  &= ~ChannelMask;	
}
/*****************************************************************************
 ** \brief	 EPWM_GetUpCmpIntFlag
 **			 获取向下比较中断标志位
 ** \param [in] ChannelNum: EPWM0,EPWM1,EPWM2,EPWM3
 ** \return  0: 无中断产生
 **          1：有中断产生
 ** \note   
*****************************************************************************/
uint8_t EPWM_GetDownCmpIntFlag( uint8_t ChannelNum)
{
	return(PWMDIF & (1<<ChannelNum)? 1:0);
}
/*****************************************************************************
 ** \brief	 EPWM_ClearUpCmpIntFlag
 **			 清除向下比较中断标志位
 ** \param [in]  ChannelNum :EPWM0,EPWM1,EPWM2,EPWM3
 ** \return  none
 ** \note   
*****************************************************************************/
void EPWM_ClearDownCmpIntFlag( uint8_t ChannelNum)
{
	PWMDIF = 0xff & (~(1<<ChannelNum));
}
/*****************************************************************************
 ** \brief	 EPWM_EnablePeriodInt
 **			 开启周期中断
 ** \param [in]  ChannelMask: EPWM_CH_0_MSK ~ EPWM_CH_3_MSK	
 ** \return   none     
 ** \note   
*****************************************************************************/
void EPWM_EnablePeriodInt( uint8_t ChannelMask)
{
	PWMPIE |= ChannelMask;
}
/*****************************************************************************
 ** \brief	 EPWM_DisablePeriodInt
 **			 关闭周期中断
 ** \param [in]ChannelMask: EPWM_CH_0_MSK ~ EPWM_CH_3_MSK	
 ** \return   none     
 ** \note   
*****************************************************************************/
void EPWM_DisablePeriodInt( uint8_t ChannelMask)
{
	PWMPIE &= ~ChannelMask;
}
/*****************************************************************************
 ** \brief	 EPWM_ClearPeriodIntFlag
 **			 清除周期中断标志位 
 ** \param [in] ChannelNum: EPWM0,EPWM1,EPWM2,EPWM3
 ** \return   none     
 ** \note   
*****************************************************************************/
void EPWM_ClearPeriodIntFlag( uint8_t ChannelNum)
{
	PWMPIF = 0xff & (~(1<<ChannelNum));
}
/*****************************************************************************
 ** \brief	 EPWM_ClearPeriodIntFlag
 **			 获取周期中断标志位 
 ** \param [in]  ChannelNum: EPWM0,EPWM1,EPWM2,EPWM3
 ** \return   0：无中断产生
 **           1：有中断产生
 ** \note   
*****************************************************************************/
uint8_t EPWM_GetPeriodIntFlag( uint8_t ChannelNum)
{
	return(PWMPIF & (1<<ChannelNum)? 1:0);
}

/*****************************************************************************
 ** \brief	 EPWM_EnableZeroInt
 **			 开启零点中断
 ** \param [in] ChannelMask: EPWM_CH_0_MSK ~ EPWM_CH_3_MSK	
 ** \return   none     
 ** \note   
*****************************************************************************/
void EPWM_EnableZeroInt( uint8_t ChannelMask)
{
	PWMZIE |= ChannelMask;
}
/*****************************************************************************
 ** \brief	 EPWM_DisableZeroInt
 **			 关闭零点中断 
 ** \param [in]ChannelMask: EPWM_CH_0_MSK ~ EPWM_CH_3_MSK	
 ** \return   none     
 ** \note   
*****************************************************************************/
void EPWM_DisableZeroInt( uint8_t ChannelMask)
{
	PWMZIE &= ~ChannelMask;
}
/*****************************************************************************
 ** \brief	 EPWM_ClearZeroIntFlag
 **			 清除零点中断标志位
 ** \param [in]  ChannelNum: EPWM0,EPWM1,EPWM2,EPWM3
 ** \return   none     
 ** \note   
*****************************************************************************/
void EPWM_ClearZeroIntFlag( uint8_t ChannelNum)
{
	PWMZIF = 0xff & (~(1<<ChannelNum));
}
/*****************************************************************************
 ** \brief	 EPWM_GetZeroIntFlag
 **			 获取零点中断标志位 
 ** \param [in] ChannelNum: EPWM0,EPWM1,EPWM2,EPWM3
 ** \return   0：无中断产生
 **           1：有中断产生   
 ** \note   
 *****************************************************************************/
uint8_t EPWM_GetZeroIntFlag( uint8_t ChannelNum)
{
	return(PWMZIF & (1<<ChannelNum)? 1:0);
}

/*****************************************************************************
 ** \brief	 EPWM_EnableFaultBrakeInt
 **			 开启故障刹车中断 
 ** \param [in] none
 ** \return  none
 ** \note  
*****************************************************************************/
void EPWM_EnableFaultBrakeInt( void)
{
	PWMFBKC  |= EPWM_PWMFBKC_PWMFBIE_Msk;   /*开启刹车中断*/
}
/*****************************************************************************
 ** \brief	 EPWM_DisableFaultBrakeInt	
 **			 关闭故障刹车中断 
 ** \param [in]none
 ** \return  none
 ** \note 
*****************************************************************************/
void EPWM_DisableFaultBrakeInt(void)
{
	PWMFBKC  &= ~(EPWM_PWMFBKC_PWMFBIE_Msk);
}
/*****************************************************************************
 ** \brief	 EPWM_GetFaultBrakeIntFlag
 **			 获取故障刹车中断标志位
 ** \param [in] none
 ** \return  0: 无中断产生
 **          1：有中断产生
 ** \note  
*****************************************************************************/
uint8_t EPWM_GetFaultBrakeIntFlag(void)
{
	return((PWMFBKC & (EPWM_PWMFBKC_PWMFBF_Msk))? 1:0);
}
/*****************************************************************************
 ** \brief	 EPWM_ClearFaultBrakeIntFlag	
 ** 		 清除故障刹车中断标志位 
 ** \param [in] none
 ** \return  none
 ** \note 
*****************************************************************************/
void EPWM_ClearFaultBrakeIntFlag( void)
{
	PWMFBKC  &= ~(EPWM_PWMFBKC_PWMFBF_Msk);   /*清刹车标志位*/
}

/*****************************************************************************
 ** \brief	 EPWM_EnableReverseOutput
 **			 开启反向输出
 ** \param [in] ChannelMask : EPWM_CH_0_MSK ~ EPWM_CH_5_MSK	
 ** \return  none
 ** \note  正常模式： EPWM 开始从初值开始计数时，PWM输出口输出为低电平, 
 **	当EPWM计数值与向上、向下计数匹配时，输出翻转
*****************************************************************************/
void  EPWM_EnableReverseOutput( uint8_t ChannelMask)
{
	PWMPINV |=ChannelMask;
}
/*****************************************************************************
 ** \brief	 EPWM_DisableReverseOutput
 **			 关闭反向输出
 ** \param [in] ChannelMask: EPWM_CH_0_MSK ~ EPWM_CH_5_MSK	
 ** \return  none
 ** \note   
*****************************************************************************/
void  EPWM_DisableReverseOutput( uint8_t ChannelMask)
{
	PWMPINV &=~ChannelMask;
}
/*****************************************************************************
 ** \brief	 EPWM_TrigSoftwareBrake
 **			 触发软件刹车
 ** \param [in]	none
 ** \return  none
 ** \note   
*****************************************************************************/
void  EPWM_TrigSoftwareBrake(void)
{
	PWMFBKC |= EPWM_PWMFBKC_PWMFBKSW_Msk;
}
/*****************************************************************************
 ** \brief	 EPWM_DisableSoftwareBreake
 **			 关闭软件刹车
 ** \param [in] none
 ** \return  none
 ** \note   
*****************************************************************************/
void  EPWM_DisableSoftwareBrake(void)
{
	PWMFBKC &= ~(EPWM_PWMFBKC_PWMFBKSW_Msk);
}

/*****************************************************************************
 ** \brief	 EPWM_EnableFBBrake
 **			 使能外部硬件触发刹车
 ** \param [in] FBSource: (1)EPWM_BRK_FB0			
 **						  (2)EPWM_BRK_FB1
 **				FBBrakeMode: (1)EPWM_BRK_FB_LOW			低电平触发刹车
 **							 (2)EPWM_BRK_FB_HIGH		高电平触发刹车
 ** \return  none
 ** \note	 
*****************************************************************************/
void EPWM_EnableFBBrake(uint8_t FBSource, uint8_t FBBrakeMode)
{
	if(FBSource == EPWM_BRK_FB0)
	{
		PWMFBKC &= ~(EPWM_PWMFBKC_PWMFB0ES_Msk);
		PWMFBKC |= (FBBrakeMode<< EPWM_PWMFBKC_PWMFB0ES_Pos)| EPWM_PWMFBKC_PWMFB0EN_Msk;
	}
	if(FBSource == EPWM_BRK_FB1)
	{
		PWMFBKC &= ~(EPWM_PWMFBKC_PWMFB1ES_Msk);
		PWMFBKC |= (FBBrakeMode<< EPWM_PWMFBKC_PWMFB1ES_Pos)| EPWM_PWMFBKC_PWMFB1EN_Msk;
	}
}

/*****************************************************************************
 ** \brief	 EPWM_DisableFBBrake
 **			 关闭外部硬件触发刹车
 ** \param [in] FBSource: (1)EPWM_BRK_FB0			
 **						  (2)EPWM_BRK_FB1
 ** \return  none
 ** \note    
*****************************************************************************/
void EPWM_DisableFBBrake(uint8_t FBSource)
{
	if(FBSource == EPWM_BRK_FB0)
	{
		PWMFBKC &= ~(EPWM_PWMFBKC_PWMFB0EN_Msk);
	}
	if(FBSource == EPWM_BRK_FB1)
	{
		PWMFBKC &= ~(EPWM_PWMFBKC_PWMFB1EN_Msk);
	}	
}

/*****************************************************************************
 ** \brief	 EPWM_EnableACMPEEBrake
 **			 使能ACMP输出边沿触发刹车
 ** \param [in] ACMPSource: (1)EPWM_BRK_ACMP0			
 **						    (2)EPWM_BRK_ACMP1
 **				BrakeMode:  (1)EPWM_BRK_ACMP_RISING			上升沿刹车
 **							(2)EPWM_BRK_ACMP_FALLING		下降沿刹车	
 ** \return  none
 ** \note	 
*****************************************************************************/
void EPWM_EnableACMPEEBrake(uint8_t ACMPSource, uint8_t BrakeMode)
{
	if(ACMPSource == EPWM_BRK_ACMP0)
	{
		CNFBCON &= ~(ACMP_CNFBCON_C0FBES_Pos);
		CNFBCON |=  BrakeMode<< ACMP_CNFBCON_C0FBES_Pos | ACMP_CNFBCON_C0FBEEN_Msk;
	}
	if(ACMPSource == EPWM_BRK_ACMP1)
	{
		CNFBCON &= ~(ACMP_CNFBCON_C1FBES_Pos);
		CNFBCON |= (BrakeMode<< ACMP_CNFBCON_C1FBES_Pos) | ACMP_CNFBCON_C1FBEEN_Msk;
	}	
}

/*****************************************************************************
 ** \brief	 EPWM_DisableACMPEEBrake
 **			 关闭ACMP输出边沿触发刹车
 ** \param [in] ACMPSource: (1)EPWM_BRK_ACMP0			
 **						    (2)EPWM_BRK_ACMP1
 ** \return  none
 ** \note    
*****************************************************************************/
void EPWM_DisableACMPEEBrake(uint8_t ACMPSource)
{
	if(ACMPSource == EPWM_BRK_ACMP0)
	{
		CNFBCON &= ~(ACMP_CNFBCON_C0FBEEN_Msk);
	}
	if(ACMPSource == EPWM_BRK_ACMP1)
	{
		CNFBCON &= ~(ACMP_CNFBCON_C1FBEEN_Msk);
	}	
}

/*****************************************************************************
 ** \brief	 EPWM_EnableACMPLEBrake
 **			 使能ACMP输出电平触发刹车
 ** \param [in] ACMPSource: (1)EPWM_BRK_ACMP0			
 **						    (2)EPWM_BRK_ACMP1
 **				BrakeMode:  (1)EPWM_BRK_ACMP_LOW		低电平触发刹车
 **							(2)EPWM_BRK_ACMP_HIGH		高电平触发刹车	
 ** \return  none
 ** \note	 
*****************************************************************************/
void EPWM_EnableACMPLEBrake(uint8_t ACMPSource, uint8_t BrakeMode)
{
	if(ACMPSource == EPWM_BRK_ACMP0)
	{
		CNFBCON &= ~(ACMP_CNFBCON_C0FBPS_Msk);
		CNFBCON |= (BrakeMode<< ACMP_CNFBCON_C0FBPS_Pos) | ACMP_CNFBCON_C0FBPEN_Msk;
	}
	if(ACMPSource == EPWM_BRK_ACMP1)
	{
		CNFBCON &= ~(ACMP_CNFBCON_C1FBPS_Msk);
		CNFBCON |= (BrakeMode<< ACMP_CNFBCON_C1FBPS_Pos) | ACMP_CNFBCON_C1FBPEN_Msk;
	}	
}

/*****************************************************************************
 ** \brief	 EPWM_DisableACMPLEBrake
 **			 关闭ACMP输出电平触发刹车
 ** \param [in] ACMPSource: (1)EPWM_BRK_ACMP0			
 **						    (2)EPWM_BRK_ACMP1
 ** \return  none
 ** \note    
*****************************************************************************/
void EPWM_DisableACMPLEBrake(uint8_t ACMPSource)
{
	if(ACMPSource == EPWM_BRK_ACMP0)
	{
		CNFBCON &= ~(ACMP_CNFBCON_C0FBPEN_Msk);
	}
	if(ACMPSource == EPWM_BRK_ACMP1)
	{
		CNFBCON &= ~(ACMP_CNFBCON_C1FBPEN_Msk);
	}	
}

/*****************************************************************************
 ** \brief	 EPWM_EnableADCBrake
 **			 使能ADC输出触发刹车
 ** \param [in]none 
 ** \return  none
 ** \note	 ADC比较器 ADCMPO值为1 触发EPWM刹车
*****************************************************************************/
void EPWM_EnableADCBrake(void)
{
	ADCMPC |=   ADC_ADCMPC_ADFBEN_Msk;
}

/*****************************************************************************
 ** \brief	 EPWM_DisableADCBrake
 **			 关闭ADC输出触发刹车
 ** \param [in]none
 ** \return  none
 ** \note    
*****************************************************************************/
void EPWM_DisableADCBrake(void)
{
	ADCMPC &= ~(ADC_ADCMPC_ADFBEN_Msk);
}

/*****************************************************************************
 ** \brief	 EPWM_GetFaultBrakeStateFlag
 **			 获取故障刹车源状态位
 ** \param [in] none
 ** \return  0: 刹车信号撤销
 **          1：刹车信号有效
 ** \note  
*****************************************************************************/
uint8_t EPWM_GetFaultBrakeStateFlag( void)
{
	return((PWMFBKC & (EPWM_PWMFBKC_BRKAF_Msk))? 1:0);
}

/*****************************************************************************
 ** \brief	 EPWM_GetFaultBrakeOutputStateFlag
 **			 获取故障刹车输出状态位
 ** \param [in] none
 ** \return  0: EPWM正常输出
 **          1：EPWM输出刹车电平
 ** \note  
*****************************************************************************/
uint8_t EPWM_GetFaultBrakeOutputStateFlag( void)
{
	return((PWMBRKC & (EPWM_PWMBRKC_BRKOSF_Msk))? 1:0);
}

/*****************************************************************************
 ** \brief	 EPWM_ClearFaultBrake	
 ** 		 清除故障刹车输出状态位
 ** \param [in] none
 ** \return  none
 ** \note 
 *****************************************************************************/
void EPWM_ClearFaultBrake( void)
{
	PWMBRKC |= (EPWM_PWMBRKC_BRKRCLR_Msk);
}

/*****************************************************************************
 ** \brief	 EPWM_AllIntEnable
 **			 使能EPWM总中断
 ** \param [in] none
 ** \return  none
 ** \note   
*****************************************************************************/
void  EPWM_AllIntEnable(void)
{
	EIE2 |= IRQ_EIE2_PWMIE_Msk;
}
/*****************************************************************************
 ** \brief	 EPWM_AllIntDisable
 **			 关闭EPWM总中断
 ** \param [in] none
 ** \return  none
 ** \note   
 ****************************************************************************/
void  EPWM_AllIntDisable(void)
{
	EIE2 &= ~(IRQ_EIE2_PWMIE_Msk);
}
