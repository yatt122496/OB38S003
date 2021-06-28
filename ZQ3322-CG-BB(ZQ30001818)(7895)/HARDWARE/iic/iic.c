/***********************************************************
*  Main.c
************************************************************
*  ����:2011.12.22 19:55
*
*  ����:  cuoiszf
*
************************************************************
*  Ӳ����AT89S52
************************************************************
* ����Ȩ�� Copyright(C)cuoiszf
* ��������
***********************************************************/
#include "HARDWARE/main/SysInc.h"
//--------------------------
/************************************************************
*������: DelayNop()
*����˵��:��ʾ��ʱ
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
*I2C��ʼ
*************************************************************/
void IicStart()
{
   SDA=1;
   SCL=1;      //   SDA ~~~~\___/~~~~~
   DelayNop(); //  	SCL ~~~~~~\______
   SDA=0;	//��SCLΪ�ߵ�ƽ�ڼ�SDA�ϳ��ָߵ�ƽ,������I2C����
   DelayNop();	//����ֹͣ�ڼ�ʱ��SCL���ǵ͵�ƽ,�����ǹرյ�
   DelayNop();
   SCL=0;
   DelayNop();
}
/************************************************************
*iic_stop
*I2Cֹͣ
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

//***��Ӧ�����Send_NoAck����
/************************************************************
          Send_NoAck����
����˵����������Ϊ���շ���
              ������Ϊ���ͷ������ͷ�Ӧ���źš�
************************************************************/
void TxNoAck(void)
{
  SDA=1;            //����������
  DelayNop();
  SCL=1;            //ʱ��������
  DelayNop();
  SCL=0;           //ʱ���߷���һ�δӸߵ͵����� û��Ӧ��
  DelayNop();
}
/************************************************************
          TxAck����
����˵����������Ϊ���շ���
              ������Ϊ���ͷ�������Ӧ���źš�
************************************************************/
void TxAck(void)
{
  SDA=0;            //����������
  DelayNop();
  SCL=1;            //ʱ��������
  DelayNop();
  SCL=0;           //ʱ���߷���һ�δӸߵ͵����� û��Ӧ��
  DelayNop();
}
/************************************************************
          Send_NoAck����
����˵����������Ϊ���շ���
              ������Ϊ���ͷ������ͷ�Ӧ���źš�
************************************************************/
//*****Ӧ�����ӳ��� CACK_flg()
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
  RetAck=1;  //��SDA=1������Ӧ����λ��Ӧ���־
  else
  RetAck=0;
  SCL=0;
  DelayNop();
  SDA_PIN_OUT();
  return RetAck;
}
/*----------------------------------------------------------------------
IIC_ReceiveByte ()  ����˵������I2C���߽�������
----------------------------------------------------------------------*/
u8 IicRxByte (void)
{
  unsigned char i,dat;
  SDA=1;        //����������
  SDA_PIN_IN();
  dat=0;
  for(i=0;i<8;i++)
  {
    dat <<=1;              //��������һλ
    SCL=0;                 //ʱ��������
    DelayNop();
    SCL=1;                 //ʱ����һ�δӵ͵��ߵ����䣬���Խ�������
    DelayNop();
    if(SDA)
    dat|= 0x01;
    else
    dat&=~0x01;
  }
  SCL=0;                  //����ʱ����Ϊ�ͣ��������������ݴ�������������ȴ�״̬
  SDA_PIN_OUT();
  DelayNop();
  return dat;          //���ؽ��յ���һ���ֽڵ�����
}
//*void IIC_SendByte() ����˵������IIC���߷�������**********

void IicTxByte(unsigned char RxData)
{
  unsigned char i=8;
  while (i--)
  {
    SCL=0;                     //ʱ�ӱ��ֵͿ��Է�������
    DelayNop();
    if(RxData&0x80)
    SDA=1;  //�����������λ
    else
    SDA=0;
    RxData <<=1;
    DelayNop();
    SCL=1;                     //��־һ��λ�������
    DelayNop();
  }                              //һ���ֽ����ݷ������
  SCL=0;             //����ʱ����Ϊ�ͣ��������������ݴ�������������ȴ�״̬
}
/////��IIC����������ָ����ַ��ʼдָ�����ȵ�����IIC_write_lendata()*******
//u8 IicDriverExamine(u8 Driver)
//{
//  u8 ReturnExamine;
//  IicStart();				 		    //���·���IIC�����ź�
//  IicTxByte (Driver);			    //��������������
//  ReturnExamine = 1;
//  if(RxAck()==0)				     	//���Ӧ���ź�
//  ReturnExamine = 0;
//  TxNoAck();
//  IicStop();
//  return (ReturnExamine);
//}
//**********��IIC����������ָ����ַ��ָ�����ȵ�����IIC_read_lendata()***
u8 IicReadLenData (u8 Driver,u8 len,u8 *ptr)
{
    //----------------------
    if(len > 8)
    return  0;
    //----------------------
	IicStart();				 		    //���·���IIC�����ź�
	IicTxByte (Driver | READ);			    //��������������
	if(RxAck()==0)				     	//���Ӧ���ź�
	{
	  IicStop();
	  return  0;
	}

	for(;len>1;len--)					//��������LEN-1���ȵ��ֽ�����
	{
	  *ptr = IicRxByte ();
	  ptr++;
	  TxAck ();					    //����Ӧ���ź�
	}
	*ptr = IicRxByte ();
	TxNoAck();						    //	���ͷ�Ӧ���ź�
	IicStop();							//	����IICֹͣ�ź�
	return 1;
}
//��IIC����������ָ����ַ��ʼдָ�����ȵ�����IIC_write_lendata()*******
/************************************************************
*
*
***********************************************************/
u8 IicWriteLenData(u8 Driver,u8 len,u8 *ptr)
{
    if(len>8)
    return  0;
    //----------
    IicStart();				 	    //����IIC START�ź�
	//----------------
	IicTxByte(Driver);				//	���������ӵ�ַ
	if(RxAck()==0)					//	���Ӧ���ź�
	{
	  IicStop();
	  return  0;
	}
	//----------------
	for(;len>0;len--)					//	��������LEN���ȵ��ֽ�����
	{
	  IicTxByte(*ptr);
	  ptr++;
	  if(RxAck()==0)					//	���Ӧ���ź�
	  {
	    IicStop();
	    return  0;
	  }
	}
	IicStop();							//	����IIC STOP�ź�
	return 1;
}
/*
u8 IicWriteData(u8 Driver,unsigned char ptr)
{
    IicStart();				 			//	����IIC START�ź�
	IicTxByte(Driver);				 	//	���������ӵ�ַ
	if(RxAck()==0)					//	���Ӧ���ź�
	{
	  IicStop();
	  return  0;
	}
//	for(;len>0;len--)					//	��������LEN���ȵ��ֽ�����
//	{
	IicTxByte (ptr);
	ptr++;
	if(RxAck()==0)					//	���Ӧ���ź�
	{
	  IicStop();
	  return  0;
	}
//	}
	IicStop();							//	����IIC STOP�ź�
	return 1;
}
*/
void IicInit(void)
{
  //---------
  IicStop();
}