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
/** \file epwm.h
**
**
**
** History:
**
******************************************************************************/
#ifndef __EPWM_H__
#define __EPWM_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s78xx.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/
/*----------------------------------------------------------------------------
 **EPWM通道Mask
/*---------------------------------------------------------------------------*/
#define EPWM_CHANNEL_NUM                     (4)    /* EPWM channel number */
#define EPWM_CH_0_MSK                       (0x1)   /* EPWM channel 0 mask */
#define EPWM_CH_1_MSK                       (0x2)   /* EPWM channel 1 mask */
#define EPWM_CH_2_MSK                       (0x4)   /* EPWM channel 2 mask */
#define EPWM_CH_3_MSK                       (0x8)   /* EPWM channel 3 mask */

#define EPWM0								(0x00)	/* EPWM channel 0 number */
#define EPWM1								(0x01)	/* EPWM channel 1 number */
#define EPWM2								(0x02)	/* EPWM channel 2 number */
#define EPWM3								(0x03)	/* EPWM channel 3 number */

/*----------------------------------------------------------------------------
 **EPWM计数模式
/*---------------------------------------------------------------------------*/
#define EPWM_COUNT_UP_DOWN			(0x02)  /*EPWM计数（COUNT）模式：上下计数（中心对齐）模式*/
#define EPWM_COUNT_DOWN				(0x00)  /*EPWM计数（COUNT）模式：向下计数（边沿对齐）模式*/
/*----------------------------------------------------------------------------
 **EPWM输出比较单元(OCU)模式
/*---------------------------------------------------------------------------*/
#define EPWM_OCU_ASYMMETRIC			(0x04)  /*EPWM输出比较单元（OCU）模式； 非对称计数模式*/
#define EPWM_OCU_SYMMETRIC			(0x00)  /*EPWM输出比较单元（OCU）模式； 对称计数模式*/
/*----------------------------------------------------------------------------
 **EPWM波形发生器单元(WFG)模式
/*---------------------------------------------------------------------------*/
#define EPWM_WFG_INDEPENDENT 		(0x00)  /*EPWM波形发生器（WFG）模式：单个（独立）模式*/
#define EPWM_WFG_COMPLEMENTARY 		(0x10)  /*EPWM波形发生器（WFG）模式：互补模式*/
#define EPWM_WFG_SYNCHRONIZED		(0x20)  /*EPWM波形发生器（WFG）模式：同步模式*/
/*----------------------------------------------------------------------------
 **EPWM输出控制单元(OC)模式
/*---------------------------------------------------------------------------*/
#define EPWM_OC_GROUP					(0x08)  /*EPWM输出控制（OC）模式： 组控模式*/
#define EPWM_OC_INDEPENDENT 			(0x00)  /*EPWM输出控制（OC）模式： 通道各自独立控制*/
/*----------------------------------------------------------------------------
 **EPWM刹车源
/*---------------------------------------------------------------------------*/
#define EPWM_BRK_SOFTWARE  					(0x00)		/*软件刹车*/
#define EPWM_BRK_FB0						(0x01)		/*FB0刹车*/
#define EPWM_BRK_FB1						(0x02)		/*FB1刹车*/
#define EPWM_BRK_ACMP0						(0x03)		/*ACMP0输出刹车*/
#define EPWM_BRK_ACMP1						(0x04)		/*ACMP1输出刹车*/
#define EPWM_BRK_ADC						(0x05)		/*ADC比较刹车*/
/*----------------------------------------------------------------------------
 **EPWM刹车源FB刹车触发模式
/*---------------------------------------------------------------------------*/
#define EPWM_BRK_FB_LOW						(0x0)	/*FB低电平触发刹车*/
#define EPWM_BRK_FB_HIGH					(0x01)	/*FB高电平触发刹车*/
/*----------------------------------------------------------------------------
 **EPWM刹车源ACMP刹车触发模式
/*---------------------------------------------------------------------------*/
#define EPWM_BRK_ACMP_LOW					(0x01)	/*ACMP输出低电平触发刹车*/
#define EPWM_BRK_ACMP_HIGH					(0x00)	/*ACMP输出高电平触发刹车*/
#define EPWM_BRK_ACMP_RISING				(0x0)	/*ACMP输出上升沿刹车*/
#define EPWM_BRK_ACMP_FALLING				(0x01)	/*ACMP输出下降沿刹车*/

