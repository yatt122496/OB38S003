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
bit           BootKeyLock;
unsigned char UpKeyValue;
//
void main( void )
{
   InitSys();
   TM1638_Init();
   GoErrTestInit();
   DowGAutoInit();
   while(1)
   { //��������
	 RSTSTAT	= Bin(00000000);  //���ÿ��Ź�
	 KeyValueApart();
	 HeatCon();
     ErrTest();
     TimerFun();
	 Disp();
	 SysTimer();
	 TimerOff();
   }
}
