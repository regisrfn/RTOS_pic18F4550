// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TASK_H
#define	TASK_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define NumberOfTasks 3 // tasks number + 1
#define FreqPIC 48
#define Prescale 2
#define TasksTime 10 //us
#define Timer (65535 - (TasksTime*FreqPIC/(unsigned short)(4*Prescale)))
#define EnterCritical GIE = 0;
#define ExitCritical  GIE = 1;
#define SwapTask {swapTask = 1;INTCONbits.TMR0IF = 1;}

#define saveRegisters {\
asm("MOVWF _taskWreg");\
asm("SWAPF STATUS,W");\
asm("MOVWF _taskStatus");\
asm("SWAPF	BSR, W");\
asm("MOVWF _taskBSR");\
asm("SWAPF	FSR2L, W");\
asm("MOVWF _taskFSR2L");\
asm("SWAPF	FSR2H, W");\
asm("MOVWF _taskFSR2H");\
asm("SWAPF	FSR0L, W");\
asm("MOVWF _taskFSR0L");\
asm("SWAPF	FSR0H, W");\
asm("MOVWF _taskFSR0H");\
asm("SWAPF	TABLAT, W");\
asm("MOVWF _taskTABLAT");\
asm("SWAPF	TBLPTRU, W");\
asm("MOVWF _taskTBLPTRU");\
asm("SWAPF	TBLPTRH, W");\
asm("MOVWF _taskTBLPTRH");\
asm("SWAPF	TBLPTRL, W");\
asm("MOVWF _taskTBLPTRL");\
asm("SWAPF	PRODH, W");\
asm("MOVWF _taskPRODH");\
asm("SWAPF	PRODL, W");\
asm("MOVWF _taskPRODL");\
asm("SWAPF	PCLATU, W");\
asm("MOVWF _taskPCLATU");\
asm("SWAPF	PCLATH, W");\
asm("MOVWF _taskPCLATH");\
asm("CLRF	FSR0L");\
asm("CLRF	FSR0H");\
asm("SWAPF	INDF0, W");\
asm("MOVWF _taskINDF0");\
asm("SWAPF	FSR0L, W");\
asm("MOVWF _taskFSR0L");\
asm("SWAPF	FSR0H, W");\
asm("MOVWF _taskFSR0H");\
}

#define saveContext {\
    savedContext[taskNumber][0] = taskWreg;\
    savedContext[taskNumber][1] = taskStatus;\
    savedContext[taskNumber][2] = taskBsr;}
#define restoreContext {\
    asm ("MOVWF _taskStatus,W");\
    asm ("MOVWF STATUS");\
    asm ("SWAPF _taskWreg,F");\
    asm ("SWAPF _taskWreg,W");\
}
unsigned short Timer0 = Timer + 1;
unsigned char Temp, taskWreg, taskStatus, taskBsr, swapTask = 0;
unsigned char savedContext[NumberOfTasks][3];
unsigned char taskNumber = 0;
unsigned char taskStack[NumberOfTasks][3];
unsigned int taskCountTime[NumberOfTasks];
unsigned int taskTime[NumberOfTasks];
unsigned char taskBlocked[NumberOfTasks];

unsigned char taskWREG, taskSTATUS, taskBSR, taskFSR2L, taskFSR2H, taskFSR0L;
unsigned char taskFSR0H, taskTABLAT, taskTBLPTRU, taskTBLPTRH, taskTBLPTRL;
unsigned char taskPRODH, taskPRODL, taskPCLATU, taskPCLATH, taskFSR0L;
unsigned char taskFSR0H, taskINDF0, taskFSR0L, taskFSR0H; 

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

