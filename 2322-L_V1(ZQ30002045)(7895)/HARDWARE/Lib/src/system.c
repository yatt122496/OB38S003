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
/** \file system.c
**
**  
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "system.h"

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
 ** \brief	 SYS_ConfigSystemClk
 **			 ??????????????????
 ** \param [in] SystemClkMode : (1)SYS_CLK_LSI:	??????????????????
 **								(2)SYS_CLK_LSE: ??????????????????
 **								(3)SYS_CLK_HSE: ??????????????????
 **								(4)SYS_CLK_HSI: ??????????????????
 ** \return  0:????????????  1???????????????
 ** \note	 
*****************************************************************************/
uint8_t SYS_ConfigSystemClk(uint8_t SystemClkMode)
{
	uint16_t WaitTime = 60000;
	uint8_t temp;
	temp = (SYS_SCKSEL_SEL_Msk | SystemClkMode);
	TA = 0xAA;
	TA = 0x55;
	SCKSEL = temp;	
	temp = temp | SYS_SCKSEL_WRITE_Msk;
	do{		
		if(SCKSTAU & (1<< SystemClkMode))
		{
			TA = 0xAA;
			TA = 0x55;
			SCKSEL = temp;		
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			return 1;
		}
	}
	while(WaitTime--);
	return 0;
}


/*****************************************************************************
 ** \brief	 SYS_EnableLVD
 **			 ????????????????????????
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_EnableLVD(void)
{
	LVDCON |= LVD_LVDCON_LVDEN_Msk;
}
/*****************************************************************************
 ** \brief	 SYS_DisableLVD
 **			  ????????????????????????
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_DisableLVD(void)
{
	LVDCON &= ~(LVD_LVDCON_LVDEN_Msk);	
}
/*****************************************************************************
 ** \brief	 SYS_ConfigLVD
 **			 ??????????????????????????????
 ** \param [in] LVDValue :(1)SYS_LVD_2_0V		LVD???????????????2.0V					
						(2)	SYS_LVD_2_16V		LVD???????????????2.16V
						(3)	SYS_LVD_2_31V		LVD???????????????2.31V
						(4)	SYS_LVD_2_45V		LVD???????????????2.45V
						(5)	SYS_LVD_2_60V		LVD???????????????2.60V
						(6)	SYS_LVD_2_73V		LVD???????????????2.73V
						(7)	SYS_LVD_2_88V		LVD???????????????2.88V
						(8)	SYS_LVD_2_98V		LVD???????????????2.98V
						(9)	SYS_LVD_3_21V		LVD???????????????3.21V
						(10)SYS_LVD_3_42V		LVD???????????????3.42V
						(11)SYS_LVD_3_62V		LVD???????????????3.62V
						(12)SYS_LVD_3_81V		LVD???????????????3.81V
						(13)SYS_LVD_4_0V		LVD???????????????4.0V
						(14)SYS_LVD_4_2V		LVD???????????????4.2V
						(15)SYS_LVD_4_43V		LVD???????????????4.43V
						(16)SYS_LVD_4_6V		LVD???????????????4.6V
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_ConfigLVD(uint8_t LVDValue)
{
	LVDCON &= ~(LVD_LVDCON_LVDSEL_Msk);
	LVDCON |= LVDValue;	
}

/*****************************************************************************
 ** \brief	 SYS_EnableLVDInt
 **			 ??????????????????????????????
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_EnableLVDInt(void)
{
	LVDCON |= LVD_LVDCON_LVDINTE_Msk;	
}
/*****************************************************************************
 ** \brief	 SYS_DisableLVDInt
 **			  ??????????????????????????????
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_DisableLVDInt(void)
{
	LVDCON &= ~(LVD_LVDCON_LVDINTE_Msk);	
}

/*****************************************************************************
 ** \brief	 SYS_GetLVDIntFlag
 **			 ??????LVD???????????????
 ** \param [in] none
 ** \return  0:????????? 1????????????
 ** \note	 
*****************************************************************************/
uint8_t SYS_GetLVDIntFlag(void)
{
	return((LVDCON & LVD_LVDCON_LVDINTF_Msk)? 1:0);
}

