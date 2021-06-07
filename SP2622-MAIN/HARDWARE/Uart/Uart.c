/***********************************************************
*  �ļ���:                                              
************************************************************
*  ����:   
*  	                                                                                                                                            
*  ����:                                                                                             
*  ����˵����
*                                                    
************************************************************
*  Ӳ����                                               
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���                           
* ��������                                
***********************************************************/
#include "..\code\main\SysInc.h"

u8 idata TxDatTim;

// ���ڳ�ʼ��
//void UartInit(void)		
//{
//	PCON &= 0x7f;		//ʹ�ܲ����ʱ���λSMOD
//	SCON = 0x50;		//8λ����,�ɱ䲨����
//	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
//	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
//	TL1 = 0xe6;		//�趨��ʱ��ֵ
//	TH1 = 0xe6;		//�趨��ʱ����װֵ
//	ET1 = 0;		//��ֹ��ʱ��1�ж�
//	TR1 = 1;		//������ʱ��1 		
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
// �����жϲ���
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
