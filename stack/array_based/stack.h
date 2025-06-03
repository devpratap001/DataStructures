#ifndef STACK_H
#define STACK_H


typedef enum
{
    TYPE_INT,
    TYPE_CHAR,
    TYPE_FLOAT,
    TYPE_DOUBLE
}datatype;

typedef struct stack_obj
{
    void* arr;
    int top, capacity;
    datatype dtype;
}stack;

void stack_init(stack*, datatype);
int push(stack*, void*, datatype);
int pop(stack*);
int is_empty(stack*);
int is_full(stack*);
int peek(stack*, void*, datatype);
void stack_free(stack*);

#endif