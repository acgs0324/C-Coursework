#include "StepStack.h"

void initStack(StepStack* step_record) {
    step_record->top = -1; // -1 indicates an empty stack
}

int isEmpty(StepStack* step_record) {
    return step_record->top == -1;
}

void resetStack(StepStack* step_record) {
    while (!isEmpty(step_record)) {
        pop(step_record);
    }
}

void push(StepStack* step_record, int data) {
    step_record->array[++step_record->top] = data;
}

int pop(StepStack* step_record) {
    return step_record->array[step_record->top--];
}