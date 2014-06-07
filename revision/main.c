#include "include.h"

int main(void) {
    student * compsci = NULL;
    id_num * indexnum = NULL;
    unsigned int nbstud = 0;
    unsigned int nbindex = 0;
    unsigned int i = 0;

    // initialize 200 students
    for (i = 0; i < 200; i++) {
        if ((compsci = grow(compsci, nbstud)) == NULL)
            // if reallocation fails, we quit
            return -1;
        else {
            // else, we initialize the student
            initialize(compsci, nbstud);
            nbstud++;
        }
    }

    // print all the students
    print_students(compsci, nbstud);

    // create the index by number
    if ((indexnum = index_num(compsci, nbstud, &nbindex)) == NULL)
        // if the indexation fails, we quit
        return -1;
    else {
        // search through the students
        search_num(compsci, indexnum, nbindex);
    }

    // free the pointers
    free(compsci);
    compsci = NULL;
    for (i = 0; i < nbindex; i++) {
        free(indexnum[i].lst);
        indexnum[i].lst = NULL;
    }
    free(indexnum);
    indexnum = NULL;

    return 0;
}
