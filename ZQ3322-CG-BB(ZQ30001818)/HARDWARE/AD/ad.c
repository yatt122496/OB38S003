/***********************************************************
*
************************************************************
*  日期:
*
*  作者:
*
************************************************************
*  硬件：
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\main\SysInc.h"
//;**************************************************/
#define FIXED_R1     18
#define REFERENCE_R  25
#define _0C_R        273
#define AD_MAX       1024
#define B25_50       3990

#define    AL  10
bit     AdReady;
float   TempValue;
//-----------------------------
uint8  AdTimes;
uint8  SensorTimes;
uint16 AdBuff;
uint16 idata ArrayADC[AL];
//-----------------------------
uint8 ErrCnt;

bit NtcErr;
/************************************************************
* 函数名: AD滤波
* 功能说明:
************************************************************/
void AdNtc( void )
{
  unsigned char        i,j;
  float        DatBuf;
  unsigned int   NtcAdValue;
  if(AdNtcNew)
  {
    AdNtcNew = 0;
    //------------------
	EA = 0;
    AdBuff  += AdNtcValue;
	EA = 1;
	//------------------
    AdTimes++;
    if(AdTimes >= 5)
    {
      AdTimes    = 0;
	  //------------------
	  ArrayADC[SensorTimes] = AdBuff / 5;
      AdBuff     = 0;
	  //------------------
	  SensorTimes++;
	  if(SensorTimes > 9)
	  {
	    SensorTimes = 0;
		//------------------
	    for( i=0;i<AL-1;i++)
	    {
		  for(j=i+1;j<AL;j++)
		  {
			if(ArrayADC[i]  > ArrayADC[j])
			{
			  NtcAdValue  = ArrayADC[i];
			  ArrayADC[i] = ArrayADC[j];
			  ArrayADC[j] = NtcAdValue;
			}
		  }
	    }
		NtcAdValue = 0;
		//------------------
	    for(i=1;i<=AL-2;i++)
	    {
		  NtcAdValue += ArrayADC[i];
	    }
	    NtcAdValue >>= 3;
		//------------------
        if((NtcAdValue > 979) || (NtcAdValue < 43)){
          if(++ErrCnt > 5){ErrCnt = 5;
            NtcErr = 1;
          }
        }else{
          if(ErrCnt > 2){
            ErrCnt-=2;
          }else{
            ErrCnt = 0;
            NtcErr = 0;
          }
        }
	    //------------------
	    if(NtcAdValue < 1)
	    DatBuf    = 1;
	    else
        DatBuf    = NtcAdValue;
	    //------------------
        DatBuf    = (float)(((AD_MAX -  DatBuf) * FIXED_R1) / DatBuf);
        DatBuf    = (B25_50 / (log(DatBuf / 50) * (REFERENCE_R + _0C_R ) + B25_50)) * (REFERENCE_R + _0C_R) - _0C_R;
	    TempValue = DatBuf;
		//------------------
	    if(TempValue < 0)
        TempValue    = 0;
	    else
	    if(TempValue > 110)
	    TempValue    = 110;
		//------------------
		AdReady      = 1;
	  }
    }
  }
}