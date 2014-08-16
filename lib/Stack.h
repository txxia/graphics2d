#ifndef STACK_H
#define STACK_H

/*
* Stack implementation with easily changeable data type.
*/

/* Node structure */
typedef struct _stack Stack;

typedef struct _stack_data{
    float x;
    float y;
} StackData;

/* Create an empty stack. */
extern Stack* stack_init(void);

/* Push the data onto the stack. */
extern void stack_push(Stack* aStack, StackData data);

/* Pop the data from top the stack.
   Return garbage if the stack is empty.*/
extern StackData stack_pop(Stack* aStack);

/* Return a copy of the data on top of the stack.
   Return garbage if the stack is empty. */
extern StackData stack_top(Stack* aStack);

/* Return true iff the stack is empty. */
extern _Bool stack_empty(Stack* aStack);

/* Empty the stack */
extern void stack_clear(Stack* aStack);

/* Delete the entire stack. (makes the ptr to the stack dangling) */
extern void stack_delete(Stack* aStack);

/* constructor for stack data */
extern StackData stack_data(float x, float y);

#endif
