#include <stdio.h>
#include "hash.h"

int main(void)
{
    Hash_Table ht;
    table_init(&ht, TYPE_CHAR);
    const char* key[] = {"one", "two", "three", "four", "nne", "five", "six", "seven", "eight"};
    char elem[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
    insert(&ht, elem + 0, key[0]);
    insert(&ht, elem + 1, key[1]);
    insert(&ht, elem + 2, key[2]);
    erase(&ht, key[1]);
    insert(&ht, elem + 3, key[3]);
    insert(&ht, elem + 4, key[4]);
    insert(&ht, elem + 5, key[5]);
    insert(&ht, elem + 6, key[6]);
    insert(&ht, elem + 7, key[7]);
    insert(&ht, elem + 8, key[8]);
    for (int i = 0; i < 9; i++)
    {
        void* data = search(&ht, key[i]);
        if (!data)
            printf("%s\t: ----\n", key[i]);
        else
            printf("%s\t: %c\n", key[i], *(char*)search(&ht, key[i]));
    }

    printf("\n");
    print_table(&ht);
    erase(&ht, key[0]);
    erase(&ht, key[6]);
    erase(&ht, key[8]);
    printf("=======================================\n");
    for (int i = 0; i < 9; i++)
    {
        void* data = search(&ht, key[i]);
        if (!data)
            printf("%s\t: ----\n", key[i]);
        else
            printf("%s\t: %c\n", key[i], *(char*)search(&ht, key[i]));
    }
    printf("\n");
    print_table(&ht);
    table_free(&ht);
    return 0;
};