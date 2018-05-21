#include "delayRTOS.h"

void Timer0_delay_us() {
    /* Enable 16-bit TMR0 register, pre-scale = 1, internal clock,timer OFF */
    T0CON = 0b10000000;
    TMR0 = Timer0; /* Load count for generating delay of 1ms */
    TMR0ON = 1; /* Turn ON Timer1 */
    while (INTCONbits.TMR0IF == 0); /* Wait for Timer1 overflow interrupt flag */
    TMR0ON = 0; /* Turn OFF timer */
    TMR0IF = 0; /* Make Timer1 overflow flag to '0' */
}

