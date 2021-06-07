#include "OB38S003.h"
#include "PWM.h"

#define PWM_VECTOR  8           //PWM Interrupt Vevtor
#define d_PWMCS     0x02        //PWMCS[2:0] (PWM clock select 0~7)
#define d_PWMXEN    0x01        //PWM Channel Enable (0~F)
#define d_PWMP0     0x00        //PWM0 Channel idle polarity select
#define d_PWMP1     0x00        //PWM1 Channel idle polarity select
#define d_PWMP2     0x00        //PWM2 Channel idle polarity select
#define d_PWMP3     0x00        //PWM3 Channel idle polarity select
#define d_PWMIE     0x00        //PWM Interrupt Enable bit

// unsigned int PWMMD = 0xFA;        //PWMMD[9:0]=Period (PWM Max Data Register 0~1023)
// unsigned int PWMD0 = 0x7D;        //PWMD0[9:0]=Duty (PWM Channel 0 Data Register 0~1023)
// unsigned int PWMD1 = 0x00;        //PWMD1[9:0]=Duty (PWM Channel 1 Data Register 0~1023)
// unsigned int PWMD2 = 0x00;        //PWMD2[9:0]=Duty (PWM Channel 2 Data Register 0~1023)
// unsigned int PWMD3 = 0x00;        //PWMD3[9:0]=Duty (PWM Channel 3 Data Register 0~1023)

void PWM_initialize(void)  //Initialize PWM
{
    EA     = 0;             //Disable All Interrupt Function
    IEPWM  = (d_PWMIE);     //Enable PWM Interrupt Function
    PWMMDH = PWMMD >> 8;
    PWMMDL = PWMMD;
}

void PWM_Output(unsigned int PWM0,unsigned int PWM1,
                unsigned int PWM2,unsigned int PWM3) //PWM Output Set
{
    PWMD0H = (PWM0>>8) | (d_PWMP0<<7);
    PWMD0L = (PWM0);
    PWMD1H = (PWM1>>8) | (d_PWMP1<<7);
    PWMD1L = (PWM1);
    PWMD2H = (PWM2>>8) | (d_PWMP2<<7);
    PWMD2L = (PWM2);
    PWMD3H = (PWM3>>8) | (d_PWMP3<<7);
    PWMD3L = (PWM3);
    // PWMC   = PWMC|(d_PWMCS<<5)|(d_PWMXEN);
	PWMC   = PWMC|(d_PWMCS<<5);
}

void PWM_ISR(void) interrupt PWM_VECTOR //PWM Interrupt Subroutine
{
    while (PWMIF)
    {
        PWMIF = 0; //Clear PWM Flag
    }
}
