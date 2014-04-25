#include <stdio.h>  // printf
#include <string.h> //strcpy

#define MAXETUDIANTS 25
#define MAXCHAR 10
#define TAILLE(X) (int)(sizeof(X)/sizeof(X[0]))

typedef struct {
    int num;
    char prenom[MAXCHAR];
} personne;

typedef struct {
    int nb;
    personne etudiants[MAXETUDIANTS];
} classe;

int mon_strcmp(char *, char *);
void afficher_classe(classe *);
void afficher_classe_sans_pointeur(classe);
