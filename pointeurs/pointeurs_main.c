#include "pointeurs.h"

int main(void) {

    int a[4] = { 0, -2, 5, 3 };

    printf("a[0] = %d\n *(a + 1) = %d\n pointeur de a = %p\n\n\n",
            a[0], *(a + 1), &a);

    int *b = a;
    printf("b = %d\n, adress de b = %p\n", b[2], &b);

    puts("/*----------------------------------------------------------------*/");

    char *nom;
    char prenom[MAXCHAR];
    char initiales[] = "pk";
    nom = "sias";
    strncpy(prenom, "nicolas", 2);
    printf("nom = %s\nprenom = %s\ninitiales = %s\n", nom, prenom, initiales);

    puts("/*----------------------------------------------------------------*/");

    char kot_simple[3][MAXCHAR] = { "nicolas", "youri", "henri" };

    for (int i = 0; i < TAILLE(kot_simple); i++)
        printf("%s\n", kot_simple[i]);

    for (int i = 0; i < TAILLE(kot_simple); i++)
        for (int j = 0; j < MAXCHAR; j++)
            printf("%c\n", kot_simple[i][j]);

    puts("/*----------------------------------------------------------------*/");

    char *kot[] = { "nicolas", "youri", "henri" };
    char **nr = kot;
    for (int i = 0; i < TAILLE(kot); i++)
        printf("etudiant du kot nr.%d : %s\n", i, *(nr+i)); //kot[i]);

    puts("/*----------------------------------------------------------------*/");

    if (mon_strcmp("blah", "blah") == 0)
        printf("mon_strcmp(a, b) == 0\n");

    puts("/*----------------------------------------------------------------*/");

    classe TM1;
    TM1.nb = MAXETUDIANTS;
    for (int i = 0; i < TM1.nb; i++) {
        TM1.etudiants[i].num = i;
        strcpy(TM1.etudiants[i].prenom, "nomvide");
    }

    afficher_classe(&TM1);

    puts("/*----------------------------------------------------------------*/");

    classe TM2;
    TM2.nb = MAXETUDIANTS;
    for (int i = 0; i < TM2.nb; i++) {
        TM2.etudiants[i].num = 25+i;
        strcpy(TM2.etudiants[i].prenom, "nomvide_TM2");

    }

    afficher_classe_sans_pointeur(TM2);

    puts("/*----------------------------------------------------------------*/");

    printf("sizeof(classe) = %lu\n", sizeof(classe));
    printf("sizeof(TM2) = %lu\n", sizeof(TM2));
    printf("sizeof(personne) = %lu\n", sizeof(personne));
    printf("sizeof(classe.etudiants) = %lu\n", sizeof(TM1.etudiants));
    printf("sizeof(classe.nb) = %lu\n", sizeof(TM1.nb));


    puts("/*----------------------------------------------------------------*/");

    // pointeurs
    int i;
    #define MAX 3
    int tab[MAX] = { 9, 3, 5 };
    puts("\n");
    for (i = 0; i < MAX; i++)
        printf("tab[%d] = tab + %d = %d = %p\n", i, i, tab[i], (tab + i));
                                            // indice,content, adresse
    puts("\n");
    printf("for (int i = 0; i < ""MAX""; printf(tab[i++])) and\n");
    printf("for (int i = 0; i < ""MAX""; printf(*(tab + i++))) = ");
    for (i = 0; i < MAX; printf("%d ", (*(tab + i++))));

    puts("\n");
    printf("tab = %p\n", tab);

    printf("*tab = %d\n", *tab);
    printf("*(tab + 1) = %d\n", *(tab + 1));
    printf("&(*(tab + 1)) = %p\n", &(*(tab + 1)));
    printf("(&(*tab)) = %p\n", (&(*tab)));
    printf("(*(&tab)) = %p\n", (*(&tab)));
    printf("(*(&tab) + 2)) = %p\n", (*(&tab) + 2));
    printf("(*(*(&tab) + 2)) = %d\n", (*(*(&tab) + 2)));
    printf("(&(*(*(&tab) + 2))) = %p\n", (&(*(*(&tab) + 2))));
    return 0;
}
