#ifndef DYNAMIC_ARRAYS_H
#define DYNAMIC_ARRAYS_H

#include <stddef.h>

//=========================================================

typedef enum
{
    TYPE_INT, TYPE_FLOAT, TYPE_CHAR, TYPE_DOUBLE
}datatype;

typedef struct
{
    void* value;
    datatype type;
}array_data;


typedef struct
{
    array_data* data;
    size_t size, capacity;
}array;

int array_init(array*);
int push(array*, void*, datatype);
int pop(array*);
int insert(array*, int, void*, datatype);
int get(array*, int, void*, datatype);
int set(array*, int, void*, datatype);
void print_array(array*);
int array_free(array*);


//=========================================================

// typedef struct
// {
//     void* arr;
//     size_t size, capacity, data_size;
// }array;

// int array_init(array*, int, int);
// int push(array*, void*);
// int pop(array*);
// int insert(array*, int, void*);
// int get(array*, int, void*);
// int set(array*, int, void*);
// int array_free(array*);


//===========================================================


// #define def_array(type, ARRAY_SIZE)                     \
// typedef struct                                          \
// {                                                       \
//     type array[ARRAY_SIZE];                             \
//     size_t size;                                        \
//     size_t capacity;                                    \
// }array;                                                 \
//                                                         \
// void array_init(array* arr)                             \
// {                                                       \
//     arr->size = 0;                                      \
//     arr->capacity = ARRAY_SIZE;                         \
// };                                                      \
//                                                         \
// int push(array* arr, type data)                         \
// {                                                       \
// if (arr->size >= arr->capacity)                         \
//         return 0;                                       \
// arr->array[arr->size++] = data;                         \
//     return 1;                                           \
// };                                                      \
//                                                         \
// int pop(array* arr)                                     \
// {                                                       \
//     if (arr->size == 0)                                 \
//         return 0;                                       \
//     arr->size--;                                        \
//     return 1;                                           \
// };                                                      \
//                                                         \
// int insert(array* arr, int index, type data)            \
// {                                                       \
//     if (index < 0 || index > arr->size)                 \
//         return 0;                                       \
//     if (arr->size == arr->capacity)                     \
//         return 0;                                       \
//     for (int i = arr->size; i > index; i--)             \
//         arr->array[i] = arr->array[i-1];                \
//     arr->array[index] = data;                           \
//     arr->size++;                                        \
//     return 1;                                           \
// };                                                      \
//                                                         \
// int get(array* arr, int index, type* data)              \
// {                                                       \
//     if (index < 0 || index >= arr->size)                \
//         return 0;                                       \
//     *data = arr->array[index];                          \
//     return 1;                                           \
// };                                                      \
//                                                         \
// int set(array* arr, int index, type data)               \
// {                                                       \
//     if (index < 0 || index >= arr->size)                \
//         return 0;                                       \
//     arr->array[index] = data;                           \
//     return 1;                                           \
// }                                                       \


//=================================================================


// #define ARRAY_SIZE 10

// typedef struct
// {
//     int array[ARRAY_SIZE];
//     size_t size, capacity;
// }array;

// void array_init(array*);
// int push(array*, int);
// int pop(array*);
// int insert(array*, int, int);
// int get(array*, int);
// int set(array*, int, int);

#endif