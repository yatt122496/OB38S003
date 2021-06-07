#include "HARDWARE/main/SysInc.h"

/***************************************************
*
*
*
****************************************************/
u8 code LumConst[7]=
{
  200,  //常亮
  100,   //微微亮
  40,   //高亮
  40,
  0
};
u8 code SpeedList1[]={33,26,18,18};
//u8 code SpeedList2[]={50,40,30,30};
/***************************************************
*
*		火焰
*
****************************************************/
u8 idata FlaTimer;       //亮度控制
u8 idata FlaTimerOn;
//---------------------
u8 idata FlaOnTimer;
u8 idata FlaAutoGears;
//
bit FlaAutoOffCon;
bit FlaAddDecSwap;
u8 idata FlaAutoTimer;
u8 idata FlaAutoOffSet;
u8 idata FlaAutoTimerOff;
u8 idata FlaOn1ms;
//---------------------
void FlaSpeedInit(void)
{
  EA = 0;
  FLA_Y = 0;
  FLA_B = 0;
  FlaAutoGears = 0;
  FlaAddDecSwap= 0;
  FlaAutoOffSet= 5;
  EA = 1;
}
/***************************************************
*
*	    底灰
*
****************************************************/
u8 idata DowTimer;       //亮度控制
u8 idata DowTimerOn;
u8 idata DowTimerOn1;
//---------------------
u8 idata DowOnTimer;
u8 idata DowAutoGears;
//
bit DowAutoOffCon;
bit DowAddDecSwap;
u8 idata DowAutoTimer;
u8 idata DowAutoOffSet;
u8 idata DowAutoOffSet1;
u8 idata DowAutoTimerOff;
u8 idata DowOn1ms;
//---------------------
bit DowGAutoOffCon;
bit DowGAddDecSwap;
u8 idata DowGOnTimer;
u8 idata DowGAutoTimer;
u8 idata DowGAutoOffSet;
u8 idata DowGAutoOffSet1;
u8 idata DowGAutoTimerOff;
//---------------------
void DowSpeedInit(void)
{
  EA = 0;
  DOW_R = 0;
  DOW_B = 0;
  DOW_G = 0;
  DowAutoGears = 0;
  DowAddDecSwap= 0;
  DowAutoOffSet= 5;
  EA = 1;
}
//---------------------
void DowGAutoInit(void)
{
  EA = 0;
  DOW_R = 0;
  DOW_B = 0;
  DOW_G = 0;
  DowGAddDecSwap= 0;
  DowGAutoOffSet= 5;
  EA = 1;

}
/***************************************************
*
*
*
****************************************************/
u8 bdata Led;
sbit  Led1 = Led^0;
sbit  Led2 = Led^1;
sbit  Led3 = Led^2;

