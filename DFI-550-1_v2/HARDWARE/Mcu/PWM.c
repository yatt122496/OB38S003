/***********************************************************
*
************************************************************
*  ����:2014-1-3 9:10
*
*  ����:
*
************************************************************
*  Ӳ����  SH79F1622
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
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
  EPWM_ConfigRunMode(EPWM_WFG_INDEPENDENT|EPWM_OC_INDEPENDENT|EPWM_OCU_SYMMETRIC|EPWM_COUNT_DOWN); //����ģʽ+�������ģʽ+�ԳƼ���ģʽ+���¼���(���Ķ���)ģʽ
	//����EPWM����ʱ��
	EPWM_ConfigChannelClk(EPWM0, EPWM_CLK_DIV_16);
	//����EPWM �����Լ�ռ�ձ�
	EPWM_ConfigChannelPeriod(EPWM0, 370);
	EPWM_ConfigChannelSymDuty(EPWM0, 0);
	//����EPWM�ļ��ط�ʽΪ�Զ�����
	EPWM_EnableAutoLoadMode(EPWM_CH_0_MSK);
	//����EPWM���������
	EPWM_EnableReverseOutput(EPWM_CH_0_MSK); //�������
//	//����EPWM���
	EPWM_EnableOutput(EPWM_CH_0_MSK);		//�������
	//����EPWM����
	EPWM_DisableDeadZone(EPWM0);
	//����EPWM���IO����
	GPIO_SET_MUX_MODE(P17CFG, GPIO_P17_MUX_PG0);

	//����EPWM
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
