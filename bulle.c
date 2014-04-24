#include <stdio.h>

#define BUF 3

int main(void) {
    int array[BUF] = { 0, 3, 2 };
    int temp, i, j, k;
    for (i = 0; i < BUF; i++) {
        for (j = 0; j < BUF-1; j++) {
            if (array[j] > array[j+1]) {
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
    for (k = 0; k < BUF; k++) {
        printf("%d\n", array[k]);
    }
}
