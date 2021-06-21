/***********************************************************
*
************************************************************
*  日期:2015-1-8 13:37
*
*  作者:
*
************************************************************
*  硬件：  SH79F084A
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#include "HARDWARE\include\SysInc.h"
//--------------------
unsigned char IrValue;
//
bit IrTimerCon;
unsigned int IrLockTimerCon;
//
bit            IrLock;
bit            IrLeadOk;
unsigned char  IrDtat;
unsigned char  IrTimer;
unsigned char  IrTimer1;
unsigned char  BitIndex;
//
#define   IR_KEY_SIZE   4

unsigned char code BitIndexList[6]={0x00,0x01,0x03,0x06,0x0D,0x1B};
u8 code IrKeyCode[IR_KEY_SIZE]={0x81,0x90,0x88,0X84};
u8 code IrKeyValue          []={  1 ,  2 ,  3 ,  4 };
/************************************************************
* 函数名: UpKey()
* 功能说明:  按键调用
************************************************************/
#if IR_TEST
xdata u8 bData[40] = {0}, bAD_indx = 0;
#endif
void IrInt( void )
{
  unsigned char IrTimerBuff;
  unsigned char IrTimerBuff1;
  if (0x02 == (P30EICFG&0x02))
  P30EICFG = 0x01;
  else
  P30EICFG = 0x02;
  //
  if ((0x01 == (P30EICFG&0x01))||(BitIndex==11))
  {
    IrTimerCon = 0;
    IrTimerBuff=IrTimer;
	IrTimerBuff1=IrTimer1;
    IrTimer=0;
	IrTimer1=0;
    IrTimerCon  = 1;
#if IR_TEST
	bData[bAD_indx] = IrTimerBuff;
	bAD_indx++;
	if (bAD_indx > 39) {
		bAD_indx--;
	}
#endif
	if(IrLeadOk==0)
	{
	  IrLeadOk=1;
	  BitIndex=0;
	  IrDtat=0;
	  return;
	}
	else
	{
	  BitIndex++;
	  if(IrTimerBuff>30)
	  IrDtat|=0x01;
	  else
	  {
	    if((BitIndex>=12)||(IrTimerBuff1>30))
	    IrDtat&=0xfe;
	    else
	    goto  IrError;
	  }
	}
	if(BitIndex<5)	//5位控制码
	{
	  if(IrDtat!=BitIndexList[BitIndex])
	  {
	    IrError:
        IrLeadOk=0;
        IrDtat=0;
        // EXF0 = Bin(00000100);
		P30EICFG = 0x02;		//配置为下降沿触发
		return;
	  }
	}
	if(BitIndex==12)
	{
	   IrTimerBuff=0;
	   do
	   {
	   	 if(IrDtat==IrKeyCode[IrTimerBuff])
		 {
		   if(IrLock==0)
		   {
		     IrValue=IrKeyValue[IrTimerBuff];
		     IrLock=1;
		   }
		   IrLockTimerCon  = 0;
		   break;
		 }
		 IrTimerBuff++;
	   }while(IrTimerBuff < IR_KEY_SIZE);
	   goto IrError;
	}
	IrDtat<<=1;
  }
}
/************************************************************
* 函数名: UpKey()
* 功能说明:  按键调用
************************************************************/
void IrCnt( void )    // 200US
{
   if(IrTimerCon)
   {
     if (0x01 == (P30EICFG&0x01))
     IrTimer++;
     else
     IrTimer1++;
	 if ((IrTimer1 > 100) || (IrTimer > 100))
	 {
	   IrLeadOk=0;
	   BitIndex=0;
   	   IrTimer1=0;
	   IrTimer=0;
       P30EICFG = 0x02;	 //下降沿
	   IrTimerCon = 0;
	 }
   }
   IrLockTimerCon++;
   if(IrLockTimerCon > 5000)	   //100MS
   {
	   IrLockTimerCon = 0;
	   IrValue=0;
	   IrLock=0;
   }
}