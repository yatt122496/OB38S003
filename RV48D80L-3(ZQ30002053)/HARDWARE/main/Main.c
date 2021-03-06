/***********************************************************
*
************************************************************
*  日期:
*
*  作者:
*
************************************************************
*  硬件：SH79F083
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
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
   { //正常工作
	 RSTSTAT	= Bin(00000000);  //重置看门狗
	 KeyValueApart();
	 HeatCon();
     ErrTest();
     TimerFun();
	 Disp();
	 SysTimer();
	 TimerOff();
   }
}
