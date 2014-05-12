#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * remove_voy(const char *);

int main(int argc, char **argv) {
    char *str = remove_voy(argv[1]);
    if (argc == 2) 
        printf("%s\n", str);
    else
        printf("remove voyels from a string\n");
    free(str);
    return 0;
}

char * remove_voy(const char *str) {
    int i;
    size_t len = strlen(str);
    char *res;
    res = malloc(len * sizeof(char));
    for (i = 0; i < (int)len; i++) {
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
    return res;
}


