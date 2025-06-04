#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int hash(char*, size_t);
static size_t getsize(DataType dtype);


Hash_Table* table_init(Hash_Table *ht, size_t size, DataType dtype)
{
    if (!ht)
        return NULL;
    ht->size = size;
    ht->elements = 0;
    ht->dtype = dtype;
    ht->hash = hash;
    ht->elem = (Element**)calloc(size, sizeof(Element*));
    if (!ht->elem)
        return NULL;
    return ht;
};

Hash_Table* resize_table(Hash_Table* ht)
{
    if (!ht)
        return NULL;
    
    size_t new_size = ht->size * 2;
    Element** new_elem = (Element**)calloc(new_size, sizeof(Element*));
    if (!new_elem)
        return NULL;
    for (size_t i = 0; i < ht->size; i++)
    {
        Element* node = ht->elem[i];
        while (node)
        {
            Element* next_node = node->next;
            size_t new_index = ht->hash(node->key, new_size);
            node->next = new_elem[new_index];
            new_elem[new_index] = node;
            node = next_node;
        }
        node = NULL;
    }
    ht->size = new_size;
    free(ht->elem);
    ht->elem = new_elem;
    return ht;
}

void table_free(Hash_Table *ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        while ((ht->elem)[i])
        {
            Element *temp = (ht->elem)[i];
            ht->elem[i] = (ht->elem)[i]->next;
            free(temp->data);
            free(temp->key);
            free(temp);
        }
    }
    free(ht->elem);
};

Element* insert(Hash_Table *ht, char *key, void *val)
{
    if (!ht || !key || !val)
        return NULL;
    if ((float)ht->elements/(float)ht->size > 0.75)
        resize_table(ht);

    size_t byte_size = getsize(ht->dtype);
    int index = ht->hash(key, ht->size);
    Element *node = (Element*)malloc(sizeof(Element));
    if (!node)
        return NULL;
    node->next = NULL;
    node->key = (char*)malloc((strlen(key)+1)*sizeof(char));
    node->data = malloc(byte_size);
    if (!node->key || !node->data)
    {
        free(node);
        return NULL;
    }
    strcpy(node->key, key);
    memcpy(node->data, val, byte_size);
    node->next = ht->elem[index];
    ht->elem[index] = node;
    ht->elements++;
    return node;
};

int delete(Hash_Table *ht, char *key)
{
    if (!ht || !key)
        return 0;
    int index = ht->hash(key, ht->size);
    Element* node = ht->elem[index], *prev = NULL;
    while (node != NULL && strcmp(node->key, key) != 0)
    {
        prev = node;
        node = node->next;
    }
    if (!node)
        return 0;
    if (prev == NULL)
    {
        ht->elem[index] = node->next;
    }
    else
    {
        prev->next = node->next;
    }
    free(node->key);
    free(node->data);
    free(node);
    ht->elements--;
    return 1;
};

void* search(Hash_Table *ht, char *key)
{
    if (!ht || !key)
        return NULL;
    int index = ht->hash(key, ht->size);
    Element* node = ht->elem[index];
    while (node != NULL && strcmp(node->key, key) != 0)
    {
        node = node->next;
    }
    if (!node)
        return NULL;
    return node->data;
};

void print_table(Hash_Table *ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        Element* temp = ht->elem[i];
        while (temp)
        {
            if (!temp->key || !temp->data)
            {
                printf("<key: --; val: --> ");
                temp = temp->next;
                continue;
            }
            switch (ht->dtype)
            {
            case TYPE_CHAR:
                printf("<key: %s; val: %c> ", temp->key, *(char*)temp->data);
                break;
            case TYPE_INT:
                printf("<key: %s; val: %d> ", temp->key, *(int*)temp->data);
                break;
            case TYPE_FLOAT:
                printf("<key: %s; val: %f> ", temp->key, *(float*)temp->data);
                break;
            case TYPE_DOUBLE:
                printf("<key: %s; val: %lf> ", temp->key, *(double*)temp->data);
                break;
            
            default:
                break;
            }
            temp = temp->next;
        }
        printf("\n");
    }
};

int hash(char* key, size_t size)
{
    // Rolling Hash function
    // unsigned long int hash = 0;
    // int i = 1, M = 131;
    // int index = 0;
    // while (key[index] != '\0')
    // {
    //     hash = (hash + (int)(*key)*i)%M;
    //     i *= 2;
    //     index++;
    // }
    // return (int)hash%size;

    //DJB2 Hash function
    // unsigned long int hash = 5381;
    // char ch;
    // while ((ch = *key++))
    // {
    //     hash = ((hash<<5) + hash) + ch;
    // }
    // return (int)(hash%size);

    //SDBM Hash function
    // unsigned long int hash = 0;
    // char ch;
    // while ((ch = *key++))
    // {
    //     hash = ch + (hash<<6) + (hash<<16) -hash;
    // }
    // return (int)(hash%size);

    // FNV-1a Hash function
    unsigned long int hash = 2166136261u;
    unsigned long int fnv_prime = 16777619u;
    char ch;
    while ((ch = *key++))
    {
        hash ^= (unsigned char)ch;
        hash *= fnv_prime;
    }
    return (int)(hash % size);
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