u8 code ColourList[]   = {0x00,0X01,0X02,0X04,0X03,0X05,0x06,0x07,0x07};
u8 code DowColourLst[] = {0x00,0X05,0X02,0X04,0X03,0X05,0x06,0x07,0x07};
/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void LedAutoCon(void)
{
  if(!Standby)return;
  if((FlaGears==FLA_MAX) || ShowOnCon){
    if(++FlaAutoTimer > SpeedList1[0]){FlaAutoTimer=0; //
       if(!FlaAddDecSwap){
	     if(FlaAutoOffSet++ > 199)
		   FlaAddDecSwap = 1;
	   }else{
	     if(FlaAutoOffSet > 5)FlaAutoOffSet--;
	     else{
	       FlaAddDecSwap=0;
	       FlaAutoGears++;
	  	   if(FlaAutoGears > FLA_AU_MAX)
	 	   FlaAutoGears    = 0;
	     }
	  }
	}
  }
  //----------------------------------------------------------
  if((DowGears==DOW_MAX) || ShowOnCon){
     if(++DowAutoTimer > SpeedList1[0]){DowAutoTimer=0; //
        if(!DowAddDecSwap){
	      if(DowAutoOffSet++ > 199)
		    DowAddDecSwap = 1;
	    }else{
	      if(DowAutoOffSet > 5)DowAutoOffSet--;
	      else{
	        DowAddDecSwap=0;
	        DowAutoGears++;
	  	    if(DowAutoGears > DOW_AU_MAX)
	 	    DowAutoGears    = 0;
	      }
	    }
	   DowAutoOffSet1=DowAutoOffSet/10;
	}
  }
  //-----------------------------------------------------------
  if(DowGears == 1){
     if(++DowGAutoTimer > SpeedList1[2]){DowGAutoTimer=0; //
        if(!DowGAddDecSwap){
	      if(DowGAutoOffSet++ > 199)
		    DowGAddDecSwap = 1;
	    }else{
	      if(DowGAutoOffSet > 5)DowGAutoOffSet--;
	      else{
	        DowGAddDecSwap=0;
	      }
	    }
	  DowGAutoOffSet1=DowGAutoOffSet/10;
	}
  }
}
/***************************************************
*
*
*
****************************************************/
void LedTimeroff(void)  interrupt TMR1_VECTOR//50us
{
	TH1 = (d_MODEVALUE_T1 - d_RELOADVALUE_T1) >> 8;
	TL1 = (d_MODEVALUE_T1 - d_RELOADVALUE_T1);
	//------------------------------
	if (!Standby)
	{
		MOT = 0; //反光马达
		FLA_Y = 0;
		FLA_B = 0;
		FLA_R = 0; //火焰
		DOW_R = 0;
		DOW_B = 0;
		DOW_G = 0; //底灰
		return;
	}
	if ((FlaGears && !ShowOnCon) || ShowOnCon)
	{
		MOT = 1;
		if ((FlaGears != FLA_MAX) && !ShowOnCon)
		{
			if (++FlaTimer > 199)
			{
				FlaTimer = 0;
				Led = ColourList[FlaGears];
				FLA_Y = Led1;
				FLA_B = Led2;
				FLA_R = Led3;
#if (LUM_EN == 1)
				FlaTimerOn = LumConst[FlaLum];
#else
				FlaTimerOn = 200;
#endif
			}
			if (FlaTimerOn != 200)
			{
				if (FlaTimerOn)
					FlaTimerOn--;
				else
				{
					FLA_Y = 0;
					FLA_B = 0;
					FLA_R = 0; //火焰
				}
			}
		}
	}
	else //档位为0
	{
		MOT = 0;
		FLA_Y = 0;
		FLA_B = 0;
		FLA_R = 0; //火焰
	}
	if (DowGears || (!FlaGears && !DowGears && HeaOnOff && !HeatLock) || ShowOnCon)
	{
		if ((DowGears != DOW_MAX) && (DowGears != 1) && !ShowOnCon)
		{
			if (++DowTimer > 199)
			{
				DowTimer = 0;
				if (!FlaGears && !DowGears && HeaOnOff && !HeatLock)
				{
					DOW_R = 1;
					DowTimerOn = LumConst[2];
				}
				else
				{
					Led = DowColourLst[DowGears - 1];
					DOW_R = Led1;
					DOW_B = Led2;
					DOW_G = Led3;
#if (LUM_EN == 1)
					DowTimerOn = LumConst[DowLum];
#else
					DowTimerOn = 200;
#endif
					if (DowGears == 2)
						DowTimerOn1 = DowTimerOn / 10;
					else
						DowTimerOn1 = DowTimerOn;
				}
			}
			//-----------------------------------------
			if (DowTimerOn != 200)
			{
				if (DowTimerOn)
					DowTimerOn--;
				else
				{
					DOW_R = 0;
					DOW_B = 0;
					DOW_G = 0;
				}
			}
			if (DowTimerOn1 != 200)
			{
				if (DowTimerOn1)
					DowTimerOn1--;
				else
				{
					DOW_G = 0;
				}
			}
		}
	}
	else
	{ //档位为0
		DOW_R = 0;
		DOW_B = 0;
		DOW_G = 0;
	}
	//-----------------
	if ((FlaGears == FLA_MAX) || ShowOnCon)
	{
		if (++FlaOnTimer > 205)
		{
			FlaOnTimer = 0;
			Led = ColourList[FlaAutoGears + 1];
			FLA_Y = Led1;
			FLA_B = Led2;
			FLA_R = Led3;
			FlaAutoOffCon = 1;
		}
		if (FlaAutoOffCon)
		{
			if (++FlaAutoTimerOff > FlaAutoOffSet)
			{
				FlaAutoTimerOff = 0;
				FlaAutoOffCon = 0;
				FLA_Y = 0;
				FLA_B = 0;
				FLA_R = 0; //火焰
			}
		}
	}
	else
	{
		FlaAddDecSwap = 0;
		FlaAutoOffSet = 0;
	}
	//-------------------------------------------------------
	if ((DowGears == DOW_MAX) || ShowOnCon)
	{
		if (++DowOnTimer > 205)
		{
			DowOnTimer = 0;
			Led = DowColourLst[DowAutoGears + 1];
			DOW_R = Led1;
			DOW_B = Led2;
			DOW_G = Led3;
			DowAutoOffCon = 1;
		}
		if (DowAutoOffCon)
		{
			if (++DowAutoTimerOff > DowAutoOffSet)
			{
				DowAutoTimerOff = 0;
				DowAutoOffCon = 0;
				DOW_R = 0;
				DOW_B = 0;
				DOW_G = 0;
			}
			//--------------------------------
			if (!DowAutoGears)
			{
				if (DowAutoTimerOff > DowAutoOffSet1)
				{
					DOW_G = 0;
				}
			}
		}
	}
	else
	{
		DowAddDecSwap = 0;
		DowAutoOffSet = 0;
	}
	//--------------------------------------
	if ((DowGears == 1) && !ShowOnCon)
	{
		if (++DowGOnTimer > 205)
		{
			DowGOnTimer = 0;
			DOW_R = 1;
			DOW_B = 0;
			DOW_G = 1;
			DowGAutoOffCon = 1;
		}
		if (DowGAutoOffCon)
		{
			if (++DowGAutoTimerOff > DowGAutoOffSet)
			{
				DowGAutoTimerOff = 0;
				DowGAutoOffCon = 0;
				DOW_R = 0;
				DOW_B = 0;
				DOW_G = 0;
			}
			if (DowGAutoTimerOff > DowGAutoOffSet1)
			{
				DOW_G = 0;
			}
		}
	}
	else
	{
		DowGAutoOffCon = 0;
		DowGAutoOffSet = 0;
	}
	//--------------------------------------
	if (LockWoodFalsh)
	{ //--150MS闪烁低灰
		if (!DowGears)
		{
			if (!DOW_R && !DOW_B && !DOW_G)
				DOW_B = 1;
		}
	}
	else if (LockWoodCon)
	{
		DOW_R = 0;
		DOW_B = 0;
		DOW_G = 0;
	}
}
