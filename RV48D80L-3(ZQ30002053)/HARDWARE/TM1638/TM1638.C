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
#include "HARDWARE/main/SysInc.h"

/************************************************************
*              TM1638配置
************************************************************/
#define  ON    1
#define  OFF   0
/******按键是否使用******/
#define  DISP_MODE    0x02
#define  WRITE_DISP   0x40 //设置为地址加1模式
#define  DISP_ADDR    0xc2 //第一位数码管显示地址
#define  READ_KEY     0x42
//
#define  NOT_USE_KEY  ON
#define  DATA_SIZE    3
/************************************************************
*              TM1638程序
/
/************************************************************
*函数名: DelayNop()
*功能说明:显示延时
************************************************************/
void  DelayNop( void )
{
   unsigned char i;
   i=5;
   while( i-- )
   {
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();
   }
}
/************************************************************
*函数名: TM1638_Init()
*功能说明:初始化TM1638
************************************************************/
void TM1638_Init( void )
{
   STB=1;
   DelayNop();
   CLK=1;
   DelayNop();
}
/************************************************************
*函数名: WriteBit()
*功能说明:向TM1638写一个字节
************************************************************/
void  WriteBit(unsigned char com)
{
   unsigned char i;
   STB=0;
   DelayNop();
   for(i=0;i<8;i++)
   {
      CLK=0;
//    DelayNop();
      if(com & 0x01)
      DIO=1;
      else
      DIO=0;
      com=com>>1;
      DelayNop();
      CLK=1;
      DelayNop();
   }
}

/************************************************************
*函数名: WriteTm1638Data()
*功能说明:写显示数据到TM1638
************************************************************/
void  WriteTm1638Data(unsigned char *PData)
{
   unsigned char RxSize;
   DelayNop();
   WriteBit(DISP_MODE);
   STB=1;
   DelayNop();
   WriteBit(WRITE_DISP);
   STB=1;
   DelayNop();
   //写第一位数码管显示地址
   WriteBit(DISP_ADDR);
   DelayNop();
   //写第一位数码管显示数据
   for(RxSize=0;RxSize<DATA_SIZE;RxSize++)
   {
     WriteBit(*PData);
	 WriteBit(0);
     PData++;
   }
   STB=1;
   DelayNop();
   WriteBit(*PData);
   STB=1;
   DelayNop();
}
