#include <stdlib.h>
#include "stack.h"

size_t getsize(datatype);
void reallocate_array(stack* st);

void stack_init(stack* st, datatype dtype)
{
    st->capacity = 2;
    size_t size = getsize(dtype);
    switch (dtype)
    {
    case TYPE_CHAR:
        st->arr = (char*)malloc(size*st->capacity);
        break;
    case TYPE_INT:
        st->arr = (int*)malloc(size*st->capacity);
        break;
    case TYPE_FLOAT:
        st->arr = (float*)malloc(size*st->capacity);
        break;
    case TYPE_DOUBLE:
        st->arr = (double*)malloc(size*st->capacity);
        break;
    
    default:
        st->arr = malloc(size*st->capacity);
        break;
    }

    st->dtype = dtype;
    st->top = -1;
};

void stack_free(stack* st)
{
    free(st->arr);
    st->capacity = 2;
    st->top = -1;
};

int push(stack* st, void* val, datatype dtype)
{
    reallocate_array(st);
    if (st->top >= st->capacity -1)
        return 0;
    if (st->dtype != dtype)
        return 0;
    switch (dtype)
    {
        case TYPE_CHAR:
            *(char*)(st->arr + ++st->top) = *(char*)val;
            break;
        case TYPE_INT:
            *(int*)(st->arr + ++st->top) = *(int*)val;
            break;
        case TYPE_FLOAT:
            *(float*)(st->arr + ++st->top) = *(float*)val;
            break;
        case TYPE_DOUBLE:
            *(double*)(st->arr + ++st->top) = *(double*)val;
            break;
        default:
            return 0;
            break;
    }
    return 1;
};

int pop(stack* st)
{
    if (st->top == -1)
        return 0;
    st->top--;
    return 1;
};

int is_empty(stack* st)
{
    return st->top == -1;
};

int is_full(stack* st)
{
    return st->top == st->capacity -1;
};

int peek(stack* st, void* dat, datatype dtype)
{
    if (st->dtype != dtype)
        return 0;
    switch (st->dtype)
    {
    case TYPE_CHAR:
        *(char*)dat = *(char*)(st->arr + st->top);
        break;
        case TYPE_INT:
        *(int*)dat = *(int*)(st->arr + st->top);
        break;
        case TYPE_FLOAT:
        *(float*)dat = *(float*)(st->arr + st->top);
        break;
        case TYPE_DOUBLE:
        *(double*)dat = *(double*)(st->arr + st->top);
        break;
        
        default:
        *(char*)dat = *(char*)(st->arr + st->top);
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
        return 1;
        break;
    }
};

void reallocate_array(stack* st)
{
    if (st->top < st->capacity -1)
        return;
    st->capacity = st->capacity*2;
    size_t size = getsize(st->dtype);
    void* temp = realloc(st->arr, size*st->capacity);
    if (!temp)
        return;
    st->arr = temp;
    temp = NULL;
};