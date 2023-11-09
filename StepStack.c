#include "StepStack.h"
#include <stdio.h>
#include <stdlib.h>

StepStack* createStack(int capacity) {
    StepStack* stack = (StepStack*)malloc(sizeof(StepStack));
    printf("Stack size: %lu\n", sizeof(StepStack));
    if (!stack) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    stack->array = (int*)malloc(sizeof(int) * capacity);
    printf("Int size: %lu\n", sizeof(int));
    if (!stack->array) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

int isEmpty(StepStack* step_record) {
    return step_record->top == -1;
}

int isFull(StepStack* stack) {
    return (stack->top == stack->capacity - 1);
}

void resetStack(StepStack* step_record) {
    while (!isEmpty(step_record)) {
        pop(step_record);
    }
}

void push(StepStack* step_record, int data) {
    if (isFull(step_record)) {
        // Double the capacity if the stack is full
        printf("Stack is full. Doubling the capacity.\n");
        step_record->capacity *= 2;
        step_record->array = (int*)realloc(step_record->array, sizeof(int) * step_record->capacity);
        if (!step_record->array) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
    }

    step_record->array[++step_record->top] = data;
}

int pop(StepStack* step_record) {
    if (isEmpty(step_record)) {
        fprintf(stderr, "Stack is empty. Cannot pop.\n");
        exit(1);
    }
    return step_record->array[step_record->top--];
}

void destroyStack(StepStack* step_record) {
    free(step_record->array);
    free(step_record);
}