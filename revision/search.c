#include "include.h"

void search_num(student * class, id_num * id, unsigned int nbid) {
    id_num * temp, key;
    printf("enter a number to search : ");
    scanf("%d", &key.num);
    temp = bsearch(&key, id, nbid, sizeof(id_num), sort_index_num);
    if (temp == NULL) {
        // exit if bsearch fails
        puts("not found\n");
    } else {
        // otherwise, print the students matching the index key
        unsigned int i = 0;
        for (i = 0; i < temp->nb; i++)
            print_students(stdout, class, temp->lst[i], true);
    }
}