/*----------------------------------------------------------------------------
 **EPWM 刹车恢复模式
/*---------------------------------------------------------------------------*/
#define EPWM_BRK_STOP				(0x00)		/*停止模式*/
#define EPWM_BRK_SUSPEND			(0x01)		/*暂停模式*/
#define EPWM_BRK_RECOVER			(0x02)		/*恢复模式*/
#define EPWM_BRK_DELAY_RECOVER		(0x03)		/*延时恢复模式*/

/*----------------------------------------------------------------------------
 **EPWM 刹车恢复加载点
/*---------------------------------------------------------------------------*/
#define EPWM_BRK_LOAD_EPWM0				(0x00)		/*EPWM0的加载点恢复*/
#define EPWM_BRK_LOAD_EPWM1				(0x01<<EPWM_PWMFBRKC_BRKRCS_Pos)		/*EPWM1的加载点恢复*/
#define EPWM_BRK_LOAD_EPWM2				(0x02<<EPWM_PWMFBRKC_BRKRCS_Pos)		/*EPWM2的加载点恢复*/
#define EPWM_BRK_LOAD_EPWM3				(0x03<<EPWM_PWMFBRKC_BRKRCS_Pos)		/*EPWM3的加载点恢复*/


/*----------------------------------------------------------------------------
 **EPWM时钟分频系数
/*---------------------------------------------------------------------------*/
#define EPWM_CLK_DIV_1						(0xff)
#define EPWM_CLK_DIV_2						(0x04)
#define EPWM_CLK_DIV_4						(0x00)
#define EPWM_CLK_DIV_8						(0x01)
#define EPWM_CLK_DIV_16						(0x02)
#define EPWM_CLK_DIV_32						(0x03)



/*****************************************************************************
 ** \brief	 EPWM_ENABLE_LOAD
 **			 使能加载周期、占空比数据(PERIODn、CMPn、CMPDn)
 ** \param [in]ChannelMask : EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
 ****************************************************************************/
#define EPWM_ENABLE_LOAD(ChannelMask) 	(PWMLOADEN |= ChannelMask)

/*****************************************************************************
 ** \brief	 EPWM_ENABLE_COUNT
 **			 使能EPWM计数
 ** \param [in] ChannelMask : EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
** \note
 ****************************************************************************/
#define EPWM_ENABLE_COUNT(ChannelMask) 	(PWMCNTE |= ChannelMask)

/*****************************************************************************
 ** \brief	 EPWM_DISABLE_COUNT
 **			 关闭EPWM计数
 ** \param [in] ChannelMask : EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
** \note
 ****************************************************************************/
#define EPWM_DISABLE_COUNT(ChannelMask) 	(PWMCNTE &= ~ChannelMask)

/*****************************************************************************
 ** \brief	 EPWM_ENABLE_OUTPUT
 **			 使能EPWM输出
 ** \param [in] ChannelMask : EPWM_CH_0_MSK 、EPWM_CH_1_MSK 、EPWM_CH_2_MSK
 **							 EPWM_CH_3_MSK
 ** \return  none
 ****************************************************************************/
#define EPWM_ENABLE_OUTPUT(ChannelMask) 	(PWMOE |= ChannelMask)
/*****************************************************************************
 ** \brief	 EPWM_DISABLE_OUTPUT
 **			 关闭EPWM输出
 ** \param [in]ChannelMask : EPWM_CH_0_MSK 、EPWM_CH_1_MSK 、EPWM_CH_2_MSK
 **							 EPWM_CH_3_MSK
 ** \return  none
 ****************************************************************************/
