#ifndef __NONE_STACK_H__
#define __NONE_STACK_H__
#include "attribule.h"

typedef struct {
    int  cnt;
    int  top;
    int  empty;
    Attribule stackp[0];
}Stack;

Stack *newStack(int n);
void delStack(Stack **);
Attribule popStack(Stack *stack);
void pushStack(Stack **stack,Attribule);
#endif
