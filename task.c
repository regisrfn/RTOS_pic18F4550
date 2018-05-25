/*
 * File:   task.c
 * Author: regis
 *
 * Created on 3 de Junho de 2017, 11:57
 */


#include <xc.h>
#include "TASK.h"

void interrupt highPriority() {
    saveRegisters;    
    if (TMR0IF == 1) {
        saveContext;
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

        TMR0 = Timer0;
        TMR0IF = 0;
        
        restoreContext;
        asm("retfie");
    }

}

void setTimerTasks() {

    GIE = 1; /* Enable Global Interrupt */
    PEIE = 1; /* Enable Peripheral Interrupt */
    TMR0IF = 0;
    /* Enable 16-bit TMR1 register,no pre-scale,internal clock, timer OFF */
    T0CON = 0x00;
    TMR0 = Timer0; /* Load Count for generating delay of 1ms */
    TMR0ON = 1; /* Turn ON Timer1 */
    TMR0IE = 1; /* Enable Timer1 Overflow Interrupt */
}

void startRTOS(void) {
    setTimerTasks();
    TMR0IF = 1;
}

void initTask(unsigned char TaskNo, unsigned int t) {

    taskStack[TaskNo][0] = TOSL;
    taskStack[TaskNo][1] = TOSH;
    taskStack[TaskNo][2] = TOSU;
    taskTime[TaskNo] = t;
    asm("POP");
}