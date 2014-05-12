#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>

#define BUF 255 

void usage(void);
void count(const char *, bool, bool);
int  check_file(const char *);

int main(int argc, char **argv) {
    if (argc > 2) {
        check_file(argv[2]);
        if (errno == ENOENT)
            printf("%s: %s: no such file or directory\n", argv[0], argv[2]);
        if (strcmp(argv[1], "-l") == 0) 
            count(argv[2], false, true); 
        else if (strcmp(argv[1], "-c") == 0) 
            count(argv[2], true, false);
        else 
            usage();
    } else if (argc == 2) {
        if (argv[1][0] == '-') 
            usage();
        else
            check_file(argv[1]);
        if (errno == ENOENT)
            printf("%s: %s: no such file or directory\n", argv[0], argv[1]);
        count(argv[1], true, true);
    } else
        usage();
    return 0;
}

void usage(void) {
    printf("wc <file>\n"
            "-l\tcount lines\n"
            "-c\tcount characters\n");
}

void count(const char *file, bool chars, bool lines) {
    FILE *f;
    if ((f = fopen(file, "r")) == NULL)
        exit(EXIT_FAILURE);
    if (lines) {
        char s[BUF];
        int countlines = 0;
        while (fgets(s, sizeof(s), f)) 
            countlines++;
        printf("%d\t", countlines);
    }
    if (chars) {
        rewind(f);
        int c = 0;
        int countchar = 0;
        while ((c = fgetc(f)) != EOF)
            countchar++;
        printf("%d\t", countchar);
    }
    printf("%s\n", file);
    fclose(f);
}

int check_file(const char *file) {
    struct stat st;
    int result = stat(file, &st);
    return result = 0;
}
