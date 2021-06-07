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
/** \file acmp.c
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "acmp.h"

/****************************************************************************/
/*	Local pre-processor symbols/macros('#define')
*****************************************************************************/

/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
*****************************************************************************/

/****************************************************************************/
/*	Local type definitions('typedef')
*****************************************************************************/

/****************************************************************************/
/*	Local variable  definitions('static')
*****************************************************************************/

/****************************************************************************/
/*	Local function prototypes('static')
*****************************************************************************/

/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
*****************************************************************************/
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
void ACMP_ConfigPositive( uint8_t ACMPn, uint8_t PositiveSource)
{
	if(ACMP0 == ACMPn)
	{
		C0CON0 &= ~(ACMP_C0CON0_C0PS_Msk);
		C0CON0 |= PositiveSource;
	}
	if(ACMP1 == ACMPn)
	{
		C1CON0 &= ~(ACMP_C1CON0_C1PS_Msk);
		C1CON0 |= PositiveSource;				
	}
}

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
void ACMP_ConfigNegative( uint8_t ACMPn, uint8_t NegativeSource, uint8_t Vref_k)
{
	if(ACMP0 == ACMPn)
	{
		C0CON0 &= ~( ACMP_C0CON0_C0NS_Msk);
		if((ACMP_NEGSEL_BG == NegativeSource) || (ACMP_NEGSEL_VREF_BG == NegativeSource) || (ACMP_NEGSEL_VREF_VDD == NegativeSource))
		{
			C0CON0 |= (1<< ACMP_C0CON0_C0NS_Pos);
		}
	}
	if(ACMP1 == ACMPn)
	{
		C1CON0 &= ~(ACMP_C1CON0_C1NS_Msk);
		if((ACMP_NEGSEL_BG == NegativeSource) || (ACMP_NEGSEL_VREF_BG == NegativeSource) || (ACMP_NEGSEL_VREF_VDD == NegativeSource))
		{
			C1CON0 |= (1<< ACMP_C1CON0_C1NS_Pos);
		}	
	}
	
	if((ACMP_NEGSEL_BG == NegativeSource))
	{
		CNVRCON &= ~(ACMP_CNVRCON_CNSVR_Msk);
	}	
	
	if((ACMP_NEGSEL_VREF_BG == NegativeSource))
	{
		CNVRCON =0x00;
		CNVRCON |= ACMP_CNVRCON_CNDIVS_Msk | ACMP_CNVRCON_CNSVR_Msk | Vref_k;		
	}
	
	if((ACMP_NEGSEL_VREF_VDD == NegativeSource))
	{
		CNVRCON =0x00;
		CNVRCON |= ACMP_CNVRCON_CNSVR_Msk | Vref_k;	
	}
}

/*****************************************************************************
 ** \brief	 ACMP_EnableReverseOutput
 **			 开启反相输出
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
*****************************************************************************/
void  ACMP_EnableReverseOutput( uint8_t ACMPn)
{
	if(ACMP0 == ACMPn)
	{
		C0CON2 |= (ACMP_C0CON2_C0POS_Msk);
	}
	if(ACMP1 == ACMPn)
	{
		C1CON2 |= (ACMP_C1CON2_C1POS_Msk);
	}
}
/*****************************************************************************
 ** \brief	 ACMP_DisableReverseOutput
 **			 关闭反向输出
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
******************************************************************************/
void  ACMP_DisableReverseOutput( uint8_t ACMPn)
{
	if(ACMP0 == ACMPn)
	{
		C0CON2 &= ~(ACMP_C0CON2_C0POS_Msk);
	}
	if(ACMP1 == ACMPn)
	{
		C1CON2 &= ~(ACMP_C1CON2_C1POS_Msk);
	}
}

