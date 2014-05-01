#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COTES 5
#define MAX_ETU 25
#define MAX_CAR 20
#define taille(X) sizeof(X)/sizeof(X[0])

typedef struct {
    int matricule;
    char nom[MAX_CAR];
    float cotes[MAX_COTES];
    float moyenne;
} etu;

typedef struct {
    etu tab[MAX_ETU];
    int nb;
} classe;

void afficher_etudiant(etu *);
void entrer_cotes(etu *);
void calculer_moyenne(etu *);
int  check_cote(float);
void initialiser_classe(classe *);
void afficher_classe(classe *);
int  comparer_moyennes(const void *, const void *);
void trier_par_moyenne(classe *);
void ecrire_binaire(classe *);

void afficher_etudiant(etu * e) {
    int i = 0;
    printf("Nom : %s\nMatricule : %d\n", e->nom, e->matricule);
    for (i = 0; i < MAX_COTES; i++)
        printf("Cote nr.%d : %2.1f/20\n", i+1, e->cotes[i]);
    printf("Moyenne : %2.1f%%\n", e->moyenne);
}

void entrer_cotes(etu * e) {
    int i = 0;
    float cote;
    for (i = 0; i < MAX_COTES; i++) {
        do {
            printf("cote nr.%d : ", i+1);
            scanf("%f", &cote);
            e->cotes[i] = cote;
        } while (check_cote(cote));
    }
}

void calculer_moyenne(etu * e) {
    int i = 0;
    float somme = 0;
    for (i = 0; i < MAX_COTES; i++) 
        somme += e->cotes[i];
    e->moyenne = (((somme/MAX_COTES)/20)*100);
}

int check_cote(float cote) {
    int decim = 10 * (cote - (int)cote);
    if (cote > 20 || cote < 0) return 1;
    else if (decim == 5 || decim == 0) return 0;
    else return 1;
}

void initialiser_classe(classe * c) {
    int i = 0;
    c->nb = 0;
    int rester = 1;
    char nom[MAX_CAR];
    printf("Entrer 0 comme nom pour finir d'encoder les etudiants\n");
    while (rester) {
        printf("Nom? : ");
        scanf("%s", nom);
        if (strcmp(nom, "0") == 0) rester = 0;
        else {
            strcpy(c->tab[c->nb].nom, nom);
            printf("Encodage de cotes pour %s\n", c->tab[c->nb].nom);
            entrer_cotes(&c->tab[c->nb]);
            c->tab[i].matricule = c->nb;
            c->nb++;
        }
    }
}

void afficher_classe(classe * c) {
    int i = 0;
    for (i = 0; i < c->nb; i++)
        afficher_etudiant(&c->tab[i]);
}

int comparer_moyennes(const void *a, const void *b) {
    etu *e1 = (etu *)a;
    etu *e2 = (etu *)b;
    return e2->moyenne - e1->moyenne;
}

void trier_par_moyenne(classe * c) {
    int i = 0;
    for (i = 0; i < c->nb; i++)
        calculer_moyenne(&c->tab[i]);
    qsort(c->tab, c->nb, sizeof(c->tab[0]), comparer_moyennes);
}

void ecrire_binaire(classe * c) {
    FILE *f;
    if ((f = fopen("classe.bin", "wb")) == NULL)
        exit(EXIT_FAILURE);
    fwrite(c->tab, sizeof(c->tab), 1, f);
    fclose(f);
}
int main(void) {
    classe tm;
    initialiser_classe(&tm);
    puts("\n---------------\n");
    trier_par_moyenne(&tm);
    afficher_classe(&tm);
    ecrire_binaire(&tm);
    return 0;
}
