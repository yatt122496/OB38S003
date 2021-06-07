#include "OB38S003.h"
#include "PWM.h"

#define PWM_VECTOR  8           //PWM Interrupt Vevtor
#define d_PWMCS     0x05        //PWMCS[2:0] (PWM clock select 0~7)
#define d_PWMXEN    0x0D        //PWM Channel Enable (0~F)
#define d_PWMP0     0x00        //PWM0 Channel idle polarity select
#define d_PWMP1     0x00        //PWM1 Channel idle polarity select
#define d_PWMP2     0x00        //PWM2 Channel idle polarity select
#define d_PWMP3     0x00        //PWM3 Channel idle polarity select
#define d_PWMIE     0x00        //PWM Interrupt Enable bit
unsigned int PWMMD = 0x03E8;        //PWMMD[9:0]=Period (PWM Max Data Register 0~1023)
// unsigned int PWMD0 = 0x01F4;        //PWMD0[9:0]=Duty (PWM Channel 0 Data Register 0~1023)
// unsigned int PWMD1 = 0x00;        //PWMD1[9:0]=Duty (PWM Channel 1 Data Register 0~1023)
// unsigned int PWMD2 = 0x01F4;        //PWMD2[9:0]=Duty (PWM Channel 2 Data Register 0~1023)
// unsigned int PWMD3 = 0x01F4;        //PWMD3[9:0]=Duty (PWM Channel 3 Data Register 0~1023)

void PWM_initialize(void)  //Initialize PWM
{
    EA     = 0;             //Disable All Interrupt Function
    IEPWM  = (d_PWMIE);     //Enable PWM Interrupt Function
	PWMC   = (d_PWMCS<<5) | (d_PWMXEN);    			//Disable PWM Function
    PWMMDH = PWMMD >> 8;
    PWMMDL = PWMMD;
    // EA     = 1;             //Enable All Interrupt
}

void PWM_Output(unsigned int PWMD0,unsigned int PWMD1,
                unsigned int PWMD2,unsigned int PWMD3) //PWM Output Set
{
    PWMD0H = (PWMD0>>8) | (d_PWMP0<<7);
    PWMD0L = (PWMD0);
    PWMD1H = (PWMD1>>8) | (d_PWMP1<<7);
    PWMD1L = (PWMD1);
    PWMD2H = (PWMD2>>8) | (d_PWMP2<<7);
    PWMD2L = (PWMD2);
    PWMD3H = (PWMD3>>8) | (d_PWMP3<<7);
    PWMD3L = (PWMD3);
    // PWMC   = PWMC|(d_PWMCS<<5)|(d_PWMXEN);
}

// void PWM_Disable(void)
// {
//     IEPWM = 0;    //Disable PWM Interrupt
//     PWMC  = 0;    //Disable PWM Function
// }

// void PWM_ISR(void) interrupt PWM_VECTOR //PWM Interrupt Subroutine
// {
//     while (PWMIF)
//     {
//         PWMIF = 0; //Clear PWM Flag
//     }
// }
