#include "include.h"

void write_file(const char * filename, const char * mode, student * class, unsigned int nb) {
    FILE *f;

    // text file
    if (!strncmp(mode, "wt", MAX_CHAR)) {
        // quit if it fails to open
        if ((f = fopen(filename, mode)) == NULL) {
            error("Failed to write text file");
            // otherwise, write data to it
        } else {
            print_students(f, class, nb);
            // close the file
            fclose(f);
        }


        // binary file
    } else if (!strncmp(mode, "wb", MAX_CHAR)) {
        if ((f = fopen(filename, mode)) == NULL) {
            error("Failed to write binary file\n");
        } else {
            fwrite(class, nb, sizeof(student), f);
            fclose(f);
        }
    } else {
        error("invalid file write mode\n");
    }
}

void * read_file(const char * filename, const char * mode, student * class, unsigned int * nb) {
    FILE *f;
    *nb = 0;

    // text file
    if (!strncmp(mode, "rt", MAX_CHAR)) {
        char s[200];
        char name[MAX_CHAR];
        if ((f = fopen(filename, mode)) == NULL) {
            error("Failed to read text file");
        } else {
            while (fgets(s, sizeof(s), f)) {
                if ((class = grow(class, (*nb + 1))) == NULL) {
                    error("failed reallocation");
                } else {
                    if (!isdigit(s[0])) break;
                    class[*nb].num = atoi(strtok(s, ";"));
                    snprintf(class[*nb].name, MAX_CHAR, "%s", strtok(NULL, ";"));
                    class[*nb].bd.day = atoi(strtok(NULL, ";"));
                    class[*nb].bd.mon = atoi(strtok(NULL, ";"));
                    class[*nb].bd.yea = atoi(strtok(NULL, ";"));
                    (*nb)++;
                }
            }
            fclose(f);
        }
    } else if (!strncmp(mode, "rb", MAX_CHAR)) {
        if ((f = fopen(filename, mode)) == NULL) {
            error("Failed to open binary file");
        } else {
            printf("ok\n");
        }
    }
    return class;
}
