#include <stdlib.h>
#include "heaps.h"

#define NULL ((void *)0)

size_t getsize(datatype);
void heapify_up(heap_max *);
void heapify_down(heap_max *);
int (*def_comparator(datatype dtype))(void *, void *);
int comp_char(void *, void *);
int comp_int(void *, void *);
int comp_float(void *, void *);
int comp_double(void *, void *);
void swap_nodes(void *, void *, size_t);

int heap_init(heap_max *heap, int size, datatype dtype)
{
    if (heap == NULL)
        return 0;
    heap->capacity = size;
    size_t bytesize = getsize(dtype);
    heap->data = malloc(bytesize * heap->capacity);
    if (!heap->data)
        return 0;
    heap->comparator = def_comparator(dtype);
    heap->size = 0;
    heap->dtype = dtype;
    return 1;
};

void heap_free(heap_max *heap)
{
    free(heap->data);
    heap = NULL;
};

int push(heap_max *heap, void *val)
{
    if (!val || !heap)
        return 0;
    if (heap->size >= heap->capacity)
        return 0;
    switch (heap->dtype)
    {
    case TYPE_CHAR:
        *(char *)(heap->data + heap->size * sizeof(char)) = *(char *)val;
        break;
    case TYPE_INT:
        *(int *)(heap->data + heap->size * sizeof(int)) = *(int *)val;
        break;
    case TYPE_FLOAT:
        *(float *)(heap->data + heap->size * sizeof(float)) = *(float *)val;
        break;
    case TYPE_DOUBLE:
        *(double *)(heap->data + heap->size * sizeof(double)) = *(double *)val;
        break;

    default:
        return 0;
        break;
    }
    heap->size++;
    heapify_up(heap);
    return 1;
};

int pop(heap_max *heap)
{
    if (!heap || heap->size == 0)
        return 0;
    size_t byte_size = getsize(heap->dtype);
    swap_nodes(heap->data, heap->data + (heap->size - 1) * byte_size, byte_size);
    heap->size--;
    if (heap->size <= 1)
        return 1;
    heapify_down(heap);
    return 1;
};

int top(heap_max *heap, void *val)
{
    if (!heap || !val)
        return 0;
    if (heap->size == 0)
        return 0;
    switch (heap->dtype)
    {
    case TYPE_CHAR:
        *(char *)val = *(char *)(heap->data);
        break;
    case TYPE_INT:
        *(int *)val = *(int *)(heap->data);
        break;
    case TYPE_FLOAT:
        *(float *)val = *(float *)(heap->data);
        break;
    case TYPE_DOUBLE:
        *(double *)val = *(double *)(heap->data);
        break;

    default:
        *(char *)val = *(char *)(heap->data);
        break;
    }
    return 1;
}

void heapify_up(heap_max *heap)
{
    size_t byte_size = getsize(heap->dtype);
    void *parent_node, *curr_node;
    size_t index = heap->size - 1;
    curr_node = heap->data + (index * byte_size);
    parent_node = heap->data + ((index - 1) / 2) * byte_size;
    while (index > 0)
    {
        curr_node = heap->data + (index * byte_size);
        parent_node = heap->data + ((index - 1) / 2) * byte_size;

        if (heap->comparator(parent_node, curr_node) < 0)
        {
            swap_nodes(parent_node, curr_node, byte_size);
            index = (index - 1) / 2;
        }
        else
        {
            break;
        }
    }
    return;
};

void heapify_down(heap_max *heap)
{
    if (!heap)
        return;
    if (heap->size == 0)
        return;
    size_t byte_size = getsize(heap->dtype);
    void *child1_node, *child2_node, *curr_node;
    size_t index = 0;
    curr_node = heap->data;
    child1_node = heap->data + ((index * 2 + 1) * byte_size);
    child2_node = heap->data + ((index * 2 + 2) * byte_size);
    while (index * 2 + 1 <= heap->size - 1)
    {
        curr_node = heap->data + (index * byte_size);
        child1_node = heap->data + (index * 2 + 1) * byte_size;
        if ((index * 2 + 2) < heap->size - 1)
            child2_node = heap->data + (index * 2 + 2) * byte_size;

        if (heap->comparator(child1_node, curr_node) > 0)
        {
            swap_nodes(child1_node, curr_node, byte_size);
            index = index * 2 + 1;
        }
        else if ((index * 2 + 2 <= heap->size - 1) && heap->comparator(child2_node, curr_node) > 0)
        {
            swap_nodes(child2_node, curr_node, byte_size);
            index = index * 2 + 2;
        }
        else
        {
            break;
        }
    }
    return;
};

void swap_nodes(void *parent, void *child, size_t bytes)
{
    char temp;
    for (int i = 0; i < bytes; i++)
    {
        temp = *(char *)(parent + i);
        *(char *)(parent + i) = *(char *)(child + i);
        *(char *)(child + i) = temp;
    }
};

int (*def_comparator(datatype dtype))(void *, void *)
{
    switch (dtype)
    {
    case TYPE_CHAR:
        return comp_char;
        break;
    case TYPE_INT:
        return comp_int;
        break;
    case TYPE_FLOAT:
        return comp_float;
        break;
    case TYPE_DOUBLE:
        return comp_double;
        break;

    default:
        return comp_char;
        break;
    }
};

int comp_char(void *val1, void *val2)
{
    return *(char *)val1 - *(char *)val2;
};

int comp_int(void *val1, void *val2)
{
    return *(int *)val1 - *(int *)val2;
};

int comp_float(void *val1, void *val2)
{
    float x = *(float *)val1, y = *(float *)val2;
    return (x > y) - (x < y);
};

int comp_double(void *val1, void *val2)
{
    double x = *(double *)val1, y = *(double *)val2;
    return (x > y) - (x < y);
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