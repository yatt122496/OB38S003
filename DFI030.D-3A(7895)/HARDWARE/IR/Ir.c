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
#include "HARDWARE\main\SysInc.h"
#include "HARDWARE\Lib\inc\timer.h"
#include "HARDWARE\Lib\inc\extint.h"
//IR 接口
unsigned char IrValue;
//IR 通讯变量
bit            IrLock;
bit            IrLeadOk;
unsigned char  BitIndex;
unsigned char  IrDtat;
unsigned char  IrTimer;
unsigned char  IrTimer1;
//IR 控制码
unsigned char code BitIndexList[6]={0x01,0x01,0x03,0x06,0x0D,0x1B};


#if (IR_YY_HD_OTP == 0)
#define  IR_KEY_SIZE  4
//                      POW  FLA  HEA   AUO
U8 code IrKeyCode[] = {0x81,0x90,0x88,0x84};
U8 code IrKeyValue[]= {  1 ,  2 ,   3,  4 };
#endif

#if (IR_YY_HD_OTP == 1)
#define  IR_KEY_SIZE  5
//                      POW  UFL  HEA  AUO  DFL
U8 code IrKeyCode[] = {0x84,0x81,0x82,0xa0,0x90};
U8 code IrKeyValue[]= {  1 ,  6 ,   3,  4 ,   7};
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
//Ir 解锁控制变量
bit            IrTimerCon;
unsigned int   IrLockTimerCon;
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
#if IR_TEST
xdata u8 bData[40] = {0}, bAD_indx = 0;
#endif
void Int2_IR( void )  interrupt P3EI_VECTOR
{
	unsigned char IrTimerBuff;
	unsigned char IrTimerBuff1;
	if (0x02 == (P30EICFG & 0x02))
		P30EICFG = 0x01;
	else
		P30EICFG = 0x02;
	P3EXTIF = 0x00; //清除中断标志位
	if ((0x01 == (P30EICFG&0x01))||(BitIndex==11))
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
	if (bAD_indx > 39) {
		bAD_indx--;
	}
#endif
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
		if (BitIndex < 5) //5位控制码
		{
			if (IrDtat != BitIndexList[BitIndex])
			{
			IrError:
				IrLeadOk = 0;
				IrDtat = 0;
				P30EICFG = 0x02;		//配置为下降沿触发
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
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void SysTimer_Isr(void)  interrupt TMR0_VECTOR
{
	TH0   = (d_MODEVALUE_T0-d_RELOADVALUE_T0) >> 8;
	TL0   = (d_MODEVALUE_T0-d_RELOADVALUE_T0);

	if (IrTimerCon)
	{
		if (0x01 == (P30EICFG&0x01))
			IrTimer++;
		else
			IrTimer1++;
		if ((IrTimer1 > 100) || (IrTimer > 100))
		{
			IrLeadOk = 0;
			BitIndex = 0;
			IrTimer1 = 0;
			IrTimer = 0;
			P30EICFG = 0x02;	 //下降沿
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
	// // Sys_Time++;
	// wIr_time++;
	// if (IR) {
	// 	TMR_Stop(TMR0);
	// }
}