#define EPWM_DISABLE_OUTPUT(ChannelMask) 	(EPWM->_PWMOE &= ~ChannelMask)
/*****************************************************************************
 ** \brief	 EPWM_SET_MASK_LEVEL
 **			设置EPWM掩码电平
 ** \param [in] MaskValue : xxxx0000 : 设置EPWM0~3 掩码值为低
 **						  ......
 **						  xxxx1111 : 设置EPWM0~3 掩码值为高
 ** \return  none
 ** \note    PG0 : bit0 、PG1：bit1、PG2: bit2、PG3：bit3
 ****************************************************************************/
#define EPWM_SET_MASK_LEVEL(MaskValue)  (PWMMASKD = MaskValue)

/*****************************************************************************
 ** \brief	 EPWM_ENABLE_MASK
 **			开启EPWM掩码输出
 ** \param [in] ChannelMsk : EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
 ****************************************************************************/
#define EPWM_ENABLE_MASK(ChannelMsk)  (PWMMASKE |= ChannelMsk)

/*****************************************************************************
 ** \brief	 EPWM_DISABLE_MASK
 **			 关闭EPWM掩码输出
 ** \param [in] ChannelMsk : EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
 ****************************************************************************/
#define EPWM_DISABLE_MASK(ChannelMsk)  (PWMMASKE &= ~(ChannelMsk))

/*****************************************************************************
 ** \brief	 EPWM_SET_BRAKE_LEVEL
 **			设置EPWM刹车电平
 ** \param [in]MaskValue : xxxx0000 : 设置EPWM0~3 刹车电平为低
 **						  ......
 **						  xxxx1111 : 设置EPWM0~3 刹车电平为高
 ** \return  none
 ** \note    PG0 : bit0 、PG1：bit1、PG2: bit2、PG3：bit3
 ****************************************************************************/
#define EPWM_SET_BRAKE_LEVEL(BrakeValue)  ( PWMFBKD = BrakeValue)


/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/


/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/

/*****************************************************************************
 ** \brief	 EPWM_ConfigRunMode
 **			 设置EPWM的运行模式
 ** \param [in] EpwmRunMode:
							   (1)EPWM_COUNT_UP_DOWN
							   (2)EPWM_COUNT_DOWN
							   (3)EPWM_OCU_ASYMMETRIC
							   (4)EPWM_OCU_SYMMETRIC
							   (5)EPWM_WFG_INDEPENDENT
							   (6)EPWM_WFG_COMPLEMENTARY
							   (7)EPWM_WFG_SYNCHRONIZED
							   (8)EPWM_OC_GROUP
							   (9)EPWM_OC_INDEPENDENT
 ** \return  none
 ** \note    以上9种摸式可组合成不同的运行模式，且共用一个8位寄存器
 ****************************************************************************/
void EPWM_ConfigRunMode( uint8_t EpwmRunMode);
/*****************************************************************************
 ** \brief	 EPWM_ConfigChannelClk
 ** \param [in] ClkDiv: (1)EPWM_CLK_DIV_1
 **						(2)EPWM_CLK_DIV_2
 **						(2)EPWM_CLK_DIV_4
 **						(2)EPWM_CLK_DIV_8
 **						(2)EPWM_CLK_DIV_16
 **						(2)EPWM_CLK_DIV_32
 ** \return  none
 ** \note
 **	(1)PWM01PSC共同控制PWM0、PWM1通道 ，所以此函数统一设置PWMxxPSC=0x01
 **	若需要其他的分频，请酌情对寄存器赋值
 **	(2)EPWM 分频分为两级：PWMxPSC PWMnDIV
 **	第一级分频(PWMxPSC)：0x00 预分频停止并且计数器停止; 其他值：系统时钟分频系数PWMxPSC+1
 **	第二级分频（PWMnDIV): 0x00 FEPWMPSC/2; 0x01 FEPWMPSC/4；0x02:FEPWMPSC/8；0x3 FEPWMPSC/16
 **	0x04 FEPWMPSC ; 其他 Fsys
 ** 分频级数：1~4096，例Fsys=8M，EPWM的频率范围：1.95k ~ 8M
 ****************************************************************************/
