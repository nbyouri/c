#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int base_2_to_10(char *, size_t);
int base_8_to_10(char *, size_t);
int base_10_to_2(int);

int base_2_to_10(char * bin, size_t siz) {
    int s = 0;
    int sum = 0;
    for (int i = 0; i < siz; i++) {
        s = *(bin + i) - '0';
        sum += (s <<= siz - (i + 1));
    }
    return sum;
}

int base_8_to_10(char * oct, size_t siz) {
    int s = 0;
    int sum = 0;
    for (int i; i < siz; i++) {
        s = *(oct + i) - '0';
        sum += (s *= pow(8, (siz - (i + 1))));
    }
    return sum;
}

int base_10_to_2(int n) {
    char * s = NULL;
    char * temp = NULL;
    int nb = 0;
    do {
        temp = realloc(temp, nb + 1 * sizeof(char));
        if (temp == NULL) {
            printf("failed to allocate memory\n");
            exit(EXIT_FAILURE);
        } else {
            temp[nb] = n % 2;
            n /= 2;
            nb++;
        }
    } while (n > 0);
    s = realloc(s, nb + 1 * sizeof(char));
    if (s == NULL) {
        printf("failed to allocate memory\n");
        exit(EXIT_FAILURE);
    } else {
        for (int i = nb; i > -1; i--)
            snprintf(s + strlen(s), sizeof(s), "%d", temp[i]);
    }
    int res = atoi(s);
    free(temp);
    free(s);
    return res;
}

int main(void) {
    // base 2 to 10
    // char binary[1024];
    // printf("Enter a binary value to convert: ");
    // scanf("%s", binary);
    // printf("(%s)10 = %d\n", binary, base_2_to_10(binary, strlen(binary)));
    // base 10 to 2
    // char n[1024];
    // printf("Enter a decimal value to convert: ");
    // scanf("%s", n);
    // printf("(%s)2 = %d\n", n, base_10(atoi(n)));
    // base 2 to 8
    // char binary[1024];
    // printf("Enter a binary value to convert: ");
    char binary[] = "0100";
    printf("(%s)2 = %d\n", binary, base_2_to_10(binary, strlen(binary)));
    strlcpy(binary, "65", sizeof(binary));
    printf("(%s)8 = %d\n", binary, base_8_to_10(binary, strlen(binary)));
    printf("%d\n", base_10_to_2(20));
    return 0;
}
