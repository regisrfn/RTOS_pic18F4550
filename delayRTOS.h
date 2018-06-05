// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DELAY_RTOS_H
#define	DELAY_RTOS_H

#include <xc.h> // include processor files - each processor file is guarded. 
#define _XTAL_FREQ 48000000
#define DELAY_FREQ_PIC 48
#define DELAY_PRESCALE 1

#define DELAY_TIME 1000 //us
#define DELAY_TIMER (65535 - (DELAY_TIME*DELAY_FREQ_PIC/(unsigned short)(4*DELAY_PRESCALE)))
const unsigned short Timer1 = DELAY_TIMER+1;

void Timer1_delay_ms();

void delay_ms(int time);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* XC_HEADER_TEMPLATE_H */