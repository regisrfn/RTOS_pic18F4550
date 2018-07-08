// C program for array implementation of stack
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "stack_structure_RTOS.h"

// function to create a stack of given capacity. It initializes size of
// stack as 0

struct Stack* createStack(unsigned char capacity) {
    static unsigned char max_size;
    max_size = capacity;

    static struct Stack* stack;
    stack = (struct Stack*) malloc(sizeof (struct Stack));
    stack->capacity = max_size;
    stack->top = -1;
    stack->array = (char*) malloc(stack->capacity * sizeof (char));
    return stack;
}

// Stack is full when top is equal to the last index

char isFull(struct Stack* s) {
    static struct Stack* stack;
    stack = s;
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1

char isEmpty(struct Stack* s) {
    static struct Stack* stack;
    stack = s;
    return stack->top == -1;
}

// Function to add an item to stack.  It increases top by 1

void push(struct Stack* s, char item) {
    static struct Stack* stack;
    stack = s;
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack.  It decreases top by 1

char pop(struct Stack* s) {
    static struct Stack* stack;
    stack = s;
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

