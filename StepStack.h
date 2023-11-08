typedef struct {
    int array[1000];
    int top;
} StepStack;

void initStack(StepStack* );

int isEmpty(StepStack* );

void resetStack(StepStack* );

void push(StepStack* , int);

int pop(StepStack* );