#ifndef _STACK_H
#define _STACK_H

/*
* Stack implementation with easily changeable data type.
*/

/* Data structure */
typedef struct{
    int x;
    int y;
} stack_data;

/* Node structure */
typedef struct stack{
    stack_data data;
    struct stack* next;
}* Stack;

/* Create an empty stack. */
Stack stack_init(void);

/* Push the data onto the stack. */
void stack_push(Stack aStack, stack_data data);

/* Pop the data from top the stack.
   Return garbage if the stack is empty.*/
stack_data stack_pop(Stack aStack);

/* Return a copy of the data on top of the stack.
   Return garbage if the stack is empty. */
stack_data stack_top(Stack aStack);

/* Return true iff the stack is empty. */
_Bool stack_empty(Stack aStack);

/* Empty the stack */
void stack_clear(Stack aStack);

/* Delete the entire stack. (makes the ptr to the stack dangling) */
void stack_delete(Stack aStack);

#include "Stack.c"

#endif