/*****************************************************************************
 ** \brief	 ACMP_EnableFilter
 **			 开启滤波
 ** \param [in] ACMPn: ACMP0、ACMP1
 **				FilterTime: (1)ACMP_NFCLK_1_TSYS ....
 ** \return  none
 ** \note   
*****************************************************************************/
void  ACMP_EnableFilter( uint8_t ACMPn, uint8_t FilterTime)
{
	if(ACMP0 == ACMPn)
	{
		C0CON2 &= ~(ACMP_C0CON2_C0FS_Msk );
		C0CON2 |= (ACMP_C0CON2_C0FE_Msk) | FilterTime;
	}
	if(ACMP1 == ACMPn)
	{
		C1CON2 &= ~(ACMP_C1CON2_C1FS_Msk );
		C1CON2 |= (ACMP_C1CON2_C1FE_Msk) | FilterTime;
	}
}
/*****************************************************************************
 ** \brief	 ACMP_DisableFilter
 **			 关闭滤波
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
******************************************************************************/
void  ACMP_DisableFilter( uint8_t ACMPn)
{
	if(ACMP0 == ACMPn)
	{
		C0CON2 &= ~(ACMP_C0CON2_C0FE_Msk);
	}
	if(ACMP1 == ACMPn)
	{
		C1CON2 &= ~(ACMP_C1CON2_C1FE_Msk);
	}
}

/*****************************************************************************
 ** \brief	 ACMP_EnableInt
 **			 开启ACMP中断
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
*****************************************************************************/
void ACMP_EnableInt( uint8_t ACMPn)
{
	CNIE |= (1<<ACMPn);
}
/*****************************************************************************
 ** \brief	 ACMP_DisableInt
 **			 关闭ACMP中断
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
******************************************************************************/
void ACMP_DisableInt( uint8_t ACMPn)
{
	CNIE &=  ~(1<< ACMPn);
}
/******************************************************************************
 ** \brief	 ACMP_GetIntFlag
 **			 获取ACMP中断标志
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  0: 无比较器中断产生 ， 非0：产生中断
 ** \note   
******************************************************************************/
uint8_t ACMP_GetIntFlag( uint8_t ACMPn)
{
	return(CNIF & (1<< ACMPn));
}
/*****************************************************************************
 ** \brief	 ACMP_ClearIntFlag
 **			清ACMP中断
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
*****************************************************************************/
void ACMP_ClearIntFlag( uint8_t ACMPn)
{
	CNIF = 0xff & (~(1<< ACMPn));
}

/*****************************************************************************
 ** \brief	 ACMP_Start
 **			 开启ACMP
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
*****************************************************************************/
void ACMP_Start( uint8_t ACMPn)
{
	if(ACMP0 == ACMPn)
	{
		C0CON0 |= (ACMP_C0CON0_C0EN_Msk);
	}
	if(ACMP1 == ACMPn)
	{
		C1CON0 |= (ACMP_C1CON0_C1EN_Msk);
	}
}

/*****************************************************************************
 ** \brief	 ACMP_Stop
 **			 关闭ACMP
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
*****************************************************************************/
void ACMP_Stop( uint8_t ACMPn)
{
	if(ACMP0 == ACMPn)
	{
		C0CON0 &= ~(ACMP_C0CON0_C0EN_Msk);
	}
	if(ACMP1 == ACMPn)
	{
		C1CON0 &= ~(ACMP_C1CON0_C1EN_Msk);
	}
}

/*****************************************************************************
 ** \brief	 ACMP_GetResult
 **			 获取比较器值
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  0/1
 ** \note   
*****************************************************************************/
uint8_t ACMP_GetResult( uint8_t ACMPn)
{
	if(ACMP0 == ACMPn)
	{
		return ((C0CON1 & ACMP_C0CON1_C0OUT_Msk)? 1:0);
	}
    if(ACMP1 == ACMPn)
	{
		return ((C1CON1 & ACMP_C1CON1_C1OUT_Msk)? 1:0);
	}
	return 0;
}

/*****************************************************************************
 ** \brief	 ACMP_EnableHYS
 **			 配置比较器迟滞模式
 ** \param [in] ACMPn: ACMP0、ACMP1
 **				HYSSelect	:(1)ACMP_HYS_SEL_P	: 正迟滞
 **							 (2)ACMP_HYS_SEL_N	: 负迟滞
**							 (3)ACMP_HYS_SEL_BOUTH :正负迟滞
 **				HYSValue 	:(1)ACMP_HYS_10	：10mV
 **							 (2)ACMP_HYS_20	：20mV
 **							 (3)ACMP_HYS_60	：60mV
 ** \return  none
 ** \note   
*****************************************************************************/
void ACMP_EnableHYS( uint8_t ACMPn ,uint8_t HYSSelect, uint8_t HYSValue)
{
	if(ACMP0 == ACMPn)
	{
		C0HYS &= ~(ACMP_C0HYS_PNS_Msk | ACMP_C0HYS_S_Msk);
		C0HYS |= ((HYSSelect<<ACMP_C0HYS_PNS_Pos) | HYSValue);
	}
	if(ACMP1 == ACMPn)
	{
		C1HYS &= ~(ACMP_C1HYS_PNS_Msk | ACMP_C1HYS_S_Msk);
		C1HYS |= ((HYSSelect<<ACMP_C1HYS_PNS_Pos) | HYSValue);	
	}	
}

