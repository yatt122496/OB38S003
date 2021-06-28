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
/** \file acmp.h
**
** 
**
** History:
** 
******************************************************************************/
#ifndef __ACMP_H__
#define __ACMP_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s78xx.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/
/*----------------------------------------------------------------------------
 **ACMP 通道
---------------------------------------------------------------------------*/
#define ACMP0 					(0x00)			/* ACMP channel 0 number */
#define ACMP1					(0x01)			/* ACMP channel 1 number */
/*----------------------------------------------------------------------------
 **ACMP 输出滤波时间
---------------------------------------------------------------------------*/
#define ACMP_NFCLK_1_TSYS		(0x00)		/*(0~1)*Tsys*/
#define ACMP_NFCLK_2_TSYS		(0x01)		/*(1~2)*Tsys*/
#define ACMP_NFCLK_3_TSYS		(0x02)		/*(2~3)*Tsys*/
#define ACMP_NGCLK_5_TSYS		(0x03)		/*(4~5)*Tsys*/
#define ACMP_NFCLK_9_TSYS		(0x04)		/*(8~9)*Tsys*/
#define ACMP_NFCLK_17_TSYS		(0x05)		/*(16~17)*Tsys*/
#define ACMP_NFCLK_33_TSYS		(0x06)		/*(32~33)*Tsys*/
#define ACMP_NGCLK_65_TSYS		(0x07)		/*(64~65)*Tsys*/
#define ACMP_NFCLK_129_TSYS		(0x08)		/*(128~129)*Tsys*/
#define ACMP_NFCLK_257_TSYS		(0x09)		/*(256~257)*Tsys*/
#define ACMP_NFCLK_513_TSYS		(0x0a)		/*(512~513)*Tsys*/
/*----------------------------------------------------------------------------
 **ACMP 正端通道
---------------------------------------------------------------------------*/
#define ACMP_POSSEL_P0			(0x00)		/*ACMP P0输入端口*/
#define ACMP_POSSEL_P1			(0x01)		/*ACMP P1输入端口*/
#define ACMP_POSSEL_P2			(0x02)		/*ACMP P2输入端口*/
#define ACMP_POSSEL_P3			(0x03)		/*ACMP P3输入端口*/

/*----------------------------------------------------------------------------
 **ACMP 负端通道
---------------------------------------------------------------------------*/
#define ACMP_NEGSEL_VREF_VDD	(0x03)		/*ACMP Vref 源选择VDD*/
#define ACMP_NEGSEL_VREF_BG		(0x02)		/*ACMP Vref 源选择BG 1.2V*/
#define ACMP_NEGSEL_BG			(0x01)		/*Bandgap:1.2V*/
#define ACMP_NEGSEL_CN			(0x00)		/*ACMP N输入端口*/

/*----------------------------------------------------------------------------
 **ACMP 正负迟滞
/*---------------------------------------------------------------------------*/
#define ACMP_HYS_SEL_P			(0x01)			/*正迟滞*/
#define ACMP_HYS_SEL_N			(0x02)			/*负迟滞*/
#define ACMP_HYS_SEL_BOUTH		(0x03)			/*正负迟滞*/
/*----------------------------------------------------------------------------
 **ACMP 迟滞配置
---------------------------------------------------------------------------*/
#define ACMP_HYS_10				(0x01)			/*10mV迟滞*/
#define ACMP_HYS_20				(0x02)			/*20mV迟滞*/
#define ACMP_HYS_60				(0x03)			/*60mV迟滞*/

/*----------------------------------------------------------------------------
 **ACMP 修调模式ACMP_ADJ_POS_IN
---------------------------------------------------------------------------*/
#define	ACMP_ADJ_POS_IN			(0x00)		//正端与负端连接, 接到P端
#define ACMP_ADJ_NAG_IN			(0x01)		//正端与负端连接, 接到N端
#define ACMP_ADJ_GND			(0x02)		//正端与负端连接，接到GND

#define ACMP_OFFSET_CONFIG		(0x00)		//使用内部Config中的调节值
#define ACMP_OFFSET_ACMPDJ		(0xAA)		//使用ACMPADJ中的调节值
											  
