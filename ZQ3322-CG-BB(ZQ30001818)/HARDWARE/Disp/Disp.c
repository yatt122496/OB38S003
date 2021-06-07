/***********************************************************
*
************************************************************
*  ����:
*
*  ����:  cuoiszf
*
************************************************************
*  Ӳ����MCS51
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE\main\SysInc.h"
//--------------------------
#define S1     2
#define S2     3
#define LED    0
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
#define  A  0x04
#define  B  0x08
#define  C  0x10
#define  D  0x40
#define  E  0x20
#define  F  0x02
#define  G  0X01
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
//����ܴ����
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
uint8 bdata DispLed;

sbit LedPow= DispLed^1;
sbit LedFla= DispLed^0;
//
sbit LedHea= DispLed^2;
//
sbit LedTmr= DispLed^3;
//
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
//-------------------------
uint8 DispBuf[5];
/************************************************************
*
* ����˵��: ����ʾ
************************************************************/
void ClrDisp(void)
{
  DispDct1 =  DISP_OFF;
  DispDct2 =  DISP_OFF;
//  DispDct3 =  DISP_OFF;
//  DispDct4 =  DISP_OFF;
  DispLed  =  0;
//  DispLed1 =  0;
}
/************************************************************
*
* ����˵��:  ��ʾ��ʼ��
************************************************************/
void DispInit(void)
{
  DispDataSet = &ClrDisp;
}
/************************************************************
*
* ����˵��:  ��ʾ
************************************************************/
void Disp( void )
{
  if(DispSensFreq==0){DispSensFreq=2;
	//--------------------------
    ClrDisp();
	//--------------------------
	DispBuf[0]	= 0;
	DispBuf[1]	= 0;
	DispBuf[2]	= 0;
	DispBuf[3]	= 0;
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
	  DispBuf[S1] = LedDispCode[DispDct1];
	  DispBuf[S2] = LedDispCode[DispDct2];
      SlowlyHidden = 0x8A;
	}else{
      KeyAct       = 0;
      DispDataSet  = ClrDisp;
      SlowlyHidden = 0;
    }
    if(BiGuangCon){
	  DispBuf[LED]=0xff;
      SlowlyHidden = 0x8A;
    }
	DispBuf[4]  = SlowlyHidden;
    //--------------------------
	WriteTm1638Data(&DispBuf[0]);
  }
}