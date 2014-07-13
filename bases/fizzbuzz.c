#include <stdio.h>
int main(void) {
    for (int i = 0; i < 100; i++) {
        if (!(i % 3)) 
            printf("%s\n", (!(i % 5)) ? "fizzbuzz" : "fizz");
        else (!(i % 5)) ? printf("buzz\n") : printf("%d\n", i);
    }
    return 0;
}
