#include "HARDWARE/main/SysInc.h"
#include "AD.h"

/***************************************************
*
*
*
****************************************************/
u8 code LumConst[7]=
{
  10,  //常亮
  5,   //微微亮
  2,   //高亮
  2,
  0
};
u8 code SpeedList1[]={33,26,18,18};
//u8 code SpeedList2[]={50,40,30,30};
/***************************************************
*
*		火焰
*
****************************************************/
u8 idata FlaTimer;       //亮度控制
u8 idata FlaTimerOn;
//---------------------
u8 idata FlaOnTimer;
u8 idata FlaAutoGears;
//
bit FlaAutoOffCon;
bit FlaAddDecSwap;
u8 idata FlaAutoTimer;
u8 idata FlaAutoOffSet;
u8 idata FlaAutoTimerOff;
u8 idata FlaOn1ms;

extern uint8 idata GoErrTimer;
extern xdata uint8 HotWaitModeTimer;
extern xdata uint8 TestNtcTimer;	//??NTC 1?????????
extern xdata uint8  MotTimer;
extern xdata uint8  MotTimer1;
extern xdata uint8  HotTimer;
extern xdata uint8  HotTimer1;
extern uint8 idata TimeTimer;
extern bit   idata TimeTimerCon;
extern uint8 idata LookWoodConTimer;
extern uint8 idata LookWoodConTimerCon;
extern uint8 idata LockTimerOtp;
//---------------------
void FlaSpeedInit(void)
{
  EA = 0;
  FLA_Y = 0;
  FLA_B = 0;
  FlaAutoGears = 0;
  FlaAddDecSwap= 0;
  FlaAutoOffSet= 5;
  EA = 1;
}
/***************************************************
*
*	    底灰
*
****************************************************/
u8 idata DowTimer;       //亮度控制
u8 idata DowTimerOn;
//---------------------
u8 idata DowOnTimer;
u8 idata DowAutoGears;
//
bit DowAutoOffCon;
bit DowAddDecSwap;
u8 idata DowAutoTimer;
u8 idata DowAutoOffSet;
u8 idata DowAutoTimerOff;
u8 idata DowOn1ms;
//---------------------
void DowSpeedInit(void)
{
	EA = 0;
	DOW_O = 0;
	DOW_B = 0;
	DOW_R = 0;
	DowAutoGears = 0;
	DowAddDecSwap= 0;
	DowAutoOffSet= 5;
	EA = 1;
}
/***************************************************
*
*
*
****************************************************/
u8 bdata Led;
sbit  Led1 = Led^0;
sbit  Led2 = Led^1;
sbit  Led3 = Led^2;

u8 code ColourList[] = {0x00,0X01,0X02,0X04,0X03,0X05,0x06,0x07,0x07};
static u8 b10ms_cnt = 0;
#if UART_TEST
xdata unsigned long Sys_Time = 0;
#endif


