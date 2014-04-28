#include <stdio.h>

#define BUF 5

int  cmp(int, int);
void swap(int *, int *);
void tri(int *);

static int tab[BUF] = { 0, 3, 2, -2, 9};

int cmp(int a, int b) {
    return a - b;
}

void swap(int * a, int * b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

void tri(int t[]) {
    int i, j;
    for (i = 0; i < BUF; i++) {
        for (j = 0; j < BUF-1; j++) {
            if (cmp(t[j], t[j+1]) > 0) {
                swap(&t[j], &t[j+1]);
            }
        }
    }
}

int main(void) {
    int k = 0;
    tri(tab);
    for (k = 0; k < BUF; k++) {
        printf("%d\n", tab[k]);
    }
}
