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
/** \file adc.h
**
** 
**
** History:
** 
******************************************************************************/
#ifndef __ADC_H__
#define __ADC_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s78xx.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/
/*----------------------------------------------------------------------------
 **ADC ͨ�����
/*---------------------------------------------------------------------------*/
#define  ADC_CH_0		 	(0x00)				/* AN0 */
#define  ADC_CH_1			(0x01)				/* AN1 */
#define  ADC_CH_2		 	(0x02)				/* AN2 */
#define  ADC_CH_3			(0x03)				/* AN3 */
#define  ADC_CH_4		 	(0x04)				/* AN4 */
#define  ADC_CH_5			(0x05)				/* AN5 */
#define  ADC_CH_6		 	(0x06)				/* AN6 */
#define  ADC_CH_7			(0x07)				/* AN7 */
#define  ADC_CH_8		 	(0x08)				/* AN8 */
#define  ADC_CH_9			(0x09)				/* AN9 */
#define  ADC_CH_10			(0x0a)				/* AN10 */
#define  ADC_CH_11		 	(0x0b)				/* AN11 */
#define  ADC_CH_12			(0x0c)				/* AN12 */
#define  ADC_CH_13		 	(0x0d)				/* AN13 */
#define  ADC_CH_14			(0x0e)				/* AN14 */
#define  ADC_CH_15			(0x0f)				/* AN15 */
#define  ADC_CH_16			(0x10)				/* AN16 */
#define  ADC_CH_17			(0x11)				/* AN17 */
#define  ADC_CH_18			(0x12)				/* AN18 */
#define  ADC_CH_19			(0x13)				/* AN19 */
#define  ADC_CH_20			(0x14)				/* AN20 */
#define  ADC_CH_21			(0x15)				/* AN21 */
#define  ADC_CH_22			(0x16)				/* AN22 */
#define  ADC_CH_23			(0x17)				/* AN23 */
#define  ADC_CH_24			(0x18)				/* AN24 */
#define  ADC_CH_25			(0x19)				/* AN25 */
#define  ADC_CH_63			(0x3f)				/* AN63 */


#define  ADC_CH_63_BGR			(0x0)				/* AN63�ӹ̶��ο���ѹ1.2V*/
#define  ADC_CH_63_ACMP_VREF	(0x1)				/* AN63��ACMP���˲ο���ѹ*/
#define  ADC_CH_63_TS			(0x4)				/* AN63���¶ȴ�����*/
#define  ADC_CH_63_VSS			(0x5)				/* AN63�� VSS ADC�ο���*/
#define  ADC_CH_63_VDD			(0x7)				/* AN63�� VDD �ο���ѹ*/

/*----------------------------------------------------------------------------
 **ADC ����ʱ�ӷ�Ƶ
/*---------------------------------------------------------------------------*/
#define  ADC_CLK_DIV_2		(0x00)
#define  ADC_CLK_DIV_4		(0x01)
#define  ADC_CLK_DIV_8		(0x02)
#define  ADC_CLK_DIV_16		(0x03)
#define  ADC_CLK_DIV_32		(0x04)
#define  ADC_CLK_DIV_64		(0x05)
#define  ADC_CLK_DIV_128	(0x06)
#define  ADC_CLK_DIV_256	(0x07)
/*----------------------------------------------------------------------------
 **ADC ת�������ʽ
/*---------------------------------------------------------------------------*/
#define	 ADC_RESULT_LEFT	(0x00<< ADC_ADCON0_ADFM_Pos)			/*�����*/
#define  ADC_RESULT_RIGHT	(0x01<< ADC_ADCON0_ADFM_Pos)			/*�Ҷ���*/

/*----------------------------------------------------------------------------
 **ADC Ӳ������ģʽ
/*---------------------------------------------------------------------------*/
#define	ADC_TG_PWM0			(0x00)		//PWM0����ADCת��
#define	ADC_TG_PWM2			(0x01)		//PWM2����ADCת��
#define	ADC_TG_ADET			(0x03)		//ADET���Ŵ���ADCת��

#define	ADC_TG_FALLING		(0x00)		//�½��ش���
#define	ADC_TG_RISING		(0x01)		//�����ش���
#define	ADC_TG_PWM_PM		(0x02)		//PWM�����е㴥��	
#define	ADC_TG_PWM_PE		(0x03)		//PWM�����յ㴥��

