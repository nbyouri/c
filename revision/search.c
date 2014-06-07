#include "include.h"

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
