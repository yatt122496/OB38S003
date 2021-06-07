#include "OB38S003.h"
#include "Timer.h"

#define TIMER0_VECTOR  1    //TIMER0 Interrupt Vevtor
#define TIMER1_VECTOR  3    //TIMER1 Interrupt Vevtor
#define TIMER2_VECTOR   5      //TIMER0 Interrupt Vevtor
#define d_T2PS          0x05      //T2CON[7:5] TIMER2 Prescaler select 0~7
#define d_T2R           0x02      //T2CON[4:3] TIMER2 Reload mode select 0~3
#define d_T2I           0x01      //T2CON[1:0] TIMER2 Input select 0~3
#define d_T0MOD        0x01 //TMOD[3:0] TIMER0 Mode setting
#define d_T1MOD        0x01 //TMOD[7:4] TIMER1 Mode setting
#define ET2            0x01 //TIMER2 overflow Interrupt Enable (Default 0 Disable)
#define ET1            0x01 //TIMER1 overflow Interrupt Enable (Default 0 Disable)
#define ET0            0x00 //TIMER0 overflow Interrupt Enable (Default 0 Disable)

#define d_MODEVALUE_T0      65536     //MODE1 16bit 65536
#define d_RELOADVALUE_T0    0      //User Define Reload Value
#define d_MODEVALUE_T1      65536    //MODE1 16bit 65536
#define d_RELOADVALUE_T1    333      //User Define Reload Value
#define d_MODEVALUE_T2      65536
#define d_RELOADVALUE_T2    3333 //User Define Reload Value

void TIMER_initialize(void)  //Initialize TIMER0
{
    IEN0 |= (ET2<<5)|(ET1<<3)|(ET0<<1); //IE=IEN0
    TMOD  = (d_T1MOD<<4)|(d_T0MOD);
    TH0   = (d_MODEVALUE_T0-d_RELOADVALUE_T0)/256;    //MODE1 16bit 65536
    TL0   = (d_MODEVALUE_T0-d_RELOADVALUE_T0)%256;

	TH1   = (d_MODEVALUE_T1-d_RELOADVALUE_T1)/256;
    TL1   = (d_MODEVALUE_T1-d_RELOADVALUE_T1)%256;
    //TR0   = 1;    //Timer0 Start bit
	TR1  = 1;

    T2CON  = (d_T2PS<<5)|(d_T2R<<3)|(d_T2I);
    TH2    = (d_MODEVALUE_T2-d_RELOADVALUE_T2)/256;
    TL2    = (d_MODEVALUE_T2-d_RELOADVALUE_T2)%256;
    CRCH   = (d_MODEVALUE_T2-d_RELOADVALUE_T2)/256; //reload velue high
    CRCL   = (d_MODEVALUE_T2-d_RELOADVALUE_T2)%256; //reload velue low

}

void TIMER0_ISR(void) interrupt TIMER0_VECTOR
{
    TH0 = (d_MODEVALUE_T0-d_RELOADVALUE_T0)/256;    //MODE1 16bit 65536
    TL0 = (d_MODEVALUE_T0-d_RELOADVALUE_T0)%256;
    // To do something by using timer interrupt.

}

// unsigned long Sys_Time = 0;
// void TIMER1_ISR(void) interrupt TIMER1_VECTOR
// {
//     TH1 = (d_MODEVALUE_T1-d_RELOADVALUE_T1)/256;
//     TL1 = (d_MODEVALUE_T1-d_RELOADVALUE_T1)%256;
// 	Sys_Time++;
//     // To do something by using timer interrupt.

// }

// void TIMER2_ISR(void) interrupt TIMER2_VECTOR
// {
//     TF2 = 0;
// 	// Sys_Time++;
// }
