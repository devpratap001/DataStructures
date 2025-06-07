#ifndef HASH_H
#define HASH_H

#include <stddef.h>

typedef enum
{
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE
}DataType;

typedef int (*gen_hash)(char*, size_t);

typedef struct Element
{
    char* key;
    void* data;
    struct Element *next;
}Element;


typedef struct Hash_Table
{
    size_t size;
    size_t elements;
    DataType dtype;
    gen_hash hash;
    Element** elem;
}Hash_Table;

Hash_Table* table_init(Hash_Table*, size_t, DataType DataType);
void table_free(Hash_Table*);
Element* insert(Hash_Table*, char*, void*);
int delete(Hash_Table*, char*);
void* search(Hash_Table*, char*);
void print_table(Hash_Table*);

#endif