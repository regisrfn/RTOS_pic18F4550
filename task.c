/*
 * File:   task.c
 * Author: regis
 *
 * Created on 3 de Junho de 2017, 11:57
 */


#include <xc.h>
#include "TASK.h"

void interrupt highPriority() {

    if (PIR1bits.TMR1IF==1) {

        TMR1 = Timer1;
        PORTBbits.RB0 = (unsigned)!PORTBbits.RB0;
        PIR1bits.TMR1IF=0;

    }

}

void setTimerTasks() {
    
    GIE=1;		/* Enable Global Interrupt */
    PEIE=1;  		/* Enable Peripheral Interrupt */
    TMR1IE=1;		/* Enable Timer1 Overflow Interrupt */
    TMR1IF=0;
    /* Enable 16-bit TMR1 register,no pre-scale,internal clock, timer OFF */
    T1CON=0x80;	
    TMR1 = Timer1;	/* Load Count for generating delay of 1ms */
    TMR1ON=1;		/* Turn ON Timer1 */
}

void startRTOS(void) {

    setTimerTasks();
    INTCONbits.GIE = 1;
    asm("return");
}