#include <stdio.h>
#include "linked_list.h"

int main(void)
{
    linked_list* list;
    int a = 5, b = 6, c = 7, d = 8, e = 9;
    list_init(&list, &a, TYPE_INT);
    push(list, &b, TYPE_INT);
    push(list, &c, TYPE_INT);
    list = pop(list);
    list = push_front(list, &d, TYPE_INT);
    list = push_front(list, &e, TYPE_INT);
    print_list(list);
    printf("=========================\n");
    list_find(list, &b, TYPE_INT, greater);
    printf("=========================\n");
    list_find(list, &b, TYPE_INT, lesser);
    printf("=========================\n");
    list_find(list, &b, TYPE_INT, equal);
    printf("=========================\n");
    list_free(list);
    list = NULL;
};