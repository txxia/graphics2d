#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Stack stack_init(void) {
    Stack ptr = (Stack) malloc(sizeof(struct stack));
    if(ptr != NULL){
        ptr->next = NULL;
    }
    else
        fputs("cannot create stack\n", stderr);
    return ptr;
}

void stack_push(Stack aStack, stack_data data) {
    Stack aNode = stack_init();
    aNode->data = data;
    aNode->next = aStack->next;
    aStack->next = aNode;
}

stack_data stack_pop(Stack aStack) {
    Stack top = aStack->next;
    stack_data data;
    if(top!=NULL){
        data = top->data;
        aStack->next = top->next;
        top->next = NULL;
        free(top);
    }
    return data;
}

stack_data stack_top(Stack aStack) {
    return aStack->next->data;
}

_Bool stack_empty(Stack aStack) {
    return (aStack->next == NULL);
}

void stack_clear(Stack aStack) {
    while(!stack_empty(aStack)) {
        stack_pop(aStack);
    }
}

void stack_delete(Stack aStack){
    if(!stack_empty(aStack))
        stack_clear(aStack);
    free(aStack);
}
