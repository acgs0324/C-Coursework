typedef struct {
    int* array;
    int top;
    int capacity;
} StepStack;

StepStack* createStack(int);
int isFull(StepStack* );
int isEmpty(StepStack* );
void resetStack(StepStack* );
void push(StepStack* , int);
int pop(StepStack* );
void destroyStack(StepStack* );