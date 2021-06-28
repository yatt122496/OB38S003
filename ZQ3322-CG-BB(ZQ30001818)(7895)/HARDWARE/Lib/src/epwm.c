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
 **			 ����EPWM������ģʽ
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
 ** \note    ����9����ʽ����ϳɲ�ͬ������ģʽ���ҹ���һ��8λ�Ĵ���
 ******************************************************************************/
void EPWM_ConfigRunMode( uint8_t EpwmRunModeMask)
{
	PWMCON = EpwmRunModeMask; 			/*ע��ֱ�Ӹ�ֵ*/
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
 **	(1)PWM01PSC��ͬ����PWM0��PWM1ͨ�� �����Դ˺���ͳһ����PWMxxPSC=0x01
 **	����Ҫ�����ķ�Ƶ��������ԼĴ�����ֵ
 **	(2)EPWM ��Ƶ��Ϊ������PWMxPSC PWMnDIV 
 **	��һ����Ƶ(PWMxPSC)��0x00 Ԥ��Ƶֹͣ���Ҽ�����ֹͣ; ����ֵ��ϵͳʱ�ӷ�Ƶϵ��PWMxPSC+1
 **	�ڶ�����Ƶ��PWMnDIV): 0x00 FEPWMPSC/2; 0x01 FEPWMPSC/4��0x02:FEPWMPSC/8��0x3 FEPWMPSC/16
 **	0x04 FEPWMPSC ; ���� Fsys 
 ** ��Ƶ������1~4096����Fsys=8M��EPWM��Ƶ�ʷ�Χ��1.95k ~ 8M	
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
 **			 ����EPWMͨ����Ƶ���Լ�ռ�ձ�
 ** \param [in] ChannelNum : EPWM0,EPWM1,EPWM2,EPWM3
 **				Period: 16λ����ֵ
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
 **			 ����EPWMͨ���Գ�ģʽռ�ձ�
 ** \param [in] ChannelNum  :EPWM0,EPWM1,EPWM2,EPWM3
 **				Duty: 16λռ�ձ�
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
 **			 ����EPWMͨ���ǶԳ�ģʽռ�ձ�
 ** \param [in] ChannelNum  :EPWM0,EPWM1,EPWM2,EPWM3
 **				DownCmp: 16 bit ���±Ƚ�ֵ
 ** \return none
 ** \note    ֻ���������Ķ������(���¼���)ģʽ
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
 **			 ����One-Shotģʽ
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
 **			 �����Զ�����ģʽ
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
 **			ʹ��PWMnͬ������
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
	PWMCNTE |= ChannelMask;		/*ʹ��PWMn������*/
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
	PWMCNTE &= ~ ChannelMask;		/*ֹͣ����*/
}


/*****************************************************************************
 ** \brief	 EPWM_EnableOutput
 **			 ����EPWM���
 ** \param [in]  ChannelMask   EPWM_CH_0_MSK ~ EPWM_CH_3_MSK   
 ** \return  none
 ** \note   
*****************************************************************************/
void EPWM_EnableOutput( uint8_t ChannelMask)
{
	PWMOE |= ChannelMask;		/*ʹ��PWM���*/	
}
/*****************************************************************************
 ** \brief	 EPWM_DisableOutput
 **			 �ر�EPWM���
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
 **			 ����EPWMɲ��ģʽ
 ** \param [in] BrakeMode: (1)EPWM_BRK_STOP		ֹͣģʽ
 **						   (2)EPWM_BRK_SUSPEND	��ͣģʽ
 **						   (3)EPWM_BRK_RECOVER	�ָ�ģʽ
 **						   (4)EPWM_BRK_DELAY_RECOVER	��ʱ�ָ�ģʽ
 **			 	Relaod:	   (1)EPWM_BRK_LOAD_EPWM0		EPWM0�ļ��ص�ָ�
 **						   (2)EPWM_BRK_LOAD_EPWM1		EPWM1�ļ��ص�ָ�
 **						   (3)EPWM_BRK_LOAD_EPWM2		EPWM2�ļ��ص�ָ�
 **						   (4)EPWM_BRK_LOAD_EPWM3		EPWM3�ļ��ص�ָ�
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
 **			 ����ɲ���ָ���ʱģʽ����ʱ
 ** \param [in] time : 0~0x3ff
 ** \return  none
 ** \note  ɲ���ָ���ʱʱ�� = time * Tsys(ϵͳʱ��)  
*****************************************************************************/
void EPWM_ConfigBrakeRecoverDelay( uint16_t time)
{
	PWMBRKRDTH = 0x3 & (time>>8);
	PWMBRKRDTL = 0xff & time;
}