/*****************************************************************************
 ** \brief	 SYS_ClearLVDIntFlag
 **			 ??????LVD???????????????
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_ClearLVDIntFlag(void)
{
	LVDCON	&= ~(LVD_LVDCON_LVDINTF_Msk);
}


/*****************************************************************************
 ** \brief	 SYS_EnableWDTReset
 **			 ??????WDT??????System
 ** \param [in] none
 **
 ** \return none
 ** \note
 *****************************************************************************/
void SYS_EnableWDTReset(void)
{
	TA = 0xAA;
	TA = 0x55;
	WDCON |= WDT_WDCON_WDTRE_Msk;
}
/*****************************************************************************
 ** \brief	 SYS_DisableWDTReset
 **			 ??????WDT??????System
 ** \param [in] none
 **
 ** \return none
 ** \note
 *****************************************************************************/
void SYS_DisableWDTReset(void)
{
	TA = 0xAA;
	TA = 0x55;
	WDCON &= ~(WDT_WDCON_WDTRE_Msk);
}
/*****************************************************************************
 ** \brief	 SYS_GetWDTResetFlag
 **			 ??????WDT??????System?????????
 ** \param [in] none
 **
 ** \return 0???????????????WDT????????????    1????????????WDT????????????
 ** \note
 *****************************************************************************/
