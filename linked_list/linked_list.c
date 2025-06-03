#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

#define MAP_DATATYPE            \
switch(dtype)                   \
{                               \
    case TYPE_CHAR:             \
        size = sizeof(char);    \
        break;                  \
    case TYPE_INT:              \
        size = sizeof(int);     \
        break;                  \
    case TYPE_FLOAT:            \
        size = sizeof(float);   \
        break;                  \
    case TYPE_DOUBLE:           \
        size = sizeof(double);  \
        break;                  \
    default:                    \
        size = sizeof(char);    \
        break;                  \
}                               \


void free_node(linked_list* list)
{
    free(list->data);
    free(list);
};
    
linked_list* list_init(linked_list** list, void* data, datatype dtype)
{
    *list = NULL;
    linked_list* temp = (linked_list*) malloc(sizeof(linked_list));
    if (!temp)
        return NULL;
    size_t size;
    MAP_DATATYPE;
    void* temp_data = malloc(size);
    if (!temp_data)
    {
        free(temp);
        return NULL;
    }
    memcpy(temp_data, data, size);
    temp->data = temp_data;
    temp_data = NULL;
    temp->next = NULL;
    temp->dtype = dtype;
    *list = temp;
    return temp;
};

void list_free(linked_list* list)
{
    while (list)
    {
        linked_list* temp = list;
        list = list->next;
        free_node(temp);
        temp = NULL;
    }
};

int push(linked_list* list, void* data, datatype dtype)
{
    if (list == NULL)
        return 0;
    linked_list* temp = list;
    while (temp->next != NULL)
        temp = temp->next;
    list_init(&temp->next, data, dtype);
    if (!temp->next)
        return 0;
    return 1;
};

linked_list* pop(linked_list* list)
{
    if (list == NULL || list->next == NULL)
        return list;
    linked_list* temp = list;
    while (temp->next->next != NULL)
        temp = temp->next;
    free_node(temp->next);
    temp->next = NULL;
    return list;
};

linked_list* push_front(linked_list* list, void* data, datatype dtype)
{
    linked_list* temp;
    list_init(&temp, data, dtype);
    if (!temp)
        return list;
    temp->next = list;
    list = temp;
    return list;
};

linked_list* pop_front(linked_list* list)
{
    if (list == NULL)
        return NULL;
    linked_list* temp = list;
    list = list->next;
    free_node(temp);
    return list;
};

void print_list(linked_list* list)
{
    while (list != NULL)
    {
        switch (list->dtype)
        {
        case TYPE_INT:
            printf("%d ", *(int*)list->data);
            break;
        case TYPE_CHAR:
            printf("%c ", *(char*)list->data);
            break;
        case TYPE_FLOAT:
            printf("%f ", *(float*)list->data);
            break;
        case TYPE_DOUBLE:
            printf("%lf ", *(double*)list->data);
            break;
        
        default:
            break;
        }
        list = list->next;
    }
    printf("\n");
};

int greater(void* val, datatype d_type, linked_list* list)
{
    if (d_type != list->dtype)
        return 1;
    switch (d_type)
    {
    case TYPE_INT:
        return *(int*)val <= *(int*)list->data;
        break;
    case TYPE_CHAR:
        return *(char*)val <= *(char*)list->data;
        break;
    case TYPE_FLOAT:
        return *(float*)val <= *(float*)list->data;
        break;
    case TYPE_DOUBLE:
        return *(double*)val <= *(double*)list->data;
        break;
    
    default:
        return 1;
        break;
    }
};

int lesser(void* val, datatype d_type, linked_list* list)
{
    if (d_type != list->dtype)
        return 1;
    switch (d_type)
    {
    case TYPE_INT:
        return *(int*)val >= *(int*)list->data;
        break;
    case TYPE_CHAR:
        return *(char*)val >= *(char*)list->data;
        break;
    case TYPE_FLOAT:
        return *(float*)val >= *(float*)list->data;
        break;
    case TYPE_DOUBLE:
        return *(double*)val >= *(double*)list->data;
        break;
    
    default:
        return 1;
        break;
    }
};

int equal(void* val, datatype d_type, linked_list* list)
{
    if (d_type != list->dtype)
        return 1;
    switch (d_type)
    {
    case TYPE_INT:
        return *(int*)val != *(int*)list->data;
        break;
    case TYPE_CHAR:
        return *(char*)val != *(char*)list->data;
        break;
    case TYPE_FLOAT:
        return *(float*)val != *(float*)list->data;
        break;
    case TYPE_DOUBLE:
        return *(double*)val != *(double*)list->data;
        break;
    
    default:
        return 1;
        break;
    }
};

void list_find(linked_list* list, void* val, datatype d_type, compare cmp)
{
    while (list != NULL)
    {
        if (cmp(val, d_type, list))
        {
            list = list->next;
            continue;
        }
        switch (list->dtype)
        {
        case TYPE_INT:
            printf("%d ", *(int*)list->data);
            break;
        case TYPE_CHAR:
            printf("%c ", *(char*)list->data);
            break;
        case TYPE_FLOAT:
            printf("%f ", *(float*)list->data);
            break;
        case TYPE_DOUBLE:
            printf("%lf ", *(double*)list->data);
            break;
        
        default:
            break;
        }
        list = list->next;
    }
    printf("\n");
};