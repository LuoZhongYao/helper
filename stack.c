#include <stdlib.h>
#include "stack.h"
#define stack_size(n) ((n * sizeof(Attribule)) + sizeof(Stack))
Stack *newStack(int n){
    Stack *stack = NULL;
    stack = malloc(stack_size(n));
    if(stack){
        stack->cnt = n;
        stack->empty = 0;
        stack->top = 0;
    }
    return stack;
}

void delStack(Stack **stack){
    if(stack){
        if(*stack)
            free(*stack);
        *stack = NULL;
    }
}

Attribule popStack(Stack *stack){
    if(stack && stack->top > 0){
        stack->top--;
    } else {
        stack->empty = 1;
    }
    return stack->stackp[stack->top];
}

void pushStack(Stack **stack,Attribule Attribule){
    if(stack && *stack){
        if((*stack)->cnt < (*stack)->top){
            (*stack)->cnt += 10;
            *stack = realloc(*stack,stack_size((*stack)->cnt));
        }
        if(stack){
            (*stack)->empty = 0;
            (*stack)->stackp[(*stack)->top] = Attribule;
            (*stack)->top++;
        }
    }
}
