#include <stdio.h>		//printf, fprintf, fopen, fclose, fgets, fread, fwrite
#include <stdlib.h>		//exit, atoi
#include <string.h>		//strcpy, strtok

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
void lire_ligne(type_manege *);

int main(void) {
    type_manege riding;
    //initialiser_bd(&riding);
    //ecrire_binaire(&riding);
    // ecrire_fitexte(&riding);
    // lire_fichtexte();
    //lire_fibinaire(&riding);
    lire_ligne(&riding);
    //charge_fitexte(&riding);
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
        fprintf(bdd, "%d : Discipline : %s : Couleur : %s : Taille : %d\n", 
                i, manege->chevaux[i].discipline, 
                manege->chevaux[i].couleur, manege->chevaux[i].taille);
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
    int nb = 0;
    if ((bdd = fopen(FICHIER_BINAIRE, "rb")) == NULL)
        exit(EXIT_FAILURE);
    fread(manege->chevaux, sizeof(manege->chevaux), 1, bdd);
    for (i = 0; i < TAILLE(manege->chevaux); i++)
        printf("%d : Discipline : %s Couleur : %s Taille : %d\n", 
                i, manege->chevaux[i].discipline, 
                manege->chevaux[i].couleur, manege->chevaux[i].taille);
    fclose(bdd);
}

void charge_fitexte(type_manege * manege) {
    FILE *bdd;
    int i = 0;
    char s[MAX_CAR];
    if ((bdd = fopen(FICHIER_TEXTE, "rt")) == NULL)
        exit(EXIT_FAILURE);
    while (fgets(s, sizeof(s), bdd)) {
        strtok(s, ":"); 	//index
        strtok(NULL, ":");	//discipline
        strcpy(manege->chevaux[manege->nbCh].discipline, strtok(NULL, ":"));
        strtok(NULL, ":");  //couleur
        strcpy(manege->chevaux[manege->nbCh].couleur, strtok(NULL, ":"));
        strtok(NULL, ":");	//taille
        manege->chevaux[manege->nbCh].taille = atoi(strtok(NULL, ":"));
        manege->nbCh++;
    }
    for (i = 0; i < TAILLE(manege->chevaux); i++)
        printf("cheval %d : %s : %s : %d\n", i, 
                manege->chevaux[i].discipline, 
                manege->chevaux[i].couleur, 
                manege->chevaux[i].taille);
    fclose(bdd);
}

void lire_ligne(type_manege * manege) {
    FILE *bdd;
    int nb = 0;
    if ((bdd = fopen(FICHIER_BINAIRE, "rb")) == NULL)
        exit(EXIT_FAILURE);
    fread(&manege->chevaux, sizeof(type_cheval), 1, bdd);
    while (!feof(bdd)) {
        //nb++;
        printf("%s : %s : %d\n",
                manege->chevaux->discipline, 
                manege->chevaux->couleur, 
                manege->chevaux->taille);
        fread(&manege->chevaux, sizeof(type_cheval), 1, bdd);
    }
    // printf("%d\n", nb); //nombre de lignes
    fclose(bdd);
}
