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
/** \file system.h
**
** 
**
** History:
** 
*****************************************************************************/
#ifndef __SYSTEM_H__
#define __SYSTEM_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s78xx.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/
/*----------------------------------------------------------------------------
 **System 系统时钟常用分频系数
---------------------------------------------------------------------------*/
#define		SYS_CLK_DIV_1 		(0x00)		
#define 	SYS_CLK_DIV_2		(0x01)
#define		SYS_CLK_DIV_4 		(0x02)
#define 	SYS_CLK_DIV_6		(0x03)
#define		SYS_CLK_DIV_8 		(0x04)
#define 	SYS_CLK_DIV_10		(0x05)
#define		SYS_CLK_DIV_12 		(0x06)
#define 	SYS_CLK_DIV_14		(0x07)
#define		SYS_CLK_DIV_16 		(0x08)
#define 	SYS_CLK_DIV_18		(0x09)
#define 	SYS_CLK_DIV_20		(0x0a)
/*----------------------------------------------------------------------------
 **System 系统时钟模式
/*---------------------------------------------------------------------------*/
#define		SYS_CLK_LSI			(0x7)			/***内部低速时钟***/
#define		SYS_CLK_LSE			(0x6)			/***外部低速时钟***/
#define		SYS_CLK_HSE			(0x5)			/***外部高速时钟****/
#define		SYS_CLK_HSI			(0x4)			/****内部高速时钟****/

/*----------------------------------------------------------------------------
 **System 系统LVD电压监测点
---------------------------------------------------------------------------*/
#define 	SYS_LVD_2_0V		(0x00)							/*LVD电压监测点2.0V*/
#define 	SYS_LVD_2_16V		(0x01<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点2.16V*/
#define 	SYS_LVD_2_31V		(0x02<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点2.31V*/
#define 	SYS_LVD_2_45V		(0x03<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点2.45V*/
#define 	SYS_LVD_2_60V		(0x04<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点2.60V*/
#define 	SYS_LVD_2_73V		(0x05<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点2.73V*/
#define 	SYS_LVD_2_88V		(0x06<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点2.88V*/
#define 	SYS_LVD_2_98V		(0x07<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点2.98V*/
#define 	SYS_LVD_3_21V		(0x08<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点3.21V*/
#define 	SYS_LVD_3_42V		(0x09<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点3.42V*/
#define 	SYS_LVD_3_62V		(0x0A<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点3.62V*/
#define 	SYS_LVD_3_81V		(0x0B<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点3.81V*/
#define 	SYS_LVD_4_0V		(0x0C<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点4.0V*/
#define 	SYS_LVD_4_2V		(0x0D<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点4.2V*/
#define 	SYS_LVD_4_43V		(0x0E<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点4.43V*/
#define 	SYS_LVD_4_6V		(0x0F<<LVD_LVDCON_LVDSEL_Pos)	/*LVD电压监测点4.6V*/

/*----------------------------------------------------------------------------
 ** 定时唤醒 时钟分频系数
---------------------------------------------------------------------------*/
#define		WUT_CLK_DIV_1 			(0x00)		// 1分频
#define		WUT_CLK_DIV_8 			(0x01)		// 8分频
#define		WUT_CLK_DIV_32 			(0x02)		// 32分频
#define		WUT_CLK_DIV_256 		(0x03)		// 256分频

/*****************************************************************************
 ** \brief	 SYS_SET_SYSTEM_CLK
 **			 配置系统时钟
 ** \param [in] SysremClkDiv: 系统时钟分频(0x00~0xff)
 ** \return  none
 ** \note	 00H:Fsys=Fosc; 其他：Fsys =Fosc/(2*CLKDIV)(2,4..510)	
*****************************************************************************/
#define		SYS_SET_SYSTEM_CLK(SysremClkDiv)	do{\
													TA = 0xAA;\
													TA = 0x55;\
													CLKDIV = SysremClkDiv;\	
												}while(0)

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
 ** \brief	 SYS_ConfigSystemClk
 **			 配置系统时钟
 ** \param [in] SystemClkMode : (1)SYS_CLK_LSI:	内部低速时钟
 **								(2)SYS_CLK_LSE: 外部低速时钟
 **								(3)SYS_CLK_HSE: 外部高速时钟
 **								(4)SYS_CLK_HSI: 内部高速时钟
 ** \return  0:配置失败  1：配置成功
 ** \note	 