/*----------------------------------------------------------------------------
 **ADC �Ƚ����
/*---------------------------------------------------------------------------*/
#define  ADC_ADRES_LESS_THAN_ADCMP		(0x01<< ADC_ADCMPC_ADCMPPS_Pos)		/*ADRES < ADCMP ; ADCMPO���1 */
#define  ADC_ADRES_MORE_THAN_ADCMP		(0x00<< ADC_ADCMPC_ADCMPPS_Pos)		/*ADRES >= ADCMP; ADCMPO���1*/

/*----------------------------------------------------------------------------
 **ADC �ο���ѹ
/*---------------------------------------------------------------------------*/
#define ADC_VREF_1P2V			(0x00)						/*Vref =1.2v*/
#define ADC_VREF_2V				(0x01<<ADC_ADCLDO_VSEL_Pos)	/*Vref =2.0v*/
#define ADC_VREF_2P4V			(0x02<<ADC_ADCLDO_VSEL_Pos)	/*Vref =2.4v*/
#define ADC_VREF_3V				(0x03<<ADC_ADCLDO_VSEL_Pos)	/*Vref =3v*/
/*****************************************************************************
 ** \brief	 ADC_IS_BUSY
 **			 �ж�ADC����״̬
 ** \param [in]	 none        
 ** \return   
*****************************************************************************/
#define  ADC_IS_BUSY				(ADCON0 & ADC_ADCON0_ADGO_Msk)
/*****************************************************************************
 ** \brief	 ADC_GO
 **			 ����ADCת��(�������)
 ** \param [in]	 none     
 ** \return  none
*****************************************************************************/
#define  ADC_GO() 				 do{\
									ADCON0 |= ADC_ADCON0_ADGO_Msk;\
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
 ** \brief	 ADC_Start
 **			 ADCģ�鿪��
 ** \param [in]	 none
 **          
 ** \return  none
*****************************************************************************/
void  ADC_Start(void);
/*****************************************************************************
 ** \brief	 ADC_Stop
 **			 ADCģ��ֹͣ
 ** \param [in] none
 **          
 ** \return  none
*****************************************************************************/
void  ADC_Stop(void);

/*****************************************************************************
 ** \brief	 ADC_ConfigRunMode
 **			  ����ADC������ģʽ
 ** \param [in] 
 **				ADCClkDiv: ADC_CLK_DIV_2 ~ ADC_CLK_DIV_256
 **          	ADCResultTpye: (1)ADC_RESULT_LEFT    �����
 **							   (2)ADC_RESULT_RIGHT   �Ҷ���
 ** \return  none
 ** \note 	 �����ģʽ: ADRESH������ݵĸ�8λ��ADRESL��4λ������ݵ�4λ
 **			 �Ҷ���ģʽ: ADRESH������ݵĸ�4λ��ADRESL������ݵ�8λ	
*****************************************************************************/
void  ADC_ConfigRunMode(uint8_t ADCClkDiv, uint8_t ADCResultTpye);

/*****************************************************************************
 ** \brief	 ADC_EnableHardwareTrig
 **			ʹ��Ӳ������ADC
 ** \param [in] none
 ** \return  none
 ** \note 	 
*****************************************************************************/
void  ADC_EnableHardwareTrig(void);

/*****************************************************************************
 ** \brief	 ADC_DisableHardwareTrigger
 **			�ر�Ӳ������ADC
 ** \param [in] none
 ** \return  none
 ** \note 	 
*****************************************************************************/
void  ADC_DisableHardwareTrig(void);

/*****************************************************************************
 ** \brief	 ADC_ConfigHardwareTrig
 **			 ����Ӳ������ģʽ
 ** \param [in] ADCTGSource: ADC_TG_PWM0��ADC_TG_PWM2��ADC_TG_ADET
 **				TGMode��(1)ADC_TG_FALLING
 **						(2)ADC_TG_RISING
 **						(3)ADC_TG_PWM_PM
 **						(4)ADC_TG_PWM_PE
 ** \return  none
 ** \note 	 
*****************************************************************************/
void  ADC_ConfigHardwareTrig(uint8_t ADCTGSource, uint8_t TGMode);
/*****************************************************************************
 ** \brief	 ADC_SetTrigDelayTime
 **			����Ӳ������ģʽ����ʱʱ��
 ** \param [in]  TrigTime: 0~1023
 ** \return  none
 ** \note 	(TrigTime + 4)) *Tsys
*****************************************************************************/
void  ADC_SetTrigDelayTime(uint16_t TrigTime);

/*****************************************************************************
 ** \brief	 ADC_EnableChannel
 **			 ʹ��ADCת��ͨ��
 ** \param [in]  ADCChannel: ADC_CH_0 ..... ADC_CH_63
 ** \return  none
 ** \note 	
*****************************************************************************/
void  ADC_EnableChannel(uint8_t ADCChannel);

