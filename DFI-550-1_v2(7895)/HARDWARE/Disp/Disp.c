/***********************************************************
*
************************************************************
*  日期:2015-1-5 16:43
*  日期:2015-1-6 10:23
*
*
*  作者:
*
************************************************************
*  硬件：  SH79F1622
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\include\SysInc.h"

u8 DispTime;
u8 DispDat[2];


u8 bdata Led;
sbit LED1 = Led^0;
sbit LED2 = Led^1;
sbit LED3 = Led^2;
sbit LED4 = Led^3;
sbit LED5 = Led^4;
//--------------------------
bit FahCon,Fah,Sub= 2;
u8 FahTime,FahSize;
//---
void FlaFahSet(u8 Set)
{
  if(Sub!=Set)
  {
    Sub     = Set;
	FahTime = 24;
	Fah     = 0;
  }
  if(!FahCon)
  {
	Fah     = 0;
	FahTime = 24;
  }
  FahCon  = 1;
  FahSize = 0;
}
//--------------------------
bit HLCon;
u8  HLTime;
void HlTimeSet(void)
{
  HLCon = 1;
  HLTime= 0;
}
//--------------------------
bit ErrFah;
u8  ErrFahTim;
void Disp(void)
{
  if(!DispTime)
  {
    DispTime = 10;
	if(Standby)
	{
	  LED1 = 1;
	  if(!HeatLock)
	  {
	     if(HeatOnOff == 1)
		 {
		   if(ErrCon)
		   {
		     if(!ErrFahTim)
			 {
			   LED4 = 1;
			   ErrFahTim = 1;
			 }
		     if(++ErrFahTim > 25)
			 {
			   ErrFahTim = 1;
		       LED4 = ~LED4;
			 }
		   }else
		   LED4 = 1;
		 }else
		 {
		   LED4 = 0;
		   ErrFahTim=0;
		 }
	  }else
	  {
	    ErrFahTim = 0;
	    if(HLCon)
		{
		  LED4 = 1;
		  HLTime++;
		  if(HLTime > 49)
		  {
			HLTime = 0;
			HLCon  = 0;
		  }
		}else
		{
		  HLTime = 0;
          LED4 = 0;
		}
	  }
	  if(FahCon)
	  {
	    FahTime++;
	    if(FahTime > 24)
	    {
		  FahTime = 0;
		  FahSize++;
		  if(FahSize > 12)
		  {
		   FahSize = 0;
		   FahCon = 0;
		   Sub    = 2;
		  }else
	      {
	        if(Sub){LED2 = ~LED2;LED3 = 0;}
			else   {LED3 = ~LED3;LED2 = 0;}
	      }
	    }
	  }else
	  {
	    FahTime = 0;
		FahSize = 0;
		Sub     = 2;
		LED2    = 0;
		LED3    = 0;
	  }
	}else
	{
	  Led    = 0;
	  FahCon = 0;
	  HLCon  = 0;
	}
	DispDat[0] = Led;
	NewDis = 1;
  }
}