/*
 * File:   task.c
 * Author: regis
 *
 * Created on 3 de Junho de 2017, 11:57
 */


#include <xc.h>
#include "TASK.h"

void interrupt highPriority() {
    SAVE_CONTEXT;
    if (TMR1IF == 1) {
        SAVE_INTO_STACK;

        taskCountTime[taskNumber]++;
        if ((swapTask) || (taskCountTime[taskNumber] >= taskTime[taskNumber])) {

            taskCountTime[taskNumber] = 0;
            if (swapTask)swapTask = 0;

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

            RESTORE_FROM_STACK;

            TMR1IF = 0;
            TMR1 = Timer1;
            RESTORE_CONTEXT;
            asm("retfie");


        }
    }

}

void setTimerTasks() {
    TMR1IF = 0;
    /* Enable 16-bit TMR1 register,no pre-scale,internal clock, timer OFF */
    T1CON = 0x80;
    TMR1 = Timer1; /* Load Count for generating delay of 1ms */
    TMR1ON = 1; /* Turn ON Timer1 */
    TMR1IE = 1; /* Enable Timer1 Overflow Interrupt */
}

void startRTOS(void) {
    setTimerTasks();
    IPEN = 1;
    GIEH = 1;
    GIEL = 1;
    TMR1IF = 1;
}

void initTask(unsigned char TaskNo, unsigned int t) {

    taskStack[TaskNo][0][0] = TOSL;
    taskStack[TaskNo][1][0] = TOSH;
    taskStack[TaskNo][2][0] = TOSU;
    taskTime[TaskNo] = t;
    asm("POP");
}