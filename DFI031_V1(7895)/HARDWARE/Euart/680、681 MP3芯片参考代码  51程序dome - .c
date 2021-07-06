/*("/*********************************************/\n");
("//项 目 名:680/681 MP3芯片参考代码\n");
("//功能要求:\n");
("//硬件配置:\n");
("//1) MCU型号: AT89C51\n");
("//2) 内部振荡频率为:11.0592MHz\n");
("//软件版本:UART1: \n");
("//公 司 名: 广州语创电子科技有限公司\n");
("//作    者: \n");
("//		硬件：\n");
("//		软件：piao\n");
("//技术支持：E-mail:1677080092@qq.com\n");
("//技术支持：QQ:1677080092,手机：15622277367\n");
("//修改记录: 1）\n");
("//          2）\n");
("/*********************************************/\n");*/
#include<REG52.H>/*主程序*/

void UART1_Init(void)
{
	SCON=0x50;/*SCON:模式1,8-bitUART,使能接收*/
	TMOD=0x20;/*TMOD:timer1,mode2,8-bitreload*/
	TH1=0xFD;/*TH1:reloadvaluefor9600baud@11.0592MHz*/
	TL1=0XFD;
	TR1=1;/*TR1:timer1run*/
	EA=1;/*打开总中断*/
	ES=1;/*打开串口中断*/
}

void UART1_SendByte(u8 dat)
{
//    while(!TI);
    SBUF = dat;
//    asm("nop");
}

void UART_SER(void)interrupt4//串行中断服务程序
{
	unsignedcharTemp;//定义临时变量
	if(RI)//判断是接收中断产生
	{
		RI=0;//标志位清零
		Temp=SBUF;//读入缓冲区的值
		P1=Temp;//把值输出到P1口，用于观察
		SBUF=Temp;//把接收到的值再发回电脑端
	}
	if(TI)//如果是发送标志位，清零
	TI=0;
}

/**
  * @brief Delay
  * @param nCount
  * @retval None
  */
void Delay(u16 nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}
void Delay_long(u16 nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    Delay(0xffff);
	nCount--;
  }
}
/*********************************************************************************************
//函数名:Next_Play()
//
//功能说明:设定音量
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Next_Play()
{
	UART1_SendByte(0x7E); 
	UART1_SendByte(0x02);
	UART1_SendByte(0x03);
	UART1_SendByte(0xEF); 
}

/*********************************************************************************************
//函数名:Last_Play()
//
//功能说明:
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Last_Play()
{
	UART1_SendByte(0x7E); 
	UART1_SendByte(0x02);
	UART1_SendByte(0x04);
	UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//函数名:Specify_Musi_Play()
//
//功能说明:指定曲目播放
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Specify_Musi_Play(u8 num)
{
	UART1_SendByte(0x7E); 
	UART1_SendByte(0x04);
	UART1_SendByte(0x41);
	UART1_SendByte(0x00);
	UART1_SendByte(num);
	UART1_SendByte(0xEF); 
}

/*********************************************************************************************
//函数名:Volume_add()
//
//功能说明:音量加
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Volume_add()
{
	UART1_SendByte(0x7E); 
	UART1_SendByte(0x02);
	UART1_SendByte(0x05);
	UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//函数名:Volume_nec()
//
//功能说明:音量减
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Volume_nec()
{
	UART1_SendByte(0x7E); 
	UART1_SendByte(0x02);
	UART1_SendByte(0x06);
	UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//函数名:Specify_Volume()
//
//功能说明:指定音量
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Specify_Volume(u8 num)
{
	UART1_SendByte(0x7E); 
	UART1_SendByte(0x03);
	UART1_SendByte(0x31);
	UART1_SendByte(num);
	UART1_SendByte(0xEF); 
}


/*********************************************************************************************
//函数名:Music_play()
//
//功能说明:播放
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Music_play()
{
	UART1_SendByte(0x7E); 
	UART1_SendByte(0x02);
	UART1_SendByte(0x01);
	UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//函数名:Music_pause()
//
//功能说明:暂停
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Music_pause()
{
	UART1_SendByte(0x7E); 
	UART1_SendByte(0x02);
	UART1_SendByte(0x02);
	UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//函数名:Music_stop()
//
//功能说明:停止
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Music_stop()
{
	UART1_SendByte(0x7E); 
	UART1_SendByte(0x02);
	UART1_SendByte(0x0E);
	UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//函数名:Cycle_play()
//
//功能说明:1:全部循环 0:单曲循环
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Cycle_play(u8 num)
{
	UART1_SendByte(0x7E); 
	UART1_SendByte(0x03);
	UART1_SendByte(0x33);
	UART1_SendByte(num);
	UART1_SendByte(0xEF); 
}
 
/**
  * @brief Delay
  * @param nCount
  * @retval None
  */
void Delay(u16 nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}
void Delay_long(u16 nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    Delay(0xffff);
	nCount--;
  }
}


void main(void)
{
	UART1_Init() ;
	
	Switch_play_Device(1);//转到TF卡
	Delay_long(12);  
	Next_Play();
	Delay_long(12);
	Cycle_play(1);//全部循环
	while(1);
}
