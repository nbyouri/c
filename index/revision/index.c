#include "include.h"

void * index_num(student * class, unsigned int nbs, unsigned int * nbi) {
    id_num * id = malloc((nbs + 1) * sizeof(id_num));
    unsigned int i = 0;
    unsigned int j = 0;
    int found = 0;

    // loop through students
    for (i = 0; i < nbs; i++) {
        // not found yet
        found = -1;
        // loop through the index
        for (j = 0; j < *nbi; j++) {
            if (class[i].num == id[j].num) {
                // we stop looping if found
                found = (int)j;
                break;
            }
        }
        // if not found
        if (found == -1) {
            // grow the index and add the new value
            id = (id_num *)realloc(id, (*nbi + 1) * sizeof(id_num));
            if (id == NULL) {
                error("failed reallocation");
            } else {
                id[*nbi].num = class[i].num;
                id[*nbi].nb = 1;
                // add the index of the student in the index list for index key
                id[*nbi].lst = (unsigned int *)malloc(sizeof(int));
                id[*nbi].lst[0] = i;
                (*nbi)++;
            }
        } else {
            // if found, just add the student in the index list
            id[found].lst = (unsigned int *)realloc(id[found].lst, 
                    (id[found].nb + 1) * sizeof(int));
            if (id[found].lst == NULL) {
                error("failed reallocation");
            } else {
                id[found].lst[id[found].nb] = i;
                id[found].nb++;
            }
        }
    }
    // sort the index array
    qsort(id, *nbi, sizeof(id_num), sort_index_num);
    return id;
}

