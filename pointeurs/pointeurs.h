#include <stdio.h>  // printf
#include <string.h> // strcpy, strcmp

#define MAXETUDIANTS 25
#define MAXCHAR 10
#define TAILLE(X) (int)(sizeof(X)/sizeof(X[0]))

typedef struct {
    char    prenom[MAXCHAR];
    int     num;
} personne;

typedef struct {
    personne   etudiants[MAXETUDIANTS];
    int        nb;
} classe;

int mon_strcmp(char *, char *);
void afficher_classe(classe *);
void afficher_classe_sans_pointeur(classe);
