#ifndef SEMAPHORE_H
#define	SEMAPHORE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include "stack_structure_RTOS.h"


typedef struct {    
    int     semaphore;
    struct Stack*  blockedTasks;
}Semaphore;


Semaphore *createSemaphore(int size);
int wait(Semaphore *S);
void signal(Semaphore *S);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