void EPWM_ConfigChannelClk(uint8_t ChannelNum,uint8_t ClkDiv);
/*****************************************************************************
 ** \brief	 EPWM_ConfigChannelPeriod
 **			 设置EPWM通道的频率以及占空比
 ** \param [in] ChannelNum : EPWM0,EPWM1,EPWM2,EPWM3
 **				Period: 16位周期值
 ** \return none
 ** \note
 ****************************************************************************/
void EPWM_ConfigChannelPeriod(uint8_t ChannelNum,uint16_t Period);

/*****************************************************************************
 ** \brief	 EPWM_ConfigChannelSymDuty
 **			 设置EPWM通道对称模式占空比
 ** \param [in] ChannelNum  :EPWM0,EPWM1,EPWM2,EPWM3
 **				Duty: 16位占空比
 ** \return none
 ** \note
 ****************************************************************************/
void EPWM_ConfigChannelSymDuty(uint8_t ChannelNum,uint16_t Duty);
 /*****************************************************************************
 ** \brief	 EPWM_ConfigChannelAsymDuty
 **			 设置EPWM通道非对称模式占空比
 ** \param [in] ChannelNum  :EPWM0,EPWM1,EPWM2,EPWM3
 **				DownCmp: 16 bit 向下比较值
 ** \return none
 ** \note    只适用于中心对齐计数(上下计数)模式
 ****************************************************************************/
void EPWM_ConfigChannelAsymDuty(uint8_t ChannelNum,uint16_t UpCmp, uint16_t DowmCmp);

 /****************************************************************************
 ** \brief	 EPWM_EnableOneShotMode
 **			 开启One-Shot模式
 ** \param [in]  ChannelMask   EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_EnableOneShotMode(uint8_t ChannelMask);
/****************************************************************************
 ** \brief	 EPWM_EnableAutoLoadMode
 **			 开启自动加载模式
 ** \param [in]  ChannelMask   EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_EnableAutoLoadMode(uint8_t ChannelMask);


/*****************************************************************************
 ** \brief	 EPWM_EnableReverseOutput
 **			 开启反向输出
 ** \param [in] ChannelMask : EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note  正常模式： EPWM 开始从初值开始计数时，PWM输出口输出为低电平,
 **	当EPWM计数值与向上、向下计数匹配时，输出翻转
*****************************************************************************/
void  EPWM_EnableReverseOutput( uint8_t ChannelMask);
/*****************************************************************************
 ** \brief	 EPWM_DisableReverseOutput
 **			 关闭反向输出
 ** \param [in]ChannelMask: EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
*****************************************************************************/
void  EPWM_DisableReverseOutput( uint8_t ChannelMask);

/*****************************************************************************
 ** \brief	 EPWM_Start
 **
 ** \param [in]  ChannelMask : EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
 ****************************************************************************/
void EPWM_Start( uint8_t ChannelMask);
/*****************************************************************************
 ** \brief	 EPWM_Stop
 **
 ** \param [in] ChannelMask   EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note    停止计数并且EPWM计数器清0
*****************************************************************************/
void EPWM_Stop( uint8_t ChannelMask);

/*****************************************************************************
 ** \brief	 EPWM_EnableOutput
 **			 开启EPWM输出
 ** \param [in] ChannelMask   EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_EnableOutput( uint8_t ChannelMask);
/*****************************************************************************
 ** \brief	 EPWM_DisableOutput
 **			 关闭EPWM输出
 ** \param [in] ChannelMask   EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_DisableOutput( uint8_t ChannelMask);

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
void EPWM_ConfigBrakeMode( uint8_t BrakeMode , uint8_t Relaod);

/*****************************************************************************
 ** \brief	 EPWM_ConfigBrakeRecoverDelay
 **			 配置刹车恢复延时模式的延时
 ** \param [in] time : 0~0x3ff
 ** \return  none
 ** \note  刹车恢复延时时间 = time * Tsys(系统时钟)
*****************************************************************************/
void EPWM_ConfigBrakeRecoverDelay( uint16_t time);

