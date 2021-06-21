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
/** \file lcd.h
**
** 
**
** History:
** 
*****************************************************************************/
#ifndef __LCD_H__
#define __LCD_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s78xx.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/
/*----------------------------------------------------------------------------
 **LCDģʽ
 ---------------------------------------------------------------------------*/
#define 	LCD_FRAME_0			(0)			/*LCD Frame 0*/
#define		LCD_FRAME_1			(LCD_LCDCON0_FRAME_Msk)		/*LCD Frame 1*/

/*----------------------------------------------------------------------------
 **LCD����ѡ��
 ---------------------------------------------------------------------------*/
#define 	LCD_CUR_SEL_8P3			(0x00)		/*LCD ����ѡ��8.3uA*/		
#define 	LCD_CUR_SEL_16P7		(0x01)		/*LCD ����ѡ��16.7uA*/
#define 	LCD_CUR_SEL_50			(0x02)		/*LCD ����ѡ��50uA*/		
#define 	LCD_CUR_SEL_100			(0x03)		/*LCD ����ѡ��100uA*/



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
 ** \brief	 LCD_ConfigCurrent
 **			 ����LCD���е���
 ** \param [in] Current: (1) LCD_CUR_SEL_8P3		LCD ����ѡ��8.3uA
 **						 (2) LCD_CUR_SEL_16P7		LCD ����ѡ��16.7uA
 **						 (3) LCD_CUR_SEL_50			LCD ����ѡ��50uA
 **						 (4) LCD_CUR_SEL_100 		LCD ����ѡ��100uA
 ** \return  none
 ** \note   
******************************************************************************/
void LCD_ConfigCurrent(uint8_t Current);

/*****************************************************************************
 ** \brief	 LCD_Start
 **			 ʹ��LCD
 ** \param [in] none
 ** \return  none
 ** \note   
******************************************************************************/
void LCD_Start(void);
/*****************************************************************************
 ** \brief	 LCD_Stop
 **			 �ر�LCD
 ** \param [in] none
 ** \return  none
 ** \note   
******************************************************************************/
void LCD_Stop(void);


/*****************************************************************************
 ** \brief	 LCD_SetFrame0
 **			 ����LCD Frame
 ** \param [in] none
 ** \return  none
 ** \note   
******************************************************************************/
void LCD_SetFrame0(void);

/*****************************************************************************
 ** \brief	 LCD_SetFrame1
 **			 ����LCD Frame
 ** \param [in] none
 ** \return  none
 ** \note   
******************************************************************************/
void LCD_SetFrame1(void);


#endif /* __LCD_H__ */


