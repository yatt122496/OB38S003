/***********************************************************
*
************************************************************
*  日期:
*
*  作者:  cuoiszf
*
************************************************************
*  硬件：MCS51
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\main\SysInc.h"
//--------------------------
#define   S1      2
#define   S2      1
#define   S3      0
#define   LED     3
//#define   LED1    1
//#define   LED2    2

/*************************************************************
*		       S3       S2     S1  LED1
*
*             COM1    COM2    COM3    COM3    COM4    COM5
*
*     SEGA     B       B       B      0x01  0
*     SEGB     F       F       F      0x02  1
*     SEGC 	   A       A       A      0x04  2
*     SEGD 	   E	   E       E      0X08  3
*     SEGE 	   D       D       D      0x10  4
*     SEGF 	   C       C       C      0x20  5
*     SEGG 	   G       G       G      0x40  6
*     SEGP 	   :                      0x80  7
*
*
*     LED     TIM    0X01    HEA    0X10
*	          DWL    0X02    FOC    0X20
*	  	      SD     0X04    FMT    0X40
*             POW    0X08    FLA    0X80
*
*************************************************************/
#define  A  0X04
#define  B  0X01
#define  C  0X20
#define  D  0X10
#define  E  0X08
#define  F  0X02
#define  G  0X40
//
//--------------------------
//               A B C D E F G
#define  SEG_0 	(A|B|C|D|E|F|0)//0
#define  SEG_1 	(0|B|C|0|0|0|0)//1			A
#define  SEG_2 	(A|B|0|D|E|0|G)//2     ==========
#define  SEG_3 	(A|B|C|D|0|0|G)//3    ||        ||
#define  SEG_4 	(0|B|C|0|0|F|G)//4	 F ||        ||	B
#define  SEG_5 	(A|0|C|D|0|F|G)//5	   ||   G    ||
#define  SEG_6 	(A|0|C|D|E|F|G)//6		==========
#define  SEG_7 	(A|B|C|0|0|0|0)//7	   ||		 ||
#define  SEG_8 	(A|B|C|D|E|F|G)//8	 E ||		 ||	C
#define  SEG_9 	(A|B|C|D|0|F|G)//9	   ||		 ||
#define  SEG_A 	(A|B|C|0|E|F|G)//10	==========
#define  SEG_B 	(0|0|C|D|E|F|G)//11	    D
#define  SEG_C 	(A|0|0|D|E|F|0)//12
#define  SEG_D 	(0|B|C|D|E|0|G)//13
#define  SEG_E 	(A|0|0|D|E|F|G)//14
#define  SEG_F 	(A|0|0|0|E|F|G)//15
#define  OFF_0 	(0|0|0|0|0|0|0)//16
#define  SEG_h 	(0|0|C|0|E|F|G)//17
#define  SEG_N 	(A|B|C|0|E|F|0)//18
#define  SEG_I 	(0|0|0|0|E|F|0)//19
#define  SEG_H 	(0|B|C|0|E|F|G)//20
//--------------------------
//--------------------------
//数码管代码表
unsigned char code LedDispCode[]=
{
  SEG_0,
  SEG_1,
  SEG_2,
  SEG_3,
  SEG_4,
  SEG_5,
  SEG_6,
  SEG_7,
  SEG_8,
  SEG_9,
  SEG_A,
  SEG_B,
  SEG_C,
  SEG_D,
  SEG_E,
  SEG_F,
  OFF_0,
  SEG_h,
  SEG_N,
  SEG_I,
  SEG_H
};

uint8       DispDct1;
uint8       DispDct2;
uint8       DispDct3;
uint8 bdata DispLed;

sbit LedPow= DispLed^1;
sbit LedFla= DispLed^0;
//
sbit LedHea= DispLed^2;
sbit LedTc = DispLed^4;
sbit LedTf = DispLed^5;
//
sbit LedTmr= DispLed^3;
sbit LedSec= DispLed^7;
//
//uint8 DispLed1;
void (*DispDataSet)();
//--------------------------
uint8 DispSensFreq;
//--------------------------
uint8 HidTimer;
uint8 SlowlyHidden;
//--------------------------
uint16 CancelErrTimer;
//--------------------------
bit BiGuangCon;
/************************************************************
*
* 功能说明: 清显示
************************************************************/
void ClrDisp(void)
{
  DispDct1 =  DISP_OFF;
  DispDct2 =  DISP_OFF;
  DispDct3 =  DISP_OFF;
//  DispDct4 =  DISP_OFF;
  DispLed  =  0;
//  DispLed1 =  0;
}
/************************************************************
*
* 功能说明:  显示初始化
************************************************************/
void DispInit(void)
{
  DispDataSet = &ClrDisp;
}
//u8 TxDispTmr;

