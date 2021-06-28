/***********************************************************
*  �ļ�˵����
************************************************************
*  ����:
*
*  ����:
*
************************************************************
*  Ӳ����sh79f083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE\main\SysInc.h"

uint8 FlaOn,FlaOff;
uint8 DotOn,DotOff;

//---------------------------------
unsigned char code FlameLumConst[]=
{
  0, //��
  2, //΢�� 1
  4, //���� 2
  6, //���� 3
  8, //΢�� 4
  10,//���� 5
  10,//����
  0
};

//---------------------------------
unsigned char code DotLumCon[]=
{
  0, //��
  4, //΢�� 1
  4, //���� 2
  6, //���� 3
  8, //΢�� 4
  8, //���� 5
  8, //����
  0
};
/************************************************************
* ������:
* ����˵��:
************************************************************/
void FlaCon( void )  //1ms
{
  if(!Standby){
	FOT = 0;
	MOT = 0;
	DOT = 0;
	DOT1= 0;
  }else{
	//-------------------
	if(FlaGears > FLA_MAX)
	FlaGears    = FLA_MAX;
	//-------------------
    if(FlaGears){
      MOT = 1;
      if(!FlaOn && !FlaOff){
         FlaOn = FlameLumConst[FlaGears];
         FlaOff = 10 - FlaOn;
      }
      if(!DotOn && !DotOff){
         DotOn = DotLumCon[FlaGears];
         DotOff = 10 - DotOn;
      }
      if(FlaOn ){FlaOn--; FOT = 1;}else
      if(FlaOff){FlaOff--;FOT = 0;}
    }else{
      //
      FOT = 0;
      MOT = 0;
//	  DOT = 0;
      FlaOn = 0;FlaOff = 0;
      //
      if(!DotOn && !DotOff){
        DotOn = 2;DotOff = 8;
      }
    }
    if(DotOn ){DotOn--; DOT = 1;DOT1 = 1;}else
    if(DotOff){DotOff--;DOT = 0;DOT1 = 0;}
  }
}