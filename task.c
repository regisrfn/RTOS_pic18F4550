/*
 * File:   task.c
 * Author: regis
 *
 * Created on 3 de Junho de 2017, 11:57
 */


#include <xc.h>
#include "TASK.h"

void interrupt highPriority() {
    SAVE_REGISTERS;
    if (TMR0IF == 1) {
        SAVE_CONTEXT;

        size_stack[taskNumber] = 0;
        while (STKPTR > 1) {
            taskStack[taskNumber][0][size_stack[taskNumber]] = TOSL;
            taskStack[taskNumber][1][size_stack[taskNumber]] = TOSH;
            taskStack[taskNumber][2][size_stack[taskNumber]] = TOSU;
            asm("POP");
            size_stack[taskNumber]++;
        }
        size_stack[taskNumber]--;

        taskNumber++;
        if (taskNumber > NUMBER_OF_TASKS - 1)
            taskNumber = 1;


        while ((signed char) size_stack[taskNumber] > -1) {
            asm("PUSH");
            TOSL = taskStack[taskNumber][0][size_stack[taskNumber]];
            TOSH = taskStack[taskNumber][1][size_stack[taskNumber]];
            TOSU = taskStack[taskNumber][2][size_stack[taskNumber]];
            size_stack[taskNumber]--;
        }

        taskWREG = savedContext[taskNumber][0];
        taskSTATUS = savedContext[taskNumber][1];
        taskBSR = savedContext[taskNumber][2];
                
        TMR0IF = 0;
        TMR0 = Timer0;
        RESTORE_CONTEXT;
        asm("retfie");
    }

}

void setTimerTasks() {
    TMR0IF = 0;
    /* Enable 16-bit TMR1 register,no pre-scale,internal clock, timer OFF */
    T0CON = 0x00;
    TMR0 = Timer0; /* Load Count for generating delay of 1ms */
    TMR0ON = 1; /* Turn ON Timer1 */
    TMR0IE = 1; /* Enable Timer1 Overflow Interrupt */
}

void startRTOS(void) {
    setTimerTasks();
    IPEN = 1;
    GIEH = 1;
    GIEL = 1;
    TMR0IF = 1;
}

void initTask(unsigned char TaskNo, unsigned int t) {

    taskStack[TaskNo][0][0] = TOSL;
    taskStack[TaskNo][1][0] = TOSH;
    taskStack[TaskNo][2][0] = TOSU;
    taskTime[TaskNo] = t;
    asm("POP");
}