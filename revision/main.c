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
            error("reallocation failed\n");
        else {
            // else, we initialize the student
            initialize(compsci, nbstud);
            nbstud++;
        }
    }

    // print all the students
    print_students(stdout, compsci, nbstud, false);

    // create the index by number
    if ((indexnum = index_num(compsci, nbstud, &nbindex)) == NULL)
        // if the indexation fails, we quit
        error("indexation failed\n");
    else {
        // search through the students
        search_num(compsci, indexnum, nbindex);
    }
    // write students to files
    write_file("compsci.txt", "wt", compsci, nbstud);
    write_file("compsci.bin", "wb", compsci, nbstud);

    // load from text file
    student * temp = NULL;
    unsigned int nbtemp = 0;
    temp = read_file("compsci.txt", "rt", temp, &nbtemp);
    if (temp == NULL) {
        error("failed to load data from file");
    } else {
        // show and write the data to a binary file
        //print_students(stdout, temp, nbtemp, false);
        write_file("temp.bin", "wb", temp, nbtemp);
    }
    free(temp);
    temp = NULL;

    // load from binary file
    student * temp2 = NULL;
    unsigned int nbtemp2 = 0;
    temp2 = read_file("temp.bin", "rb", temp2, &nbtemp2);
    if (temp2 == NULL) {
        error("failed to load from binary file");
    } else {
        // show students and write to a text file
        //print_students(stdout, temp2, nbtemp2, false);
        write_file("temp.txt", "wt", temp2, nbtemp2);
    }
    free(temp2);
    temp2 = NULL;


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
