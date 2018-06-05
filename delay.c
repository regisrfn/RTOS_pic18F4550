#include "delayRTOS.h"

void Timer1_delay_ms() {
    /* Enable 16-bit TMR1 register, No pre-scale, internal clock,timer OFF */
    T1CON = 0x80;
    TMR1 = Timer1; /* Load count for generating delay of 1ms */
    TMR1ON = 1; /* Turn ON Timer1 */
    while (TMR1IF == 0); /* Wait for Timer1 overflow interrupt flag */
    TMR1ON = 0; /* Turn OFF timer */
    TMR1IF = 0; /* Make Timer1 overflow flag to '0' */

}

void delay_ms(int time){
    static int i;
    static int t;
    t = time;    
    for(i = 0; i < t;i++){
        Timer1_delay_ms();
    }
}