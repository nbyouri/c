#include "include.h"

// reallocate the student array
void * grow(student * class, unsigned int nb) {
    student * temp;
    temp = (student *)realloc(class, (nb + 1) * sizeof(student));
    if (temp == NULL) {
        if (class != NULL)
            free(class);
        class = NULL;
        return NULL;
    }
    return temp;
}

// print the structure to a stream
void print_students(FILE * fi, student * class, unsigned int nb, bool one) {
    // print only one item at index 'nb' or nb items
    unsigned int i = 0;
    for (i = one ? nb : 0; i < nb + one; i++)
        fprintf(fi, "%02d;%s;%02d;%02d;%04d\n", 
                class[i].num, class[i].name, 
                class[i].bd.day, class[i].bd.mon, class[i].bd.yea);
}

// print an error message and exit
void error(const char * msg) {
    fprintf(stderr, "ERROR: %s\n", msg);
    exit(EXIT_FAILURE);
}

int sort_index_num(const void * a, const void * b) {
    return (int)(((id_num *)a)->num - ((id_num *)b)->num);
}

int sort_num(const void * a, const void * b) {
    return (int)(((student *)a)->num - ((student *)b)->num);
}

