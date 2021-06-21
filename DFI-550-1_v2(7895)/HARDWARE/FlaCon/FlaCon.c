/***********************************************************
*
************************************************************
*  日期:
*
*  作者:
*
************************************************************
*  硬件：  SH79F1622
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
//-------------------------------
#include "HARDWARE\include\SysInc.h"
//-------------------------------
////			        6.20   5.80   5.60   4.90   4.28   3.22   2.00  ms
//u16 FlaLumList[]={0xef40,0xf054,0xf0df,0xf2c3,0xf470,0xf74d,0xfa99};
//			       (2.00   3.20   4.30   4.80   5.00   5.80   6.00) ms	- 0.3MS
// u16 FlaLumList[]={0XFB68,0xf82A,0xf531,0xf3D8,0xf34D,0xf124,0xf054};
u16 FlaLumList[]={0XD827,0xBC07,0xA23E,0x968D,0x91D7,0x7F1A,0x780E};
bit FlaOutCon;

void FlaInit(void)
{
  //--------------------
//   P1M0 &=~Bin(00010000); //火焰
//   P1M1 |= Bin(00010000);
  	// P05CFG = GPIO_P05_MUX_AN5;
	// P11CFG = GPIO_MUX_GPIO;
	// P30CFG = GPIO_MUX_GPIO;
	// P12CFG = GPIO_MUX_GPIO;
	P22CFG = GPIO_MUX_GPIO;
	// P21CFG = GPIO_MUX_GPIO;
	// P20CFG = GPIO_MUX_GPIO;
	// P17CFG = GPIO_MUX_GPIO;//P06外部中断IR
	// P0TRIS = (P0TRIS & ~((1 << 5))) | ((0));
	// P1TRIS = (P1TRIS & ~((1 << 1) | (1 << 2))) | ((1 << 7));
	P2TRIS = (P2TRIS & ~(0)) | ((1 << 2));
	// P3TRIS = (P3TRIS & ~((1 << 0))) | (0);
  //--------------------
//   P3M0 &=~Bin(00000010); //反光马达
//   P3M1 |= Bin(00000010);
	// P24CFG = GPIO_MUX_GPIO;
	P25CFG = GPIO_MUX_GPIO;
	// P31CFG = GPIO_MUX_GPIO;
	// P04CFG = GPIO_MUX_GPIO;
	// P00CFG = GPIO_MUX_GPIO;
	// P01CFG = GPIO_MUX_GPIO;

	// P03CFG = GPIO_MUX_GPIO;
	// P0TRIS = (P0TRIS & ~((1 << 0) | (1 << 1) | (1 << 3) | (1 << 4))) | (0);
	// P1TRIS = (P1TRIS & ~((0))) | ((0));
	P2TRIS = (P2TRIS & ~(0)) | ((1 << 5));
	// P3TRIS = (P3TRIS & ~((1 << 1))) | ((0));
}

void FlaZoOn(void)
{
  u16 FlaLumBuf;
  FLA = 0;
  if(Standby)
  {
    FlaOutCon = 0;
    FlaLumBuf = FlaLumList[FlaGears];
	//--------
	ET1 = 0;
    TR1 = 0;
    TH1 = (u8)(FlaLumBuf>>8);
    TL1 = (u8)(FlaLumBuf);
    TR1 = 1;
	ET1 = 1;
	//--------
  }else
  {
	TR1 = 0;
	ET1 = 0;
  }
}

void FlaOff(void)
{
  if(!FlaOutCon)
  {
    FlaOutCon = 1;
	FLA = 1;
    TH1   = 0xe8;
	TL1   = 0x90;
  }else
  {
	TR1 = 0;
    FLA = 0;
  }
}
void FlaMotOut(void)
{
  if(Standby)
  {
    MOT = 1;
  }
  else
  {
    MOT = 0;
	FLA = 0;
  }
}
