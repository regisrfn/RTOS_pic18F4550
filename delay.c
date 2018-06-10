#include "delayRTOS.h"

void delay_us(unsigned int time) {
    /* Enable 16-bit TMR1 register, No pre-scale, internal clock,timer OFF */
    static unsigned int t;
    t = time;

    T0CON = 0x00;
    TMR0 = 65535UL - t * timer_us;
    /* Load count for generating delay of 1ms */
    TMR0ON = 1; /* Turn ON Timer1 */
    while (TMR0IF == 0); /* Wait for Timer1 overflow interrupt flag */
    TMR0ON = 0; /* Turn OFF timer */
    TMR0IF = 0; /* Make Timer1 overflow flag to '0' */

}

void delay_ms(unsigned int time) {
    static unsigned int t;
    t = time;

    T0CON = 0x07;
    /* Load count for generating delay of 1ms */
    TMR0 = 65535UL - t * timer_ms;
    TMR0ON = 1; /* Turn ON Timer1 */
    while (TMR0IF == 0); /* Wait for Timer1 overflow interrupt flag */
    TMR0ON = 0; /* Turn OFF timer */
    TMR0IF = 0; /* Make Timer1 overflow flag to '0' */
}