/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/
/*----------------------------------------------------------------------------
 **ACMP 负端基准电压系数K
---------------------------------------------------------------------------*/
typedef enum Vref_K{
	Vref_K_167_10000 =0x0, 				// K = 167/10000 = 1.67%
	Vref_K_333_10000 =0x1, 				// K = 334/10000 = 3.34%
	Vref_K_500_10000 =0x2, 				// K = 500/10000 = 5.00%
	Vref_K_667_10000 =0x3, 				// K = 667/10000 = 6.67%
	Vref_K_833_10000 =0x4,				// K = 833/10000 = 8.33%
	Vref_K_1000_10000 =0x5,    			// K = 1000/10000 = 10.00%
	Vref_K_1167_10000 =0x6, 			// K = 1167/10000 = 11.67%
	Vref_K_1333_10000 =0x7, 			// K = 1333/10000 = 13.33%
	Vref_K_1500_10000 =0x8, 			// K = 1500/10000 = 15.00%
	Vref_K_1667_10000 =0x9,				// K = 1667/10000 = 16.67%
	Vref_K_1833_10000 =0xa,  			// K = 1833/10000 = 18.33%	
	Vref_K_2000_10000 =0xb, 			// K = 2000/10000 = 20.00%
	Vref_K_2167_10000 =0xc, 			// K = 2167/10000 = 21.67%
	Vref_K_2333_10000 =0xd, 			// K = 2333/10000 = 23.33%
	Vref_K_2500_10000 =0xe,				// K = 2500/10000 = 25.00%
	Vref_K_2667_10000 =0xf,				// K = 2667/10000 = 26.67%
	Vref_K_5000_10000 =0x10,			// K = 5000/10000 = 50%	
	Vref_K_7500_10000 =0x20,			// K = 7500/10000 = 75%
	Vref_K_10000_10000 =0x30,			// K = 10000/10000 = 100%
}Vref_K_T;

/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/


/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/
/******************************************************************************
 ** \brief	 ACMP_ConfigPositive
 **			 设置比较器正端输入
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** 			 PositiveSource:  (1)ACMP_POSSEL_P0		
 **								  (2)ACMP_POSSEL_P1		
 **								  (3)ACMP_POSSEL_P2		
 **								  (4)ACMP_POSSEL_P3			
 ** \return  none
 ** \note   
*****************************************************************************/
void ACMP_ConfigPositive( uint8_t ACMPn, uint8_t PositiveSource);

/*****************************************************************************
 ** \brief	 ACMP_ConfigNegative
 **			 设置比较器负端输入
 ** \param [in] ACMPn: ACMP0、ACMP1
 **				NegativeSource:  (1)ACMP_NEGSEL_CN		:CnN			
 **								 (2)ACMP_NEGSEL_VREF_BG	: ACMP Vref 源选择BG
 **								 (3)ACMP_NEGSEL_VREF_VDD：ACMP Vref 源选择VDD
 **								 (4)ACMP_NEGSEL_BG		: 内部1.2V BG	
 **				Vref_k: 基准电压系数K (1)Vref_K_167_10000......Vref_K_10000_10000  分压系数K	
 ** \return  none
 ** \note   
*****************************************************************************/
void ACMP_ConfigNegative( uint8_t ACMPn, uint8_t NegativeSource,uint8_t Vref_k);


/*****************************************************************************
 ** \brief	 ACMP_EnableReverseOutput
 **			 开启反相输出
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
*****************************************************************************/
void  ACMP_EnableReverseOutput( uint8_t ACMPn);
/*****************************************************************************
 ** \brief	 ACMP_DisableReverseOutput
 **			 关闭反向输出
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
******************************************************************************/
void  ACMP_DisableReverseOutput( uint8_t ACMPn);

/******************************************************************************
 ** \brief	 ACMP_EnableFilter
 **			 开启滤波
 ** \param [in] ACMPn: ACMP0、ACMP1
 **				FilterTime: (1)ACMP_NFCLK_1_TSYS ....
 ** \return  none
 ** \note   
******************************************************************************/
void  ACMP_EnableFilter( uint8_t ACMPn, uint8_t FilterTime);
/******************************************************************************
 ** \brief	 ACMP_DisableFilter
 **			 关闭滤波
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
*****************************************************************************/
void  ACMP_DisableFilter( uint8_t ACMPn);


