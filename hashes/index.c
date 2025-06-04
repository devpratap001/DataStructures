#include <stdio.h>
#include "hash.h"

int main(void)
{
    Hash_Table ht;
    table_init(&ht, 10, TYPE_CHAR);
    char* key[] = {"one", "two", "three", "four", "nne", "five", "six", "seven", "eight"};
    char elem[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
    insert(&ht, key[0], elem + 0);
    insert(&ht, key[1], elem + 1);
    insert(&ht, key[2], elem + 2);
    insert(&ht, key[3], elem + 3);
    insert(&ht, key[4], elem + 4);
    insert(&ht, key[5], elem + 5);
    insert(&ht, key[6], elem + 6);
    insert(&ht, key[7], elem + 7);
    insert(&ht, key[8], elem + 8);
    insert(&ht, key[1], elem + 5);
    for (int i = 0; i < 9; i++)
    {
        void* data = search(&ht, key[i]);
        if (!data)
            printf("%s\t: ----\n", key[i]);
        else
            printf("%s\t: %c\n", key[i], *(char*)search(&ht, key[i]));
    }
    print_table(&ht);
    delete(&ht, key[0]);
    delete(&ht, key[4]);
    printf("==================================\n");
    for (int i = 0; i < 9; i++)
    {
        void* data = search(&ht, key[i]);
        if (!data)
            printf("%s\t: ----\n", key[i]);
        else
            printf("%s\t: %c\n", key[i], *(char*)search(&ht, key[i]));
    }
    print_table(&ht);
    table_free(&ht);
    return 0;
};