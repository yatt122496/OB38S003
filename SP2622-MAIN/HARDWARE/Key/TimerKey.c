/***********************************************************
*  �ļ�˵����ҡ�س���
************************************************************
*  ����:2011.12.22 19:55
*
*  ����:  cuoiszf
*
************************************************************
*  Ӳ����sh79f083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE\main\SysInc.h"
//--------------------
bit     TimerCon;
uint8   MsTimer;
uint8   clk[3];
//clk1[3];
bit     TmrDisOtp;
bit     SecFlh;


/************************************************************
* ������:
* ����˵��:
************************************************************/
void ClrTmr(void)
{
  TimerCon = 0;
  clk[0]   = 0;
  clk[1]   = 0;
  clk[2]   = 0;
//  clk1[0]  = 0;
//  clk1[1]  = 0;
//  clk1[2]  = 0;
  MsTimer  = 0;
}
/************************************************************
* ������:
* ����˵��:��ʱ��ʾ
************************************************************/
void TimDisp( void )
{
  if((clk[0] || clk[1] || clk[2])){
    if(TmrDisOtp){
      if(clk[2]){
        DispDct2 = clk[2];
        DispDct3 = _h_;
      }else{
	    goto TmrDispMin;
      }
    }else{
      if(!SecFlh){
        LedSec = 1;
      }
      DispDct1 = clk[2];
      TmrDispMin:
      DispDct2 = clk[1]/10;
	  DispDct3 = clk[1]%10; // 8:88
    }
  }else{
    DispDct1= 0 ;   //"0FF"
    DispDct2=_F_;
    DispDct3=_F_;
  }
  LedTmr = 1;
}
/************************************************************
* ������:
* ����˵��:��ʱ
************************************************************/
void TimKey( void )
{
  if(!Standby){
    Standby = 1;
    if(ErrCon)
    return;
    KeyAct  = 0;
  }
  CancelAllFlash(0);
  DispDataSet = &TimDisp;
  if((KeyAct & K2_TIM) || (!clk[1] && !clk[2])){
    TmrDisOtp =1;
    TimerCon = 0;
    if(!clk[2]){
	   if(clk[1] <= 29){
	     clk[1] = 30;
	   }else
	   if(clk[1] <= 59){
         clk[1] = 0;
	     clk[2] = 1;
       }
    }else{
	  if(++clk[2] > 9){ //max 9h
        clk[0] = 0;
	    clk[1] = 0;
	    clk[2] = 0;
        goto GoActTmr;
	  }
	  clk[1] = 0;
	}
	clk[0] = 59;
    //---------------
    //
	MsTimer  = 0;
    TimerCon = 1;
  }else{
    TmrDisOtp = 0;
  }
  GoActTmr:
  KeyAct = K2_TIM;
}

/************************************************************
* ������:
* ����˵��:�����ж�
************************************************************/
void TIMER2_ISR(void) interrupt TIMER2_VECTOR
{
    TF2 = 0;
	if(TimerCon) {
		if(++MsTimer > 99){MsTimer = 0;
			if(--clk[0] > 59){clk[0] = 59;
				if(--clk[1] > 59){clk[1] = 59;
					if(--clk[2] > 9){clk[2] = 0;
						goto OffTmr;
					}
				}
			}
			if(!clk[1] && !clk[2]){
			OffTmr:
			TimerCon = 0;
			clk[0]  = 0;
			clk[1]  = 0;
			Standby  = 0;      //��ʱ��,����
			KeyAct   = 0;
			}
		}
		if(MsTimer < 64)SecFlh = 0;
		else            SecFlh = 1;
	}
	// Sys_Time++;
}
// void TimerFun( void )TIMER1
// {
//   TF1 = 0;
//   TH1   =	(65536-(SCLK/T1_FD/T1_FREQ))/256;
//   TL1   =	(65536-(SCLK/T1_FD/T1_FREQ))%256-1;
//   if(TimerCon){
//     if(++MsTimer > 99){MsTimer = 0;
//       if(--clk[0] > 59){clk[0] = 59;
//         if(--clk[1] > 59){clk[1] = 59;
//            if(--clk[2] > 9){clk[2] = 0;
//              goto OffTmr;
//            }
//         }
//       }
//       if(!clk[1] && !clk[2]){
//         OffTmr:
//         TimerCon = 0;
//         clk[0]  = 0;
//         clk[1]  = 0;
//         Standby  = 0;      //��ʱ��,����
//         KeyAct   = 0;
//       }
//     }
//     if(MsTimer < 64)SecFlh = 0;
//     else            SecFlh = 1;
//   }
// }
/************************************************************
* ������:
* ����˵��:
************************************************************/
void TimerOff(void)
{

}