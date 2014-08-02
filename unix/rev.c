#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char str[BUFSIZ];
    int str_size = 0;

    if (argc >= 2) {
        for (int i = argc - 1; i > 0; i--) {

            strlcpy(str, argv[i], BUFSIZ);
            str_size = (int)strnlen(str, BUFSIZ); 

            for (int j = str_size; j >= 0; j--)
                printf("%c", *(str + j));

            (i != 1) ? printf(" ") : puts("\n");
        }
    } else
        printf("enter stuff to reverse\n");

    return 0;
}