/*****************************************************************************
 ** \brief	 EPWM_EnableFaultBrake
 **			 使能EPWM刹车模式
 ** \param [in] none
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_EnableFaultBrake( void);
/*****************************************************************************
 ** \brief	 EPWM_DisableFaultBrake
 **			 关闭EPWM刹车
 ** \param [in] none
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_DisableFaultBrake(void);

/****************************************************************************
 ** \brief	 EPWM_ConfigChannelBrakeLevel
 **			 设置EPWM通道刹车电平
 ** \param [in]  ChannelMask： EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 **		   		 BrakeLevel: FaultBreake后的EPWM通道电平 ：0/1(低/高)
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_ConfigChannelBrakeLevel( uint8_t ChannelMask, uint8_t BrakeLevel);

/****************************************************************************
 ** \brief	 EPWM_EnableDeadZone
 **			 开启死区
 ** \param [in] ChannelMask: EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 **			DeadTime : 死区时间( 0~0xFF) = DeadTime * Tepwm
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_EnableDeadZone( uint8_t ChannelMask, uint8_t DeadTime);
/*****************************************************************************
 ** \brief	 EPWM_DisableDeadZone
 **			 关闭EPWM死区
 ** \param [in] ChannelMask:  EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_DisableDeadZone( uint8_t ChannelMask);
/*****************************************************************************
 ** \brief	 EPWM_EnableMaskControl
 **			 掩码控制开启
 ** \param [in] ChannelMask:  EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** 	    	MaskLevel: 掩码的数据 :0/1(低/高)
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_EnableMaskControl( uint8_t ChannelMask, uint8_t MaskLevel);
/*****************************************************************************
 ** \brief	 EPWM_DisableMaskControl
 **			 掩码控制关闭
 ** \param [in] ChannelMask:  EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_DisableMaskControl( uint8_t ChannelMask);
/*****************************************************************************
 ** \brief	 EPWM_EnableUpCmpInt
 **			 开启向上比较中断
 ** \param [in]  ChannelMask： EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_EnableUpCmpInt( uint8_t ChannelMask);
/*****************************************************************************
 ** \brief	 EPWM_DisableUpCmptInt
 **			 关闭向上比较中断
 ** \param [in]ChannelMask ：EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_DisableUpCmpInt( uint8_t ChannelMask);
/*****************************************************************************
 ** \brief	 EPWM_GetUpCmpIntFlag
 **			 获取向上比较中断标志位
 ** \param [in] ChannelNum:EPWM0,EPWM1,EPWM2,EPWM3
 ** \return  0: 无中断产生
 **          1：有中断产生
 ** \note
*****************************************************************************/
uint8_t EPWM_GetUpCmpIntFlag( uint8_t ChannelNum);
/*****************************************************************************
 ** \brief	 EPWM_ClearUpCmpIntFlag
 **			 清除向上比较中断标志位
 ** \param [in] ChannelNum:EPWM0,EPWM1,EPWM2,EPWM3
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_ClearUpCmpIntFlag( uint8_t ChannelNum);
/*****************************************************************************
 ** \brief	 EPWM_EnableDownCmpInt
 **			 开启向下比较中断
 ** \param [in] ChannelMask : EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_EnableDownCmpInt( uint8_t ChannelMask);
/*****************************************************************************
 ** \brief	 EPWM_DisableDownCmpInt
 **			 关闭向下比较中断
 ** \param [in] ChannelMask : EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_DisableDownCmpInt( uint8_t ChannelMask);
/*****************************************************************************
 ** \brief	 EPWM_GetUpCmpIntFlag
 **			 获取向下比较中断标志位
 ** \param [in] ChannelNum: EPWM0,EPWM1,EPWM2,EPWM3
 ** \return  0: 无中断产生
 **          1：有中断产生
 ** \note
*****************************************************************************/
uint8_t EPWM_GetDownCmpIntFlag( uint8_t ChannelNum);
/*****************************************************************************
 ** \brief	 EPWM_ClearUpCmpIntFlag
 **			 清除向下比较中断标志位
 ** \param [in] ChannelNum :EPWM0,EPWM1,EPWM2,EPWM3
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_ClearDownCmpIntFlag( uint8_t ChannelNum);
/*****************************************************************************
 ** \brief	 EPWM_EnablePeriodInt
 **			 开启周期中断
 ** \param [in] ChannelMask: EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return   none
 ** \note
*****************************************************************************/
void EPWM_EnablePeriodInt( uint8_t ChannelMask);
/*****************************************************************************
 ** \brief	 EPWM_DisablePeriodInt
 **			 关闭周期中断
 ** \param [in]  ChannelMask: EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return   none
 ** \note
*****************************************************************************/
void EPWM_DisablePeriodInt( uint8_t ChannelMask);
/*****************************************************************************
 ** \brief	 EPWM_ClearPeriodIntFlag
 **			 获取周期中断标志位
 ** \param [in]  ChannelNum: EPWM0,EPWM1,EPWM2,EPWM3
 ** \return   0：无中断产生
 **           1：有中断产生
 ** \note
*****************************************************************************/
uint8_t EPWM_GetPeriodIntFlag( uint8_t ChannelNum);
/*****************************************************************************
 ** \brief	 EPWM_ClearPeriodIntFlag
 **			 清除周期中断标志位
 ** \param [in]  ChannelNum: EPWM0,EPWM1,EPWM2,EPWM3
 ** \return   none
 ** \note
*****************************************************************************/
void EPWM_ClearPeriodIntFlag( uint8_t ChannelNum);
/*****************************************************************************
 ** \brief	 EPWM_EnableZeroInt
 **			 开启零点中断
 ** \param [in]  ChannelMask: EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return   none
 ** \note
*****************************************************************************/
void EPWM_EnableZeroInt( uint8_t ChannelMask);
/*****************************************************************************
 ** \brief	 EPWM_DisableZeroInt
 **			 关闭零点中断
 ** \param [in]ChannelMask: EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 ** \return   none
 ** \note
*****************************************************************************/
void EPWM_DisableZeroInt( uint8_t ChannelMask);
/*****************************************************************************
 ** \brief	 EPWM_GetZeroIntFlag
 **			 获取零点中断标志位
 ** \param [in] ChannelNum: EPWM0,EPWM1,EPWM2,EPWM3
 ** \return   0：无中断产生
 **           1：有中断产生
 ** \note
 *****************************************************************************/
