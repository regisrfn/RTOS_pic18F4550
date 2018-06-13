// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TASK_H
#define	TASK_H

#include <xc.h> // include processor files - each processor file is guarded.  
#define MAX_TASKS 3
#define MINIMUM_TASK_TIME 50UL //us
#define NUMBER_OF_TASKS (MAX_TASKS+1)

#define FREQ_PIC 48UL // (MHz)
#define _XTAL_FREQ 48000000
#define PRESCALE 1UL
#define TIMER (65535UL - (MINIMUM_TASK_TIME*FREQ_PIC/(4*PRESCALE)))

#define MAX_SIZE_STACK 10 // maximum size of stack functions --> max functions for task

#define SAVE_REGISTERS {\
taskWREG = WREG;\
taskSTATUS = STATUS;\
taskBSR = BSR;\
}

#define SAVE_CONTEXT {\
    savedContext[taskNumber][0] = taskWREG;\
    savedContext[taskNumber][1] = taskSTATUS;\
    savedContext[taskNumber][2] = taskBSR;\
}

#define RESTORE_CONTEXT {\
    BSR = taskBSR;\
    WREG = taskWREG;\
    STATUS = taskSTATUS;\
}
unsigned short Timer1 = TIMER;
unsigned char taskStack     [NUMBER_OF_TASKS][3][MAX_SIZE_STACK];
unsigned char savedContext  [NUMBER_OF_TASKS][3];
unsigned char taskBlocked   [NUMBER_OF_TASKS];
unsigned int  taskTime      [NUMBER_OF_TASKS];
unsigned int  taskCountTime [NUMBER_OF_TASKS];
unsigned char size_stack    [NUMBER_OF_TASKS];
unsigned char taskNumber = 0;
unsigned char taskWREG, taskSTATUS, taskBSR;

void interrupt highPriority();
void setTimerTasks();
void initBlocked();
void initTask(unsigned char TaskNo, unsigned int t);
void startRTOS();

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* TASK_H */

