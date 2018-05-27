// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DELAY_RTOS_H
#define	DELAY_RTOS_H

#include <xc.h> // include processor files - each processor file is guarded.  
#define delay_FreqPIC 48
#define delay_Prescale 1
#define delay_TasksTime 1000//us
#define delay_Timer (65535 - (delay_TasksTime*delay_FreqPIC/(unsigned short)(4*delay_Prescale)))

volatile unsigned short Timer1 = delay_Timer+1;

void Timer1_delay_us();
void delay_us(unsigned int time);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

