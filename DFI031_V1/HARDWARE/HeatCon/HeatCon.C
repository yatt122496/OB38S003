/***********************************************************
*  IR.C
************************************************************
*  日期:2011.10.6 15:00
*  作者:  cuoiszf
*  功能说明：发热控制：
	（1）.等待模式概念说明:
	      是指当机器在加热中环境温度到达设定温度后进入停止加热时，
	      机器会以3分钟等待、3分钟加热，6分钟等待、3分钟加热，9分
	      钟等待、3分钟加热这样的等待递增循环模式，最大的等待时间
	      为100分钟。如果100分钟内没有回复，还会以100分钟的等量时
	      间进行等待，直到回复为止。这定义为等待模式 。
	（2）. 加热与控制：
	      如果设定温度高于环境温度，则会一直加温到设定温度，当环境被加
	      热到达设定温度时，HEATER会进入保护状态。如果在保护过程中（包
	      括抽风时间）温度没有下降到设定温度值的±1℃范围内时，等待时间
	      将加3分钟递增的抽风等待；如果在保护过程中（包括抽风时间）温度
	      下降到设定温度值的±1℃范围内时，等待时间将变为12分钟等时抽风
	      等待；如果在保护过程中（包括抽风时间）温度下降到设定温度值的
	      -1℃范围以下时，机器将回复加热，并且等待时间将在前一个等待时间
	      的基础上减3分钟的抽风等待。如果设定温度低于环境温度，则会加热3
	      分钟，在3分钟的加热过程中，环境温度还没有降到设定的回复温度，将
	      进入3分钟抽热风的等待模式。（考虑用遥控器的HEATER键开关操作）
*
* 修改说明：
*	请将加热时的温度补偿温度从原来的3度改为1度，保护温度为+0.5度，回复温度为-1度。
*
************************************************************
*  硬件：
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\main\SysInc.h"
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
#define   MAX_WAIT_TIME    100		                    /* 最大等待时间				       */
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
void HeatCon( void )
{
   unsigned char  SetTfBuff;
   unsigned char  TfBuff;
   float   TempValueBuff;
   if(GoErrCon)
   {
     HOT         = 0;
	 FAN         = 0;
	 MotDelayOff = 0;
     return;
   }
   if(!Standby || !HeatOnOff || !AdReady || HeatLock || AdNtcErr)//待机关加热
   {
	 HOT     = 0;
	 HotOnOff= 0;
     if(!MotDelayOff)
	 FAN = 0;
     return;
   }
   //-----------------------------------
   if(VrValue < 10)
   SetTfBuff   = 10;
   else
   if(VrValue > 40)
   SetTfBuff   = 10;
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