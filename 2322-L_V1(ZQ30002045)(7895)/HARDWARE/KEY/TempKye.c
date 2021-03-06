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
bit   TcTf;
uint8 code SetTcTable[] =
{//设置摄氏温度
	0,	   //32	 	0
//	17,	   //63 	1
	18,	   //63 	2
	19,	   //66 	3
	20,	   //63 	4
	21,	   //70 	5
	22,	   //63 	6
	23,	   //73 	7
	24,	   //75 	8
	25,	   //77 	9
	26,	   //63 	10
	27,	   //82 	11
	60	   //63 	12
};
uint8 code SetTfTable[] =
{//设置华氏温度
	0,	   //OFF 	0
//	62,	   //16.67 	1
	64,	   //17.78 	2
	66,	   //18.89 	3
	68,	   //20.00 	4
	70,	   //21.11 	5
	72,	   //22.22 	6
	74,	   //23.33 	7
	76,	   //24.44 	8
	78,	   //25.56 	9
	80,	   //26.67 	10
	82,	   //27.78 	11
	140,   //ON 	12
};
bit     HeaOnOff;
uint8   HeatGears;

bit     SetTemp;
bit     HeatLock;
uint8   HeatLockTimer;

void HeatDisp(void)
{
	if(ErrCon){
	  DispDct1 = E;
	  DispDct2 = ErrCon;
	}else if(!HeatLock && HeaOnOff)//加热锁打开，且温显标志位1 ，显示温度
	{
		if(HeatGears >= 11)
		{
			DispDct1 = 0;//显示字符0
			DispDct2 = N;//显示字符N
		}else if(HeatGears)//温度档位不为0
		{
			if(TcTf)//摄氏温标为1 ，显示摄氏温度
			{
				DispDct1 = SetTcTable[HeatGears] / 10;
				DispDct2 = SetTcTable[HeatGears] % 10;
			}
			else//摄氏温标为0 ，显示华氏温度
			{
			   	DispDct1 = SetTfTable[HeatGears] / 10;
				DispDct2 = SetTfTable[HeatGears] % 10;
			}
		}
//		if(!TempSwFah)
//		{
		  if(TcTf)//摄氏温标为1 ，显示摄氏温度
		  DispLed = 0X40;//摄氏温度指示灯亮
		  else
		  DispLed = 0X08;//华氏温度指示灯亮
//		}
	}
}
/************************************************************
* 函数名:
* 功能说明:  获得加热键状态
************************************************************/
void GainHeaterPsw(void)
{
   if(!SetTemp)//不在温度设置状态
   HeatLockTimer = 0;//加温锁计时清零
   if(ErrCon){
    SetTemp = 1; TempFlash = 1;
	KeyAct = K2_HEA;
	DispDataSet = &HeatDisp;
   }if(HeatLock)//加热键在锁定状态
   {
	 LookFlhWood(1);//闪烁
	 KeyAct = K2_HEA;
   }
   else//加热键不在锁定状态
   {
	 if(HeaOnOff)//温显标志位1 ，显示温度
	 DispDataSet = &HeatDisp;
	 //CancelAllFlash(2);
   }
}

void TempSetKey(void)
{
   if(ErrCon){
	 SetTemp = 1; TempFlash = 1;
     return;
   }
   if(!HeaOnOff || HeatLock){// || !(KeyAct & K2_HEA)){
     return;
   }
   DispDataSet = &HeatDisp;//温度键按下，显示温度
   if(KeyAct & K2_HEA){
     HeatGears++;
     if(HeatGears > 11)
     HeatGears = 1;
     //
     if(HeatGears < 11  && !HeatTest)
     Heat3min();
     else{
	   TsetHeat();
	   HeatTest = 1;
     }
   }
   if(!SetTemp){
     TempFlash  = 1;
     SetTemp    = 1;
   }
   TempFlashTimerCon=0;
   KeyAct = K2_HEA;
}
/************************************************************
*
*
************************************************************/
void HeatKey(bit PcbIr)
{
  DispDataSet = &HeatDisp;//温度键按下，显示温度

  if(ErrCon){
	SetTemp = 1;TempFlash = 1;
	KeyAct = K2_HEA;//激活加热，显示
    return;
  }

  if(HeatLock)//加热锁锁定
  {
    LookFlhWood(1);//闪烁
	KeyAct = K2_HEA;//激活加热，显示
    return;
  }
  //CancelAllFlash(0);

  if(!PcbIr)
  SetTemp = 0;

  if(!SetTemp)
  {
    if(!HeatGears)
	HeatGears = 10;
	//
	HeatTest = 0;
    if(HeaOnOff)
	{
      if(KeyAct & K2_HEA)
	  {
		HeaOnOff   = 0;
		KeyAct     = 0;
		return;
	  }
	}
	else
	{
	  HeaOnOff   = 1;
	  Heat3min();
	}
  }else
  {
	HeatGears++;
	if(HeatGears > 11)
	HeatGears = 1;
	//
	if(HeatGears < 11  && !HeatTest)
	Heat3min();
	else
	{
	  TsetHeat();
	  HeatTest = 1;
	}
	TempFlashTimerCon=0;
  }
  KeyAct = K2_HEA;
}

/************************************************************
* 函数名: UpKey()
* 功能说明:  按键调用
************************************************************/
void HeatSetAndLook( void )
{
  HeatLockTimer++;
  if(HeaOnOff && !HeatLock && (HeatLockTimer == 1))
  {
    SetTemp    = 1;//温度设置标志置1
	TempFlash  = 1;
	KeyAct = K2_HEA;//激活加热，显?
  }
  else
  {
  	if(HeatLockTimer > 1)
	{
	  HeatLockTimer = 0;
	  SetTemp       = 0;
	  HeatLock      = ~HeatLock;
	  HeatTest = 0;
      if(!HeatLock)
      {
	    if(KeyAct & K2_HEA)
	    {
		  HeatGears = 10;
		  HeaOnOff  = 1;
		  Heat3min();
	    }
      }else
	  {
	    HeatGears  = 0;
	    HeaOnOff   = 0;
	  }
      DispDataSet = &HeatDisp;
      LookFlhWood(1);
	}
  }
//  KeyAct = K2_HEA;
}
/***********************************************************
*
*				温度转换
***********************************************************/
void TempSw(void)
{
	if(!HeatLock && HeaOnOff)
	{
   	  KeyAct = K2_HEA;
	  TempSwFahSet();
	  DispDataSet = &HeatDisp;
	}
}