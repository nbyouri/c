#include "include.h"

// print the structure to a stream
void print_students(FILE * fi, student * class, unsigned int nb) {
    unsigned int i = 0;
    for (i = 0; i < nb; i++) {
        fprintf(fi, "%02d : %s : %02d/%02d/%04d\n", 
                class[i].num, class[i].name, 
                class[i].bd.day, class[i].bd.mon, class[i].bd.yea);
    }
}

// print an error message and exit
void error(const char * msg) {
    fprintf(stderr, "ERROR: %s\n", msg);
    exit(EXIT_FAILURE);
}

