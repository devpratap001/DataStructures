#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

Hash_Table* rehash(Hash_Table*);
size_t getsize(DataType dtype);
unsigned long int hash(const char*);
int probe_index(int);

Hash_Table* table_init(Hash_Table* ht, DataType dtype)
{
    if (!ht)
        return NULL;
    ht->dtype = dtype;
    ht->size = 100;
    ht->elements = 0;
    ht->data = (Entry*)calloc(ht->size, sizeof(Entry));
    if (!ht->data)
        return NULL;
    return ht;
};

void table_free(Hash_Table* ht)
{
    if (!ht || !ht->data)
        return;
    for (size_t i = 0; i < ht->size; i++)
    {
        if (ht->data[i].is_occupied && !ht->data[i].is_deleted)
        {
            free(ht->data[i].key);
            free(ht->data[i].value);
        }
        ht->data[i].is_occupied = 0;
        ht->data[i].is_deleted = 0;
    }
    free(ht->data);
};

int insert(Hash_Table* ht, void* val, const char* key)
{
    if (!ht || !val || !key)
        return 0;
    if ((float)ht->elements / (float)ht->size > 0.6)
        rehash(ht);
    size_t index = hash(key) % ht->size;
    int i = 0;
    while (i < ht->size)
    {
        size_t p_index = (index + probe_index(i))%ht->size;
        Entry*  temp = &ht->data[p_index];

        if (!temp->is_occupied || temp->is_deleted)
        {
            temp->key = malloc(strlen(key) + 1);
            size_t byte_size = getsize(ht->dtype);
            temp->value = malloc(byte_size);
            if (!temp->key || !temp->value)
                return 0;
            strcpy(temp->key, key);
            memcpy(temp->value, val, byte_size);
            temp->is_occupied = 1;
            temp->is_deleted = 0;
            ht->elements++;
            return 1;
        }
        i++;
    }
    return 0;
};

void* search(Hash_Table* ht, const char* key)
{
    if (!ht || !key)
        return NULL;
    size_t index = hash(key)%ht->size, i = 0;
    while (i < ht->size)
    {
        size_t p_index = (index + probe_index(i))%ht->size;
        Entry* temp = &ht->data[p_index];

        if (!temp->is_occupied && !temp->is_deleted)
            return NULL;
        if (temp->is_occupied && !temp->is_deleted && !strcmp(key, temp->key))
            return temp->value;
        
        i++;
    }
    return NULL;
};

int erase(Hash_Table* ht, const char* key)
{
    if (!ht || !key)
        return 0;
    size_t index = hash(key)%ht->size, i = 0;
    while (i < ht->size)
    {
        size_t p_index = (index + probe_index(i))%ht->size;
        Entry* temp = &ht->data[p_index];

        if (!temp->is_occupied && !temp->is_deleted)
            return 0;
        if (temp->is_occupied && !temp->is_deleted && !strcmp(key, temp->key))
        {
            free(temp->key);
            free(temp->value);
            temp->is_deleted = 1;
            ht->elements--;
        }
        
        i++;
    }
    return 0;
};

void print_table(Hash_Table* ht)
{
    for (size_t i = 0; i < ht->size; i++)
    {
        if (ht->data[i].is_occupied && !ht->data[i].is_deleted)
        {
            if (!ht->data[i].value)
            {
                printf("%s\t: ----\n", ht->data[i].key);
                continue;
            }
            switch (ht->dtype)
            {
            case TYPE_CHAR:
                printf("%s\t: %c\n", ht->data[i].key, *(char*)ht->data[i].value);
                break;
            case TYPE_INT:
                printf("%s\t: %d\n", ht->data[i].key, *(int*)ht->data[i].value);
                break;
            case TYPE_FLOAT:
                printf("%s\t: %f\n", ht->data[i].key, *(float*)ht->data[i].value);
                break;
            case TYPE_DOUBLE:
                printf("%s\t: %lf\n", ht->data[i].key, *(double*)ht->data[i].value);
                break;
            
            default:
                break;
            }
        }
    }
};

Hash_Table* rehash(Hash_Table* ht)
{
    if (!ht)
        return NULL;
    size_t new_size = ht->size * 2;
    Entry* newdata = (Entry*)calloc(new_size, sizeof(Entry));
    if (!newdata)
        return ht;
    for (size_t j = 0; j < ht->size; j++)
    {
        Entry* temp = &ht->data[j];
        if (!temp->is_occupied || temp->is_deleted)
            continue;
        size_t index = hash(temp->key);
        size_t i =0;
        while (i < new_size)
        {
            size_t c_index = (index +probe_index(i))%new_size;
            if (!newdata[c_index].is_occupied || newdata[c_index].is_deleted)
            {
                newdata[c_index].key = temp->key;
                newdata[c_index].value = temp->value;
                newdata[c_index].is_occupied = temp->is_occupied;
                newdata[c_index].is_deleted = temp->is_deleted;
                break;
            }
            i++;
        }
    }
    free(ht->data);
    ht->data = newdata;
    ht->size = new_size;
    return ht;
};

unsigned long int hash(const char* key)
{
    int M = 1e9+7;
    unsigned long int hash_val = 5381;
    char ch;
    while ((ch = *key++))
    {
        hash_val = ((hash_val<<5) + hash_val + ch)%M;
    }
    return hash_val;
};

int probe_index(int i)
{
    return i + i*i;
};

size_t getsize(DataType dtype)
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