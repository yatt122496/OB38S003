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
/** \file lcd.c
**
**  
**
**	History:
**
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "lcd.h"

/****************************************************************************/
/*	Local pre-processor symbols/macros('#define')
****************************************************************************/

/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
****************************************************************************/

/****************************************************************************/
/*	Local type definitions('typedef')
****************************************************************************/

/****************************************************************************/
/*	Local variable  definitions('static')
****************************************************************************/

/****************************************************************************/
/*	Local function prototypes('static')
****************************************************************************/

/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
****************************************************************************/

/*****************************************************************************
 ** \brief	 LCD_ConfigCurrent
 **			 配置LCD运行电流
 ** \param [in] Current: (1) LCD_CUR_SEL_8P3		LCD 电流选择8.3uA
 **						 (2) LCD_CUR_SEL_16P7		LCD 电流选择16.7uA
 **						 (3) LCD_CUR_SEL_50			LCD 电流选择50uA
 **						 (4) LCD_CUR_SEL_100 		LCD 电流选择100uA
 ** \return  none
 ** \note   
******************************************************************************/
void LCD_ConfigCurrent(uint8_t Current)
{
	LCDCON0 &= ~(LCD_LCDCON0_IESL_Msk);
	LCDCON0 |= Current;
}

/*****************************************************************************
 ** \brief	 LCD_Start
 **			 使能LCD
 ** \param [in] none
 ** \return  none
 ** \note   
******************************************************************************/
void LCD_Start(void)
{
	LCDCON0 |= LCD_LCDCON0_EN_Msk;
}
/*****************************************************************************
 ** \brief	 LCD_Stop
 **			 关闭LCD
 ** \param [in] none
 ** \return  none
 ** \note   
******************************************************************************/
void LCD_Stop(void)
{
	LCDCON0 &= ~(LCD_LCDCON0_EN_Msk);
}


/*****************************************************************************
 ** \brief	 LCD_SetFrame0
 **			 设置LCD Frame
 ** \param [in] none
 ** \return  none
 ** \note   
******************************************************************************/
void LCD_SetFrame0(void)
{
	LCDCON0 &= ~(LCD_LCDCON0_FRAME_Msk);
}

/*****************************************************************************
 ** \brief	 LCD_SetFrame1
 **			 设置LCD Frame
 ** \param [in] none
 ** \return  none
 ** \note   
******************************************************************************/
void LCD_SetFrame1(void)
{
	LCDCON0 |= LCD_LCDCON0_FRAME_Msk;
}


