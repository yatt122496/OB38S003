/***********************************************************
*
************************************************************
*  ÈÕÆÚ:
*
*  ×÷Õß:
*
************************************************************
*  Ó²¼þ£ºSH79F083
************************************************************
* ¡¾°æÈ¨¡¿ Copyright(C)ÅôÁÖµç×Ó
* ¡¾ÉùÃ÷¡¿
***********************************************************/
#include "HARDWARE/main/SysInc.h"
bit   TcTf;
uint8 code SetTcTable[] =
{//ÉèÖÃÉãÊÏÎÂ¶È
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
{//ÉèÖÃ»ªÊÏÎÂ¶È
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
	}else if(!HeatLock && HeaOnOff)//¼ÓÈÈËø´ò¿ª£¬ÇÒÎÂÏÔ±êÖ¾Î»1 £¬ÏÔÊ¾ÎÂ¶È
	{
		if(HeatGears >= 11)
		{
			DispDct1 = 0;//ÏÔÊ¾×Ö·û0
			DispDct2 = N;//ÏÔÊ¾×Ö·ûN
		}else if(HeatGears)//ÎÂ¶ÈµµÎ»²»Îª0
		{
			if(TcTf)//ÉãÊÏÎÂ±êÎª1 £¬ÏÔÊ¾ÉãÊÏÎÂ¶È
			{
				DispDct1 = SetTcTable[HeatGears] / 10;
				DispDct2 = SetTcTable[HeatGears] % 10;
			}
			else//ÉãÊÏÎÂ±êÎª0 £¬ÏÔÊ¾»ªÊÏÎÂ¶È
			{
			   	DispDct1 = SetTfTable[HeatGears] / 10;
				DispDct2 = SetTfTable[HeatGears] % 10;
			}
		}
//		if(!TempSwFah)
//		{
		  if(TcTf)//ÉãÊÏÎÂ±êÎª1 £¬ÏÔÊ¾ÉãÊÏÎÂ¶È
		  DispLed = 0X40;//ÉãÊÏÎÂ¶ÈÖ¸Ê¾µÆÁÁ
		  else
		  DispLed = 0X08;//»ªÊÏÎÂ¶ÈÖ¸Ê¾µÆÁÁ
//		}
	}
}
/************************************************************
* º¯ÊýÃû:
* ¹¦ÄÜËµÃ÷:  »ñµÃ¼ÓÈÈ¼ü×´Ì¬
************************************************************/
void GainHeaterPsw(void)
{
   if(!SetTemp)//²»ÔÚÎÂ¶ÈÉèÖÃ×´Ì¬
   HeatLockTimer = 0;//¼ÓÎÂËø¼ÆÊ±ÇåÁã
   if(ErrCon){
    SetTemp = 1; TempFlash = 1;
	KeyAct = K2_HEA;
	DispDataSet = &HeatDisp;
   }if(HeatLock)//¼ÓÈÈ¼üÔÚËø¶¨×´Ì¬
   {
	 LookFlhWood(1);//ÉÁË¸
	 KeyAct = K2_HEA;
   }
   else//¼ÓÈÈ¼ü²»ÔÚËø¶¨×´Ì¬
   {
	 if(HeaOnOff)//ÎÂÏÔ±êÖ¾Î»1 £¬ÏÔÊ¾ÎÂ¶È
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
   DispDataSet = &HeatDisp;//ÎÂ¶È¼ü°´ÏÂ£¬ÏÔÊ¾ÎÂ¶È
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
  DispDataSet = &HeatDisp;//ÎÂ¶È¼ü°´ÏÂ£¬ÏÔÊ¾ÎÂ¶È

  if(ErrCon){
	SetTemp = 1;TempFlash = 1;
	KeyAct = K2_HEA;//¼¤»î¼ÓÈÈ£¬ÏÔÊ¾
    return;
  }
  //------------------------------
  if(HeatLock)//¼ÓÈÈËøËø¶¨
  {
    LookFlhWood(1);//ÉÁË¸
	KeyAct = K2_HEA;//¼¤»î¼ÓÈÈ£¬ÏÔÊ¾
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
* º¯ÊýÃû: UpKey()
* ¹¦ÄÜËµÃ÷:  °´¼üµ÷ÓÃ
************************************************************/
void HeatSetAndLook( void )
{
  HeatLockTimer++;
  if(HeaOnOff && !HeatLock && (HeatLockTimer == 1))
  {
    SetTemp    = 1;//ÎÂ¶ÈÉèÖÃ±êÖ¾ÖÃ1
	TempFlash  = 1;
	KeyAct = K2_HEA;//¼¤»î¼ÓÈÈ£¬ÏÔÊ
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
*				ÎÂ¶È×ª»»
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