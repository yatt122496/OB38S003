/*--------------------------------------------------------------------------
Header file for UART0.
Modify on 2010/07/1.
--------------------------------------------------------------------------*/

#ifndef __UART_0__
#define __UART_0__

#include "HARDWARE\main\SysInc.h"
// Example Code
/*
void main(void)
{
    init_UART0();
    while(1)
    {
        UART0_TX(0xAA);    // 0xAA is data.
    }
}
*/
#if UART_TEST
void UART0_TX(unsigned char n_temp0);
void init_UART0(void);
#endif

#endif
