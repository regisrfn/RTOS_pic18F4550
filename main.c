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
#define Pulse1 LATBbits.LATB0
#define Pulse2 LATBbits.LATB1
#define _XTAL_FREQ 48000000


void TASK1();
void TASK2();

void main(void) {

    TRISB = 0;
    PORTB = 0;
    
    TASK1();
    TASK2();
    startRTOS();

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
    static int test  = 100;
    while (1) {
        __delay_us(10);
        Pulse1 = (unsigned)!Pulse1;
        test++;      
    }
}

void TASK2() {
    initTask(2, 1);
    static int i = 7;
    while (1) {
        delay_us(2);
        Pulse2 = (unsigned)!Pulse2;
        i++;
    }
}

