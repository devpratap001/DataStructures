#include <stdio.h>
#include "dynamic_arrays.h"

int main(void)
{
    int a = 10;
    float b = 2.15;
    char c = 'c';
    double d = 12568.265;
    int e = 12;
    char f = 'f';
    array arr1;
    array_init(&arr1);
    push(&arr1, &a, TYPE_INT);
    push(&arr1, &b, TYPE_FLOAT);
    push(&arr1, &c, TYPE_CHAR);
    push(&arr1, &d, TYPE_DOUBLE);
    insert(&arr1, 2, &e, TYPE_INT);
    push(&arr1, &f, TYPE_CHAR);
    print_array(&arr1);

    // int _a, _c;
    // char _d;
    // float _b;
    // double _e;
    // get(&arr1, 0, &_a, TYPE_INT);
    // get(&arr1, 1, &_b, TYPE_FLOAT);
    // get(&arr1, 2, &_c, TYPE_INT);
    // get(&arr1, 3, &_d, TYPE_CHAR);
    // get(&arr1, 4, &_e, TYPE_DOUBLE);

    // printf("%d %f %d %c %lf\n", _a, _b, _c, _d, _e);

    array_free(&arr1);

    //===========================================================

    // float args[] = {1.2, 2.4, 3.6, 4.1, 5.8, 6.9, 7.7, 8.4};
    // array arr1;
    // array_init(&arr1, sizeof(float), 5);
    // push(&arr1, args);
    // push(&arr1, args +1);
    // push(&arr1, args +2);
    // push(&arr1, args +3);
    // insert(&arr1, 2, args +4);
    // push(&arr1, args + 5);
    // for (int i = 0; i < arr1.size; i++)
    // {
    //     float data;
    //     get(&arr1, i, &data);
    //     printf("%f ", data);
    // }
    // printf("\n");
    // array_free(&arr1);
    return 0;
};