/*****************************************************************************
 ** \brief	 ACMP_DisableHYS
 **			 关闭比较器迟滞模式
 ** \param [in] ACMPn: ACMP0、ACMP1
 ** \return  none
 ** \note   
*****************************************************************************/
void ACMP_DisableHYS( uint8_t ACMPn)
{
	if(ACMP0 == ACMPn)
	{
		C0HYS &= ~(ACMP_C0HYS_S_Msk | ACMP_C0HYS_S_Msk);
	}
	if(ACMP1 == ACMPn)
	{
		C1HYS &= ~(ACMP_C1HYS_S_Msk | ACMP_C1HYS_S_Msk);
	}
}

/*****************************************************************************
 ** \brief	 ACMP_ConfigOffsetAdj
 **			 配置ACMP失调电压调节方式
 ** \param [in] ACMPn : ACMP0、ACMP1		
 **				OffsetAdjMode:	(1)ACMP_OFFSET_CONFIG
 **								(2)ACMP_OFFSET_ACMPDJ
 **				AdjVlue : 失调电压调节值：0x00~0x1f
 ** \return  none
 ** \note   
*****************************************************************************/
void ACMP_ConfigOffsetAdj(uint8_t ACMPn,uint8_t OffsetAdjMode, uint8_t AdjVlue)
{
	if(ACMP0 == ACMPn)
	{
		if( ACMP_OFFSET_ACMPDJ== OffsetAdjMode)
		{
			C0CON1 &= ~(ACMP_C0CON1_C0ADJ_Msk);
			C0CON1 |= AdjVlue;
		 	C0ADJE = ACMP_OFFSET_ACMPDJ;
		}
	}
	if(ACMP1 == ACMPn)
	{
		if( ACMP_OFFSET_ACMPDJ== OffsetAdjMode)
		{
			C1CON1 &= ~(ACMP_C1CON1_C1ADJ_Msk);
			C1CON1 |= AdjVlue;
		 	C1ADJE = ACMP_OFFSET_ACMPDJ;
		}
	}	
}

