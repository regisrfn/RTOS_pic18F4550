// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DELAY_RTOS_H
#define	DELAY_RTOS_H

#include <xc.h> // include processor files - each processor file is guarded. 
#define _XTAL_FREQ 48000000
#define DELAY_FREQ_PIC 48UL
#define DELAY_PRESCALE 256UL
#define DELAY_PRESCALE_MICROSECONDS 2UL
#define DELAY_TIME 1000UL //us

const unsigned short timer_ms = DELAY_TIME * DELAY_FREQ_PIC / (4UL * DELAY_PRESCALE);
const unsigned short timer_us = DELAY_FREQ_PIC / (4UL * DELAY_PRESCALE_MICROSECONDS);

void delay_us(unsigned int time);
void delay_ms(unsigned int time);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* XC_HEADER_TEMPLATE_H */