/*****************************************************************************
 ** \brief	 EPWM_EnableFaultBrake
 **			 ʹ��EPWMɲ��ģʽ
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
 **			 �ر�EPWMɲ��
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
 **			 ����EPWMͨ��ɲ����ƽ
 ** \param [in]  ChannelMask�� EPWM_CH_0_MSK ~ EPWM_CH_3_MSK
 **		   		 BrakeLevel: FaultBreake���EPWMͨ����ƽ ��0/1(��/��)
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
 **			 ��������
 ** \param [in] Channel: EPWM0��EPWM1....EPWM3		
 **			DeadTime : ����ʱ��( 0~0xFF) = DeadTime * Tepwm
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
 **			 �ر�EPWM����
 ** \param [in] Channel: EPWM0��EPWM1....EPWM3	
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
 **			 ������ƿ���
 ** \param [in] ChannelMask:  EPWM_CH_0_MSK ~ EPWM_CH_3_MSK	 	
 ** 	    	MaskLevel: ��������� :0/1(��/��)
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
	
	PWMMASKE  |= ChannelMask;			/*ʹ�ܿ���λ*/	
}
/*****************************************************************************
 ** \brief	 EPWM_DisableMaskControl
 **			 ������ƹر�
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
 **			 �������ϱȽ��ж�
 ** \param [in]  ChannelMask�� EPWM_CH_0_MSK ~ EPWM_CH_3_MSK		
 ** \return  none
 ** \note   
*****************************************************************************/
void EPWM_EnableUpCmpInt( uint8_t ChannelMask)
{
	PWMUIE |= ChannelMask ;
}
/*****************************************************************************
 ** \brief	 EPWM_DisableUpCmptInt
 **			 �ر����ϱȽ��ж�
 ** \param [in]  ChannelMask ��EPWM_CH_0_MSK ~ EPWM_CH_3_MSK	
 ** \return  none
 ** \note   
*****************************************************************************/
void EPWM_DisableUpCmpInt( uint8_t ChannelMask)
{
	PWMUIE &= ~ChannelMask ;
}
/*****************************************************************************
 ** \brief	 EPWM_GetUpCmpIntFlag
 **			 ��ȡ���ϱȽ��жϱ�־λ
 ** \param [in] ChannelNum:EPWM0,EPWM1,EPWM2,EPWM3
 ** \return  0: ���жϲ���
 **          1�����жϲ���
 ** \note   
*****************************************************************************/
uint8_t EPWM_GetUpCmpIntFlag( uint8_t ChannelNum)
{
	return(PWMUIF & (1<<ChannelNum)? 1:0);

}
/*****************************************************************************
 ** \brief	 EPWM_ClearUpCmpIntFlag
 **			 ������ϱȽ��жϱ�־λ
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
 **			 �������±Ƚ��ж�
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
 **			 �ر����±Ƚ��ж�
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
 **			 ��ȡ���±Ƚ��жϱ�־λ
 ** \param [in] ChannelNum: EPWM0,EPWM1,EPWM2,EPWM3
 ** \return  0: ���жϲ���
 **          1�����жϲ���
 ** \note   
*****************************************************************************/
uint8_t EPWM_GetDownCmpIntFlag( uint8_t ChannelNum)
{
	return(PWMDIF & (1<<ChannelNum)? 1:0);
}
/*****************************************************************************
 ** \brief	 EPWM_ClearUpCmpIntFlag
 **			 ������±Ƚ��жϱ�־λ
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
 **			 ���������ж�
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
 **			 �ر������ж�
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
 **			 ��������жϱ�־λ 
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
 **			 ��ȡ�����жϱ�־λ 
 ** \param [in]  ChannelNum: EPWM0,EPWM1,EPWM2,EPWM3
 ** \return   0�����жϲ���
 **           1�����жϲ���
 ** \note   
*****************************************************************************/
uint8_t EPWM_GetPeriodIntFlag( uint8_t ChannelNum)
{
	return(PWMPIF & (1<<ChannelNum)? 1:0);
}

/*****************************************************************************
 ** \brief	 EPWM_EnableZeroInt
 **			 ��������ж�
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
 **			 �ر�����ж� 
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
 **			 �������жϱ�־λ
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
 **			 ��ȡ����жϱ�־λ 
 ** \param [in] ChannelNum: EPWM0,EPWM1,EPWM2,EPWM3
 ** \return   0�����жϲ���
 **           1�����жϲ���   
 ** \note   
 *****************************************************************************/
uint8_t EPWM_GetZeroIntFlag( uint8_t ChannelNum)
{
	return(PWMZIF & (1<<ChannelNum)? 1:0);
}

