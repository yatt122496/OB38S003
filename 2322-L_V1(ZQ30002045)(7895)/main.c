/***********************************************************
*  �ļ�˵����
************************************************************
*  ����:
*
*  ����:
*
************************************************************
*  Ӳ����sh79f083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE/main/SysInc.h"
#include "HARDWARE\Lib\inc\wdt.h"

#if IR_TEST
	extern xdata u8 bData[40], bAD_indx;
#endif

bit           BootKeyLock;
unsigned char UpKeyValue;
//
void main( void )
{
#if UART_TEST
#if IR_TEST
	xdata u8 i;
#endif
	xdata unsigned long dwSys_time = 0;
#endif
   InitSys();
   TM1638_Init();
   GoErrTestInit();
#if UART_TEST
	// init_UART0();
#endif
   while(1)
   { //��������
	//  RSTSTAT	= Bin(00000000);  //���ÿ��Ź�
#if UART_TEST
		if (Sys_Time - dwSys_time > 999) {
			dwSys_time = Sys_Time;
			// UART0_TX(0xff);
#if IR_TEST
			UART0_TX(bAD_indx);
			for ( i = 0; i < bAD_indx; i++) {
				UART0_TX(bData[i]);
			}
			bAD_indx = 0;
#endif
		}
#endif
#if WDT_SWITCH
		WDT_ClearWDT(); //������Ź�������
#endif
		KeyValueApart();
		HeatCon();
		ErrTest();
		Disp();
		SysTimer();
		TimerOff();
   }
}
