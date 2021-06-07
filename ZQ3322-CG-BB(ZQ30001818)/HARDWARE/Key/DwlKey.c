/***********************************************************
*  文件说明：
************************************************************
*  日期:
*
*  作者:
*
************************************************************
*  硬件：sh79f083a
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\main\SysInc.h"

#if (DWL_EN==1)

	u8   TestCon;
	bit  DwlGears;

	void DwlDisp(void)
	{
	  if(!DwlGears){
		DispDct1   =  0;
		DispDct2   = _F_;
//		DispDct3   = _F_;
	  }else{
		DispDct1   =  0 ;
		DispDct2   = _N_;
	  }
	}

	void DwlKey(void)
	{
	  if(!Standby){
		Standby = 1;
		KeyAct  = 0;
	  }
	  DispDataSet = &DwlDisp;
	  if(DwlGears){
		if(KeyAct & K2_DWL){
		  DwlGears = 0;
		}
	  }else{
		DwlGears = 1;
	  }
	  KeyAct = K2_DWL;
	}

	void DwlCon(void)
	{
	  if(DwlGears && Standby){
		DWL = 1;
	  }else{
		DWL = 0;
	  }
	}

	void TestEnter(void)
	{
	  if(ErrCon){
		return;
	  }
	  if(TestCon != 0x55){
		TestClrMin();
	  }
	  TestCon = 0x55;
	}

#endif