uint8_t SYS_GetWDTResetFlag(void)
{
	return((WDCON & WDT_WDCON_WDTRF_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	 SYS_ClearWDTResetFlag
 **			 ??????WDT??????System?????????
 ** \param [in] none
 **
 ** \return   none
 ** \note
 *****************************************************************************/
void SYS_ClearWDTResetFlag(void)
{
	TA = 0xAA;
	TA = 0x55;
	WDCON &= ~(WDT_WDCON_WDTRF_Msk);	
}

/*****************************************************************************
 ** \brief	 SYS_EnableSoftwareReset
 **			 ??????????????????System
 ** \param [in] none
 **
 ** \return none
 ** \note
 *****************************************************************************/
void SYS_EnableSoftwareReset(void)
{
	TA = 0xAA;
	TA = 0x55;
	WDCON |= WDT_WDCON_SWRST_Msk;
}
/*****************************************************************************
 ** \brief	 SYS_DisableSoftwareReset
 **			 ??????????????????System
 ** \param [in] none
 **
 ** \return none
 ** \note
 *****************************************************************************/
void SYS_DisableSoftwareReset(void)
{
	TA = 0xAA;
	TA = 0x55;
	WDCON &= ~(WDT_WDCON_SWRST_Msk);
}
/*****************************************************************************
 ** \brief	 SYS_GetPowerOnResetFlag
 **			 ??????????????????System?????????
 ** \param [in] none
 **
 ** \return   0?????????????????????????????????    1??????????????????????????????
 ** \note
 *****************************************************************************/
uint8_t SYS_GetPowerOnResetFlag(void)
{
	return((WDCON & WDT_WDCON_PORF_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	 SYS_ClearPowerOnResetFlag
 **			 ??????PowerOn??????System?????????
 ** \param [in] none
 **
 ** \return   none
 ** \note
 *****************************************************************************/
void SYS_ClearPowerOnResetFlag(void)
{
	WDCON &= ~(WDT_WDCON_PORF_Msk);	
}


/*****************************************************************************
 ** \brief	 SYS_EnableWakeUp
 **			 ??????????????????
 ** \param [in] none
 **
 ** \return none
 ** \note	 ?????????????????????GPIO????????????
 *****************************************************************************/
void SYS_EnableWakeUp(void)
{
	PCON |= SYS_PCON_SWE_Msk;
}
/*****************************************************************************
 ** \brief	 SYS_EnableWakeUp
 **			 ??????????????????
 ** \param [in] none
 **
 ** \return none
 ** \note	???????????????????????????LVR????????????
 *****************************************************************************/
void SYS_DisableWakeUp(void)
{
	PCON &= ~(SYS_PCON_SWE_Msk);
}

/*****************************************************************************
 ** \brief	 SYS_EnterStop
 **			 ???????????????STOP??????
 ** \param [in] none
 **
 ** \return none
 ** \note	
 *****************************************************************************/
void SYS_EnterStop(void)
{
	_nop_();
	_nop_();
	PCON |= SYS_PCON_STOP_Msk;
	_nop_();
	_nop_();	
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
/*****************************************************************************
 ** \brief	 SYS_EnterIdle
 **			 ?????????????????????Idle??????
 ** \param [in] none
 **
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_EnterIdle(void)
{
	_nop_();
	_nop_();
	PCON |= SYS_PCON_IDLE_Msk;
	_nop_();
	_nop_();	
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

/*****************************************************************************
 ** \brief	 SYS_EnableWakeUpTrig
 **			 ????????????????????????
 ** \param [in] none
 **
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_EnableWakeUpTrig(void)
{
	WUTCRH |= (WUT_WUTCRH_WUTEN_Msk);

}
/*****************************************************************************
 ** \brief	 SYS_DisableWakeUpTrig
 **			 ????????????????????????
 ** \param [in] none
 **
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_DisableWakeUpTrig(void)
{
	WUTCRH &= ~(WUT_WUTCRH_WUTEN_Msk);
}

/*****************************************************************************
 ** \brief	 SYS_ConfigWUTCLK
 **			????????????????????????
 ** \param [in] clkdiv: (1)WUT_CLK_DIV_1 
 **						(2)WUT_CLK_DIV_8
 **						(2)WUT_CLK_DIV_32
**						(2)WUT_CLK_DIV_256
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_ConfigWUTCLK(uint8_t clkdiv )
{
	WUTCRH &= ~(WUT_WUTCRH_WUTPS_Msk);
	WUTCRH |= (clkdiv<<WUT_WUTCRH_WUTPS_Pos);
}

/*****************************************************************************
 ** \brief	 SYS_ConfigWUTTime
 **			????????????????????????
 ** \param [in] time: 12it???0x0 ~ 0xFFF???
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_ConfigWUTTime(uint16_t time )
{
	WUTCRH &= ~(WUT_WUTCRH_WUTD_Msk);
	WUTCRH |= time>>8;
	WUTCRL = time;
}

/*****************************************************************************
 ** \brief	 SYS_EnableSCM
 **			 ????????????????????????
 ** \param [in] none
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_EnableSCM(void)
{
	XT_SCM |= SYS_XTSCM_SCMEN_Msk;
}
/*****************************************************************************
 ** \brief	 SYS_DisableSCM
 **			 ????????????????????????
 ** \param [in] none
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_DisableSCM(void)
{
	XT_SCM &= ~(SYS_XTSCM_SCMEN_Msk);
}

/*****************************************************************************
 ** \brief	 SYS_EnableSCMInt
 **			 ??????????????????????????????
 ** \param [in] none
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_EnableSCMInt(void)
{
	XT_SCM |= SYS_XTSCM_SCMIE_Msk;	
}
/*****************************************************************************
 ** \brief	 SYS_DisableSCMInt
 **			 ??????????????????????????????
 ** \param [in] none
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_DisableSCMInt(void)
{
	XT_SCM &= ~(SYS_XTSCM_SCMIE_Msk);
}
/*****************************************************************************
 ** \brief	 SYS_GetSCMIntFlag
 **			 ?????????????????????????????????
 ** \param [in] none
 ** \return  0:????????? 1????????????
 ** \note	 
*****************************************************************************/
uint8_t SYS_GetSCMIntFlag(void)
{
	return((XT_SCM & SYS_XTSCM_SCMIF_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	 SYS_GetSCMState
 **			 ??????????????????????????????
 ** \param [in] none
 ** \return  0:???????????? 1?????????
 ** \note	 
*****************************************************************************/
uint8_t SYS_GetSCMState(void)
{
	return((XT_SCM & SYS_XTSCM_SCMSTA_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	 SYS_ClearSCMIntFlag
 **			 ?????????????????????????????????
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_ClearSCMIntFlag(void)
{
	XT_SCM &= ~(SYS_XTSCM_SCMIF_Msk);	
}

