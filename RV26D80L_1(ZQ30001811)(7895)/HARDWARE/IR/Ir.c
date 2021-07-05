/***********************************************************
*  文件说明：摇控程序
************************************************************
*  日期:2011.12.22 19:55
*
*  作者:  cuoiszf
*
************************************************************
*  硬件：sh79f083
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE/main/SysInc.h"
//
unsigned char IrValue;
//
bit IrTimerCon;
unsigned int IrLockTimerCon;
//
unsigned char  IrLock;
bit            IrLeadOk;
unsigned char  IrDtat;
unsigned char  IrTimer;
unsigned char  IrTimer1;
unsigned char  BitIndex;


xdata unsigned char BitIndexList[]={0x01,0x01,0x03,0x06,0x0D,0x1B};
//
#define IR_SIZE   6
//					  //            POW  FLA  HEA  TIM  DOW  UP
xdata unsigned char IrKeyCode[6]   ={0x81,0x90,0x88,0x84,0Xc3,0xa0};
xdata unsigned char IrKeyV   [6]   ={   1,   2,   6,   4,   5,  7};
static unsigned short wIr_time = 0;
#if UART_TEST
xdata u8 bData[40] = 0, bAD_indx = 0;
#endif

/************************************************************
* 函数名: UpKey()
* 功能说明:  按键调用
************************************************************/
void Int2_IR( void )  interrupt P3EI_VECTOR
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
			if (BitIndex < 5) //5位控制码
			{
				if (IrDtat != BitIndexList[BitIndex])
				{
				IrError:
					IrLeadOk = 0;
					IrDtat = 0;
					// EXF0 = Bin(00000100);
					P30EICFG = 0x02; //配置为下降沿触发
					return;
				}
			}
			else if (BitIndex == 12)
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
		if (GoErrCount > 80)
			GoErrCount = 90;
	}
}
/************************************************************
* 函数名: UpKey()
* 功能说明:  按键调用
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
			P30EICFG = 0x02; //下降沿
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
