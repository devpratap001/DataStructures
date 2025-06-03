#include <stdio.h>

#include "stack.h"

int main(void)
{
    stack pipe;
    stack_init(&pipe, TYPE_CHAR);
    char a = 'b', b = 'c', c = 'd', d = 'e', e = 'f';
    push(&pipe, &a, TYPE_CHAR);
    push(&pipe, &b, TYPE_CHAR);
    push(&pipe, &c, TYPE_CHAR);
    push(&pipe, &d, TYPE_CHAR);
    push(&pipe, &e, TYPE_CHAR);
    char temp;
    peek(&pipe, &temp);
    pop(&pipe);
    printf("%c ", temp);
    peek(&pipe, &temp);
    pop(&pipe);
    printf("%c ", temp);
    peek(&pipe, &temp);
    pop(&pipe);
    printf("%c ", temp);
    peek(&pipe, &temp);
    pop(&pipe);
    printf("%c ", temp);
    peek(&pipe, &temp);
    pop(&pipe);
    printf("%c ", temp);
    if (is_empty(&pipe))
        printf("\nthat's all\n");
    stack_free(&pipe);
    return 0;
};