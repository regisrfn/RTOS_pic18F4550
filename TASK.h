// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TASK_H
#define	TASK_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define NumberOfTasks 3 // tasks number + 1
#define FreqPIC 48
#define Prescale 2
#define TasksTime 10 //us
#define Timer (65535 - (TasksTime*FreqPIC/(4*Prescale)))
#define EnterCritical GIE = 0;
#define ExitCritical  GIE = 1;
#define SwapTask {swapTask = 1;INTCONbits.TMR0IF = 1;}

volatile unsigned short Timer0 = Timer + 1 ;
volatile unsigned char Temp, taskWreg, taskStatus, taskBsr, swapTask = 0;
volatile unsigned char savedContext[NumberOfTasks][3];
volatile unsigned char taskNumber = 0;
volatile unsigned char taskStack[NumberOfTasks][3];
volatile unsigned int taskCountTime[NumberOfTasks];
volatile unsigned int taskTime[NumberOfTasks];
volatile unsigned char taskBlocked[NumberOfTasks];


void interrupt highPriority();
void  setTimerTasks();
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

