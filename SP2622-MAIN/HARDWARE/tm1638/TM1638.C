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
#include "..\code\main\SysInc.h"
#include <INTRINS.H>

/************************************************************
*              TM1638配置
************************************************************/
#define  ON    1
#define  OFF   0
/******按键是否使用******/
#define  NOT_USE_KEY  ON
#define  DATA_SIZE    4
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
      DelayNop();
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
*函数名: TM1638_Init() 
*功能说明:初始化TM1638 
************************************************************/
void TM1638_Init( void )
{     
   STB=1;
   DelayNop(); 
   CLK=1;
   DelayNop(); 
   STB=1;
   DelayNop();
   DelayNop();
   WriteBit(0X03);
   STB=1;
   DelayNop();
   WriteBit(0X40);
   STB=1;
   DelayNop();
}
/************************************************************
*函数名: WriteTm1638Data() 
*功能说明:写显示数据到TM1638 
************************************************************/
void  WriteTm1638Data(uint8 Len,unsigned char *PData)
{
   unsigned char RxSize;
   DelayNop();
   WriteBit(0X03);
   STB=1;
   DelayNop();
   WriteBit(0X40);
   STB=1;
   DelayNop();
   WriteBit(0Xc0);
   for(RxSize=0;RxSize<Len;RxSize++){
     WriteBit(PData[RxSize]);//写入第0、1位数码管
     WriteBit(0);
   }
   STB=1; 
   DelayNop();     
   //-------------
   STB=1; 
   DelayNop();
   WriteBit(PData[RxSize]); //写入显示开关命令
   STB=1;
   DelayNop();   
}
/************************************************************/
#if NOT_USE_KEY //按键没有用可以屏蔽编译
/************************************************************
*函数名: ReadBit() 
*功能说明:向TM1638读一个字节
************************************************************/
unsigned char ReadBit( void )
{
   unsigned char com,i;         
   STB=0;
   DIO_PIN_IN();
   DelayNop();
   com=0;       
   for(i=0;i<8;i++)
   {
      com>>=1; 
	  CLK=0;	  
      DelayNop(); 	  
      if(DIO==1)
      com|=0x80;
      else
      com&=0x7f;      
	  DelayNop(); 
      CLK=1;
      DelayNop();          
   }     
   DIO_PIN_OUT();       
   return  com;          
}
/************************************************************
*函数名: ReadKdy() 
*功能说明:读按键值 
************************************************************/
void ReadKey(unsigned char *PKeyDat)
{ 
  WriteBit(0X42);
  DelayNop();
  DelayNop();   
  *PKeyDat=ReadBit();
  DelayNop();
  PKeyDat++;
  *PKeyDat=ReadBit();
  DelayNop();
//  PKeyDat++;
//  *PKeyDat=ReadBit();
//  DelayNop();
//  PKeyDat++;
//  *PKeyDat=ReadBit();
//  DelayNop();
//  PKeyDat++;
//  *PKeyDat=ReadBit();
//  DelayNop();
  STB=1;
}
/************************************************************/
#endif
/************************************************************/