#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "static_arrays.h"

//===================================================================

#define MAP_DATATYPE                         \
switch (dtype)                               \
{                                            \
    case TYPE_CHAR:                          \
        size = sizeof(char);                 \
        break;                               \
    case TYPE_INT:                           \
        size = sizeof(int);                  \
        break;                               \
    case TYPE_FLOAT:                         \
        size = sizeof(float);                \
        break;                               \
    case TYPE_DOUBLE:                        \
        size = sizeof(double);               \
        break;                               \
    default:                                 \
        return 0;                            \
}                                            \

int array_init(array* arr1, int capacity)
{
    arr1->data = malloc(capacity*sizeof(array_data));
    if (!arr1->data)
        return 0;
    arr1->capacity = capacity;
    arr1->size = 0;
    return 1;
};

int array_free(array* arr1)
{
    for (int i = 0; i < arr1->size; i++)
        free(arr1->data[i].value);
    free(arr1->data);
    return 1;
};

int push(array* arr1, void* input, datatype dtype)
{
    if (arr1->size >= arr1->capacity)
        return 0;
    size_t size;
    MAP_DATATYPE;
    void* temp = malloc(size);
    if (!temp)
        return 0;
    memcpy(temp, input, size);
    arr1->data[arr1->size].value = temp;
    arr1->data[arr1->size].type = dtype;
    arr1->size++;
    return 1;
};

int pop(array* arr1)
{
    if (arr1->size == 0)
        return 0;
    free(arr1->data[arr1->size -1].value);
    arr1->data[arr1->size -1].value = NULL;
    arr1->size--;
    return 1;
};

int insert(array* arr1, int index, void* input, datatype dtype)
{
    if (arr1->size >= arr1->capacity)
        return 0;
    if (index < 0 || index >= arr1->size)
        return 0;
    size_t size;
    MAP_DATATYPE;
    for (int i = arr1->size; i > index; i--)
    {
        arr1->data[i].value = arr1->data[i-1].value;
        arr1->data[i].type = arr1->data[i-1].type;
    }
    void* temp = malloc(size);
    if (!temp)
        return 0;
    memcpy(temp, input, size);
    arr1->data[index].value = temp;
    arr1->data[index].type = dtype;
    arr1->size++;
    return 1;
};

int get(array* arr1, int index, void* output, datatype dtype)
{
    if (index < 0 || index >= arr1->size)
        return 0;
    size_t size;
    MAP_DATATYPE;
    if (arr1->data[index].type != dtype)
        return 0;
    memcpy(output, arr1->data[index].value, size);
    return 1;
};

int set(array* arr1, int index, void* input, datatype dtype)
{
    if (index < 0 || index >= arr1->size)
        return 0;
    size_t size;
    MAP_DATATYPE;
    if (arr1->data[index].type != dtype)
        return 0;
    memcpy(arr1->data[index].value, input, size);
    return 1;
};

void print_array(array* arr1)
{
    for (int i = 0; i < arr1->size; i++)
    {
        void* ptr;
        ptr = arr1->data[i].value;
        switch (arr1->data[i].type)
        {
        case TYPE_INT:
            printf("%d ", *(int*)ptr);
            break;
        case TYPE_CHAR:
            printf("%c ", *(char*)ptr);
            break;
        case TYPE_FLOAT:
            printf("%f ", *(float*)ptr);
            break;
        case TYPE_DOUBLE:
            printf("%lf ", *(double*)ptr);
            break;
        
        default:
            break;
        }
    }
    printf("\n");
};

//===================================================================

// int array_init(array* arr1, int datatype, int capacity)
// {
//     arr1->arr = malloc(datatype*capacity);
//     if (!arr1->arr)
//         return 0;
//     arr1->capacity= capacity;
//     arr1->size = 0;
//     arr1->data_size = datatype;
//     return 1;
// };

// int push(array* arr1, void* data)
// {
//     if (arr1->size >= arr1->capacity)
//         return 0;
//     void* ptr = arr1->arr + arr1->size*arr1->data_size;
//     memcpy(ptr, data, arr1->data_size);
//     arr1->size++;
//     return 1;
// };

// int pop(array* arr1)
// {
//     if (arr1->size == 0)
//         return 0;
//     arr1->size--;
//     return 1;
// };

// int insert(array* arr1, int index, void* data)
// {
//     if (arr1->size >= arr1->capacity)
//         return 0;
//     if (index < 0 || index >= arr1->size)
//         return 0;
//     void* ptr = arr1->arr + arr1->size*arr1->data_size;
//     while (ptr != arr1->arr + index*arr1->data_size)
//     {
//         memcpy(ptr, ptr -arr1->data_size, arr1->data_size);
//         ptr = ptr - arr1->data_size;
//     }
//     memcpy(ptr, data, arr1->data_size);
//     arr1->size++;
//     return 1;
// };

// int get(array* arr1, int index, void* data)
// {
//     if (index < 0 || index >= arr1->size)
//         return 0;
//     memcpy(data, arr1->arr + index*arr1->data_size, arr1->data_size);
//     return 1;
// };

// int set(array* arr1, int index, void* data)
// {
//     if (index < 0 || index >= arr1->size)
//         return 0;
//     memcpy(arr1->arr + index*arr1->data_size, data, arr1->data_size);
//     return 1;
// };

// int array_free(array* arr1)
// {
//     free(arr1->arr);
//     arr1->arr = NULL;
//     arr1->size = 0;
//     return 1;
// };

//===========================================================================



// void array_init(array* arr)
// {
//     arr->size = 0;
//     arr->capacity = ARRAY_SIZE;
// };

// int push(array* arr, int data)
// {
//     if (arr->size >= arr->capacity)
//         return 0;
//     arr->array[arr->size++] = data;
//     return 1;
// };

// int pop(array* arr)
// {
//     if (arr->size == 0)
//         return 0;
//     arr->size--;
//     return 1;
// };

// int insert(array* arr, int index, int data)
// {
//     if (index < 0 || index > arr->size)
//         return 0;
//     if (arr->size == arr->capacity)
//         return 0;
//     for (int i = arr->size; i > index; i--)
//         arr->array[i] = arr->array[i-1];
//     arr->array[index] = data;
//     arr->size++;
//     return 1;
// };

// int get(array* arr, int index)
// {
//     if (index < 0 || index >= arr->size)
//         return -1;
//     return arr->array[index];
// };

// int set(array* arr, int index, int data)
// {
//     if (index < 0 || index >= arr->size)
//         return -1;
//     arr->array[index] = data;
//     return 1;
// }