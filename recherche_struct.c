#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 20

struct tfe {
    char titre[MAX_CHAR];
    int cat;
};

struct index_titre {
    char titre[MAX_CHAR];
    int nb;
    int * lst;
};

struct index_titre * 
indexation(struct tfe *, int, struct index_titre *, int *);
int trieindex(const void * a, const void * b);
void recherche(struct tfe *, int, struct index_titre *, int);

struct index_titre * 
indexation(struct tfe * tab, int nb, struct index_titre * indtab, int * nbindex) {
    struct index_titre * id = (struct index_titre *)malloc(nb * sizeof(struct index_titre));
    *nbindex = 0;
    int i = 0;
    int j = 0;
    int trouve = -1;
    for (i = 0; i < nb; i++) {
        for (j = 0; j < *nbindex; j++) {
            if (strcmp(tab[i].titre, id[j].titre) == 0) {
                trouve = j;
                break;
            }
        }
        if (trouve == -1) {
            id = (struct index_titre *)realloc(id, ((*nbindex) + 1) * sizeof(struct index_titre));
            strcpy(id[*nbindex].titre, tab[i].titre);
            id[*nbindex].lst = (int *)malloc(sizeof(int));
            id[*nbindex].nb = 1;
            id[*nbindex].lst[0] = i;
            (*nbindex)++;
        } else {
            id[trouve].lst = (int *)realloc(id[trouve].lst, (id[trouve].nb + 1) * sizeof(int));
            id[trouve].lst[id[trouve].nb] = i;
            id[trouve].nb++;
        }
    }
    qsort(id, (*nbindex), sizeof(id[0]), trieindex);
    for (i = 0; i < *nbindex; i++) {
        printf("titre : %s\n", id[i].titre);
        for (j = 0; j < id[i].nb; j++)
            printf("%d\n", id[i].lst[j]);
        puts("\n");
    }
    return id;
}

int trieindex(const void * a, const void * b) {
    return strcmp(((struct index_titre *)a)->titre, ((struct index_titre *)b)->titre);
}

void recherche(struct tfe * tab, int nb, struct index_titre * idtab, int nbid) {
    struct index_titre * temp, cle;
    char input[MAX_CHAR];
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%s", cle.titre) != 1)
        printf("mauvaise entree");
    temp = (struct index_titre *)bsearch(&cle, idtab, nbid, sizeof(temp[0]), trieindex);
    if (temp == NULL)
        printf("not found\n");
    else
        for (int j = 0; j < temp->nb; j++)
            printf("%d) titre : %s ;; categorie : %d\n", j, tab[temp->lst[j]].titre, tab[temp->lst[j]].cat);
}

int main(void) {
    struct index_titre * idtab = NULL;
    int nbi = 0;
    struct tfe tab[] = {
        { .titre = "bcdef", .cat = 2 },
        { .titre = "harst", .cat = 4 }, 
        { .titre = "xcfd", .cat = 4 },
        { .titre = "harst", .cat = 1 },
    };
    int nbs = (sizeof(tab)/sizeof(tab[0]));
    idtab = indexation(tab, nbs, idtab, &nbi);
    recherche(tab, nbs, idtab, nbi);
    // for (int n = 0; n < (sizeof(tab)/sizeof(tab[0])); n++) {
    //     printf("travaux[%d] \n\t{ %s, %d },\n", n, tab[n].titre, tab[n].cat);

    // }
    free(idtab);
    return 0;
}
