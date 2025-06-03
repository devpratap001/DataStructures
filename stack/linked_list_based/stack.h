#ifndef STACK_H
#define STACK_H

typedef enum
{
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE
}datatype;

struct node
{
    void* data;
    struct node* prev;
};

typedef struct linkedlistobj
{
    struct node* tail;
    int size;
    datatype dtype;
}stack;

void stack_init(stack*, datatype);
void stack_free(stack*);
int push(stack*, void*, datatype);
int pop(stack*);
int is_empty(stack*);
int peek(stack*, void*);

#endif