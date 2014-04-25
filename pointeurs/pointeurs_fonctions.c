#include "pointeurs.h"

void afficher_classe(classe * la_classe) {
    int i = 0;
    for (i = 0; i < la_classe->nb; i++) {
        printf("etudiant %d/%d :\n"
                "\tPrenom: %s\n"
                "\tIdentifiant: %d\n",
                i+1, la_classe->nb, la_classe->etudiants[i].prenom, 
                la_classe->etudiants[i].num);
    }
}

void afficher_classe_sans_pointeur(classe TM2) {
    int i = 0;
    for (i = 0; i < TM2.nb; i++) {
        printf("etudiant %d/%d :\n"
                "\tPrenom: %s\n"
                "\tIdentifiant: %d\n",
                i+1, TM2.nb, TM2.etudiants[i].prenom, TM2.etudiants[i].num);
    }
}

int mon_strcmp(char *a, char *b) {
    return strcmp(a, b);
}
