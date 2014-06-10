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
        /*
         *
         * Lecture ligne par ligne.
         *
         */
        /*
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
        */


        /*
         *
         * Lecture en une fois.
         *
         */
        // trouver le nombre d'enregistrements dans le fichier
        fseek(f, 0, SEEK_END);
        nb = ftell(f) / sizeof(TPers);

        // rembobinner le fichier
        rewind(f);

        // agrandir le tableau pour contenir ce nombre d'enregistrements
        tab = realloc(tab, (nb + 1) * sizeof(TPers));
        if (tab == NULL) {
            printf("erreur reallocation\n");
            return -1;
        } else {
            // puis on lit tout en une fois
            fread(tab, sizeof(TPers), nb, f);
        }
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
