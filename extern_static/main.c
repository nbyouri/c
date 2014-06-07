#include "include.h"
#include "int.h"

extern int inc(int);
extern size_t int_arrsiz(int *);
extern void print_int_ten_times(int);

int main(void) {
    unsigned int nb = 0;
    unsigned int i = 0;
    int * arr = NULL;
    printf("How many elements do you want in the integer array? : ");
    scanf("%d", &nb);
    if ((arr = realloc(arr, nb * sizeof(int))) == NULL)
        return -1;
    else {
        for (i = 0; i < nb; arr[i++] = arc4random() % 10);
        printf("LENGTH(arr) : %ld\n", int_arrsiz(arr));
        printf("array size: %d\n", nb);
        for (i = 0; i < nb; printf("%d ", arr[i++]));
        printf("\n------\n");
        for (i = 0; i < nb; print_int_ten_times(arr[i++]));
        printf("\n%d\n", inc(200));
    }
    free(arr);
    return 0;
}

