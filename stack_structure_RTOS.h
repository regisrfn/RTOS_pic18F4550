// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef STACK_STRUCT_RTOS_H
#define	STACK_STRUCT_RTOS_H

#include <xc.h> // include processor files - each processor file is guarded.  

// A structure to represent a stack
struct Stack
{
    char top;
    unsigned char capacity;
    char* array;
};

struct Stack* createStack(unsigned char capacity);
char isFull(struct Stack* stack);
char isEmpty(struct Stack* stack);
void push(struct Stack* stack, char item);
char pop(struct Stack* stack);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