uint8_t EPWM_GetZeroIntFlag( uint8_t ChannelNum);
/*****************************************************************************
 ** \brief	 EPWM_ClearZeroIntFlag
 **			 清除零点中断标志位
 ** \param [in] ChannelNum: EPWM0,EPWM1,EPWM2,EPWM3
 ** \return   none
 ** \note
*****************************************************************************/
void EPWM_ClearZeroIntFlag( uint8_t ChannelNum);
/*****************************************************************************
 ** \brief	 EPWM_EnableFaultBrakeInt
 **			 开启故障刹车中断
 ** \param [in]none
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_EnableFaultBrakeInt( void);
/*****************************************************************************
 ** \brief	 EPWM_DisableFaultBrakeInt
 **			 关闭故障刹车中断
 ** \param [in]none
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_DisableFaultBrakeInt(void);
/*****************************************************************************
 ** \brief	 EPWM_GetFaultBrakeIntFlag
 **			 获取故障刹车中断标志位
 ** \param [in] none
 ** \return  0: 无中断产生
 **          1：有中断产生
 ** \note
*****************************************************************************/
uint8_t EPWM_GetFaultBrakeIntFlag( void);
/*****************************************************************************
 ** \brief	 EPWM_ClearFaultBrakeIntFlag
 ** 		 清除故障刹车中断标志位
 ** \param [in] none
 ** \return  none
 ** \note
 *****************************************************************************/
