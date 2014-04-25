#include <stdio.h>  // printf
#include <string.h> //strcpy

#define MAXETUDIANTS 25
#define MAXCHAR 10
#define TAILLE(X) sizeof(X)/sizeof(X[0])

typedef struct {
	int num;
	char prenom[MAXCHAR];
} personne;

typedef struct {
	int nb;
	personne etudiants[MAXETUDIANTS];
} classe;

classe TM2;

int mon_strcmp(char *, char *);
void afficher_classe(classe *);
void afficher_classe_sans_pointeur(classe);

int main(void) {
	/*
    int a[4] = { 0, -2, 5, 3 };

    printf("a[0] = %d\n *(a + 1) = %d\n pointeur de a = %p\n\n\n",
            a[0], *(a + 1), &a);

    int *b = a;
    printf("b = %d\n, adress de b = %p", b[2], &b);
	*/
	/*---------------------------------------------------------------*/
	/*
    char *nom;
    char prenom[MAXCHAR];
    char initiales[] = "pk";
    nom = "sias";
    strncpy(prenom, "nicolas", 2);
    printf("nom = %s\nprenom = %s\ninitiales = %s\n", nom, prenom, initiales);
    */
    /*----------------------------------------------------------------*/
    /*
    char kot_simple[3][MAXCHAR] = { "nicolas", "youri", "henri" };
    // affiche les prenoms
    for (int i = 0; i < TAILLE(kot_simple); i++)
    	printf("%s\n", kot_simple[i]);
    
    for (int i = 0; i < TAILLE(kot_simple); i++)
    	for (int j = 0; j < MAXCHAR; j++)
    		printf("%c\n", kot_simple[i][j]);
    */
    /*----------------------------------------------------------------*/
    /*
    char *kot[] = { "nicolas", "youri", "henri" };
    char **nr = kot;
    for (int i = 0; i < TAILLE(kot); i++)
    	printf("etudiant du kot nr.%d : %s\n", i, *(nr+i)); //kot[i]);
    */
	/*----------------------------------------------------------------*/
	/*
	if (mon_strcmp("blah", "blah") == 0)
		printf("mon_strcmp(a, b) == 0\n");
	*/
	/*----------------------------------------------------------------*/
	//initialiser classe
	classe TM1;
	TM1.nb = MAXETUDIANTS;
	for (int i = 0; i < TM1.nb; i++) {
		TM1.etudiants[i].num = i;
		strcpy(TM1.etudiants[i].prenom, "nomvide");
	}
	/*
	TM2.nb = MAXETUDIANTS;
	for (int i = 0; i < TM2.nb; i++) {
		TM2.etudiants[i].num = 25+i;
		strcpy(TM2.etudiants[i].prenom, "nomvide_TM2");
	
	}*/
	afficher_classe(&TM1);

	puts("/*----------------------------------------------------------------*/");
	/*
	afficher_classe_sans_pointeur(TM2);
	*/
    return 0;
}
/*
int mon_strcmp(char *a, char *b) {
	return strcmp(a, b);
}
*/
void afficher_classe(classe * la_classe) {
	int i = 0;
	int j = 0;
	for (i = 0; i < la_classe->nb; i++) {
		printf("etudiant %d/%d :\n"
				"\tPrenom: %s\n"
				"\tIdentifiant: %d\n",
				i+1, la_classe->nb, la_classe->etudiants[i].prenom, la_classe->etudiants[i].num);
	}
}
/*
void afficher_classe_sans_pointeur(classe TM2) {
	int i = 0;
	int j = 0;
	for (i = 0; i < TM2.nb; i++) {
		printf("etudiant %d/%d :\n"
				"\tPrenom: %s\n"
				"\tIdentifiant: %d\n",
				i+1, TM2.nb, TM2.etudiants[i].prenom, TM2.etudiants[i].num);
	}
}
*/