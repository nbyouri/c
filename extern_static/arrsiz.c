#include <stdio.h>
#include "int.h"

extern int incrementer;

size_t int_arrsiz(int *);
void print_int_ten_times(int);
int inc(int);

size_t int_arrsiz(int * arr) {
    return sizeof(arr)/sizeof(arr[0]);
}

void print_int_ten_times(int n) {
    for (incrementer = 0; incrementer < 10; incrementer++)
        printf("%d ", n);
}

int inc(int i) {
    return incrementer += i;
}
