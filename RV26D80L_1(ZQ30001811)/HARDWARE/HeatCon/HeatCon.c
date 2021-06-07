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
#define   TEMP_ADJUST               1.5	/* 温度补尝，  4℃  4*1.8=7.2    (7) ℉ */
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
#define   HEA_WAIT_TIME    6   /* 加热等待时间  */
/*	 以下数据是根据最低等待时间算出，开加热加热3分钟，后从最低等待时间开始工作  */
#define   STA_WAIT_TIME	   LOW_WAIT_TIME            	/* 开始等待                        */
#define   STA_HEA_TIME	   LOW_WAIT_TIME-LOW_HEA_TIME	/* 开始加热时间                    */

bit   HotOnOff;
bit   MotDelayOff;
bit   HotDelayeOn;
bit   TempFallSubWait;

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
   HotDelayeOn       = 1;
  //----------------------
   HotOnOff           = 1;
   TempFallSubWait    = 1;
   AutoAddTime        = STA_WAIT_TIME;		//3
   HeaterOffTime      = STA_HEA_TIME;		//0
   HeaterMinute       = 0;
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void TsetHeat(void)
{
   HotOnOff       = 0;
   TempFallSubWait= 0;
   HeaterOffTime  = 0;
   HeaterMinute   = 0;
   //-----------------------
   AutoAddTime    = HEA_WAIT_TIME;	//6
}
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void HeatCon( void )
{
   unsigned char  DataBuff;
   float  TfBuff;
   float  SetTcBuff;
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
   if(!Standby || !HeaOnOff || ErrCon)//如果超温或待机关加热
   {
	 HOT      = 0;
	 HotOnOff = 0;
	 //------------------------------------------
	 HotDelayeOn = 0;//发热关，发热延迟开标志清零
	 //------------------------------------------
	 if(!MotDelayOff)
	 FAN      = 0;
   //-------------------------
     return;
   }
   SetTcBuff = (float)SetTcTable[HeatGears];
   if(SetTcBuff  >= 60)
   SetTcBuff     = 60;
   else
   if(SetTcBuff <= 20)
   SetTcBuff = SetTcBuff + TEMP_ADJUST;////+5;//设置温度加3，是因炉内温度比室内温度高3度
   //-----------------------------------
   TfBuff = TempValue + TEMP_CONTROL_NEGATIVE;
   if(SetTcBuff >= TfBuff)//室温是设定温度的±1度,设定温度减1是让室温在±1度内
   {
     if(HotOnOff == 0)//低于设定温度的±1度,加热
     {
	  //----------------------
       HotDelayeOn       = 1;
      //----------------------
       HotOnOff    = 1;
       AutoAddTime = HEA_WAIT_TIME;//6 将从3分钟加热3分钟等待开始
     }
     if(TempFallSubWait == 1)//执行到这里是因为温度到了适中的边境,
     {                 //或者在等待过程中温度降低，以递减3来恢复温度
       TempFallSubWait = 0;
       DataBuff = HeaterOffTime + LOW_HEA_TIME;	 //3
       if(DataBuff > AutoAddTime)
       {
         DataBuff = AutoAddTime - LOW_HEA_TIME;
         if(DataBuff <= HEA_WAIT_TIME)
         DataBuff     = HEA_WAIT_TIME;	//6
         AutoAddTime  = DataBuff;
       }
     }      //等待计时失效
     HeaterOffTime = 0;     //清除分钟计数器重新开始等待
     HeaterMinute  = 0;      //比如前面是以9分等待3分加热9+3=12在这期间温度下降到±1度以下
   }                      //跑到这里来执行就要12-3=9变为6分等待3分加热，清除计数让它重新
   else                   //计数，如果温度还没有恢复继续减3直到温度恢复
   {
      TfBuff = TempValue - TEMP_CONTROL_POSITIVE;
      if(SetTcBuff <= TfBuff)
      {    //设定温度低于室温了
        if(HotOnOff == 1)//是这样我们应该关闭加热
        {
          if(TempFallSubWait == 0)
		  {
            HotOnOff            = 0;
		    //------------------------------
		    if(AutoAddTime <= STA_WAIT_TIME)		//3
		    AutoAddTime     = HEA_WAIT_TIME;		//6
		    //------------------------------
		  }
        }
      }
      else
      {//到这里来说明我们的控制很好,温度以经达到适中(±1度内)
        if(HotOnOff == 1)
        {
          if(TempFallSubWait == 0)//这时如果加热是开的,那么就让它继续加热
          goto GoOutCon;
        }
        else
        AutoAddTime = 12;//HEA_WAIT_TIME;//15在温度低于±1度内时,将以12分钟的等待
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
          DataBuff = HeaterOffTime + LOW_HEA_TIME;
          if(DataBuff >= AutoAddTime)
          {
            TempFallSubWait = 1;
		   //----------------------
            HotDelayeOn       = 1;
           //----------------------
            HotOnOff        = 1;
            if(HeaterOffTime >= AutoAddTime)//执行到这里说明温度一直都没降下来
            {								 //3 >= 6  != !> ->>>>-> 6 = 6 6+3=9  6分钟等待3分钟加热
              DataBuff = AutoAddTime + LOW_HEA_TIME;//我们的延时将从3分钟等待，3分钟加热，6分钟等待3分钟加热以此累推。。。。。。
              if(DataBuff >= MAX_WAIT_TIME)
              DataBuff     = MAX_WAIT_TIME;           //直到103分钟不再加3
              AutoAddTime     = DataBuff;
	          HotOnOff        = 0;           //加热要关的
	          TempFallSubWait = 0;       //温度下降控制也是要关的
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
	 if(!MotDelayOff)
	 FAN  = 0;
	 //------------------------------------------
	 HotDelayeOn = 0;//发热关，发热延迟开标志清零
	 //------------------------------------------
   }
}