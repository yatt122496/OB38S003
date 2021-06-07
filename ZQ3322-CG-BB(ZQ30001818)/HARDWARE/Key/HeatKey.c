/***********************************************************
*  文件说明：摇控程序
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
#include "HARDWARE\main\SysInc.h"
//----------------------------
bit   TcTf;
//bit   FirstHeat;
bit   HeatLock;
bit   HeatOnOff;
uint8 HeatGears;
//-------------
bit   TempSwCon;
//----------------------------
//uint8 code SetTcTable[]=
//{	//设置的温度档位
//	0,	//	OFF	//	0
//	18,	//	65 	//	1
//	21,	//	70 	//	2
//	24,	//	75 	//	3
//	27,	//	80 	//	4
//  29, //  85  //  5
//  32, //  90  //  6
//	40	//	ON	//	7
//};
////----------------------------
//uint8 code SetTfTable[]=
//{
//	0,	//	OFF //	0
//	65,	//	18 	//	1
//	70,	//	21 	//	2
//	75,	//	24 	//	3
//	80,	//	27 	//	4
//  85, //  29  //  5
//  90, //  32  //  6
//	104,//	on	//	7
//};
//----------------------------
uint8 code SetTfTable[28]=
{
//0    1   2   3   4   5   6   7   8   9
  0,  65, 66, 67, 68, 69, 70, 71, 72, 73,
//10  11  12  13  14  15  16  17  18  19
  74, 75, 76, 77, 78, 79, 80, 81, 82, 83,
//20  21  22  23  24  25  26  27  28  29
  84, 85, 86, 87, 88, 89, 90, 140
};
//----------------------------
uint8 code SetTcTable[28]=
{
//0   1   2   3   4   5   6   7   8   9
  0, 18, 19, 19, 20, 20, 21, 21, 22, 22,
//10 11  12  13  14  15  16  17  18  19,
 23, 24, 24, 25, 25, 26, 27, 27, 28, 28,
//20 21  22  23  24  25  26  27  28  29
 29, 29, 30, 30, 31, 31, 32, 60
};
//----------------------------
uint8 code Set5F_HeatGearList[8]=
{
  0,  //OFF    OFF    0
  1,  //18     65     1
  6,  //21     70     2
  11, //24     75     3
  16, //27     80     4
  21, //29     85     5
  26, //32     90     6
  27  //ON     0N     7
};
//-------------------------------------
uint8 code Set1F_HeatGearList[28]=
{
  0,  //OFF   0FF  y  0
  1,  //18    65      1
  1,  //19    66      2
  1,  //19    67      3
  2,  //20    68      4
  2,  //20    69      5
  2,  //21    70   y  6
  2,  //21    71      7
  2,  //22    72      8
  3,  //22    73      9
  3,  //23    74      10
  3,  //24    75   y  11
  3,  //24    76      12
  3,  //25    77      13
  4,  //25    78      14
  4,  //26    79      15
  4,  //27    80   y  16
  4,  //27    81      17
  4,  //28    82      18
  5,  //28    83      19
  5,  //29    84      20
  5,  //29    85   y  21
  5,  //30    86      22
  5,  //30    87      23
  6,  //31    88      24
  6,  //31    89      25
  6,  //32    90   y  26
  7   //on    on   y  27
};
//-------------------------------------
uint8 code Set1C_HeatGearList[17]=  //1C增加
{
  0,  //Off  0
  1,  //18   1
  2,  //19   2
  4,  //20   3
  6,  //21   4
  8,  //22   5
  10, //23   6
  11, //24   7
  13, //25   8
  15, //26   9
  16, //27   10
  19, //28   11
  20, //29   12
  22, //30   13
  24, //31   14
  26, //32   15
  27  //On   16
};
//-------------------------------------
uint8 code SetFC_HeatGearList[28]=   //1C增加 Set1CGears=HeatGears
{
//Set1CGears
   0, //Off  0
   1, //18   1
   2, //19   2
   2, //19   3
   3, //20   4
   3, //20   5
   4, //21   6
   4, //21   7
   5, //22   8
   5, //22   9
   6, //23   10
   7, //24   11
   7, //24   12
   8, //25   13
   8, //25   14
   9, //26   15
   10,//27   16
   10,//27   17
   11,//28   18
   11,//28   19
   12,//29   20
   12,//29   21
   13,//30   22
   13,//30   23
   14,//31   24
   14,//31   25
   15,//32   26
   16,//On   27
};
/************************************************************
*
* 		   设定温度显示
************************************************************/
void TempDisp(void)
{
  uint8  DataBuff;
  if(!HeatLock){
    if(HeatOnOff){
	  if(HeatGears == 27){
        DispDct1  = _H_;
	    DispDct2  = _I_;
      }else
  	  if(HeatGears){
	    if(TcTf){
		  DataBuff = SetTcTable[HeatGears];
//          DispDct3   = _C_;
	    }else{
		  DataBuff = SetTfTable[HeatGears];
//          DispDct3   = _F_;
	    }
        DispDct1   = DataBuff / 10;
		DispDct2   = DataBuff % 10;
	  }
	}else{
	  DispDct1   =  0;
	  DispDct2   = _F_;
//	  DispDct3   = _F_;
	}
//    if(TcTf){LedTc = 1;}
//    else    {LedTf = 1;}
	LedHea = 1;
  }
}
/************************************************************
* 函数名:
* 功能说明:  获得加热键状态
************************************************************/
//bit GainHeaterPsw(void)
//{
//   CancelAllFlash(1);
//   DispDataSet = &TempDisp;
//   if(HeatLock==1){
//	 LookFlhWood();
//	 KeyAct=K2_HEA;
//   } else
//   if(HeatOnOff==0)
//   HeatKey(0);
//   else
//   return 0;
//   return 1;
//}
/************************************************************
*
* 	加热档位宽度控制
************************************************************/
bit GearWidth1F_En;   //档位5F/2C 1F/1C
uint8 Set5FGears;
uint8 Set1CGears;