*****************************************************************************/
uint8_t SYS_ConfigSystemClk(uint8_t SystemClkMode);												
/*****************************************************************************
 ** \brief	 SYS_EnableLVD
 **			 开启电压监测功能
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_EnableLVD(void);
/*****************************************************************************
 ** \brief	 SYS_DisableLVD
 **			  关闭电压监测功能
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_DisableLVD(void);
/*****************************************************************************
 ** \brief	 SYS_ConfigLVD
 **			 配置系统电压监测电压
 ** \param [in] LVDValue :(1)SYS_LVD_2_0V		LVD电压监测点2.0V					
						(2)	SYS_LVD_2_16V		LVD电压监测点2.16V
						(3)	SYS_LVD_2_31V		LVD电压监测点2.31V
						(4)	SYS_LVD_2_45V		LVD电压监测点2.45V
						(5)	SYS_LVD_2_60V		LVD电压监测点2.60V
						(6)	SYS_LVD_2_73V		LVD电压监测点2.73V
						(7)	SYS_LVD_2_88V		LVD电压监测点2.88V
						(8)	SYS_LVD_2_98V		LVD电压监测点2.98V
						(9)	SYS_LVD_3_21V		LVD电压监测点3.21V
						(10)SYS_LVD_3_42V		LVD电压监测点3.42V
						(11)SYS_LVD_3_62V		LVD电压监测点3.62V
						(12)SYS_LVD_3_81V		LVD电压监测点3.81V
						(13)SYS_LVD_4_0V		LVD电压监测点4.0V
						(14)SYS_LVD_4_2V		LVD电压监测点4.2V
						(15)SYS_LVD_4_43V		LVD电压监测点4.43V
						(16)SYS_LVD_4_6V		LVD电压监测点4.6V
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_ConfigLVD(uint8_t LVDValue);

/*****************************************************************************
 ** \brief	 SYS_EnableLVDInt
 **			 开启电压监测中断功能
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_EnableLVDInt(void);
/*****************************************************************************
 ** \brief	 SYS_DisableLVDInt
 **			  关闭电压监测中断功能
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_DisableLVDInt(void);

/*****************************************************************************
 ** \brief	 SYS_GetLVDIntFlag
 **			 获取LVD中断标志位
 ** \param [in] none
 ** \return  0:无中断 1：有中断
 ** \note	 
*****************************************************************************/
uint8_t SYS_GetLVDIntFlag(void);

/*****************************************************************************
 ** \brief	 SYS_ClearLVDIntFlag
 **			 清除LVD中断标志位
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_ClearLVDIntFlag(void);


/*****************************************************************************
 ** \brief	 SYS_EnableWDTReset
 **			 使能WDT复位System
 ** \param [in] none
 ** \return none
 ** \note
 *****************************************************************************/
void SYS_EnableWDTReset(void);
/*****************************************************************************
 ** \brief	 SYS_DisableWDTReset
 **			 关闭WDT复位System
 ** \param [in] none
 ** \return none
 ** \note
 *****************************************************************************/
void SYS_DisableWDTReset(void);
/*****************************************************************************
 ** \brief	 SYS_GetWDTResetFlag
 **			 获取WDT复位System的标志
 ** \param [in] none
 ** \return 0：复位不由WDT溢出引起    1：复位由WDT溢出引起
 ** \note
 *****************************************************************************/
uint8_t SYS_GetWDTResetFlag(void);
/*****************************************************************************
 ** \brief	 SYS_ClearWDTResetFlag
 **			 清除WDT复位System的标志
 ** \param [in] none
 ** \return   none
 ** \note
 *****************************************************************************/
void SYS_ClearWDTResetFlag(void);

/*****************************************************************************
 ** \brief	 SYS_EnableSoftwareReset
 **			 使能软件复位System
 ** \param [in] none
 ** \return none
 ** \note
 *****************************************************************************/
void SYS_EnableSoftwareReset(void);
/*****************************************************************************
 ** \brief	 SYS_DisableSoftwareReset
 **			 关闭软件复位System
 ** \param [in] none
 ** \return none
 ** \note
 *****************************************************************************/
