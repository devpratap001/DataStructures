#include <stdio.h>
#include "heaps.h"

int main(void)
{
    heap_max heap;
    heap_init(&heap, 5, TYPE_CHAR);
    char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
    push(&heap, &a);
    push(&heap, &b);
    push(&heap, &c);
    push(&heap, &e);
    push(&heap, &d);
    while (heap.size > 0)
    {
        char ch;
        top(&heap, &ch);
        printf("%c ", ch);
        pop(&heap);
    }
    printf("\n");
    heap_free(&heap);
    return 0;
};