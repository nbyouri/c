#include <stdio.h>

#define siz(X) (int)(sizeof(X)/sizeof(X[0]))
#define BUF 10

static int tab[BUF] = { 0, 2, 3, 4, 11, 10, 2, -2, 1, 1 };

int max(int *);
int min(int *);
int cmp(int, int);
int cmpm(int, int);

int cmp(int a, int b) {
    return a > b ? a : b;
}

int cmpm(int a, int b) {
    return a < b ? a : b;
}

int max(int * tb) {
    int res = tb[0];
    int max = 0;
    for (int i = 0; i < siz(tab); i++) {
        max = i + 1;
        if (res < cmp(tb[max], tb[i]))
            res = tb[max];
    }
    return res;
}

int min(int * tb) {
    int res = tb[0];
    int min = 0;
    for (int i = 0; i < siz(tab); i++) {
        min = i + 1;
        if (res > cmpm(tb[i], tb[min]))
            res = tb[min];
    }
    return res;
}

int main(void) {
    printf("tab max = %d\n", max(tab));
    printf("tab min = %d\n", min(tab));

    return 0;
}
