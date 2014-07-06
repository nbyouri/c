#include <stdio.h>
#include <string.h>

#define BUF 2048

int main(int argc, char **argv) {
    char str[BUF];
    if (argc >= 2) {
        for (int i = argc - 1; i > 0; i--) {
            strlcpy(str, argv[i], BUF);
            for (int j = (int)strnlen(str, BUF); j >= 0; j--)
                printf("%c", *(str + j));
            (i != 1) ? printf(" ") : puts("\n");
        }
    } else
        printf("enter stuff to reverse\n");
    return 0;
}
