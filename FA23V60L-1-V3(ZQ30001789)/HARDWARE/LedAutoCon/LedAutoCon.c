#include "HARDWARE/main/SysInc.h"


// uint8 FlaTimer;
// uint8 FlaTimerOn;
// uint8 FlameTimOff;
// uint8 FalTimer1ms;

// unsigned char  code FlameLumConst[7]=
// {
//   0,   //��
//   10,  //����
//   2,   //΢΢��
//   5,   //����
//   10,  //����
//   0
// };
/************************************************************
* ������:
* ����˵��:
************************************************************/
// void Timer0FlaIsr( void ) interrupt TIMER0  //1ms
// {
//   TF0   = 0   ;
//   TH0   =	0XFA;				//1ms
//   TL0   =	0X99;
//   if(!Standby)//����״̬���صƹص��
//   {
//     MOT  = 0;
// 	FOT  = 0;
// 	DOT  = 0;
// 	DWL1 = 0;
// 	DWL2 = 0;
//    #if ((CUN14_EN==1) || (M3022LC_EN==1) || (RV26D08L_EN==1))
//     DOT1= 0;
//    #endif
// 	//--------
//   }else
//   {
//     FlaTimer++;//����ʱ��
//     if(FlaTimer>10)//����10ms
//     {
//       FlaTimer=0; //����
// 	  if(FlaGears)
//  	  {
// 	    //--------
// 	    DOT = 1;
// 	  #if ((CUN14_EN==1) || (M3022LC_EN==1) || (RV26D08L_EN==1))
// 		DOT1= 1;
// 	  #endif
// 	    //--------
// 		if(FlaGears != 1 && !FlaLock)//��λΪ2.3.4
// 		{
// 		  MOT  = 1;
// 	      FOT  = 1;
//           DWL1 = 1;
// 		  DWL2 = 1;
// 		}else//��λΪ1
// 		{
// 		  MOT  = 0;
// 	      FOT  = 0;
// 		  DWL1 = 0;
// 		  DWL2 = 0;
// 		}
//         FlaTimerOn  = FlameLumConst[FlaGears];//���浵λ����
//         FlameTimOff = FlaTimerOn;
// 	  }else//��λΪ0
// 	  {
// 	    MOT = 0;
// 	    FOT = 0;
// 		DWL1= 0;
// 		DWL2= 0;
// 	    if((HeaOnOff)&&(!HeatLock))
// 	    {
// 	      //--------
// 		  DOT = 1;
// 	    #if ((CUN14_EN==1) || (M3022LC_EN==1) || (RV26D08L_EN==1))
// 		  DOT1= 1;
// 	    #endif
// 	      //--------
//        	#if (FA26V60_EN==1)
// 		  FlameTimOff = 2;
//         #else
// 	      FlameTimOff = 1;
// 		#endif
// 	      FlaTimerOn  = FlameTimOff;
// 	    }else{
// 	     DOT = 0;
// 	   #if ((CUN14_EN==1) || (M3022LC_EN==1) || (RV26D08L_EN==1))
// 		 DOT1= 0;
// 	   #endif
// 		}
// 	  }
//     }
//     if(FlaTimerOn!=10)
//     {
// 	  if(FlameTimOff != 0)
// 	  FlameTimOff--;
// 	  else
// 	  {
// 	    FOT  = 0;
// 	    DOT  = 0;
// 	  #if ((CUN14_EN==1) || (M3022LC_EN==1) || (RV26D08L_EN==1))
// 		DOT1= 0;
// 	  #endif
// 	  }
//     }
//     if(LockWoodFalsh)//--100MS��˸�ͻ�
// 	{
//       DOT=1;
//     #if ((CUN14_EN==1) || (M3022LC_EN==1) || (RV26D08L_EN==1))
// 	  DOT1= 1;
// 	#endif
// 	}
//     else
//     if(LockWoodCon)
// 	{
//       DOT=0;
// 	#if ((CUN14_EN==1) || (M3022LC_EN==1) || (RV26D08L_EN==1))
// 	  DOT1=0;
// 	#endif
// 	}
//   }
// }
