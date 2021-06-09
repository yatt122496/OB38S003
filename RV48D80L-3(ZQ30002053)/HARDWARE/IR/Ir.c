/***********************************************************
*  �ļ�˵����ҡ�س���
************************************************************
*  ����:2011.12.22 19:55
*
*  ����:  cuoiszf
*
************************************************************
*  Ӳ����sh79f083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE/main/SysInc.h"
//
unsigned char IrValue;
//
bit IrTimerCon;
unsigned int IrLockTimerCon;
//
bit            IrLock;
bit            IrLeadOk;
unsigned char  IrDtat;
unsigned char  IrTimer;
unsigned char  IrTimer1;
unsigned char  BitIndex;

#if (CT_YY_EN==1)
	unsigned char code BitIndexList[]={0x01,0x01,0x03,0x06,0x0D,0x1B};
	//
	#define IR_SIZE   6
	//					  //            POW  FLA  HEA  TIM  DOW  UP
	unsigned char code IrKeyCode[6]   ={0x81,0x90,0x88,0x84,0Xc3,0xa0};
	unsigned char code IrKeyV   [6]   ={   1,   2,   6,   4,   5,  7};
#else
	#define IR_SIZE   6
	unsigned char code BitIndexList[5]={0x00,0x00,0x01,0x03,0x06};
	//									POW  FLA  HEA  SDL
	unsigned char code IrKeyCode[]   ={0x48,0x42,0x60,0x50,0X44,0x40};
	unsigned char code IrKeyV[]      ={   1,   2,   6,   4,   5,   7};
#endif
/************************************************************
* ������: UpKey()
* ����˵��:  ��������
************************************************************/

void P3EI_IRQHandler(void)  interrupt P3EI_VECTOR
{
	unsigned char IrTimerBuff;
	unsigned char IrTimerBuff1;
	if (P3EXTIF & 0x01)
	{
		P3EXTIF &= 0xfe;
		if (0x02 == (P30EICFG & 0x02))
			P30EICFG = 0x01;
		else
			P30EICFG = 0x02;
		if ((0x01 == (P30EICFG & 0x01)) || (BitIndex == 11))
		{
			IrTimerCon = 0;
			IrTimerBuff = IrTimer;
			IrTimerBuff1 = IrTimer1;
			IrTimer = 0;
			IrTimer1 = 0;
			IrTimerCon = 1;
#if IR_TEST
			bData[bAD_indx] = IrTimerBuff;
			bAD_indx++;
			if (bAD_indx > 39)
			{
				bAD_indx--;
			}
#endif
			if (!IrLeadOk)
			{
				IrLeadOk = 1;
				BitIndex = 0;
				IrDtat = 0;
				return;
			}
			else
			{
				BitIndex++;
				if (IrTimerBuff > 30)
					IrDtat |= 0x01;
				else if ((BitIndex >= 12) || (IrTimerBuff1 > 30))
					IrDtat &= 0xfe;
				else
					goto IrError;
			}
			if (BitIndex < 5) //5λ������
			{
				if (IrDtat != BitIndexList[BitIndex])
				{
				IrError:
					IrLeadOk = 0;
					IrDtat = 0;
					P30EICFG = 0x02; //����Ϊ�½��ش���
					return;
				}
			}
			if (BitIndex == 12)
			{
				IrTimerBuff = 0;
				do
				{
					if (IrDtat == IrKeyCode[IrTimerBuff])
					{
						if (!IrLock)
						{
							IrValue = IrKeyV[IrTimerBuff];
							IrLock = 1;
							BiGuangCon = 1;
						}
						IrLockTimerCon = 0;
						break;
					}
					IrTimerBuff++;
				} while (IrTimerBuff < IR_SIZE);
				goto IrError;
			}
			IrDtat <<= 1;
		}
	}
	if (P3EXTIF & 0x02)
	{
		P3EXTIF = 0;
		// IE0  = 0;
		GoErrCount++;
		if(GoErrCount > 80)
			GoErrCount    = 90;
	}
}
/************************************************************
* ������: UpKey()
* ����˵��:  ��������
************************************************************/
void IrIsr(void)  interrupt TMR0_VECTOR		//20us
{
	TH0 = (d_MODEVALUE_T0 - d_RELOADVALUE_T0) >> 8;
	TL0 = (d_MODEVALUE_T0 - d_RELOADVALUE_T0);
	if (IrTimerCon)
	{
		if (0x01 == (P30EICFG & 0x01))
			IrTimer++;
		else
			IrTimer1++;
		if ((IrTimer1 > 100) || (IrTimer > 100))
		{
			IrLeadOk = 0;
			BitIndex = 0;
			IrTimer1 = 0;
			IrTimer = 0;
			P30EICFG = 0x02; //�½���
			IrTimerCon = 0;
		}
	}
	if (IrLock)
	{
		IrLockTimerCon++;
		if (IrLockTimerCon > 5000)
		{
			IrLockTimerCon = 0;
			IrValue = 0;
			IrLock = 0;
		}
	}
}
// void PwmIrIsr( void ) interrupt PWM    // 200US
// {
//    PWMCON = Bin(10110000);
//    if(IrTimerCon)
//    {
//      if(IT20==0)
//      IrTimer++;
//      else
//      IrTimer1++;
// 	 if((IrTimer1 > 10)||(IrTimer > 10))
// 	 {
// 	   IrLeadOk=0;
// 	   BitIndex=0;
//    	   IrTimer1=0;
// 	   IrTimer=0;
//        EXF0 = Bin(00000100);//�½��ش���
// 	   IrTimerCon = 0;
// 	 }
//    }
//    if(IrLock)
//    {
//      IrLockTimerCon++;
//      if(IrLockTimerCon > 500)
//      {
// 	   IrLockTimerCon = 0;
// 	   IrValue        = 0;
// 	   IrLock         = 0;
//      }
//    }
// }