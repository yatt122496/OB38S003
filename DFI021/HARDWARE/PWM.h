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

void PWM_initialize(void);
void PWM_Output(unsigned int PWMD0, unsigned int PWMD1,
                unsigned int PWMD2, unsigned int PWMD3);
// void PWM_Disable(void);
// void PWM_ISR(void);

#endif