/*****************************************************************************
 ** \brief	 ADC_ConfigAN63
 **			 ����AN63ͨ��
 ** \param [in]	An31Channel:��1��ADC_CH_63_BGR...ADC_CH_63_VDD
 ** \return  none
 ** \note 	
*****************************************************************************/
void  ADC_ConfigAN63(uint8_t An31Channel);

/*****************************************************************************
 ** \brief	 ADC_ConfigADCCMPOutput
 **			 ����ADC�Ƚ��������
 ** \param [in]  ADCCMPOut: (1)ADC_ADRES_LESS_THAN_ADCMP 	: ADRES < ADCMP ; ADCMPO���1
 **						    (2)ADC_ADRES_MORE_THAN_ADCMP 	: ADRES >= ADCMP; ADCMPO���1
 ** \return  none
 ** \note 
*****************************************************************************/
void  ADC_ConfigADCCMPOutput(uint8_t ADCCMPOut);

/*****************************************************************************
 ** \brief	 ADC_ConfigCompareValue
 **			 ����ADC�Ƚ�ֵ
 ** \param [in]  ADCCompareValue: ADCMPH,ADCMPL
 ** \return  none
 ** \note 
*****************************************************************************/
void ADC_ConfigCompareValue(uint16_t ADCCompareValue);
/*****************************************************************************
 ** \brief	 ADC_GetCmpResult
 **			 ��ȡADC�ȽϽ��
 ** \param [in]  none
 ** \return   0/1
 ** \note 
*****************************************************************************/
uint8_t  ADC_GetCmpResult(void);

/*****************************************************************************
 ** \brief	 ADC_GetADCResult
 **			 ��ȡADCת�����
 ** \param [in]  none
 ** \return  16bits ADCֵ
 ** \note 
*****************************************************************************/
uint16_t  ADC_GetADCResult(void);

/*****************************************************************************
 ** \brief	 ADC_EnableInt
 **			 ����ADCת������ж�
 ** \param [in]  none
 ** \return  none
 ** \note 
*****************************************************************************/
void ADC_EnableInt(void);
/*****************************************************************************
 ** \brief	 ADC_DisableInt
 **			 �ر�ADCת������ж�
 ** \param [in]  none
 ** \return  none
 ** \note 
*****************************************************************************/
void ADC_DisableInt(void);
/*****************************************************************************
 ** \brief	 ADC_GetIntFlag
 **			 ��ȡADCת������жϱ�־λ
 ** \param [in]  none
 ** \return  0�����жϣ�1�������ж�
 ** \note 
******************************************************************************/
uint8_t ADC_GetIntFlag(void);
/******************************************************************************
 ** \brief	 ADC_ClearIntFlag
 **			 ��ADCת������жϱ�־λ
 ** \param [in] none
 ** \return  none
 ** \note   
******************************************************************************/
void ADC_ClearIntFlag(void);

/*****************************************************************************
 ** \brief	 ADC_EnableLDO
 **			ʹ��ADC��LDO
 ** \param [in] none
 ** \return  none
 ** \note   
*****************************************************************************/
void ADC_EnableLDO(void);
/*****************************************************************************
 ** \brief	 ADC_DisableLDO
 **			�ر�ADC��LDO
 ** \param [in] none
 ** \return  none
 ** \note   
*****************************************************************************/
void ADC_DisableLDO(void);
/*****************************************************************************
 ** \brief	 ADC_ConfigADCVref
 **			 ����ADC��VREF
 ** \param [in] ADCVref :(1)ADC_VREF_1P2V :	Vref =1.2v
 **						 (2)ADC_VREF_2V	  : Vref =2v
 **						 (2)ADC_VREF_2P4V : Vref =2.4v
 **						 (2)ADC_VREF_3V	  : Vref =3v
 ** \return  none
 ** \note   
*****************************************************************************/
void ADC_ConfigADCVref(uint8_t ADCVref);

/*****************************************************************************
 ** \brief	 ADC_EnableLDOOutput
 **			ʹ��ADC��LDO�����P16��
 ** \param [in] none
 ** \return  none
 ** \note   
*****************************************************************************/
void ADC_EnableLDOOutput(void);
/*****************************************************************************
 ** \brief	 ADC_DisableLDOOutput
 **			�ر�ADC��LDO�����P16��
 ** \param [in] none
 ** \return  none
 ** \note   
*****************************************************************************/
void ADC_DisableLDOOutput(void);


#endif /* __ADC_H__ */






