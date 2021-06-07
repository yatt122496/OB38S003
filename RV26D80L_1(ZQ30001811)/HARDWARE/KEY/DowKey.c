/***********************************************************
*
************************************************************
*  日期: 2015-8-28 10:53
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

uint8   DowGears=1;

void DowDisp(void)
{
  if(DowGears){
    DispDct1 = D;
	DispDct2 = (DOW_MAX+1)-DowGears;
//	DispLed  = LED_FLA;
  }
}

void DowKey(void)
{
  CancelAllFlash(0);
  DispDataSet = &DowDisp;
  if((KeyAct & K2_DOW) || !DowGears){
	if(++DowGears	> DOW_MAX){DowGears = 1;
//	  KeyAct = 0;
//	  return;
	}
	if(DowGears == DOW_MAX)DowSpeedInit();
  }
  KeyAct = K2_DOW;
}

//u8 DowLum=0;
//u8 DowAS =1;
//void DowLumDisp(void)
//{
//  if(DowGears){
//   if(DowLum > 2)DowLum = 2;
//   DispDct2 = 3-DowLum;
//  }
//}
//void DowASDisp(void)
//{
//  if(DowGears){
//   if(DowAS > 2)DowAS = 2;
//   DispDct2 = DowAS+1;
//  }
//}
//void DowAutoKey(void)
//{
// if(DowGears){
//  if(DowGears > DOW_MAX) DowGears = DOW_MAX;
//  //---------------
//  if(DowGears!=DOW_MAX){
//    DispDataSet = &DowLumDisp;
//	if(KeyAct & K2_DAO){
//      if(++DowLum > 2){DowLum = 0;}
//	}
//  }else{
//    DispDataSet = &DowASDisp;
//	if(KeyAct & K2_DAO){
//      if(++DowAS > 2){DowAS = 0;}
//	  DowSpeedInit();
//	}
//  }
//  KeyAct = K2_DAO;
// }
//}

