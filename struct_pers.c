#include <stdio.h>
#include <stdlib.h>

#define persDat "personnes.dat"

typedef struct TDate {
    int annee;
    int mois;
    int jour;
} TDate; // structure abstraite de date

typedef struct TPers {
    int  persId;
    char persNom[41];
    char persPrn[21];
    char persSexe;
    TDate persNaiss;
    char persAdr[51];
    int  vilId;
} TPers; // structure abstraite de personne

int main(void) {
    FILE *f;
    TPers * tab = NULL;
    unsigned int nb = 0;
    unsigned int i = 0;

    // on ouvre le fichier binaire
    if ((f = fopen(persDat, "rb")) == NULL) {
        printf("failed to open %s\n", persDat);
        return -1;
    } else {
        // tant que pas fin du fichier
        while (!feof(f)) {
            // on agrandit notre tableau de personnes
            tab = realloc(tab, (nb + 1) * sizeof(TPers));
            if (tab == NULL) {
                printf("failed to reallocate\n");
                return -1;
            } else {
                // si ça a marché, on lit une personne
                fread(&tab[nb], sizeof(TPers), 1, f);
                // nombre de personnes + 1
                nb++;
            }
        }
        // la derniere ligne est toujours mauvaise
        nb--;
    }


    // ecrire des donnees enregistrees
    for (i = 0; i < nb; i++)
        printf("%d : %s : %s : %c : %s\n", 
        tab[i].persId, tab[i].persNom, tab[i].persPrn, tab[i].persSexe, tab[i].persAdr);

    fclose(f);
    free(tab);
    tab = NULL;
    return 0;
}
