/***********************************************************
*
************************************************************
*  ����:
*
*  ����:
*
************************************************************
*  Ӳ����SH79F083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE/main/SysInc.h"
#include "HARDWARE\Lib\inc\wdt.h"

bit           BootKeyLock;
xdata unsigned char UpKeyValue;
//
#if UART_TEST
	extern xdata u8 bData[40], bAD_indx;
#endif
void main( void )
{
#if UART_TEST
	xdata u8 i;
	xdata unsigned long dwSys_time = 0;
#endif

	InitSys();
	TM1638_Init();
	GoErrTestInit();
#if UART_TEST
	// init_UART0();
#endif
	while(1) {
#if UART_TEST
		if (Sys_Time - dwSys_time > 999) {
			dwSys_time = Sys_Time;
			DOW_O = !DOW_O;

			UART0_TX(0xff);
			UART0_TX(bAD_indx);
			for ( i = 0; i < bAD_indx; i++) {
				UART0_TX(bData[i]);
			}
			bAD_indx = 0;
		}
#endif
		//��������
		//  RSTSTAT	= Bin(00000000);  //���ÿ��Ź�
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
