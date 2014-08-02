#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * remove_voy(const char *);

char * remove_voy(const char *str) {
    size_t i;
    size_t len;
    char *res = NULL;
    if (str != NULL) {
        len = strlen(str);
        res = malloc(len * sizeof(char));
        for (i = 0; i < len; i++) {
            if (str[i] == 'a' || 
                    str[i] == 'e' ||
                    str[i] == 'i' ||
                    str[i] == 'o' ||
                    str[i] == 'u' ||
                    str[i] == 'y')
                res[i] = 'X';
            else
                res[i] = str[i];
        }
    }
    return res;
}

int main(int argc, char **argv) {
    char *str = remove_voy(argv[1]);

    if ((argc < 2) || (argc > 2))
        printf("./voy <string>\n");

    else if (argc == 2) {
        printf("%s\n", str);
    }

    if (str != NULL) {
        free(str);
        str = NULL;
    }
    return 0;
}