/******************************************************************************
 ** \brief	 ACMP_EnableInt
 **			 开启ACMP中断
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
 *****************************************************************************/
void ACMP_EnableInt(uint8_t ACMPn);
/*****************************************************************************
 ** \brief	 ACMP_DisableInt
 **			 关闭ACMP中断
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
*****************************************************************************/
void ACMP_DisableInt( uint8_t ACMPn);
/*****************************************************************************
 ** \brief	 ACMP_GetIntFlag
 **			 获取ACMP中断标志
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  0: 无比较器中断产生 ， 1：产生中断
 ** \note   
******************************************************************************/
uint8_t ACMP_GetIntFlag( uint8_t ACMPn);
/*****************************************************************************
 ** \brief	 ACMP_ClearIntFlag
 **			 清ACMP中断
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
******************************************************************************/
void ACMP_ClearIntFlag( uint8_t ACMPn);

/*****************************************************************************
 ** \brief	 ACMP_Start
 **			 开启ACMP
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
******************************************************************************/
void ACMP_Start( uint8_t ACMPn);

/*****************************************************************************
 ** \brief	 ACMP_Stop
 **			 关闭ACMP
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
**********************************************************************�*******/
void ACMP_Stop( uint8_t ACMPn);

/*****************************************************************************
 ** \brief	 ACMP_GetResult
 **			 获取比较器值
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  0/1
 ** \note   
 *****************************************************************************/
uint8_t ACMP_GetResult( uint8_t ACMPn);

/*****************************************************************************
 ** \brief	 ACMP_EnableHYS
 **			 配置比较器迟滞模式
 ** \param [in] ACMPn: ACMP0、ACMP1
 **				HYSSelect	:(1)ACMP_HYS_SEL_P	: 正迟滞
 **							 (2)ACMP_HYS_SEL_N	: 负迟滞
 **							 (3)ACMP_HYS_SEL_BOUTH
 **				HYSValue 	:(1)ACMP_HYS_10	：10mV
 **							 (2)ACMP_HYS_20	：20mV
 **							 (3)ACMP_HYS_60	：60mV
 ** \return  none
 ** \note   
*****************************************************************************/
void ACMP_EnableHYS( uint8_t ACMPn ,uint8_t HYSSelect, uint8_t HYSValue);

/*****************************************************************************
 ** \brief	 ACMP_DisableHYS
 **			 关闭比较器迟滞模式
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
*****************************************************************************/
void ACMP_DisableHYS( uint8_t ACMPn);

/*****************************************************************************
 ** \brief	 ACMP_ConfigOffsetAdj
 **			 配置ACMP失调电压调节方式
 ** \param [in] ACMPn : ACMP0		
 **				OffsetAdjMode:	(1)ACMP_OFFSET_CONFIG
 **								(2)ACMP_OFFSET_ACMPDJ
 **				AdjVlue : 失调电压调节值：0x00~0x1f
 ** \return  none
 ** \note   
*****************************************************************************/
void ACMP_ConfigOffsetAdj(uint8_t ACMPn,uint8_t OffsetAdjMode, uint8_t AdjVlue);


/*****************************************************************************
 ** \brief	 ACMP_GetOffsetAdjValue
 **			 获取ACMP失调电压调节值
 ** \param [in] ACMPn : ACMP0
 **				ACMPMode:  (1)ACMP_ADJ_POS_IN		//正端与负端连接, 接到P端
 **						   (2)ACMP_ADJ_NAG_IN		//正端与负端连接, 接到N端
 **						   (3)ACMP_ADJ_GND			//正端与负端连接，接到GND
 **				InputPort: (1)ACMP_POSSEL_P0 .... ACMP_POSSEL_P3   //正端输入选择
 **						  （2）ACMP_NEGSEL_CN 		//负端的输入选择
 ** \return  5位失调电压修调值
 ** \note   
 *****************************************************************************/
uint8_t  ACMP_GetOffsetAdjValue(uint8_t ACMPn, uint8_t ACMPMode, uint8_t InputPort);



#endif /* __ACMP_H__ */







