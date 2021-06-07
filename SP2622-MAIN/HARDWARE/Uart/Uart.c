/***********************************************************
*  文件名:                                              
************************************************************
*  日期:   
*  	                                                                                                                                            
*  作者:                                                                                             
*  功能说明：
*                                                    
************************************************************
*  硬件：                                               
************************************************************
* 【版权】 Copyright(C)鹏林电子                           
* 【声明】                                
***********************************************************/
#include "..\code\main\SysInc.h"

u8 idata TxDatTim;

// 串口初始化
//void UartInit(void)		
//{
//	PCON &= 0x7f;		//使能波特率倍速位SMOD
//	SCON = 0x50;		//8位数据,可变波特率
//	TMOD &= 0x0F;		//清除定时器1模式位
//	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
//	TL1 = 0xe6;		//设定定时初值
//	TH1 = 0xe6;		//设定定时器重装值
//	ET1 = 0;		//禁止定时器1中断
//	TR1 = 1;		//启动定时器1 		
//	ES0 = 1;
//}
bit LeOk;
bit RxLead;
//bit RxOk;
//bit RxNewDat;
u8 idata RxIdx;
u8 idata RxBuf[20];
u8 idata RxSize; 
//

bit TxNewDat;
bit TxLead;
u8 idata TxSize; 
u8 idata TxIdx;
u8 idata TxBuf[16];
//=============================================================================
// 串口中断部分
//=============================================================================
u8 TxSetDat(u8 Len,u8 *pDat)
{
  u8 n,Sun,Dat;
//  if(!TxLead){
    TxNewDat = 0;
    Sun      = 0;
    TxBuf[0] = 0x50;  
    Sun      = 0x50;
    TxBuf[1] = 0x4c;  
    Sun     += 0x4c; 
    for(n=0;n<Len;n++){
      Dat        = pDat[n];
      TxBuf[n+2] = Dat;     
      Sun += Dat;
    }  
    TxBuf[n+2] = Sun;  
    TxSize = Len+3;
    TxLead = 1;
    TxIdx  = 0;
    SBUF = TxBuf[0];
    return 0;  
//  }else{
//    return 1;   
//  }      
}

//void TxClrLead(void)
//{
//  TxLead = 0;  
//}
//----------------------------------------
//
//
//----------------------------------------
bit RxOk;
u16 Uto;

void UartTo(void)
{  
  if(RxOk){
    if(++Uto > 999){Uto = 0; 
      //  
      RxIdx       = 0;
      LeOk        = 0; 
      //        
      RxOk        = 0;  
      PcbKeyValue = 0; 
    }        
  }else
  Uto = 0;      
}
//----------------------------------------
//
//
//----------------------------------------
u8 PcbKeyValue;
void UART_Interrupt_Receive(void)EUART
{   
  if(RI==1){RI = 0;          
	RxBuf[RxIdx] = SBUF;
	RxIdx++;
	if(!RxLead){
      if(RxBuf[0] == 0x50 && LeOk == 0){
        RxIdx = 1;
        LeOk  = 1; 
      }else{	  
        if(LeOk){	
	      if(RxBuf[1] == 0x4c){
	        RxSize = (2+2);
	        RxLead = 1;
	      }else{
	        RxIdx = 0;
          }
          LeOk  = 0;		  
        }else{
          RxIdx = 0;
        }    
      }              
    }else{        
	  if(RxIdx >= RxSize){          
	    RxIdx  = 0;
	    RxLead = 0;	
        if(RxBuf[2] == (~RxBuf[3])){           
		  PcbKeyValue = RxBuf[2];
        }            
	  }
    }      
    RxOk = 1;   
    Uto    = 0; 
  }
  if(TI==1){TI = 0;
//    if(TxLead){
      TxIdx++;
      if(TxIdx >= TxSize){
        TxLead = 0;
      }else{
        SBUF = TxBuf[TxIdx]; 
      }
//    }
  }
}
