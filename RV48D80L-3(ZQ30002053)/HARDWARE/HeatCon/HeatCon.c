/***********************************************************
*
************************************************************
*  日期:2011.12.22 19:55
*
*  作者:  cuoiszf
*
************************************************************
*  硬件：sh79f083
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE/main/SysInc.h"

/************************************************************
* 温度补尝：  炉内温度比室内温度高，所以做温度补尝
* 正数、负数：为温度控制范为，正负多少度
***********************************************************/
#define   TEMP_ADJUST               3	/* 温度补尝，  4℃  4*1.8=7.2    (7) ℉ */
#define   TEMP_CONTROL_NEGATIVE     1 	/* 负数 恢复   1℃  1*1.8=1.8    (2) ℉ */
#define   TEMP_CONTROL_POSITIVE     1 	/* 正数 保护 0.5℃  0.5*1.8=0.9  (1) ℉ */
/************************************************************
* 以下为抽风等待常数
*                    			   以下都要以分钟为单位
***********************************************************/
#define   MAX_WAIT_TIME    101		                    /* 最大等待时间				       */
#define   LOW_WAIT_TIME	   3					        /* 最低等待时间				       */
#define   LOW_HEA_TIME     1                            /* 最低加热时间                    */
/*   等待与加热共用了多少时间                          */
#define   HEA_WAIT_TIME    4                            /* 加热等待时间  */
/*	 以下数据是根据最低等待时间算出，开加热加热3分钟，后从最低等待时间开始工作  */
#define   STA_WAIT_TIME	   LOW_WAIT_TIME            	/* 开始等待                        */
#define   STA_HEA_TIME	   LOW_WAIT_TIME-LOW_HEA_TIME	/* 开始加热时间                    */

bit   HotOnOff;
bit   MotDelayOff;
bit   HotDelayeOn;
bit   FanOnOff;

uint8 HeaterMinute;
uint8 HeaterOffTime;
uint8 AutoAddTime=HEA_WAIT_TIME;
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void Heat3min(void)
{
  //----------------------
   HotDelayeOn     = 1;
  //----------------------
   HotOnOff        = 1;
   AutoAddTime     = 0;//STA_WAIT_TIME;		//3
   HeaterOffTime   = STA_HEA_TIME;		//0
   HeaterMinute    = 0;
  //----------------------
   FanOnOff = 0;
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void TsetHeat(void)
{
   HotOnOff       = 0;
   HeaterOffTime  = 0;
   HeaterMinute   = 0;
   //-----------------------
   AutoAddTime    = LOW_WAIT_TIME;
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void HeatCon( void )
{
   unsigned char  SetTcBuff;
   unsigned char  DataBuff;
   float          TfBuff;
   DigitalFiltering();
   //---------------------------
   if(GoErrCon&&Standby)
   {
   //HOT         = 0;
	 FAN         = 0;
	 MotDelayOff = 0;
	 HotDelayeOn = 0;
     return;
   }
   if(!Standby  || !HeaOnOff || ShowCon || ErrCon)//如果超温或待机关加热
   {
	 HOT      = 0;
     FanOnOff = 0;
	 HotOnOff = 0;
	 //------------------------------------------
	 HotDelayeOn = 0;//发热关，发热延迟开标志清零
	 //------------------------------------------
	 if(!MotDelayOff)
	 FAN      = 0;
   //-------------------------
     return;
   }
   SetTcBuff = SetTcTable[HeatGears];
   if(SetTcBuff  >= 60)
   SetTcBuff     = 60;
   else
   SetTcBuff = SetTcBuff + TEMP_ADJUST;//+5;//设置温度加3，是因炉内温度比室内温度高3度
   //-----------------------------------
   TfBuff = TempValue + TEMP_CONTROL_NEGATIVE;
   if(SetTcBuff >= TfBuff)//室温是设定温度的±1度,设定温度减1是让室温在±1度内
   {
     if(HotOnOff == 0)//低于设定温度的±1度,加热
     {
	   FanOnOff = 0;
	  //----------------------
       HotDelayeOn = 1;
      //----------------------
       HotOnOff    = 1;
       AutoAddTime = 0;
     }
     HeaterOffTime = 0;     //清除分钟计数器重新开始等待
     HeaterMinute  = 0;      //比如前面是以9分等待3分加热9+3=12在这期间温度下降到±1度以下
   }                      //跑到这里来执行就要12-3=9变为6分等待3分加热，清除计数让它重新
   else                   //计数，如果温度还没有恢复继续减3直到温度恢复
   {
      TfBuff = TempValue - TEMP_CONTROL_POSITIVE;
      if(SetTcBuff > TfBuff)
      {//到这里来说明我们的控制很好,温度以经达到适中(±1度内)
        if(HotOnOff == 1)
        {
          goto GoOutCon;
        }
      }
	  //-----------------
      if(HeaterSec)//如果一秒到了我们的加热与关加热等待延时将开始工作了
      {
        HeaterSec = 0;
        HeaterMinute++;
        if(HeaterMinute > 59)
        {
          HeaterMinute = 0;
          HeaterOffTime++;        //6,3, 3+3=6  6==6 ON HEAT
          DataBuff = HeaterOffTime + LOW_HEA_TIME;//
          if(DataBuff > AutoAddTime)
          {
			FanOnOff  = 1;
            HotOnOff  = 0;
            if(HeaterOffTime > AutoAddTime)//执行到这里说明温度一直都没降下来
            {								 //3 >= 6  != !> ->>>>-> 6 = 6 6+3=9  6分钟等待3分钟加热
              DataBuff = AutoAddTime + LOW_WAIT_TIME;//我们的延时将从3分钟等待，3分钟加热，6分钟等待3分钟加热以此累推。。。。。。
              if(DataBuff >= MAX_WAIT_TIME)
              DataBuff     = MAX_WAIT_TIME;  //直到103分钟不再加3
              AutoAddTime  = DataBuff;
	          FanOnOff     = 0;          //加热要关的
	          HeaterOffTime   = 0;      //清计数
	          HeaterMinute    = 0;
            }
          }
		}
	  }
   }
   GoOutCon:
   if(HotOnOff)
   {
  //-------------------------------
	 if(!HotDelayeOn)
	  HOT  = 1;
  //-------------------------------
	 FAN  = 1;
	 MotDelayOff=1;
   }else
   {
	 HOT  = 0;
	 if(!FanOnOff){
	   if(!MotDelayOff)
	    FAN  = 0;
     }else
	  FAN  = 1;
	 //------------------------------------------
	 HotDelayeOn = 0;//发热关，发热延迟开标志清零
	 //------------------------------------------
   }
}