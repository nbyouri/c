
#include "include.h"

student * grow(student * class, unsigned int nb) {
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

void initialize(student * class, unsigned int nb) {
    // random number
    class[nb].num = arc4random() % 100;

    // random birthday
    class[nb].bd.day = arc4random() % 30;
    class[nb].bd.mon = arc4random() % 11;
    class[nb].bd.yea = 1990 + arc4random() % 6;

    // name = peter + random number
    char randomnum[MAX_CHAR];
    snprintf(randomnum, sizeof(randomnum), "%02d", arc4random() % 100);
    strlcpy(class[nb].name, "peter", sizeof(class[nb].name));
    strlcat(class[nb].name, randomnum, sizeof(class[nb].name));
}

void print_students(student * class, unsigned int nb) {
    unsigned int i = 0;
    for (i = 0; i < nb; i++) {
        printf("%02d : %s : %02d/%02d/%04d\n", 
                class[i].num, class[i].name, 
                class[i].bd.day, class[i].bd.mon, class[i].bd.yea);
    }
}

id_num * index_num(student * class, unsigned int nbs, unsigned int * nbi) {
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
            id[*nbi].num = class[i].num;
            id[*nbi].nb = 1;
            // add the index of the student in the index list for index key
            id[*nbi].lst = (unsigned int *)malloc(sizeof(int));
            id[*nbi].lst[0] = i;
            (*nbi)++;
        } else {
            // if found, just add the student in the index list
            id[found].lst = (unsigned int *)realloc(id[found].lst, 
                    (id[found].nb + 1) * sizeof(int));
            id[found].lst[id[found].nb] = i;
            id[found].nb++;
        }
    }
    // sort the index array
    qsort(id, *nbi, sizeof(id_num), sort_index_num);
    return id;
}

int sort_index_num(const void * a, const void * b) {
    return (int)(((id_num *)a)->num - ((id_num *)b)->num);
}

void search_num(student * class, id_num * id, unsigned int nbid) {
    id_num * temp, key;
    printf("enter a number to search : ");
    scanf("%d", &key.num);
    temp = bsearch(&key, id, nbid, sizeof(id_num), sort_index_num);
    if (temp == NULL) {
        // exit if bsearch fails
        printf("failed to bsearch\n");
        exit(EXIT_FAILURE);
    } else {
        // otherwise, print the students matching the index key
        unsigned int i = 0;
        for (i = 0; i < temp->nb; i++) {
            printf("%02d : %s : %02d/%02d/%04d\n", 
                    class[temp->lst[i]].num, 
                    class[temp->lst[i]].name, 
                    class[temp->lst[i]].bd.day, 
                    class[temp->lst[i]].bd.mon, 
                    class[temp->lst[i]].bd.yea);
        }
    }
}

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