uint8 PcbKeyValue;
uint8 IicErrTim;
//----------------------
uint8 CompoundKeyCnt;

//----------------------
/************************************************************
*
* 功能说明:  显示
************************************************************/
void Disp( void )
{
  unsigned char DispBuff[6],Dat;
  if(DispSensFreq==0){
	  DispSensFreq=2;
	//--------------------------
    ClrDisp();
	//--------------------------
	DispBuff[0]	= 0;
	DispBuff[1]	= 0;
	DispBuff[2]	= 0;
	DispBuff[3]	= 0;
	DispBuff[4]	= 0;
	DispBuff[5]	= 0;
	//-----------------
#if (DWL_EN==1)
	if(DispDataSet != ClrDisp   && DispDataSet != PowerDisp && DispDataSet != FlaDisp &&
	   DispDataSet != TempDisp  && DispDataSet != TimDisp   && DispDataSet != DispTempValue &&
       DispDataSet != ErrDis    && DispDataSet != CfDisp    && DispDataSet != DwlDisp)
#else
	if(DispDataSet != ClrDisp   && DispDataSet != PowerDisp && DispDataSet != FlaDisp &&
	   DispDataSet != TempDisp  && DispDataSet != TimDisp   && DispDataSet != DispTempValue &&
       DispDataSet != ErrDis    && DispDataSet != CfDisp )
#endif
	{
	  DispDataSet = &ClrDisp;
	}
	//--------------------------
    if(FunEndFlash==0)DispDataSet();
	//--------------------------
    if(Hidden){
	  DispBuff[S1] = LedDispCode[DispDct1];if(DispLed& 0x80){DispBuff[S1] |= 0x80;}
	  DispBuff[S2] = LedDispCode[DispDct2];
	  DispBuff[S3] = LedDispCode[DispDct3];
      SlowlyHidden = 7;
	}else{
      KeyAct       = 0;
      DispDataSet  = ClrDisp;
      SlowlyHidden = 0;
    }
    if(BiGuangCon){
      SlowlyHidden = 7;
      DispBuff[LED]=0xff;
    }
//    if(SlowlyHidden)
    DispBuff[4] = ((SlowlyHidden<<4)|0X01);
//    else
//    DispBuff[4] = 1;
//    DispBuff[0]= 0XFF;
//    DispBuff[1]= 0XFF;
//    DispBuff[2]= 0XFF;
//    DispBuff[3]= 0XFF;
//    DispBuff[4]= 0X71;
    //--------------------------
    DispBuff[5] = DispBuff[0]+DispBuff[1]+DispBuff[2]+DispBuff[3]+DispBuff[4];
	IicWriteLenData(0xAA,6,&DispBuff[0]);
    //-------------------------------
   //--
  //--	  读按键
 //--
//-----------------------------------
	if(IicReadLenData(0xAA,3,&DispBuff[0])){
	  Dat = DispBuff[0];
	  if((Dat == ~DispBuff[1]) && (DispBuff[2]==0xa5)){
	    IicErrTim = 0;
		if(Dat){
		  switch(Dat){
			case 0x01:Dat = 5;break;
			case 0x02:Dat = 4;break;
			case 0x04:Dat = 3;break;
		    case 0x08:Dat = 2;break;
            case 0x10:Dat = 1;break;
			case 0x06:Dat = 6;break;
			default:  break;
		  }
		  //-----------------------------------------------
		  if(!PcbKeyValue || (Dat == PcbKeyValue)){//此键确定被按下
			  if(Dat==3 || Dat==4){
			   if(++CompoundKeyCnt > 3){
				CompoundKeyCnt = 3;
				PcbKeyValue = Dat;
			    if(Dat == 3)ClrErrTmr();
			   }
			  }else{
			   CompoundKeyCnt = 0;
			   PcbKeyValue = Dat;
              }
		  }else{
			PcbKeyValue =  0xff;
		  }//-------
		}else{
		  PcbKeyValue = 0;
		//------------------------
		  CompoundKeyCnt = 0;
	    //------------------------
		}
	  }else
	  goto IicErr;
	}else{
	  IicErr:
	  if(++IicErrTim > 4){IicErrTim   = 0;
        PcbKeyValue =  0xff;//告诉按键处理程序,去错了
	  }
	}
  }
}