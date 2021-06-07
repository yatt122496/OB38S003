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
//Ir 解锁控制变量
bit            IrTimerCon;
unsigned int   IrLockTimerCon;

static unsigned short wIr_time = 0;
#if IR_TEST
xdata u8 bData[40] = 0, bAD_indx = 0;
#endif
void SysTimer_Isr(void) interrupt TIMER0_VECTOR
{
	TH0 = (d_MODEVALUE_T0-d_RELOADVALUE_T0)/256;    //MODE1 16bit 65536
    TL0 = (d_MODEVALUE_T0-d_RELOADVALUE_T0)%256;
	wIr_time++;
	if (IR) {
		TR0 = 0;
	}
}

/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void Int2_IR( void ) interrupt INT1
{
	unsigned char IrTimerBuff;
	// unsigned char IrTimerBuff1;
	if (wIr_time < 20) {
		wIr_time = 0;
		TR0 = 1;
		return;
	}

	if(!IrLeadOk) {
		IrLeadOk = 1;
		BitIndex = 0;
		IrDtat   = 0;
	} else {
		BitIndex++;
		IrDtat <<= 1;
		if ((wIr_time > 90) && (wIr_time < 150)) {
			IrDtat |= 0x01;
		} else if ((wIr_time > 25) && (wIr_time < 60)) {
			IrDtat &= 0xfe;
		} else {
			goto  IrError;
		}
#if IR_TEST
	bData[bAD_indx] = wIr_time;
	bAD_indx++;
	if (bAD_indx > 39) {
		bAD_indx--;
	}
#endif
		if(BitIndex < 5) {	//5位控制码
			if(IrDtat!=BitIndexList[BitIndex]) {
				goto  IrError;
			}
		} else if (BitIndex == 12) {
			IrTimerBuff = 0;
			do {
				if(IrDtat == IrKeyCode[IrTimerBuff]) {
					if(!IrLock) {
						IrValue = IrKeyValue[IrTimerBuff];
						IrLock  = 1;
					}
					IrLeadOk = 0;
					// IrLockTimerCon  = 0;
					break;
				}
				IrTimerBuff++;
			} while(IrTimerBuff < IR_KEY_SIZE);
			IrError:
			if (IrLock) {
				IrLockTimerCon  = 0;
			}
			BitIndex = 0;
			IrDtat   = 0;
			IrLeadOk = 0;
			return;
		}
	}
	wIr_time = 0;
	TR0 = 1;
}

void IrLockTmr(void)
{
	static u8 bTime = 0;
	if(IrLock == 1) {
		if(++IrLockTimerCon > 9) {
			IrLockTimerCon	  = 0;
			IrValue           = 0;
			IrLock			  = 0;
		}
	}

	if (IR) {
		bTime++;
		if (bTime > 4) {
			bTime = 0;
			IrLeadOk = 0;
		}
	} else {
		bTime = 0;
	}
}

// void Int2_IR( void )  interrupt INT1
// {
//   unsigned char IrTimerBuff;
//   unsigned char IrTimerBuff1;
//   if(IT20==1)
//   EXF0 = Bin(00001000);
//   else
//   EXF0 = Bin(00000100);
//   if((IT20==0)||(BitIndex==11))
//   {
//     IrTimerCon = 0;
//     IrTimerBuff=IrTimer;
// 	IrTimerBuff1=IrTimer1;
//     IrTimer=0;
// 	IrTimer1=0;
//     IrTimerCon  = 1;
// 	if(IrLeadOk==0)
// 	{
// 	  IrLeadOk=1;
// 	  BitIndex=0;
// 	  IrDtat=0;
// 	  return;
// 	}
// 	else
// 	{
// 	  BitIndex++;
// 	  if(IrTimerBuff>3)
// 	  IrDtat|=0x01;
// 	  else
// 	  {
// 	    if((BitIndex>=12)||(IrTimerBuff1>3))
// 	    IrDtat&=0xfe;
// 	    else
// 	    goto  IrError;
// 	  }
// 	}
// 	if(BitIndex<5)	//5位控制码
// 	{
// 	  if(IrDtat!=BitIndexList[BitIndex])
// 	  {
// 	    IrError:
//         IrLeadOk=0;
//         IrDtat=0;
//         EXF0 = Bin(00000100);
// 		return;
// 	  }
// 	}
// 	if(BitIndex==12)
// 	{
// 	   IrTimerBuff=0;
// 	   do
// 	   {
// 	   	 if(IrDtat==IrKeyCode[IrTimerBuff])
// 		 {
// 		   if(IrLock==0)
// 		   {
// 		     IrValue=IrKeyValue[IrTimerBuff];
// 		     IrLock=1;
// 		   }
// 		   IrLockTimerCon  = 0;
// 		   break;
// 		 }
// 		 IrTimerBuff++;
// 	   }while(IrTimerBuff < IR_KEY_SIZE);
// 	   goto IrError;
// 	}
// 	IrDtat<<=1;
//   }
// }
// /************************************************************
// * 函数名:
// * 功能说明:
// ************************************************************/
// void PWM_ISR( void ) PWM 	  //200US
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
//        EXF0 = Bin(00000100);
// 	   IrTimerCon = 0;
// 	 }
//    }
//    IrLockTimerCon++;
//    if(IrLockTimerCon > 500)	   //100MS
//    {
// 	   IrLockTimerCon = 0;
// 	   IrValue=0;
// 	   IrLock=0;
//    }
// }