/*****************************************************************************
 ** \brief	 ACMP_Dealy
 **			 延时函数
 ** \param [in]none
 ** \return  none
 ** \note   
*****************************************************************************/
static void ACMP_Dealy(void)
{
	volatile uint8_t i;
	for(i=0;i<50;i++)
		_nop_();
}
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
uint8_t  ACMP_GetOffsetAdjValue(uint8_t ACMPn, uint8_t ACMPMode, uint8_t InputPort)
{
	uint8_t temp, AcmpOut,Adjvalue, ACMPCON1Temp;
	Adjvalue =0;	
	if(ACMP0 == ACMPn)
	{
		/*(1)关闭ACMP模块*/
		ACMP_Stop(ACMP0);
		/*(2)设置ACMP模块修调模式*/		
		if(ACMP_ADJ_POS_IN == ACMPMode)//正端与负端连接, 接到P端
		{
			C0CON1 |= (ACMP_C0CON1_C0CRS_Msk);
			C0CON0 &= ~(ACMP_C0CON0_C0PS_Msk);
			P11CFG = 0x01;			
		}
		if(ACMP_ADJ_GND == ACMPMode)//正端与负端连接, 接到GND
		{
			C0CON1 &= ~(ACMP_C0CON1_C0CRS_Msk);
			C0CON1 |= (0x1<<ACMP_C0CON1_C0CRS_Pos);			
			C0CON0 |= ACMP_C0CON0_C0N2G_Msk;
		}
		if(ACMP_ADJ_NAG_IN == ACMPMode)//正端与负端连接, 接到N端
		{
			C0CON1 &= ~(ACMP_C0CON1_C0CRS_Msk);
			C0CON0 &= ~(ACMP_C0CON0_C0N2G_Msk | ACMP_C0CON0_C0NS_Msk);
			if(ACMP_NEGSEL_CN == InputPort)
			{
				P12CFG = 0x01;					
			}		
		}
		
		/*(3)开启ACMP修调模式*/	
		C0CON0 |= ACMP_C0CON0_C0COFM_Msk;
		C0ADJE = 0xAA;     //使用C0ADJE中的数据
		C0CON1 &= ~(ACMP_C0CON1_C0ADJ_Msk);
		
		/*(4)开启ACMP*/
		ACMP_Start(ACMP0);
		ACMP_Dealy();
		/*(5)查询修调值*/
		ACMPCON1Temp = C0CON1;
		AcmpOut = ACMP_GetResult(ACMP0);
		for(temp=0; temp<0x20;temp++)
		{
			ACMPCON1Temp &= ~(ACMP_C0CON1_C0ADJ_Msk);
			ACMPCON1Temp |= temp;
			C0CON1 = ACMPCON1Temp;
			ACMP_Dealy();
			if(AcmpOut!= ACMP_GetResult(ACMP0))
			{
				Adjvalue = temp;
				break; 
			}
		}
		/*(6)关闭ACMP*/
		C0CON0 = 0x00;
		C0CON1 = 0x00;
		return 	Adjvalue;	
	}	

	if(ACMP1 == ACMPn)
	{
		/*(1)关闭ACMP模块*/
		ACMP_Stop(ACMP1);
		/*(2)设置ACMP模块修调模式*/		
		if(ACMP_ADJ_POS_IN == ACMPMode)//正端与负端连接, 接到P端
		{
			C1CON1 |= (ACMP_C1CON1_C1CRS_Msk);
			C1CON0 &= ~(ACMP_C1CON0_C1PS_Msk);
			switch(InputPort)			//选择正端端口
			{
				case ACMP_POSSEL_P0:
					P21CFG = 0x01;
					C1CON0 |= 0x00;
					break;
				case ACMP_POSSEL_P1:
					P23CFG = 0x01;
					C1CON0 |= 0x01;
					break;
				case ACMP_POSSEL_P2:
					P00CFG = 0x01;
					C1CON0 |= 0x02;
					break;					
				case ACMP_POSSEL_P3:
					P06CFG = 0x01;
					C1CON0 |= 0x03;
					break;
				default:
					break;
			}
		}
		if(ACMP_ADJ_GND == ACMPMode)//正端与负端连接, 接到GND
		{
			C1CON1 &= ~(ACMP_C1CON1_C1CRS_Msk);
			C1CON1 |= (0x1<<ACMP_C1CON1_C1CRS_Pos);				
			C1CON0 |= ACMP_C1CON0_C1N2G_Msk;
		}
		if(ACMP_ADJ_NAG_IN == ACMPMode)//正端与负端连接, 接到N端
		{
			C1CON1 &= ~(ACMP_C1CON1_C1CRS_Msk);
			C1CON0 &= ~(ACMP_C1CON0_C1N2G_Msk | ACMP_C1CON0_C1NS_Msk);
			if(ACMP_NEGSEL_CN == InputPort)
			{
				P22CFG = 0x01;					
			}		
		}
		
		/*(3)开启ACMP修调模式*/	
		C1CON0 |= ACMP_C1CON0_C1COFM_Msk;
		C1ADJE = 0xAA;     //使用C1ADJE中的数据
		C1CON1 &= ~(ACMP_C1CON1_C1ADJ_Msk);
		
		/*(4)开启ACMP*/
		ACMP_Start(ACMP1);
		ACMP_Dealy();
		/*(5)查询修调值*/
		ACMPCON1Temp = C1CON1;
		AcmpOut = ACMP_GetResult(ACMP1);
		for(temp=0; temp<0x20;temp++)
		{		
			ACMPCON1Temp &= ~(ACMP_C0CON1_C0ADJ_Msk);			
			ACMPCON1Temp |= temp;
			C1CON1 = ACMPCON1Temp;
			ACMP_Dealy();
			if(AcmpOut!= ACMP_GetResult(ACMP1))
			{
				Adjvalue = temp;
				break; 
			}
		}
		/*(6)关闭ACMP*/
		C1CON0 = 0x00;
		C1CON1 = 0x00;
		return 	Adjvalue;	
	}	
	return 0;
}