void SYS_DisableSoftwareReset(void);

/*****************************************************************************
 ** \brief	 SYS_GetPowerOnResetFlag
 **			 获取上电复位System的标志
 ** \param [in] none
 ** \return   0：复位不由上电复位引起    1：复位由上电复位引起
 ** \note
 *****************************************************************************/
uint8_t SYS_GetPowerOnResetFlag(void);


/*****************************************************************************
 ** \brief	 SYS_ClearPowerOnResetFlag
 **			 清除PowerOn复位System的标志
 ** \param [in] none
 ** \return   none
 ** \note
 *****************************************************************************/
void SYS_ClearPowerOnResetFlag(void);

/*****************************************************************************
 ** \brief	 SYS_EnableWakeUp
 **			 使能休眠唤醒
 ** \param [in] none
 **
 ** \return none
 ** \note	 可由外部中断唤醒
 *****************************************************************************/
void SYS_EnableWakeUp(void);
/*****************************************************************************
 ** \brief	 SYS_EnableWakeUp
 **			 关闭休眠唤醒
 ** \param [in] none
 **
 ** \return none
 ** \note	
 *****************************************************************************/
void SYS_DisableWakeUp(void);

/*****************************************************************************
 ** \brief	 SYS_EnterStop
 **			 进入休眠中STOP状态
 ** \param [in] none
 **
 ** \return none
 ** \note	
 *****************************************************************************/
void SYS_EnterStop(void);
/*****************************************************************************
 ** \brief	 SYS_EnterIdle
 **			 进入休眠模式中Idle状态
 ** \param [in] none
 **
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_EnterIdle(void);


/*****************************************************************************
 ** \brief	 SYS_EnableWakeUpTrig
 **			 使能定时唤醒功能
 ** \param [in] none
 **
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_EnableWakeUpTrig(void);
/*****************************************************************************
 ** \brief	 SYS_DisableWakeUpTrig
 **			 关闭定时唤醒功能
 ** \param [in] none
 **
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_DisableWakeUpTrig(void);

/*****************************************************************************
 ** \brief	 SYS_ConfigWUTCLK
 **			设置定时唤醒时钟
 ** \param [in] clkdiv: (1)WUT_CLK_DIV_1 
 **						(2)WUT_CLK_DIV_8
 **						(2)WUT_CLK_DIV_32
**						(2)WUT_CLK_DIV_256
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_ConfigWUTCLK(uint8_t ckkdiv );

/*****************************************************************************
 ** \brief	 SYS_ConfigWUTTime
 **			设置定时唤醒时间
 ** \param [in] time: 12it（0x0 ~ 0xFFF）
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_ConfigWUTTime(uint16_t time );


/*****************************************************************************
 ** \brief	 SYS_EnableSCM
 **			 使能停振监测功能
 ** \param [in] none
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_EnableSCM(void);
/*****************************************************************************
 ** \brief	 SYS_DisableSCM
 **			 关闭停振监测功能
 ** \param [in] none
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_DisableSCM(void);

/*****************************************************************************
 ** \brief	 SYS_EnableSCMInt
 **			 使能停振监测中断功能
 ** \param [in] none
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_EnableSCMInt(void);
/*****************************************************************************
 ** \brief	 SYS_DisableSCMInt
 **			 关闭停振监测中断功能
 ** \param [in] none
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_DisableSCMInt(void);
/*****************************************************************************
 ** \brief	 SYS_GetSCMIntFlag
 **			 获取停振监测中断标志位
 ** \param [in] none
 ** \return  0:无中断 1：有中断
 ** \note	 
*****************************************************************************/
uint8_t SYS_GetSCMIntFlag(void);
/*****************************************************************************
 ** \brief	 SYS_GetSCMState
 **			 获取停振监测状态位位
 ** \param [in] none
 ** \return  0:停振恢复 1：停振
 ** \note	 
*****************************************************************************/
uint8_t SYS_GetSCMState(void);
/*****************************************************************************
 ** \brief	 SYS_ClearSCMIntFlag
 **			 清除停振监测中断标志位
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_ClearSCMIntFlag(void);



#endif /* __SYSTEM_H__ */



