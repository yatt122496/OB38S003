/*--------------------------------------------------------------------------
Header file for PWM.
Modify on 2018/01/09
--------------------------------------------------------------------------*/
#ifndef __PWM_H__
#define __PWM_H__

// Example Code
/*
extern unsigned int PWMD0;
extern unsigned int PWMD1;
extern unsigned int PWMD2;
extern unsigned int PWMD3;

void main(void) //Main Function Start
{
    PWM_initialize();     //Call PWM Initial Subroutine
    PWM_Output(PWMD0, PWMD1, PWMD2, PWMD3);
    while(1)
    {
        ;
    }
    //PWM_Disable();
}
*/
#define PWMMD 266        //PWMMD[9:0]=Period (PWM Max Data Register 0~1023)
#define PWMD0 0x7D        //PWMD0[9:0]=Duty (PWM Channel 0 Data Register 0~1023)
#define PWMD1 0x00        //PWMD1[9:0]=Duty (PWM Channel 1 Data Register 0~1023)
#define PWMD2 0x00        //PWMD2[9:0]=Duty (PWM Channel 2 Data Register 0~1023)
#define PWMD3 0x00        //PWMD3[9:0]=Duty (PWM Channel 3 Data Register 0~1023)

void PWM_initialize(void);
void PWM_Output(unsigned int PWM0, unsigned int PWM1,
                unsigned int PWM2, unsigned int PWM3);
void PWM_ISR(void);

#endif
