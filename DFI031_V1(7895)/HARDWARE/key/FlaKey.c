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
//-----------------
U8  FlaGears;
//-----------------
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void FlaKey(void)
{
  if(!FlaGears){
	FlaGears   = 5;
  }else
  if(FlaGears){
    FlaGears--;
  }
  KeySaveDat();
}
void FlaUKey(void)
{
   FlaGears++;
   if(FlaGears > 5){
	 FlaGears   = 5;
   }else{
     KeySaveDat();
   }
}
void FlaDKey(void)
{
  if(FlaGears){
    FlaGears--;
    KeySaveDat();
  }
}