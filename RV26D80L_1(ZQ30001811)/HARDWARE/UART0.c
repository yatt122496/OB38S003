#include "OB38S003.h"
#include "UART0.h"

//===============================================================
//DEFINITIONs
//===============================================================
#define d_S0RELH        0x03
#define d_S0RELL        0xCC

//===============================================================
//GLOBAL VARIABLE
//===============================================================
bit bU0TX = 0;

//=========================================================================
void init_UART0(void)
{
    S0RELH   = d_S0RELH;
    S0RELL   = d_S0RELL;
    AUX     |= 0x80;            // BRS = 1
    PCON    |= 0x80;            // SMOD =1
    IEN0    |= 0x90;            // EA=1, ES0=1, interrupt enable
    S0CON    = 0x50;            // mode 1, SM20=0, Revice enable
    TI       = 0;
}

void UART0_ISR(void) interrupt d_UART0_Vector
{
    unsigned char RXBUF0;

    if (RI)                     // INT_RX
    {
        RI = 0;                 // RI clear
        RXBUF0 = S0BUF;         // Read BUF, user code...
    }
    else                        // INT_TX
    {
        bU0TX  = 0;
        TI     = 0;             // TI clear
    }
}

void UART0_TX(unsigned char n_temp0)
{
    bU0TX = 1;
    S0BUF = n_temp0;
    while(bU0TX)
    {
        ;
    }
}

//=========================================================================
