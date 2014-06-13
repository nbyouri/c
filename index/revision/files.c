#include "include.h"

void write_file(const char * filename, const char * mode, student * class, unsigned int nb) {
    FILE *f;

    chdir(DATA_DIR);

    // text file
    if (!strncmp(mode, "wt", MAX_CHAR)) {
        // quit if it fails to open
        if ((f = fopen(filename, mode)) == NULL) {
            error("Failed to write text file");
            // otherwise, write data to it
        } else {
            print_students(f, class, nb, false);
            // close the file
            fclose(f);
        }


        // binary file
    } else if (!strncmp(mode, "wb", MAX_CHAR)) {
        if ((f = fopen(filename, mode)) == NULL) {
            error("Failed to write binary file");
        } else {
            fwrite(class, sizeof(student), nb, f);
            fclose(f);
        }
    } else {
        error("invalid file write mode");
    }
}

void * read_file(const char * filename, const char * mode, student * class, unsigned int * nb) {
    FILE *f;
    *nb = 0;

    chdir(DATA_DIR);
    
    // text file
    if (!strncmp(mode, "rt", MAX_CHAR)) {
        char s[MAX_CHAR_BIG];
        if ((f = fopen(filename, mode)) == NULL) {
            error("Failed to read text file");
        } else {
            while (fgets(s, sizeof(s), f)) {
                if ((class = grow(class, *nb)) == NULL) {
                    error("failed reallocation");
                } else {
                    // break if the line is invalid, to avoid crashes
                    if (!isdigit((unsigned char)s[0])) break;
                    class[*nb].num = (unsigned)atoi(strtok(s, ";"));
                    snprintf(class[*nb].name, MAX_CHAR, "%s", strtok(NULL, ";"));
                    class[*nb].bd.day = (unsigned)atoi(strtok(NULL, ";"));
                    class[*nb].bd.mon = (unsigned)atoi(strtok(NULL, ";"));
                    class[*nb].bd.yea = (unsigned)atoi(strtok(NULL, ";"));
                    (*nb)++;
                }
            }
            fclose(f);
        }
        // binary file
    } else if (!strncmp(mode, "rb", MAX_CHAR)) {
        if ((f = fopen(filename, mode)) == NULL) {
            error("Failed to open binary file");
        } else {
            // find the number of elements in the binary files and rewind it
            fseek(f, 0, SEEK_END);
            *nb = (unsigned)ftell(f) / sizeof(student);
            rewind(f);
            if ((class = grow(class, *nb)) == NULL)
                error("failed to reallocate");
            else
                fread(class, sizeof(student), *nb, f);
            fclose(f);
        }
    } else {
        error("invalid file read mode");
    }
    return class;
}
