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
bit DotAotoCon;
//-----------------
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void FlaKey(void)
{
//  if(!Standby)
//  {
//    Standby = 1;
//	if(!FlaGears)
//    goto OnFla;
//  }else
//  {
//    OnFla:
	FlaGears++;
	if(FlaGears > 5)
	{
	  FlaGears   = 0;
	  DotAotoCon = 0;
	}
//  }
  KeySaveDat();
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void DotAutoKey(void)
{
  if(FlaGears){
    DotAotoCon = !DotAotoCon;
    KeySaveDat();
  }
}