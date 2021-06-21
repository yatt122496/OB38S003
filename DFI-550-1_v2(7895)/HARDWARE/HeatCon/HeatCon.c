/***********************************************************
*
************************************************************
*  日期:2015-1-8 08:18
*
*  作者:
*
************************************************************
*  硬件：
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\include\SysInc.h"

/************************************************************
* 温度补尝：  炉内温度比室内温度高，所以做温度补尝
* 正数、负数：为温度控制范为，正负多少度
***********************************************************/
#define   TEMP_ADJUST               0	/* 温度补尝，  1℃  1*1.8=1.8    (2) ℉ */
#define   TEMP_CONTROL_NEGATIVE     1 	/* 负数 恢复   1℃  1*1.8=1.8    (2) ℉ */
#define   TEMP_CONTROL_POSITIVE     1 	/* 正数 保护 0.5℃  0.5*1.8=0.9  (1) ℉ */
/************************************************************
* 以下为抽风等待常数
*                    			   以下都要以分钟为单位
***********************************************************/
#define   MAX_WAIT_TIME    103		                    /* 最大等待时间				       */
#define   LOW_WAIT_TIME	   3					        /* 最低等待时间				       */
#define   LOW_HEA_TIME     3                            /* 最低加热时间                    */
/*     等待与加热共用了多少时间                         */
#define   HEA_WAIT_TIME    LOW_WAIT_TIME + LOW_HEA_TIME /* 加热时间+等待时间=加热等待时间  */
#define   WAIT_TIME        15 							/* 等时时间						   */
/*	 以下数据是根据最低等待时间算出，开加热加热3分钟，后从最低等待时间开始工作  */
#define   STA_WAIT_TIME	   LOW_WAIT_TIME            	/* 开始等待                        */
#define   STA_HEA_TIME	   LOW_WAIT_TIME-LOW_HEA_TIME	/* 开始加热时间                    */


bit HotOnOff;
bit MotDelayOff;
bit TempFallSubWait;
unsigned char AutoAddTime=HEA_WAIT_TIME;
unsigned char HeaterOffTime;
unsigned char HeaterMinute;
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void Hot3min(void)
{
   HotOnOff=1;
   TempFallSubWait=1;
   AutoAddTime=STA_WAIT_TIME;
   HeaterOffTime=STA_HEA_TIME;
   HeaterMinute=0;
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void HeatInit(void)
{
//   P4M0  &=~Bin(00000110);
//   P4M1  |= Bin(00000110);
	P33CFG = GPIO_MUX_GPIO;
	P32CFG = GPIO_MUX_GPIO;

	// P0TRIS = (P0TRIS & ~((0))) | ((0));
	// P1TRIS = (P1TRIS & ~((0))) | ((0));
	// P2TRIS = (P2TRIS & ~((0))) | ((1 << 3));
	P3TRIS = (P3TRIS & ~((0))) | ((1 << 2) | (1 << 3));
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void HeatCon( void )
{
   unsigned char  SetTfBuff;
   unsigned char  TfBuff;
   float   TempValueBuff;
   if(!Standby || !HeatOnOff || !AdReady || HeatLock)//待机关加热
   {
	 HOT     = 0;
	 HotOnOff= 0;
     if(!MotDelayOff)
	 FAN = 0;
     return;
   }
   if(ErrCon)
   {
     HotOnOff = 1;
	 goto GoOutCon;
   }
   //-----------------------------------
   if(VrValue < 10)
   SetTfBuff   = 10;
   else
   if(VrValue > 65)
   SetTfBuff  = 65;
   else
   SetTfBuff   = VrValue;
   //-----------------------------------
   SetTfBuff  += TEMP_ADJUST;//+5;//设置温度加3
   //-----------------------------------
   TempValueBuff = TempValue + TEMP_CONTROL_NEGATIVE; /* 负数 */
   //-----------------------------------
   if(SetTfBuff >= TempValueBuff)
   {
     if(HotOnOff==0)
     {
       HotOnOff=1;
       AutoAddTime=HEA_WAIT_TIME;
     }
     if(TempFallSubWait==1)
     {
       TempFallSubWait=0;
       TfBuff=HeaterOffTime+LOW_HEA_TIME;
       if(TfBuff>=AutoAddTime)
       {
         TfBuff=AutoAddTime-LOW_HEA_TIME;
         if(TfBuff<=HEA_WAIT_TIME)
         TfBuff=HEA_WAIT_TIME;
         AutoAddTime=TfBuff;
       }
     }
     HeaterOffTime=0;
     HeaterMinute=0;
   }
   else
   {
      //-----------------------------------
	  TempValueBuff = TempValue - TEMP_CONTROL_POSITIVE; /* 正数 */
	  //-----------------------------------
      if(SetTfBuff <= TempValueBuff)
      {
        if(HotOnOff==1)
        {
          if(TempFallSubWait==0)
		  {
            HotOnOff        = 0;
			if(AutoAddTime <= LOW_WAIT_TIME)
			AutoAddTime     = HEA_WAIT_TIME;
		  }
        }
      }
      else
      {
        if(HotOnOff==1)
        {
          if(TempFallSubWait==0)
          goto GoOutCon;
        }
        else
        AutoAddTime = WAIT_TIME;//15min
      }
	  //------------------
	  if(!HotOnOff && MotDelayOff)
	  {
		HeaterMinute  = 0;
		HeaterOffTime = 0;				   //风机延时1.5分钟加入保护等待15分钟内
	  }else
      if(HeaterSec==1)//如果一秒到了我们的加热与关加热等待延时将开始工作了
      {
        HeaterSec=0;
		//------------------
        HeaterMinute++;
        if(HeaterMinute>59)
        {
          HeaterMinute=0;
		  //----------------
          HeaterOffTime++;
		}
	  }
      TfBuff=HeaterOffTime+LOW_HEA_TIME;
      if(TfBuff>=AutoAddTime)
      {
        TempFallSubWait= 1;
        HotOnOff       = 1;
        if(HeaterOffTime>=AutoAddTime)
        {
          TfBuff=AutoAddTime+LOW_HEA_TIME;
          if(TfBuff>=MAX_WAIT_TIME)
          TfBuff=MAX_WAIT_TIME;
          AutoAddTime=TfBuff;
	      HotOnOff=0;
	      TempFallSubWait=0;
	      HeaterOffTime=0;
	      HeaterMinute=0;
        }
      }
   }
   GoOutCon:
   if(HotOnOff==1)
   {
	 HOT        = 1;
	 FAN        = 1;
	 MotDelayOff= 1;
   }
   else
   {
     HOT=0;
     if(MotDelayOff==0)
	 FAN=0;
   }
}