void GearsWidthKey(void)
{
 if(KeyAct & K2_HEA)
 {
   FunEndFlashSet();
   DispDataSet = &TempDisp;
   GearWidth1F_En = ~GearWidth1F_En;
   HeatGears   = Set5F_HeatGearList[Set5FGears];
   Set1CGears  = SetFC_HeatGearList[HeatGears];
//   BzSet();
 }
}
/************************************************************
*
* 			加热键
************************************************************/
//
void HeatKey(bit Opt)
{
  CancelAllFlash(1);
  if(!Standby){
    Standby = 1;
    KeyAct  = 0;
  }
  if(ErrCon || HeatLock){
    ErrDisIni();
    DispDataSet = &ErrDis;
    KeyAct  = 0;
    return;
  }
  DispDataSet = &TempDisp;
  if(Opt){
    if(!HeatOnOff)return;
  }
  if(KeyAct & K2_HEA || (!HeatOnOff)){
    HeatOnOff =1;
    if(GearWidth1F_En){
      if(TcTf){
        if(++Set1CGears > 16){
          if(!Opt){
			Set1CGears= 0;
			HeatOnOff = 0;
		  }else{
			Set1CGears= 1;
		  }
		}
         HeatGears = Set1C_HeatGearList[Set1CGears];
		 Set5FGears = Set1F_HeatGearList[HeatGears];
	  }else{
		 HeatOnOff =1;
	    if(++HeatGears > 27){
		  if(!Opt){
			HeatGears = 0;
			HeatOnOff = 0;
		  }else{
			HeatGears = 1;
		  }
        }
	    Set5FGears = Set1F_HeatGearList[HeatGears];
		Set1CGears  = SetFC_HeatGearList[HeatGears];
	  }
    }else{
	  if(++Set5FGears > 7){
	    if(!Opt){
		  Set5FGears = 0;
		  HeatOnOff = 0;
		}else{
		  Set5FGears = 1;
		}
	  }
	  HeatGears   = Set5F_HeatGearList[Set5FGears];
	  Set1CGears  = SetFC_HeatGearList[HeatGears];
	}
	HeaClr1min();
  }
  KeyAct = K2_HEA;
}
/************************************************************
*
*
************************************************************/
void HeaKey(void)
{
  if(!Standby){
    Standby = 1;
    KeyAct  = 0;
  }
  if(ErrCon || HeatLock){
    ErrDisIni();
    DispDataSet = &ErrDis;
    KeyAct  = 0;
    return;
  }
  //--------------
  DispDataSet = &TempDisp;
  if(!HeatGears){
    HeatGears = 1;
    Set5FGears = Set1F_HeatGearList[HeatGears];
    Set1CGears = SetFC_HeatGearList[HeatGears];
  }
  if(HeatOnOff){
    if(KeyAct & K2_HEA)
	{
	  HeatOnOff   = 0;
	  KeyAct     = 0;
	  return;
	}
  }else{
    HeatOnOff   = 1;
  }
  HeaClr1min();
  KeyAct = K2_HEA;
}
/************************************************************
*
*
************************************************************/
void CfDisp(void)
{
  if(TcTf){
    DispDct1 = _F_;
//    LedTf = 1;
  }else{
    DispDct1 = _C_;
//LedTc = 1;
  }
//  LedHea  = 1;
//  if(!HeatGears){
//    DispLed = 0;
//  }
  DispLed &= (~0x80);
}
/************************************************************
*
* 		   温度转换
************************************************************/
void TempSw( void )
{
//  TcTf   = ~TcTf;//加热锁了不能转换温度
  KeyAct = 0; //K2_HEA
  DispDataSet = &CfDisp;
  TempSwCon = 1;
}
/************************************************************
*
* 		   加热锁
************************************************************/
void HeatLook( void )
{
  HeatLock = ~HeatLock;
//  CancelAllFlash(1);
//  HeatTest    = 0;
  if(!HeatLock){
    KeyAct=K2_HEA;
	DispDataSet = &TempDisp;
//    BzSet();
  }else{
     ErrDisIni();
     DispDataSet = &ErrDis;
  }
}

uint8 FunSwCnt;
/************************************************************
*
*
************************************************************/
void HeaLockSw( void )
{
  if(ErrCon && (ErrCon != 3)){
    KeyAct  = 0;
    return;
  }
   FunSwCnt++;
   if(FunSwCnt == 1 && !HeatLock){ //
     TempSw();
   }else{
     if(FunSwCnt > 1){
       FunSwCnt = 0;
       HeatLook();
     }
   }
}
/************************************************************
*
*
************************************************************/
void HeaClrCnt(void)
{
  FunSwCnt = 0;
}