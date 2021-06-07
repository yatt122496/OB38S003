/***********************************************************
*  Main.c
************************************************************
*  日期:2011.12.22 19:55
*
*  作者:  cuoiszf
*
************************************************************
*  硬件：AT89S52
************************************************************
* 【版权】 Copyright(C)cuoiszf
* 【声明】
***********************************************************/
#include "HARDWARE/main/SysInc.h"
//--------------------------
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
*iic_start
*I2C开始
*************************************************************/
void IicStart()
{
   SDA=1;
   SCL=1;      //   SDA ~~~~\___/~~~~~
   DelayNop(); //  	SCL ~~~~~~\______
   SDA=0;	//在SCL为高电平期间SDA上出现高电平,则启动I2C总线
   DelayNop();	//由于停止期间时钟SCL上是低电平,总线是关闭的
   DelayNop();
   SCL=0;
   DelayNop();
}
/************************************************************
*iic_stop
*I2C停止
*************************************************************/
void IicStop()
{
   SDA=0;
   SCL=0;
   DelayNop();	   //SDA ______/~~~~~~
   SCL=1;		   //SCL ____/~~~~~~~~
   DelayNop();
   DelayNop();
   SDA=1;
   DelayNop();
}

//***无应答程序Send_NoAck（）
/************************************************************
          Send_NoAck（）
函数说明：主器件为接收方，
              从器件为发送方，发送非应答信号。
************************************************************/
void TxNoAck(void)
{
  SDA=1;            //数据线拉高
  DelayNop();
  SCL=1;            //时钟线拉高
  DelayNop();
  SCL=0;           //时钟线发生一次从高低的跳变 没有应答
  DelayNop();
}
/************************************************************
          TxAck（）
函数说明：主器件为接收方，
              从器件为发送方，发送应答信号。
************************************************************/
void TxAck(void)
{
  SDA=0;            //数据线拉高
  DelayNop();
  SCL=1;            //时钟线拉高
  DelayNop();
  SCL=0;           //时钟线发生一次从高低的跳变 没有应答
  DelayNop();
}
/************************************************************
          Send_NoAck（）
函数说明：主器件为接收方，
              从器件为发送方，发送非应答信号。
************************************************************/
//*****应答检查子程序 CACK_flg()
u8 RxAck(void)
{
  u8 RetAck;
  SDA = 1;
  SDA_PIN_IN();
  DelayNop();
  DelayNop();
  SCL=1;
  DelayNop();
  if(SDA==0)
  RetAck=1;  //若SDA=1表明无应答，置位无应答标志
  else
  RetAck=0;
  SCL=0;
  DelayNop();
  SDA_PIN_OUT();
  return RetAck;
}
/*----------------------------------------------------------------------
IIC_ReceiveByte ()  函数说明：从I2C总线接受数据
----------------------------------------------------------------------*/
u8 IicRxByte (void)
{
  unsigned char i,dat;
  SDA=1;        //数据线拉高
  SDA_PIN_IN();
  dat=0;
  for(i=0;i<8;i++)
  {
    dat <<=1;              //数据左移一位
    SCL=0;                 //时钟线拉低
    DelayNop();
    SCL=1;                 //时钟做一次从低到高的跳变，可以接收数据
    DelayNop();
    if(SDA)
    dat|= 0x01;
    else
    dat&=~0x01;
  }
  SCL=0;                  //保持时钟线为低，从器件进行数据处理，主器件进入等待状态
  SDA_PIN_OUT();
  DelayNop();
  return dat;          //返回接收到的一个字节的数据
}
//*void IIC_SendByte() 函数说明：向IIC总线发送数据**********

void IicTxByte(unsigned char RxData)
{
  unsigned char i=8;
  while (i--)
  {
    SCL=0;                     //时钟保持低可以发送数据
    DelayNop();
    if(RxData&0x80)
    SDA=1;  //发送数据最高位
    else
    SDA=0;
    RxData <<=1;
    DelayNop();
    SCL=1;                     //标志一个位发送完毕
    DelayNop();
  }                              //一个字节数据发送完毕
  SCL=0;             //保持时钟线为低，从器件进行数据处理，主器件进入等待状态
}
/////往IIC总线上器件指定地址开始写指定长度的数据IIC_write_lendata()*******
//u8 IicDriverExamine(u8 Driver)
//{
//  u8 ReturnExamine;
//  IicStart();				 		    //重新发送IIC启动信号
//  IicTxByte (Driver);			    //发送器件读命令
//  ReturnExamine = 1;
//  if(RxAck()==0)				     	//检测应答信号
//  ReturnExamine = 0;
//  TxNoAck();
//  IicStop();
//  return (ReturnExamine);
//}
//**********从IIC总线上器件指定地址读指定长度的数据IIC_read_lendata()***
u8 IicReadLenData (u8 Driver,u8 len,u8 *ptr)
{
    //----------------------
    if(len > 8)
    return  0;
    //----------------------
	IicStart();				 		    //重新发送IIC启动信号
	IicTxByte (Driver | READ);			    //发送器件读命令
	if(RxAck()==0)				     	//检测应答信号
	{
	  IicStop();
	  return  0;
	}

	for(;len>1;len--)					//连续接收LEN-1长度的字节数据
	{
	  *ptr = IicRxByte ();
	  ptr++;
	  TxAck ();					    //发送应答信号
	}
	*ptr = IicRxByte ();
	TxNoAck();						    //	发送非应答信号
	IicStop();							//	发送IIC停止信号
	return 1;
}
//往IIC总线上器件指定地址开始写指定长度的数据IIC_write_lendata()*******
/************************************************************
*
*
***********************************************************/
u8 IicWriteLenData(u8 Driver,u8 len,u8 *ptr)
{
    if(len>8)
    return  0;
    //----------
    IicStart();				 	    //发送IIC START信号
	//----------------
	IicTxByte(Driver);				//	发送器件从地址
	if(RxAck()==0)					//	检测应答信号
	{
	  IicStop();
	  return  0;
	}
	//----------------
	for(;len>0;len--)					//	连续发送LEN长度的字节数据
	{
	  IicTxByte(*ptr);
	  ptr++;
	  if(RxAck()==0)					//	检测应答信号
	  {
	    IicStop();
	    return  0;
	  }
	}
	IicStop();							//	发送IIC STOP信号
	return 1;
}
/*
u8 IicWriteData(u8 Driver,unsigned char ptr)
{
    IicStart();				 			//	发送IIC START信号
	IicTxByte(Driver);				 	//	发送器件从地址
	if(RxAck()==0)					//	检测应答信号
	{
	  IicStop();
	  return  0;
	}
//	for(;len>0;len--)					//	连续发送LEN长度的字节数据
//	{
	IicTxByte (ptr);
	ptr++;
	if(RxAck()==0)					//	检测应答信号
	{
	  IicStop();
	  return  0;
	}
//	}
	IicStop();							//	发送IIC STOP信号
	return 1;
}
*/
void IicInit(void)
{
  //---------
  IicStop();
}