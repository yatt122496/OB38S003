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
/** \file uart.h
**
**
**
** History:
** 
******************************************************************************/
#ifndef __UART_H__
#define __UART_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s78xx.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/

/*----------------------------------------------------------------------------
 **UART 模式
/*---------------------------------------------------------------------------*/
#define UART_MOD_SYN				(0x00)		/*同步模式*/
#define	UART_MOD_ASY_8BIT 			(0x01)		/*8位异步模式且波特率可变*/				
#define UART_MOD_ASY_9BIT			(0x03)		/*9位异步模式且波特率可变*/
#define UART_MOD_ASY_9BIT_STATIC	(0x02)		/*9位异步模式且波特率为Fsys/32或者Fsys/64*/
/*----------------------------------------------------------------------------
 **UART 波特率时钟
/*---------------------------------------------------------------------------*/
#define UART_BAUD_TMR1				(0x00)		/*波特率时钟选择Timer1*/
#define UART_BAUD_TMR4				(0x01)		/*波特率时钟选择Timer4*/
#define UART_BAUD_TMR2				(0x02)		/*波特率时钟选择Timer2*/
#define UART_BAUD_BRT				(0x03)		/*波特率时钟选择BRT*/
/*----------------------------------------------------------------------------
 ** BRT 波特率定时器时钟分频
/*---------------------------------------------------------------------------*/
#define BRT_CLK_DIV_1				(0x00)		/*Fbrt = Fsys/1*/
#define BRT_CLK_DIV_2				(0x01)		/*Fbrt = Fsys/2*/
#define BRT_CLK_DIV_4				(0x02)		/*Fbrt = Fsys/4*/
#define BRT_CLK_DIV_8				(0x03)		/*Fbrt = Fsys/8*/
#define BRT_CLK_DIV_16				(0x04)		/*Fbrt = Fsys/16*/
#define BRT_CLK_DIV_32				(0x05)		/*Fbrt = Fsys/32*/
#define BRT_CLK_DIV_64				(0x06)		/*Fbrt = Fsys/64*/
#define BRT_CLK_DIV_128				(0x07)		/*Fbrt = Fsys/128*/
/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/



/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/


/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/
/******************************************************************************
 ** \brief UART_ConfigRunMode
 **			配置UART运行模式
 ** \param [in] UARTMode:		(1)UART_MOD_SYN : 同步模式
 **								(2)UART_MOD_ASY_8BIT: 8位异步模式
 **								(3)UART_MOD_ASY_9BIT：9位异步模式
 **								(4)UART_MOD_ASY_9BIT_STATIC：9位波特率固定异步模式
 **				UARTBaudTimer:  (1)UART_BAUD_TMR1 :	Timer1产生波特率
 **								(2)UART_BAUD_TMR4 :	Timer4产生波特率
 **								(3)UART_BAUD_TMR2 : Timer2产生波特率
 **								(4)UART_BAUD_BRT : BRT产生波特率
 ** \return none
******************************************************************************/
void UART_ConfigRunMode(uint8_t UARTMode, uint8_t UARTBaudTimer);
/******************************************************************************
 ** \brief UART_EnableDoubleFrequency
 **			使能UART波特率倍频模式
 ** \param [in]none
 ** \return none
******************************************************************************/
void UART_EnableDoubleFrequency(void);
/******************************************************************************
 ** \brief UART_DisableDoubleFrequency
 **			关闭UART波特率倍频模式
 ** \param [in]none
 ** \return none
******************************************************************************/
void UART_DisableDoubleFrequency(void);

/******************************************************************************
 ** \brief UART_ConfigBaudRate
 **			配置UART波特率
 ** \param [in]BaudRateValue:  波特率值
 ** \return Timer1/4: 8位自动重装模式的THx值
 **			Timer2: 16 位自动重装模式的 RLDH:RLDL 值
 **			BRT: 16 位定时模式 BRTH:BRTL 值
******************************************************************************/
uint16_t UART_ConfigBaudRate(uint32_t  BaudRateValue);

/******************************************************************************
 ** \brief UART_EnableReceive
 **			开启接收模式
 ** \param [in]none
 ** \return 
******************************************************************************/
void UART_EnableReceive(void);
/******************************************************************************
 ** \brief UART_DisableReceive
 **			关闭接收模式
 ** \param [in]none
 ** \return none
******************************************************************************/
void UART_DisableReceive(void);

/******************************************************************************
 ** \brief UART_EnableInt
 **			开启中断
 ** \param [in]none
 ** \return none
******************************************************************************/
void UART_EnableInt(void);
/******************************************************************************
 ** \brief UART_DisableInt
 **			关闭中断
 ** \param [in]none
 ** \return none
******************************************************************************/
void UART_DisableInt(void);

/******************************************************************************
 ** \brief UART_GetReceiveIntFlag
 **			获取接收中断标志位
 ** \param [in] none
 ** \return 0：无中断，1：有中断
******************************************************************************/
uint8_t  UART_GetReceiveIntFlag(void);

/******************************************************************************
 ** \brief UART_ClearReceiveIntFlag
 **			清除接收中断标志位
 ** \param [in] none
 ** \return 
******************************************************************************/
void UART_ClearReceiveIntFlag(void);

/******************************************************************************
 ** \brief UART_GetSendIntFlag
 **			获取发送中断标志位
 ** \param [in]none
 ** \return 0：无中断，1：有中断
******************************************************************************/
uint8_t  UART_GetSendIntFlag(void);

/******************************************************************************
 ** \brief UART_ClearSendIntFlag
 **			清除发送中断标志位
 ** \param [in]none
 ** \return 
******************************************************************************/
void UART_ClearSendIntFlag(void);

/******************************************************************************
 ** \brief UART_GetBuff
 **			获取接收Buff的值
 ** \param [in]none
 ** \return 
******************************************************************************/
uint8_t UART_GetBuff(void);

/******************************************************************************
 ** \brief UART_SendBuff
 **			发送数据到发送Buff
 ** \param [in] UARTSendValue : 发送的8位值
 ** \return 
******************************************************************************/
void UART_SendBuff( uint8_t UARTSendValue);

/******************************************************************************
 ** \brief UART_SendNinthBit
 **			发送数据的第九位
 ** \param [in] UARTSendValue : 发送的第九位值 0 /1
 ** \return 
******************************************************************************/
void UART_SendNinthBit( uint8_t UARTSendValue);
/******************************************************************************
 ** \brief UART_GetNinthBit
 **			获取数据的第九位
 ** \param [in]none
 ** \return 0/1
******************************************************************************/
uint8_t UART_GetNinthBit(void);

/******************************************************************************
 ** \brief UART_EnableBRT
 **		   使能BRT时钟模块
 ** \param [in]none
 ** \return none
******************************************************************************/
void UART_EnableBRT(void);
/******************************************************************************
 ** \brief UART_ConfigBRTClk
 **		   配置BRT模块时钟
 ** \param [in]BRTClkDiv : BRT_CLK_DIV_1 ~ BRT_CLK_DIV_128
 ** \return none
******************************************************************************/
void UART_ConfigBRTClk(uint8_t BRTClkDiv);
/******************************************************************************
 ** \brief UART_ConfigBRTPeriod
 **		   配置BRT模块时钟周期
 ** \param [in]BRTPeriod: 16bit
 ** \return none
******************************************************************************/
void UART_ConfigBRTPeriod( uint16_t BRTPeriod);

/******************************************************************************
 ** \brief UART_DisableBRT
 **		   关闭BRT时钟模块
 ** \param [in]none
 ** \return none
******************************************************************************/
void UART_DisableBRT(void);


#endif /* __UART_H__ */






