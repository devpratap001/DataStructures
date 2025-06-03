#include <stdlib.h>
#include "stack.h"

size_t getsize(datatype);

void stack_init(stack* st, datatype dtype)
{
    st->tail = NULL;
    st->dtype = dtype;
    st->size = 0;
};

void stack_free(stack* st)
{
    st->size = 0;
    while (st->tail != NULL)
    {
        struct node* temp = st->tail->prev;
        free(st->tail->data);
        free(st->tail);
        st->tail = temp;
    };
};

int push(stack* st, void* dat, datatype dtype)
{
    if (st->dtype != dtype)
        return 0;
    struct node* temp = malloc(sizeof(struct node));
    if (!temp)
        return 0;
    size_t size = getsize(dtype);
    temp->data = malloc(size);
    if (!temp->data)
    {
        free(temp);
        return 0;
    }
    switch (dtype)
    {
    case TYPE_CHAR:
        *(char*)temp->data = *(char*)dat;
        break;
        case TYPE_INT:
        *(int*)temp->data = *(int*)dat;
        break;
    case TYPE_FLOAT:
        *(float*)temp->data = *(float*)dat;
        break;
    case TYPE_DOUBLE:
        *(double*)temp->data = *(double*)dat;
        break;
        
    default:
        *(char*)temp->data = *(char*)dat;
        break;
    }
    temp->prev = st->tail;
    st->tail = temp;
    st->size++;
    return 1;
};

int pop(stack* st)
{
    if (st->tail == NULL)
        return 0;
    struct node* temp = st->tail;
    st->tail =st->tail->prev;
    st->size--;
    free(temp->data);
    free(temp);
    temp = NULL;
    return 1;
};

int is_empty(stack* st)
{
    return st->size == 0;
};

int peek(stack* st, void* dat)
{
    if (st->size == 0)
        return 0;
    switch (st->dtype)
    {
    case TYPE_CHAR:
        *(char*)dat = *(char*)st->tail->data;
        break;
    case TYPE_INT:
        *(int*)dat = *(int*)st->tail->data;
        break;
    case TYPE_FLOAT:
        *(float*)dat = *(float*)st->tail->data;
        break;
    case TYPE_DOUBLE:
        *(double*)dat = *(double*)st->tail->data;
        break;
        
    default:
        *(char*)dat = *(char*)st->tail->data;
        break;
    }
    return 1;
};

size_t getsize(datatype dtype)
{
    switch (dtype)
    {
    case TYPE_CHAR:
        return sizeof(char);
        break;
    case TYPE_INT:
        return sizeof(int);
        break;
    case TYPE_FLOAT:
        return sizeof(float);
        break;
    case TYPE_DOUBLE:
        return sizeof(double);
        break;
    
    default:
        return sizeof(char);
        break;
    }
};