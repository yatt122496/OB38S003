/***********************************************************
*  文件说明：
************************************************************
*  日期:
*
*  作者:
*
************************************************************
*  硬件：sh79f083
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\main\SysInc.h"

uint8 FlaOn,FlaOff;
uint8 DotOn,DotOff;

//---------------------------------
unsigned char code FlameLumConst[]=
{
  0, //关
  2, //微亮 1
  4, //中亮 2
  6, //常亮 3
  8, //微亮 4
  10,//中亮 5
  10,//常亮
  0
};

//---------------------------------
unsigned char code DotLumCon[]=
{
  0, //关
  4, //微亮 1
  4, //中亮 2
  6, //常亮 3
  8, //微亮 4
  8, //中亮 5
  8, //常亮
  0
};
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void FlaCon( void )  //1ms
{
  if(!Standby){
	FOT = 0;
	MOT = 0;
	DOT = 0;
	DOT1= 0;
  }else{
	//-------------------
	if(FlaGears > FLA_MAX)
	FlaGears    = FLA_MAX;
	//-------------------
    if(FlaGears){
      MOT = 1;
      if(!FlaOn && !FlaOff){
         FlaOn = FlameLumConst[FlaGears];
         FlaOff = 10 - FlaOn;
      }
      if(!DotOn && !DotOff){
         DotOn = DotLumCon[FlaGears];
         DotOff = 10 - DotOn;
      }
      if(FlaOn ){FlaOn--; FOT = 1;}else
      if(FlaOff){FlaOff--;FOT = 0;}
    }else{
      //
      FOT = 0;
      MOT = 0;
//	  DOT = 0;
      FlaOn = 0;FlaOff = 0;
      //
      if(!DotOn && !DotOff){
        DotOn = 2;DotOff = 8;
      }
    }
    if(DotOn ){DotOn--; DOT = 1;DOT1 = 1;}else
    if(DotOff){DotOff--;DOT = 0;DOT1 = 0;}
  }
}