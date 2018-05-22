/*
 * File:   task.c
 * Author: regis
 *
 * Created on 3 de Junho de 2017, 11:57
 */


#include <xc.h>
#include "TASK.h"

void interrupt highPriority() {

    if (PIR1bits.TMR1IF == 1) {

        TMR1 = Timer1;

        taskStack[taskNumber][0] = TOSL;
        taskStack[taskNumber][1] = TOSH;
        taskStack[taskNumber][2] = TOSU;
        asm("POP");

        
        taskNumber++;
        if (taskNumber > NumberOfTasks - 1)
            taskNumber = 1;
        
        
        
        asm("PUSH");
        TOSL = taskStack[taskNumber][0];
        TOSH = taskStack[taskNumber][1];
        TOSU = taskStack[taskNumber][2];

        PIR1bits.TMR1IF = 0;
        asm("retfie");

    }

}

void setTimerTasks() {

    GIE = 1; /* Enable Global Interrupt */
    PEIE = 1; /* Enable Peripheral Interrupt */
    TMR1IE = 1; /* Enable Timer1 Overflow Interrupt */
    TMR1IF = 0;
    /* Enable 16-bit TMR1 register,no pre-scale,internal clock, timer OFF */
    T1CON = 0x80;
    TMR1 = Timer1; /* Load Count for generating delay of 1ms */
    TMR1ON = 1; /* Turn ON Timer1 */
}

void startRTOS(void) {
    setTimerTasks();
    TMR1IF = 1;
}

void initTask(unsigned char TaskNo, unsigned int t) {

    taskStack[TaskNo][0] = TOSL;
    taskStack[TaskNo][1] = TOSH;
    taskStack[TaskNo][2] = TOSU;
    taskTime[TaskNo] = t;
    asm("POP");
}