#ifndef LINKED_LIST_H
#define LINKED_LIST_H


typedef enum
{
    TYPE_INT,
    TYPE_CHAR,
    TYPE_FLOAT,
    TYPE_DOUBLE
}datatype;

typedef struct l_list
{
    void* data;
    datatype dtype;
    struct l_list* next;
}linked_list;

typedef int (*compare)(void*, datatype, linked_list*);
int greater(void*, datatype, linked_list*);
int lesser(void*, datatype, linked_list*);
int equal(void*, datatype, linked_list*);

linked_list* list_init(linked_list** list, void* data, datatype);
void list_free(linked_list*);
int push(linked_list*, void*, datatype);
linked_list* pop(linked_list*);
linked_list* push_front(linked_list*, void*, datatype);
linked_list* pop_front(linked_list*);
void print_list(linked_list*);
void list_find(linked_list*, void* data, datatype, compare);

#endif