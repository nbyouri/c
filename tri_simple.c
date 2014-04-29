#include <stdio.h>

#define BUF 5

int  cmp(int *, int *);
void swap(int *, int *);
void tri(int *);

static int tab[BUF] = { 0, 3, 2, -2, 9};

int cmp(int *a, int *b) {
    return *a - *b;
}

void swap(int *a, int *b) {
    int  te;
    te = *a;
    *a = *b;
    *b = te;
}

void tri(int *t) {
    for (int i = 0; i < BUF; i++) {
        for (int j = 0; j < BUF-1; j++) {
            if (cmp(&t[j], &t[j+1]) > 0) 
                swap(&t[j], &t[j+1]);
        }
    }
}

int main(void) {
    tri(tab);
    for (int k = 0; k < BUF; k++) 
        printf("%d\n", tab[k]);
}
