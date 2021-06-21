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
/*
   ("*********************************************\n");
   ("//�� Ŀ ��:680/681 MP3оƬ�ο�����\n");
   ("//����Ҫ��:\n");
   ("//Ӳ������:\n");
   ("//1) MCU�ͺ�: AT89C51\n");
   ("//2) �ڲ���Ƶ��Ϊ:11.0592MHz\n");
   ("//����汾:UART1: \n");
   ("//�� ˾ ��: �����ﴴ���ӿƼ����޹�˾\n");
   ("//��    ��: \n");
   ("//		Ӳ����\n");
   ("//		�����piao\n");
   ("//����֧�֣�E-mail:1677080092@qq.com\n");
   ("//����֧�֣�QQ:1677080092,�ֻ���15622277367\n");
   ("//�޸ļ�¼: 1��\n");
   ("//          2��\n");
   ("*********************************************\n");
*/
/*************************************************
*
*
*
*
*************************************************/
void EuartInit(void)
{
  #define ES1      1<<( 4 )
  #define BAUD  19200	   //�����ٶ�
  #define FOSC  8300000
  #define FD    12
  //	    bit7   bit6   bit5   bit4	bit3   bit2	  bit1   bit0
  //SCON    SM0    SM1    SM2    REN    TB8    TB8    TI     RI
  //SBUF
  //PCON1   SMOD   SSTAT   -- 	   --	  --	 --		--	   --
  //SADDR	SADDR7 SADDR6 SADDR5 SADDR4 SADDR3 SADDR2 SADDR1 SADDR0
  //SADEN	SADEN7 SADEN6 SADEN5 SADEN4 SADEN3 SADEN2 SADEN1 SADEN0
  //RXCON   --     --     --     --     --     --     RXCON1 RXCON0
	// PCON|=0X80;
	// SCON=0x40;/*SCON:ģʽ1,8-bitUART,*/
	// TMOD &= 0x0f;		//?????1???
	// TMOD |= 0x20;		//?????1?8???????
	// TL1 = 0xF7;		//??????
	// TH1 = 0xF7;		//????????
	// TR1=1;/*TR1:timer1run*/
	// ES0=1;/*�򿪴����ж�*/
}
bit SendOk;
void delay_us(u16 us)
{
	u16 y;
	for (y=0; y<us;y++);
}

void UART1_SendByte(u8 dat)
{
    // SendOk = 1;
    // SBUF = dat;
	// while(SendOk);
	u8 i = 0;

	VTX=0;		//!<��ʼλ
	delay_us(cVTX_Time);
	for(i = 0; i < 8; i++){
		if(dat & 0x01)
			VTX=1;
		else
			VTX=0;
		delay_us(cVTX_Time);
		dat >>= 1;
	}
	VTX=1;		//!<ֹͣλ
	delay_us(cVTX_Time);
}
/*********************************************************************************************
//������:void UART_SER(void)EUART
//
//����˵��:
//
//��ڲ���:NO
//
//���ڲ���:NO
***********************************************************************************************/
// void UART_SER(void)EUART//�����жϷ������
// {
// //	u8 Temp;//������ʱ����
// 	if(RI)//�ж��ǽ����жϲ���
// 	{
// 		RI=0;//��־λ����
// //		Temp=SBUF;//���뻺������ֵ
// //		P1=Temp;//��ֵ�����P1�ڣ����ڹ۲�
// //		SBUF=Temp;//�ѽ��յ���ֵ�ٷ��ص��Զ�
// 	}
// 	if(TI)//����Ƿ��ͱ�־λ������
//     {
// 	  TI=0;
//       SendOk = 0;
//     }
// }
u8  Vol;
bit NewVol;
u8  SendSize;
u8  MusicTime50ms;

u8 code VolList[]={0,10,20,25};
/*********************************************************************************************
//������:Specify_Volume()
//
//����˵��:ָ������
//
//��ڲ���:
//
//���ڲ���:NO
***********************************************************************************************/
void Specify_Volume(void)
{
  SendSize = 2;
  NewVol   = 1;
  MusicTime50ms = 0;
}

void VolKey(void)
{
  if(!Vol)
  SendSize = 2;
  else
  SendSize = 3;
  Vol++;
  if(Vol > 3)
  {
    Vol = 0;
	Music_stop();
  }else
  {
	 NewVol   = 1;
     MusicTime50ms = 0;
  }
  //Specify_Volume(Vol);
}

/*********************************************************************************************
//������:Music_stop()
//
//����˵��:ֹͣ
//
//��ڲ���:
//
//���ڲ���:NO
***********************************************************************************************/
void Music_stop()
{
  NewVol = 1;
}
void MusicCon(void)
{
  if(Standby && Vol)
  {
    if(NewVol)
	{
	  if(!MusicTime50ms)
	  {
		if(SendSize == 2 || SendSize == 3)
		{
		  SendSize = 0;
		  //-------------------
	      UART1_SendByte(0x7E);
	      UART1_SendByte(0x03);
	      UART1_SendByte(0x31);
	      UART1_SendByte(VolList[Vol]); //ָ������
	      UART1_SendByte(0xEF);
		  //-------------------
		  MusicTime50ms = 4;
		  if(SendSize == 3)
		  NewVol = 0;
		  else
		  SendSize = 1;
		}else
		if(SendSize == 1)
		{
		  UART1_SendByte(0x7E);
	      UART1_SendByte(0x02);
	      UART1_SendByte(0x01);
	      UART1_SendByte(0xEF);
		  NewVol = 0;
		  SendSize = 0;
		}
	  }
	}
  }else
  {
	if(NewVol)
	{
	  NewVol = 0;
	  if(!MusicTime50ms)
	  {
	    UART1_SendByte(0x7E);
	    UART1_SendByte(0x02);
	    UART1_SendByte(0x0E);
	    UART1_SendByte(0xEF);
	  }
	}
  }
}
void Cycle_play(u8 num)
{
	UART1_SendByte(0x7E);
	UART1_SendByte(0x03);
	UART1_SendByte(0x33);
	UART1_SendByte(num);
	UART1_SendByte(0xEF);
}
