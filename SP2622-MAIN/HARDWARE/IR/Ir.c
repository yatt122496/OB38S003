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

#define d_MODEVALUE_T0      65536     //MODE1 16bit 65536
#define d_RELOADVALUE_T0    200      //User Define Reload Value

uint8  IrValue;
bit    IrLock;
bit    IrLeadOk;
uint8  IrDtat[3];
uint8  BitIndex;
bit    TimerVO;
uint16 IrTimerBuff;
uint16 IrTimerBuff1;
uint8  IrLockTimerCon;
uint8 bIr_lock = 0;

/*

         A8              K1

         A5              K2

      A3    A7       K3     K4

         A4              K5

      A1    A2       K6     K7

*/
#if ((L2320_EN == 1) || (SP2622_UL_EN == 1))	  //L2320_UL
   #define  IR_KEY_SIZE  5
  //   					        POW   HEA  TIM  DWL TEST
	uint8  code IrKeyCode[10] ={0xA8,0xA3,0xA7,0xA4,0xAA,0xff};
//  #if ((L2320_EN == 1))
	uint8  code IrKeyValue[10]={ 1  , 2  ,  3 ,  4 ,  7 ,0xff};
//  #else
//	uint8  code IrKeyValue[10]={ 1  , 2  ,  4 ,  3 ,  7 ,0xff};
//  #endif
#else
   #define  IR_KEY_SIZE  6
  //   					        POW  FLA  HEA  TIM  DWL TEST
	uint8  code IrKeyCode[10] ={0xA8,0xA5,0xA3,0xA7,0xA4,0xAA,0xff};
	uint8  code IrKeyValue[10]={ 1  ,  2 ,  3 ,  4 ,  5 ,  7 ,0xff};
#endif

static unsigned short wIr_time = 0;
#if IR_TEST
xdata u8 bData[40] = {0}, bAD_indx = 0;
#endif

void TIMER0_ISR(void) interrupt TIMER0_VECTOR
{
    TH0 = (d_MODEVALUE_T0-d_RELOADVALUE_T0)/256;    //MODE1 16bit 65536
    TL0 = (d_MODEVALUE_T0-d_RELOADVALUE_T0)%256;
	wIr_time++;
	if (IR) {
		TR0 = 0;
	}
    // To do something by using timer interrupt.

}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
#define IR_VALUE 10
void Int2_IR( void ) interrupt INT1
{
#if UART_TEST
	bData[bAD_indx] = wIr_time;
	bAD_indx++;
	if (bAD_indx > 39) {
		bAD_indx--;
	}
#endif
	if(IrLeadOk) {
		IrDtat[2] >>= 1;
		if((wIr_time < IR_VALUE) && (wIr_time >= IR_VALUE - 3)) {
			IrDtat[2] &= 0x7f;
		} else if ((wIr_time < IR_VALUE * 3) && (wIr_time >= IR_VALUE + 2)) {
			IrDtat[2] |= 0x80;
		} else {
			goto IrErr;
		}
		// if (wIr_time < 8) {
		// 	IrDtat[2] &= 0x7f;
		// } else {
		// 	IrDtat[2] |= 0x80;
		// }
		if(--BitIndex == 0){
			//----------------------------------------
			if ((IrDtat[0] == 0x6a) && (IrDtat[1] == ~IrDtat[2])) {
				IrTimerBuff=0;
				do{
					//----------------------------------------
					if(IrDtat[1]==IrKeyCode[IrTimerBuff]){
						if(!IrLock){
							IrValue     = IrKeyValue[IrTimerBuff];
							IrLock      = 1;
							BiGuangCon  = 1;
						}
						// IrValue     = IrKeyValue[IrTimerBuff];
						IrLockTimerCon = 0;
						break;
					}

					//----------------------------------------
					IrTimerBuff++;
				}while(IrTimerBuff < IR_KEY_SIZE);
			}
			IrErr:
			IrLeadOk  = 0;
			BitIndex  = 0;
		//----------------------------------------
		}else{
		//----------------------------------------
			if((BitIndex & 0x07) == 0){
				IrDtat[0]=IrDtat[1];
				IrDtat[1]=IrDtat[2];
			}
		//----------------------------------------
		}
	}else if ((wIr_time > 80) && (wIr_time < 120)) {
		IrLeadOk  = 1;
		BitIndex  = 24;
	}
	TR0 = 1;
	wIr_time = 0;
}

void IrLockTmr(void)
{
	static u8 bTime = 0;
	if(IrLock) {
		if(++IrLockTimerCon > 9) {
			IrLockTimerCon	 = 0;
			IrValue           = 0;
			IrLock            = 0;
		}
	}
}
