#ifndef HASH_H
#define HASH_H

#include <stddef.h>

typedef enum DataType
{
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE
}DataType;

typedef struct Entry
{
    char* key;
    void* value;
    int is_occupied;
    int is_deleted;
}Entry;


typedef struct Hash_Table
{
    size_t size;
    int elements;
    DataType dtype;
    Entry* data;
}Hash_Table;

Hash_Table* table_init(Hash_Table*, DataType);
void table_free(Hash_Table*);
int insert(Hash_Table*, void*,const char*);
void* search(Hash_Table*, const char*);
int erase(Hash_Table*, const char*);
void print_table(Hash_Table*);

#endif