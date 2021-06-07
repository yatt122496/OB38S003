/***********************************************************
*  TM1638驱动
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
//-------------------------------
bit   TM1638KeyTimer;
uint8 UpKeyDat;
uint8 TM1638KeyValue;
//-------------------------------
//uint8 bdata KeyBuf;
//sbit  KeyBufBit1 = KeyBuf^0;
//sbit  KeyBufBit2 = KeyBuf^1;
//sbit  KeyBufBit3 = KeyBuf^2;
//sbit  KeyBufBit4 = KeyBuf^3;
//sbit  KeyBufBit5 = KeyBuf^4;
//sbit  KeyBufBit6 = KeyBuf^5;
//sbit  KeyBufBit7 = KeyBuf^6;
//sbit  KeyBufBit8 = KeyBuf^7;
////-------------------------------
//uint8 bdata KeyDat;
//sbit  K1 = KeyDat^0;
//sbit  K2 = KeyDat^1;
//sbit  K3 = KeyDat^2;
//sbit  K4 = KeyDat^3;
//sbit  K5 = KeyDat^4;
//sbit  K6 = KeyDat^5;
//sbit  K7 = KeyDat^6;
//sbit  K8 = KeyDat^7;
////---------------------
/***********************************************************
*
*			K1
*
*  SEG1		POW
*  SEG2		FLA
*  SEG3     HEA
*  SEG4     TIM
*  SEG5
*  SEG6
*  SEG7
*  SEG8
***********************************************************/
u8 KeyCnt;
unsigned char GainTM1638KeyValue(void)
{
  u8 KeyDat;
//  if(TM1638KeyTimer){TM1638KeyTimer  = 0;
//**********************************************
  KeyDat = PcbKeyValue;
//**********************************************
    if(KeyDat){
	  if(UpKeyDat != KeyDat){
	     UpKeyDat = KeyDat;
//         if(KeyCnt > 2)KeyCnt-= 2;
//         else          KeyCnt = 0;
      }else{
//        if(++KeyCnt > 3){
          switch(KeyDat){
	        case 0x01: KeyDat = 5;break;  //POW
	        case 0x02: KeyDat = 4;break;  //HEA  TempSwFlashTimerCon=0;
	        case 0x04: KeyDat = 3;ClrErrTmr();break;  //TIM
	        case 0x08: KeyDat = 2;break;  //FLA
            case 0x10: KeyDat = 1;break;  //FLA
	        default  : TM1638KeyValue = 0xff; KeyDat = 0;break;
          }
	      if((!TM1638KeyValue) || (KeyDat == TM1638KeyValue)){
		    TM1638KeyValue = KeyDat;
	      }else{
		    TM1638KeyValue= 0xff;
	      }
	    }
//	  }
	}else{
	  UpKeyDat      = 0;
	  //--------------
	  TM1638KeyValue= 0;
	}
//  }
  return TM1638KeyValue;
}