/************************************************************
* 函数名:
* 功能说明:
************************************************************/
void Timer0FlaIsr( void ) interrupt TIMER2_VECTOR   //1ms
{
	TF2   =  0;
	b10ms_cnt++;
#if UART_TEST
	Sys_Time++;
#endif
	if (b10ms_cnt > 9) {
		b10ms_cnt = 0;
		IrLockTmr();
		if(ADCfinish) {
			ADCfinish = 0;
			if((ADCC2&0x02)) {//??????1????
				AdKeyNew    = 1;
				// AdKeyValue  = ADDH;
				AdKeyValue  = n_data >> 4;

				// uart_send(&AdKeyValue, 1);
				// ADCON       = AD_NTC  ;//Bin(10000001);
				ADC_Start(d_ADC_CH0_IN);
				if (TouchKeyTim) {
					if (AdKeyValue > 250) {
						TouchKeyCnt1 = 0;
						if (++TouchKeyCnt0 > 9) {
							TouchKeyCnt0 = 9;
							TouchKeyOpt = 0;
						}
					} else {
						TouchKeyCnt0 = 0;
						if (++TouchKeyCnt1 > 9) {
							TouchKeyCnt1 = 9;
							TouchKeyOpt = 1;
						}
					}
				}
				// FLA_B = !FLA_B;
			} else {//??????3???????
				AdNtcNew    = 1;
				AdNtcValue  = n_data >> 2;
				// AdNtcValue  = (ADDH << 2) | (ADDL & 0x03);
				// ADCON       = AD_KEY  ;//Bin(10000011);
				ADC_Start(d_ADC_CH2_IN);
				// FLA_Y = !FLA_Y;
			}
		}
		//***********************************************
		if (HOT && !GoErrCon) {
			EX0 = 1;
			if (++GoErrTimer > 99) {
				GoErrTimer = 0;
				if (GoErrCount > 40) {
					GoErrCon   = 0;
					GoErrCount = 0;
				}
				else
					GoErrCon = 1;
			}
		} else {
			EX0 = 0;
			IE0 = 0;
			GoErrCount = 0;
			GoErrTimer = 0;
		}
		//***********************************************
		if(DispSensFreq)DispSensFreq--;
		if(TouchKeyTim)TouchKeyTim--;
		//***********************************************
		HotWaitModeTimer++;
		if(HotWaitModeTimer > 99) {
			HotWaitModeTimer = 0;
			HeaterSec        = 1;
			if(HeatTest) {		 //Hot Test Timer 1mim
				TestNtcTimer++;
				if(TestNtcTimer > 59) {
					TestNtcTimer = 0;
					HeatTest      = 0;		//Test cancel
				}
			}
		}
		//***********************************************
		if(!HotOnOff && MotDelayOff) {  //????
			MotTimer++;
			if(MotTimer > 99) {				   //1S
				MotTimer   = 0;
				MotTimer1++;
				if(MotTimer1 > FAN_DELAY_TIME) { //8s
					MotTimer1   = 0;
					MotDelayOff = 0;
				}
			}
		} else {
			MotTimer  = 0;
			MotTimer1 = 0;
		}
		//----------------------------------
		if (FAN && HotDelayeOn) {
			if(++HotTimer > 99) {
				HotTimer = 0;
				if(++HotTimer1 > HOT_DELAY_TIME) {
					HotTimer1   = 0;
					HotDelayeOn = 0;
				}
			}
		} else {
			HotTimer  = 0;
			HotTimer1 = 0;
		}
		//***********************************************
		TimeTimer++;//?10ms
		if (TimeTimer > 4) {//?50ms
			TimeTimer     = 0;//??
			TimeTimerCon  = 1;//???50ms
			//--------------------
			if(KeySwitchTimer)
				KeySwitchTimer--;//?50ms
			//--------------------
			if(LockWoodCon) {//??????
				LookWoodConTimer++;//50ms
				if(LookWoodConTimer > LockTimerOtp) {
					LookWoodConTimer  = 0;//100ms
					LookWoodConTimerCon++;//?100ms
					if(LookWoodConTimerCon > 11) {//?1s
						LookWoodConTimerCon  = 0;
						LockWoodCon          = 0;
						LockWoodFalsh        = 0;
					} else {//??1s????????
						if(!LockWoodFalsh)
							LockWoodFalsh = 1;
						else
							LockWoodFalsh = 0;
					}
				}
			}
		}
		//-----------------------------------------
		TimerFun();
	}

	if(!Standby)//待机状态，关灯关电机
	{
		MOT  = 0;
		FLA_Y = 0;
		FLA_B = 0;
	#if (RV_7COLOUR == 1)
		FLA_R = 0;  //火焰
	#endif
		DOW_O = 0;
		DOW_B = 0;
		DOW_R = 0;  //底灰
		//--------
	}else {
		if(FlaGears){
		MOT   = 1;
		if(FlaGears != FLA_MAX){
			if(++FlaTimer > 9){
				FlaTimer= 0;
		#if (RV_7COLOUR == 1)
				Led = ColourList[FlaGears];
		#else
				Led = FlaGears;
		#endif
				FLA_Y  = Led1;
				FLA_B  = Led2;
		#if (RV_7COLOUR == 1)
				FLA_R  = Led3;
		#endif
				FlaTimerOn  = LumConst[0];
			}
			if(FlaTimerOn != 10){
				if(FlaTimerOn)
					FlaTimerOn--;
				else{
					FLA_Y = 0;
					FLA_B = 0;
				#if (RV_7COLOUR == 1)
					FLA_R	= 0;
				#endif
				}
			}
		}else{
			if (++FlaAutoTimer > SpeedList1[0]) {
				FlaAutoTimer=0; //
				if(!FlaAddDecSwap){
					if(FlaAutoOffSet++ > 199)
					FlaAddDecSwap = 1;
				}else{
					if(FlaAutoOffSet > 5)FlaAutoOffSet--;
					else{
						FlaAddDecSwap=0;
						FlaAutoGears++;
						if(FlaAutoGears > FLA_AU_MAX)
						FlaAutoGears    = 0;
					}
				}
			}
		}
	} else {
		MOT   = 0;
		FLA_Y  = 0;FLA_B  = 0;
	#if (RV_7COLOUR == 1)
		FLA_R  = 0;
	#endif
	}
	//--------------------------------------------------------------
	if(DowGears || (!FlaGears && !DowGears && HeaOnOff && !HeatLock)){
		if(DowGears != DOW_MAX){
			if(++DowTimer > 9){
				DowTimer= 0;
				if(!FlaGears && !DowGears && HeaOnOff && !HeatLock){
					DOW_O = 1;
					DowTimerOn  = LumConst[2];
				}else{
					Led = ColourList[DowGears];
					DOW_R = Led1;
					DOW_B = Led2;
					DOW_O = Led3;
					DowTimerOn  = LumConst[0];
				}
			}
			if(DowTimerOn != 10){
				if(DowTimerOn)
					DowTimerOn--;
				else{
					DOW_O = 0;
					DOW_B = 0;
					DOW_R = 0;
				}
			}
		}else{
			if(++DowAutoTimer > SpeedList1[0]){
				DowAutoTimer=0; //
				if(!DowAddDecSwap){
					if(DowAutoOffSet++ > 199)
						DowAddDecSwap = 1;
				}else{
					if(DowAutoOffSet > 5)DowAutoOffSet--;
					else{
						DowAddDecSwap=0;
						DowAutoGears++;
						if(DowAutoGears > DOW_AU_MAX)
							DowAutoGears    = 0;
					}
				}
			}
		}
	}else{//档位为0
		DOW_O = 0;
		DOW_B = 0;
		DOW_R = 0;
	}
	//-----------------
	if(LockWoodFalsh){//--150MS闪烁低灰
		if(!DowGears){
			if(!DOW_O && !DOW_B && !DOW_R)
				DOW_B = 1;
		}
	}else
		if(LockWoodCon){
			DOW_O = 0;DOW_B = 0;DOW_R = 0;
		}
	}
}
/***************************************************
*
*
*
****************************************************/
void LedTimeroff(void) interrupt TIMER1_VECTOR //50us
{
    TH1 = (d_MODEVALUE_T1-d_RELOADVALUE_T1)/256;
    TL1 = (d_MODEVALUE_T1-d_RELOADVALUE_T1)%256;
	//------------------------------
	if(!Standby)return;
	if(FlaGears == FLA_MAX){
		if(++FlaOnTimer > 205){
			FlaOnTimer = 0;
#if (RV_7COLOUR == 1)
			Led = ColourList[FlaAutoGears+1];
#else
			Led = FlaAutoGears+1;
#endif
			FLA_Y  = Led1;
			FLA_B  = Led2;
#if (RV_7COLOUR == 1)
			FLA_R  = Led3;
#endif
			FlaAutoOffCon= 1;
		}
		if(FlaAutoOffCon){
			if(++FlaAutoTimerOff > FlaAutoOffSet){
				FlaAutoTimerOff = 0;
				FlaAutoOffCon   = 0;
				FLA_B  = 0;
				FLA_Y  = 0;
	#if (RV_7COLOUR == 1)
				FLA_R  = 0;
#endif
			}
		}
	}else{
		FlaAddDecSwap = 0;
		FlaAutoOffSet = 0;
	}
		//-----------------
	if (DowGears == DOW_MAX) {
		if(++DowOnTimer > 205){
			DowOnTimer = 0;
			Led = ColourList[DowAutoGears+1];
			DOW_R = Led1;
			DOW_B = Led2;
			DOW_O = Led3;
			DowAutoOffCon= 1;
		}
		if(DowAutoOffCon){
			if(++DowAutoTimerOff > DowAutoOffSet){DowAutoTimerOff = 0;
				DowAutoOffCon   = 0;
				DOW_O           = 0;
				DOW_B           = 0;
				DOW_R           = 0;
			}
		}
	}else{
		DowAddDecSwap = 0;
		DowAutoOffSet = 0;
	}
}
