#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->array = (int*)malloc(sizeof(int) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

int isEmpty(Stack* stack) {
    return (stack->top == -1);
}

int isFull(Stack* stack) {
    return (stack->top == stack->capacity - 1);
}

void resetStack(Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
}

void push(Stack* stack, int data) {
    if (isFull(stack)) {
        stack->capacity *= 2;
        stack->array = (int*)realloc(stack->array, sizeof(int) * stack->capacity);
    }
    stack->array[++stack->top] = data;
}

int pop(Stack* stack) {
    return stack->array[stack->top--];
}

void destroyStack(Stack* stack) {
    free(stack->array);
    free(stack);
}