/*****************************************************************************
 ** \brief	 EPWM_EnableFaultBrakeInt
 **			 ��������ɲ���ж� 
 ** \param [in] none
 ** \return  none
 ** \note  
*****************************************************************************/
void EPWM_EnableFaultBrakeInt( void)
{
	PWMFBKC  |= EPWM_PWMFBKC_PWMFBIE_Msk;   /*����ɲ���ж�*/
}
/*****************************************************************************
 ** \brief	 EPWM_DisableFaultBrakeInt	
 **			 �رչ���ɲ���ж� 
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
 **			 ��ȡ����ɲ���жϱ�־λ
 ** \param [in] none
 ** \return  0: ���жϲ���
 **          1�����жϲ���
 ** \note  
*****************************************************************************/
uint8_t EPWM_GetFaultBrakeIntFlag(void)
{
	return((PWMFBKC & (EPWM_PWMFBKC_PWMFBF_Msk))? 1:0);
}
/*****************************************************************************
 ** \brief	 EPWM_ClearFaultBrakeIntFlag	
 ** 		 �������ɲ���жϱ�־λ 
 ** \param [in] none
 ** \return  none
 ** \note 
*****************************************************************************/
void EPWM_ClearFaultBrakeIntFlag( void)
{
	PWMFBKC  &= ~(EPWM_PWMFBKC_PWMFBF_Msk);   /*��ɲ����־λ*/
}

/*****************************************************************************
 ** \brief	 EPWM_EnableReverseOutput
 **			 �����������
 ** \param [in] ChannelMask : EPWM_CH_0_MSK ~ EPWM_CH_5_MSK	
 ** \return  none
 ** \note  ����ģʽ�� EPWM ��ʼ�ӳ�ֵ��ʼ����ʱ��PWM��������Ϊ�͵�ƽ, 
 **	��EPWM����ֵ�����ϡ����¼���ƥ��ʱ�������ת
*****************************************************************************/
void  EPWM_EnableReverseOutput( uint8_t ChannelMask)
{
	PWMPINV |=ChannelMask;
}
/*****************************************************************************
 ** \brief	 EPWM_DisableReverseOutput
 **			 �رշ������
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
 **			 �������ɲ��
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
 **			 �ر����ɲ��
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
 **			 ʹ���ⲿӲ������ɲ��
 ** \param [in] FBSource: (1)EPWM_BRK_FB0			
 **						  (2)EPWM_BRK_FB1
 **				FBBrakeMode: (1)EPWM_BRK_FB_LOW			�͵�ƽ����ɲ��
 **							 (2)EPWM_BRK_FB_HIGH		�ߵ�ƽ����ɲ��
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
 **			 �ر��ⲿӲ������ɲ��
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
 **			 ʹ��ACMP������ش���ɲ��
 ** \param [in] ACMPSource: (1)EPWM_BRK_ACMP0			
 **						    (2)EPWM_BRK_ACMP1
 **				BrakeMode:  (1)EPWM_BRK_ACMP_RISING			������ɲ��
 **							(2)EPWM_BRK_ACMP_FALLING		�½���ɲ��	
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
 **			 �ر�ACMP������ش���ɲ��
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
 **			 ʹ��ACMP�����ƽ����ɲ��
 ** \param [in] ACMPSource: (1)EPWM_BRK_ACMP0			
 **						    (2)EPWM_BRK_ACMP1
 **				BrakeMode:  (1)EPWM_BRK_ACMP_LOW		�͵�ƽ����ɲ��
 **							(2)EPWM_BRK_ACMP_HIGH		�ߵ�ƽ����ɲ��	
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
 **			 �ر�ACMP�����ƽ����ɲ��
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
 **			 ʹ��ADC�������ɲ��
 ** \param [in]none 
 ** \return  none
 ** \note	 ADC�Ƚ��� ADCMPOֵΪ1 ����EPWMɲ��
*****************************************************************************/
void EPWM_EnableADCBrake(void)
{
	ADCMPC |=   ADC_ADCMPC_ADFBEN_Msk;
}

/*****************************************************************************
 ** \brief	 EPWM_DisableADCBrake
 **			 �ر�ADC�������ɲ��
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
 **			 ��ȡ����ɲ��Դ״̬λ
 ** \param [in] none
 ** \return  0: ɲ���źų���
 **          1��ɲ���ź���Ч
 ** \note  
*****************************************************************************/
uint8_t EPWM_GetFaultBrakeStateFlag( void)
{
	return((PWMFBKC & (EPWM_PWMFBKC_BRKAF_Msk))? 1:0);
}

/*****************************************************************************
 ** \brief	 EPWM_GetFaultBrakeOutputStateFlag
 **			 ��ȡ����ɲ�����״̬λ
 ** \param [in] none
 ** \return  0: EPWM�������
 **          1��EPWM���ɲ����ƽ
 ** \note  
*****************************************************************************/
uint8_t EPWM_GetFaultBrakeOutputStateFlag( void)
{
	return((PWMBRKC & (EPWM_PWMBRKC_BRKOSF_Msk))? 1:0);
}

/*****************************************************************************
 ** \brief	 EPWM_ClearFaultBrake	
 ** 		 �������ɲ�����״̬λ
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
 **			 ʹ��EPWM���ж�
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
 **			 �ر�EPWM���ж�
 ** \param [in] none
 ** \return  none
 ** \note   
 ****************************************************************************/
void  EPWM_AllIntDisable(void)
{
	EIE2 &= ~(IRQ_EIE2_PWMIE_Msk);
}
