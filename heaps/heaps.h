#ifndef HEAPS_H
#define HEAPS_H

typedef enum
{
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE
}datatype;

typedef struct heap_max
{
    void* data;
    int size, capacity;
    datatype dtype;
    int (*comparator)(void*, void*);
}heap_max;

int heap_init(heap_max*, int, datatype);
void heap_free(heap_max*);
int push(heap_max*, void*);
int pop(heap_max*);
int top(heap_max*, void*);

#endif