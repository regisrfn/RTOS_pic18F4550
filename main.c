/*
 * File:   main.c
 * Author: regis
 *
 * Created on 21 de Maio de 2018, 11:51
 */


#include <xc.h>
#include <p18f4550.h>
#include "CONFIG.h" // Configuration Bit Settings
#include "TASK.h"   // Configuration of RTOS variables
#include "delayRTOS.h"
#define Pulse LATB


void TASK1();
void TASK2();

void main(void) {


    TRISB = 0;
    PORTB = 0;

    
    TASK1();
    TASK2();
    startRTOS();
    while (1);

}

//void Timer1_delay() {
//    /* Enable 16-bit TMR1 register, No pre-scale, internal clock,timer OFF */
//    T1CON = 0x80;
//    TMR1 = Timer; /* Load count for generating delay of 1ms */
//    T1CONbits.TMR1ON = 1; /* Turn ON Timer1 */
//    while (PIR1bits.TMR1IF == 0); /* Wait for Timer1 overflow interrupt flag */
//    TMR1ON = 0; /* Turn OFF timer */
//    TMR1IF = 0; /* Make Timer1 overflow flag to '0' */
//}

void TASK1() {
    initTask(1, 1);
    while (1) {
        Timer1_delay_us();
        PORTBbits.RB0 = (unsigned) !PORTBbits.RB0;
    }
}

void TASK2() {
    initTask(2, 1);
    int test;
    while (1) {
        // Timer0_delay_us();
        test = 1;
        test = 2;
        test = 3;
        test = 4;
        test = 5;
    }
}

