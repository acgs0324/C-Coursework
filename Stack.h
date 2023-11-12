#ifndef STACK_H
#define STACK_H

typedef struct{
    int* array;
    int top;
    int capacity;
} Stack;

Stack* createStack(int);
int isFull(Stack* );
int isEmpty(Stack* );
void resetStack(Stack* );
void push(Stack* , int);
int pop(Stack* );
void destroyStack(Stack* );

#endif