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
#include "HARDWARE\main\SysInc.h"
#include "HARDWARE\Lib\inc\timer.h"
#include "HARDWARE\Lib\inc\extint.h"
//IR �ӿ�
unsigned char IrValue;
//IR ͨѶ����
bit            IrLock;
bit            IrLeadOk;
unsigned char  BitIndex;
unsigned char  IrDtat;
unsigned char  IrTimer;
unsigned char  IrTimer1;
//IR ������
unsigned char code BitIndexList[6]={0x01,0x01,0x03,0x06,0x0D,0x1B};


#if (IR_YY_HD_OTP == 0)
#define  IR_KEY_SIZE  3
//                      POW  FLA  HEA
U8 code IrKeyCode[] = {0x81,0x90,0x88,};
U8 code IrKeyValue[]= {  1 ,  2 ,   3 };
#endif

#if (IR_YY_HD_OTP == 1)
#define  IR_KEY_SIZE  4
//                      POW  UFL  HEA  DFL
U8 code IrKeyCode[] = {0x84,0x81,0x82,0x90};
U8 code IrKeyValue[]= {  1 ,  4 ,  3 ,   5};
#endif

#if (IR_YY_HD_OTP == 2)
#define  IR_KEY_SIZE  5
//                      POW  FLA  HEA   AUO
U8 code IrKeyCode[] = {0x81,0x90,0x88,0x84};
U8 code IrKeyValue[]= {  1 ,  2 ,   3,  4 };
#endif

#if (IR_YY_HD_OTP == 3)
#define  IR_KEY_SIZE  5
//                      POW FLA  HEA  AUO  VOL
U8 code IrKeyCode[] = {0x81,0x90,0x88,0x84,0xc3};
U8 code IrKeyValue[]= {  1 ,  2 ,   3,  4,   5 };
#endif
//
#if (IR_YY_HD_OTP == 4)
#define  IR_KEY_SIZE  5
//                      POW FLA  HEA   AUO  VOL
U8 code IrKeyCode[] = {0x84,0x81,0x90,0x82, 0xA0};
U8 code IrKeyValue[]= {  1 ,  2 ,   3,  4,   5 };
#endif
//Ir �������Ʊ���
bit            IrTimerCon;
unsigned int   IrLockTimerCon;

static unsigned short wIr_time = 0;
#if IR_TEST
xdata u8 bData[40] = 0, bAD_indx = 0;
#endif
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
			if (IrLeadOk == 0)
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
				else
				{
					if ((BitIndex >= 12) || (IrTimerBuff1 > 30))
						IrDtat &= 0xfe;
					else
						goto IrError;
				}
			}
			if (BitIndex < 5) //5λ������
			{
				if (IrDtat != BitIndexList[BitIndex])
				{
				IrError:
					IrLeadOk = 0;
					IrDtat = 0;
					// EXF0 = Bin(00000100);
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
						if (IrLock == 0)
						{
							IrValue = IrKeyValue[IrTimerBuff];
							IrLock = 1;
						}
						IrLockTimerCon = 0;
						break;
					}
					IrTimerBuff++;
				} while (IrTimerBuff < IR_KEY_SIZE);
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
* ������:
* ����˵��:
************************************************************/
void PWM_ISR( void )  interrupt TMR0_VECTOR
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
			//    EXF0 = Bin(00000100);
			P30EICFG = 0x02; //�½���
			IrTimerCon = 0;
		}
	}
	IrLockTimerCon++;
	if (IrLockTimerCon > 5000) //100MS
	{
		IrLockTimerCon = 0;
		IrValue = 0;
		IrLock = 0;
	}
}
