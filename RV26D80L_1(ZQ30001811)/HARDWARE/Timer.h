/*--------------------------------------------------------------------------
Header file for Timer0.
Modify on 2012/04/12.
--------------------------------------------------------------------------*/

#ifndef __TIMER_0_H__
#define __TIMER_0_H__

// Example Code
/*
void main(void)
{
    TIMER0_initialize();
    TR0  = 1;
    TR1  = 1;
    EA   = 1;
    while(1);
}
*/
// extern unsigned long Sys_Time;
void TIMER_initialize(void);

 #endif
