/***********************************************************
*
************************************************************
*  日期:2014-1-3 9:10
*
*  作者:
*
************************************************************
*  硬件：  SH79F1622
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\include\SysInc.h"
#include "HARDWARE\Lib\inc\epwm.h"
//-------------------------------
#ifdef PWM_EN
//-------------------------------
void PwmInit(void)
{
  //-----------------------------
  #define PWM_FD     16
  #define PWM_FREQ	 4000  	//100Ms
  //-----------------------------
  //   	  bit7   bit6    bit5     bit4	  bit3    bit2	  bit1   bit0
  //PWMCON  PWMEN  PWMS   PWMCK1   PWMCK0     -       -     PWMIF  PWMSS
//   PWMCON= Bin(10110000);
//   PWMP  = (SCLK/PWM_FD/(PWM_FREQ*2))%256-1; //(SCLK/PWM_FD/PWM_FREQ  )%256-1;
//   PWMD  = (SCLK/PWM_FD/(PWM_FREQ*2))%256-1;
//   IntSet(PWM,3,1);
//   P1M0  |= Bin(10000000);
//   P1M1  &=~Bin(10000000);
  EPWM_ConfigRunMode(EPWM_WFG_INDEPENDENT|EPWM_OC_INDEPENDENT|EPWM_OCU_SYMMETRIC|EPWM_COUNT_DOWN); //互补模式+输出独立模式+对称计数模式+上下计数(中心对齐)模式
	//设置EPWM运行时钟
	EPWM_ConfigChannelClk(EPWM0, EPWM_CLK_DIV_16);
	//设置EPWM 周期以及占空比
	EPWM_ConfigChannelPeriod(EPWM0, 370);
	EPWM_ConfigChannelSymDuty(EPWM0, 0);
	//设置EPWM的加载方式为自动加载
	EPWM_EnableAutoLoadMode(EPWM_CH_0_MSK);
	//设置EPWM的输出极性
	EPWM_EnableReverseOutput(EPWM_CH_0_MSK); //反向输出
//	//设置EPWM输出
	EPWM_EnableOutput(EPWM_CH_0_MSK);		//开启输出
	//设置EPWM死区
	EPWM_DisableDeadZone(EPWM0);
	//设置EPWM输出IO复用
	GPIO_SET_MUX_MODE(P17CFG, GPIO_P17_MUX_PG0);

	//开启EPWM
	EPWM_Start(EPWM_CH_0_MSK);
}
bit BzOn;
bit BzCon;
bit BzTime50ms;
u8 BzTime,BzTime1,BzSize;

void BzSet(u8 Set)
{
 BzTime = 0;
 BzTime1= 0;
 BzSize = Set;
 BzCon  = 1;
//  P1M0  &=~Bin(10000000);
//  P1M1  |= Bin(10000000);
EPWM_ConfigChannelSymDuty(EPWM0, 185);
}
void Bz(void)
{
  if(BzTime50ms)
  {
	BzTime50ms = 0;
	//-------------
	if(BzCon)
	{
      BzTime++;
      if(BzTime > 49)
      {
	    BzTime = 0;
		BzTime1++;
	    if(BzTime1 >= BzSize)
	    {
	      BzTime1 = 0;
		  BzCon   = 0;
	    //   P1M0  |= Bin(10000000);
        //   P1M1  &=~Bin(10000000);
		EPWM_ConfigChannelSymDuty(EPWM0, 0);
	    }else
	    {
		  if((PWMD0L))
		  {
	        // P1M0  |= Bin(10000000);
            // P1M1  &=~Bin(10000000);
			EPWM_ConfigChannelSymDuty(EPWM0, 0);
		  }else
		  {
            // P1M0  &=~Bin(10000000);
		    // P1M1  |= Bin(10000000);
			EPWM_ConfigChannelSymDuty(EPWM0, 185);
		  }
	    }
      }
	}else
	{
	  BzTime  = 0;
	  BzTime1 = 0;
	//   P1M0  |= Bin(10000000);
    //   P1M1  &=~Bin(10000000);
	EPWM_ConfigChannelSymDuty(EPWM0, 0);
	}
	//-------------
  }
}
// void PwmIsr(void) interrupt PWM		//BZ 4000HZ 125uS
// {
//   PWMCON = Bin(10110000);
//   BZ = ~BZ;
// }
#endif