void EPWM_ClearFaultBrakeIntFlag( void);
/*****************************************************************************
 ** \brief	 EPWM_TrigSoftwareBrake
 **			  触发软件刹车
 ** \param [in]	none
 ** \return  none
 ** \note
*****************************************************************************/
void  EPWM_TrigSoftwareBrake(void);
/*****************************************************************************
 ** \brief	 EPWM_DisableSoftwareBreake
 **			 关闭软件刹车
 ** \param [in] none
 ** \return  none
 ** \note
*****************************************************************************/
void  EPWM_DisableSoftwareBrake(void);


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
void EPWM_EnableFBBrake(uint8_t FBSource, uint8_t FBBrakeMode);

/*****************************************************************************
 ** \brief	 EPWM_DisableFBBrake
 **			 关闭外部硬件触发刹车
 ** \param [in] FBSource: (1)EPWM_BRK_FB0
 **						  (2)EPWM_BRK_FB1
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_DisableFBBrake(uint8_t FBSource);

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
void EPWM_EnableACMPEEBrake(uint8_t ACMPSource, uint8_t BrakeMode);

/*****************************************************************************
 ** \brief	 EPWM_DisableACMPEEBrake
 **			 关闭ACMP输出边沿触发刹车
 ** \param [in] ACMPSource: (1)EPWM_BRK_ACMP0
 **						    (2)EPWM_BRK_ACMP1
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_DisableACMPEEBrake(uint8_t ACMPSource);

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
void EPWM_EnableACMPLEBrake(uint8_t ACMPSource, uint8_t BrakeMode);

/*****************************************************************************
 ** \brief	 EPWM_DisableACMPLEBrake
 **			 关闭ACMP输出电平触发刹车
 ** \param [in] ACMPSource: (1)EPWM_BRK_ACMP0
 **						    (2)EPWM_BRK_ACMP1
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_DisableACMPLEBrake(uint8_t ACMPSource);


/*****************************************************************************
 ** \brief	 EPWM_EnableADCBrake
 **			 使能ADC输出触发刹车
 ** \param [in]none
 ** \return  none
 ** \note	 ADC比较器 ADCMPO值为1 触发EPWM刹车
*****************************************************************************/
void EPWM_EnableADCBrake( void);

/*****************************************************************************
 ** \brief	 EPWM_DisableADCBrake
 **			 关闭ADC输出触发刹车
 ** \param [in]none
 ** \return  none
 ** \note
*****************************************************************************/
void EPWM_DisableADCBrake(void);


/*****************************************************************************
 ** \brief	 EPWM_GetFaultBrakeStateFlag
 **			 获取故障刹车源状态位
 ** \param [in] none
 ** \return  0: 刹车信号撤销
 **          1：刹车信号有效
 ** \note
*****************************************************************************/
uint8_t EPWM_GetFaultBrakeStateFlag( void);

/*****************************************************************************
 ** \brief	 EPWM_GetFaultBrakeOutputStateFlag
 **			 获取故障刹车输出状态位
 ** \param [in] none
 ** \return  0: EPWM正常输出
 **          1：EPWM输出刹车电平
 ** \note
*****************************************************************************/
uint8_t EPWM_GetFaultBrakeOutputStateFlag( void);

/*****************************************************************************
 ** \brief	 EPWM_ClearFaultBrake
 ** 		 清除故障刹车状态
 ** \param [in] none
 ** \return  none
 ** \note
 *****************************************************************************/
void EPWM_ClearFaultBrake( void);


/*****************************************************************************
 ** \brief	 EPWM_AllIntEnable
 **			 使能EPWM总中断
 ** \param [in] none
 ** \return  none
 ** \note
*****************************************************************************/
void  EPWM_AllIntEnable(void);
/*****************************************************************************
 ** \brief	 EPWM_AllIntDisable
 **			 关闭EPWM总中断
 ** \param [in] none
 ** \return  none
 ** \note
*****************************************************************************/
void  EPWM_AllIntDisable(void);

/****************************************************************************
 ** \brief	 EPWM_EnableSynCount
 **			使能PWMn同步计数
 ** \param [in]  none
 ** \return  none
 ** \note
 ****************************************************************************/
void EPWM_EnableSynCount(void);




#endif /* __EPWM_H__ */







