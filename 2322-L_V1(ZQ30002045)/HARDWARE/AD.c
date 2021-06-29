#include "OB38S003.h"
#include "AD.h"

unsigned int n_data    = 0x0000;
unsigned char ADCfinish = 0;


void ADC_Start(unsigned char n_ADC_CH)
{
	ADCC1 = d_ADCnEN0;
    ADCC2  = n_ADC_CH; //Set a new channel
    ADCC2 |= 0x80;      //ADC start conversion
}

void ADC_Init(void)
{
    ADCC1 = d_ADCnEN0;                 //Set ADC channel
    ADCCS = d_ADCnEN1 | d_ADC_CLK_Sel; //Set ADC channel & Select ADC clock
    IEADC = 1;                         //Enable ADC interrupt.
}

unsigned int ADC_Read12() //12-bit ADC
{
    unsigned int n_ADCD12 = 0x0000;
    n_ADCD12 = (ADCDH<<4) | (ADCDL&0x0f);     //12-bit ADC
    return n_ADCD12;
}

void ADCInterrupt(void) interrupt d_ADC_Vector // ADC Interrupt Vector Address 0053h => interrupt 10
{
	if (!ADCfinish) {
		n_data = ADC_Read12(); //Read ADC
   		ADCfinish = 1;
	}
}

