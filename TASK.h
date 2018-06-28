// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TASK_H
#define	TASK_H

#include <xc.h> // include processor files - each processor file is guarded.  
#define MAX_TASKS 3
#define MINIMUM_TASK_TIME 10UL //us
#define NUMBER_OF_TASKS (MAX_TASKS+1)

#define FREQ_PIC 48UL // (MHz)
#define _XTAL_FREQ 48000000
#define PRESCALE 1UL
#define TIMER (65535UL - (MINIMUM_TASK_TIME*FREQ_PIC/(4*PRESCALE)))

#define MAX_SIZE_STACK 10 // maximum size of stack functions --> max functions for task


#define SAVE_CONTEXT {\
asm("MOVFF	WREG, _taskWREG");											\
asm("MOVFF   STATUS, _taskSTATUS");										\
asm("MOVFF	BSR, _taskBSR");											\
asm("MOVFF	FSR2L, _taskFSR2L");										\
asm("MOVFF	FSR2H, _taskFSR2H");										\
asm("MOVFF	FSR0L, _taskFSR0L");										\
asm("MOVFF	FSR0H, _taskFSR0H");										\
asm("MOVFF	TABLAT, _taskTABLAT");										\
asm("MOVFF	TBLPTRU, _taskTBLPTRU");									\
asm("MOVFF	TBLPTRH, _taskTBLPTRH");									\
asm("MOVFF	TBLPTRL, _taskTBLPTRL");									\
asm("MOVFF	PRODH, _taskPRODH");										\
asm("MOVFF	PRODL, _taskPRODL");										\
asm("MOVFF	PCLATU, _taskPCLATU");										\
asm("MOVFF	PCLATH, _taskPCLATH");										\
asm("CLRF	FSR0L");													\
asm("CLRF	FSR0H");													\
}

#define SAVE_INTO_STACK {\
savedContext[taskNumber][0] = taskPCLATH;\
savedContext[taskNumber][1] = taskPCLATU;\
savedContext[taskNumber][2] = taskPRODL;\
savedContext[taskNumber][3] = taskPRODH;\
savedContext[taskNumber][4] = taskTBLPTRL;\
savedContext[taskNumber][5] = taskTBLPTRH;\
savedContext[taskNumber][6] = taskTBLPTRU;\
savedContext[taskNumber][7] = taskTABLAT;\
savedContext[taskNumber][8] = taskFSR0H;\
savedContext[taskNumber][9] = taskFSR0L;\
savedContext[taskNumber][10] = taskFSR2H;\
savedContext[taskNumber][11] = taskFSR2L;\
savedContext[taskNumber][12] = taskBSR;\
savedContext[taskNumber][13] = taskSTATUS;\
savedContext[taskNumber][14] = taskWREG;\
}
#define RESTORE_FROM_STACK {\
taskPCLATH = savedContext[taskNumber][0];\
taskPCLATU = savedContext[taskNumber][1];\
taskPRODL = savedContext[taskNumber][2];\
taskPRODH = savedContext[taskNumber][3];\
taskTBLPTRL = savedContext[taskNumber][4];\
taskTBLPTRH = savedContext[taskNumber][5];\
taskTBLPTRU = savedContext[taskNumber][6];\
taskTABLAT = savedContext[taskNumber][7];\
taskFSR0H = savedContext[taskNumber][8];\
taskFSR0L = savedContext[taskNumber][9];\
taskFSR2H = savedContext[taskNumber][10];\
taskFSR2L = savedContext[taskNumber][11];\
taskBSR = savedContext[taskNumber][12];\
taskSTATUS = savedContext[taskNumber][13];\
taskWREG = savedContext[taskNumber][14];\
}

#define RESTORE_CONTEXT {\
asm("MOVFF	_taskPCLATH, PCLATH");										\
asm("MOVFF	_taskPCLATU, PCLATU");										\
asm("MOVFF	_taskPRODL, PRODL");										\
asm("MOVFF	_taskPRODH, PRODH");										\
asm("MOVFF	_taskTBLPTRL, TBLPTRL");									\
asm("MOVFF	_taskTBLPTRH, TBLPTRH");									\
asm("MOVFF	_taskTBLPTRU, TBLPTRU");									\
asm("MOVFF	_taskTABLAT, TABLAT");										\
asm("MOVFF	_taskFSR0H, FSR0H");										\
asm("MOVFF	_taskFSR0L, FSR0L");										\
asm("MOVFF	_taskFSR2H, FSR2H");										\
asm("MOVFF	_taskFSR2L, FSR2L");										\
asm("MOVFF	_taskBSR, BSR");											\
asm("MOVFF	_taskSTATUS, STATUS");										\
asm("MOVFF	_taskWREG, WREG");											\
}
unsigned short Timer1 = TIMER;
unsigned char taskStack     [NUMBER_OF_TASKS][3][MAX_SIZE_STACK];
unsigned char savedContext  [NUMBER_OF_TASKS][15];
unsigned char taskBlocked   [NUMBER_OF_TASKS];
unsigned int  taskTime      [NUMBER_OF_TASKS];
unsigned int  taskCountTime [NUMBER_OF_TASKS];
unsigned char size_stack    [NUMBER_OF_TASKS];
unsigned char taskNumber = 0;
unsigned char taskWREG, taskSTATUS, taskBSR;
unsigned char taskFSR2L,taskFSR2H,taskFSR0L,taskFSR0H,taskTABLAT;
unsigned char taskTBLPTRU,taskTBLPTRH,taskTBLPTRL,taskPRODH,taskPRODL,taskPCLATU,taskPCLATH;

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

