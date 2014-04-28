#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxTfes 4

typedef struct {
    char titre[20];
    int categorie;
} TTfe;

typedef struct {
    int nbTfes;
    TTfe tbTfes;
} TpTfes;

static TpTfes T_travaux[maxTfes] = {
    { .nbTfes = 1, { .titre = "bcdef", .categorie = 2 }},
    { .nbTfes = 2, { .titre = "arst", .categorie = 4 }}, 
    { .nbTfes = 3, { .titre = "xcfd", .categorie = 4 }},
    { .nbTfes = 4, { .titre = "harst", .categorie = 1 }},
};

int fcomp_categories(const void *, const void *);
int fcomp_titres(const void *, const void *);
void trier(TpTfes *); 
void echange(TpTfes *, TpTfes *);

int fcomp_categories(const void * a, const void * b) {
    TpTfes * p1 = (TpTfes *)a;
    TpTfes * p2 = (TpTfes *)b;
    return p2->tbTfes.categorie - p1->tbTfes.categorie;
}

int fcomp_titres(const void * a, const void * b) {
    TpTfes * p1 = (TpTfes *)a;
    TpTfes * p2 = (TpTfes *)b;
    return strcmp(p1->tbTfes.titre, p2->tbTfes.titre);
}

void echange(TpTfes * trav1, TpTfes * trav2) {
    TpTfes temp = *trav1;
    *trav1 = *trav2;
    *trav2 = temp;
}

void trier(TpTfes * trav) {
    for (int i = 0; i < maxTfes; i++) {
        for (int j = 0; j < maxTfes - 1; j++) {
            if (fcomp_categories(&trav[j], &trav[j+1]) > 0) {
                echange(&trav[j], &trav[j+1]);
            } else if (fcomp_categories(&trav[j], &trav[j+1]) == 0) {
                if (fcomp_titres(&trav[j], &trav[j+1]) > 0)  
                    echange(&trav[j], &trav[j+1]);
            }
        } 
    }
}

int main(void) {
    //qsort(T_travaux, sizeof(T_travaux)/sizeof(TpTfes), sizeof(T_travaux[0]), fcomp_titres);
    trier(T_travaux);
    for (int n = 0; n < (sizeof(T_travaux)/sizeof(T_travaux[0])); n++) {
        printf("travaux[%d] \n\t{ %d, { %s, %d }},\n", n, T_travaux[n].nbTfes, 
                T_travaux[n].tbTfes.titre, T_travaux[n].tbTfes.categorie);
    }
    return 0;
}
