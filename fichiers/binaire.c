#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FICHIER_BINAIRE "riding.bin"
#define FICHIER_TEXTE "riding.txt"
#define MAX_CHEVAUX 100
#define MAX_CAR 1000
#define TAILLE(X) (int)(sizeof(X)/sizeof(X[0]))

typedef struct {
	char discipline[MAX_CAR];
	char couleur[MAX_CAR];
	int  taille;
} type_cheval;

typedef struct {
	int nbCh;
	type_cheval chevaux[MAX_CHEVAUX];
} type_manege;

void initialiser_bd(type_manege *);
void ecrire_fitexte(type_manege *);
void ecrire_binaire(type_manege *);
void lire_fichtexte(void);
void lire_fibinaire(type_manege *);
void charge_fitexte(type_manege *);

int main(void) {
	type_manege riding;
	//initialiser_bd(&riding);
	//ecrire_binaire(&riding);
	//ecrire_fitexte(&riding);
	//lire_fichtexte();
	lire_fibinaire(&riding);
	return 0;
}

void initialiser_bd(type_manege * manege) {
	int i = 0;
	manege->nbCh = 0;
	for (i = 0; i < MAX_CHEVAUX; i++) {
		strcpy(manege->chevaux[i].discipline, "dressage");
		strcpy(manege->chevaux[i].couleur, "blanc");
		manege->chevaux[i].taille = 180;
		manege->nbCh++;
	}
}

void ecrire_fitexte(type_manege * manege) {
	int i = 0;
	FILE *bdd;
	if ((bdd = fopen(FICHIER_TEXTE, "wt")) == NULL)
		exit(EXIT_FAILURE);
	for (i = 0; i < manege->nbCh; i++) 
		fprintf(bdd, "%d )\n Discipline : %s\n Couleur : %s\n Taille : %d\n\n", 
			i, manege->chevaux[i].discipline, manege->chevaux[i].couleur, manege->chevaux[i].taille);
	fclose(bdd);
}

void ecrire_binaire(type_manege * manege) {
	FILE *bdd;
	if ((bdd = fopen(FICHIER_BINAIRE, "wb")) == NULL)
		exit(EXIT_FAILURE);
	fwrite(manege->chevaux, sizeof(manege->chevaux), 1, bdd);
	fclose(bdd);
}

void lire_fichtexte(void) {
	FILE *bdd;
	char s[MAX_CAR];
	if ((bdd = fopen(FICHIER_TEXTE, "rt")) == NULL)
		exit(EXIT_FAILURE);
	while (fgets(s, sizeof(s), bdd)) {
		printf("%s", s);
	}
	fclose(bdd);
}

void lire_fibinaire(type_manege * manege) {
	FILE *bdd;
	int i = 0;
	if ((bdd = fopen(FICHIER_BINAIRE, "rb")) == NULL)
		exit(EXIT_FAILURE);
	fread(manege->chevaux, sizeof(manege->chevaux), 1, bdd);
	for (i = 0; i < TAILLE(manege->chevaux); i++)
		printf("%d )\n Discipline : %s\n Couleur : %s\n Taille : %d\n\n", 
			i, manege->chevaux[i].discipline, manege->chevaux[i].couleur, manege->chevaux[i].taille);
	fclose(bdd);
}
