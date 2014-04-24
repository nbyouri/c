#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

// index tableau == marticule.

// constantes globales 
#define NB_COTES 5
#define NB_ETU 5
#define NB_NOM 20
#define FICHIER "data_classe"

// variables globales
static int i = 0;
static int j = 0;
static int choix = 0;

// type de donnees etudiant
typedef struct {
    int   matr;
    char  nom[NB_NOM];
    float cotes[5];
    float moyenne;
} etudiant;

// classe d'etudiants
typedef struct {
    int nbEtu;
    etudiant etudiants[NB_ETU];
} classe;

// declarations de fonctions
int  lire_fichier(void);
int  ecrire_fichier(classe *);
void echange_structure(etudiant *, etudiant *);
int  comp_moyenne(float, float);
void trier_par_moyenne(classe *);
float verif_cotes(float);
void encoder_cotes(classe *, bool, int, bool);
int  choix_etudiant(classe *);
void calculer_moyenne(classe *, int, bool);
void menu_principal(classe);
void modifier_etudiant(classe *, int);
void afficher_tout(classe *);

// c'est ici que tout ce passe...
int main(void) {
    // initialisation des etudiants.
    classe classe_1;
    classe_1.nbEtu = NB_ETU; //vilain.
    for (i = 0; i < classe_1.nbEtu; i++) {
        classe_1.etudiants[i].matr = i;
        strcpy(classe_1.etudiants[i].nom, "0");
    }
    encoder_cotes(&classe_1, true, 0, true);
    // on commence
    menu_principal(classe_1);
    return 0;
}

// menu principal 
void menu_principal(classe classe_1) {
    char lire[3];
    bool rester = true;
    // fonction graphique
    system("clear");
    printf("Bienvenue Sur La plateforme Etudiants!\n\n\n");
    // boucle principale
    while (rester) {
        printf("1) ---> Afficher tous les etudiants\n"
                "2) ---> Ajouter/Modifier/Supprimer un etudiant\n"
                "3) ---> Calculer la moyenne d'un etudiant\n"
                "4) ---> Encoder une cote\n"
                "5) ---> Afficher par ordre de pourcents\n"
                "6) ---> Ecrire sur fichier\n"
                "0) ---> Sortir de la plateforme\n\t> ");
        scanf("%d", &choix);
        switch (choix) {
            case 1 : 
                afficher_tout(&classe_1);
                break;
            case 2 : 
                modifier_etudiant(&classe_1, choix_etudiant(&classe_1));
                break;
            case 3 : 
                calculer_moyenne(&classe_1, choix_etudiant(&classe_1), false);
                break;
            case 4 :
                encoder_cotes(&classe_1, true, 0, false);
                break;
            case 5 : 
                calculer_moyenne(&classe_1, 0, true);
                trier_par_moyenne(&classe_1);
                for (i = 0; i < classe_1.nbEtu; i++) {
                    printf("%d) Moyenne de l'etudiant nr.%d : %2.1f%%\n", 
                            i+1, classe_1.etudiants[i].matr, classe_1.etudiants[i].moyenne);
                }
                puts("\n");
                break;
            case 6 : 
                ecrire_fichier(&classe_1);
                break;
            case 0 : 
                printf("Lire fichier? (o/n) : ");
                scanf("%s", lire);
                if (strcmp(lire, "o") == 0) lire_fichier();
                rester = false;
                break;
            default: 
                printf("Choix invalide\n");
        }
    }
}

int lire_fichier(void) {
    // lire le fichier de la classe
    FILE *fp;
    char s[100];
    if ((fp = fopen(FICHIER, "r")) == NULL)
        return -1;
    while (fgets(s, 100, fp)) {
        s[strlen(s)-1] = '\0';
        printf("%s\n", s);
    }
    fclose(fp);
    return 0;
}

int ecrire_fichier(classe * classe) {
    // on ecrit les donnees de la classe sur un fichier
    FILE *fp;
    if ((fp =  fopen(FICHIER, "w")) == NULL) 
        return -1;
    for (i = 0; i < classe->nbEtu; i++) {
        fprintf(fp, "%d: \nNom : %s, Matricule: %d\n", 
                i+1 , classe->etudiants[i].nom, classe->etudiants[i].matr);
        for (j = 0; j < NB_COTES; j++) {
            fprintf(fp, "Cote %d: %2.1f/20\n", j, classe->etudiants[i].cotes[j]);
        }
        fputs("\n", fp);
    }
    fclose(fp);
    return 0;
}

void echange_structure(etudiant * etu1, etudiant * etu2) {
    // echange de structure avec une structure tampon
    etudiant temp = *etu1;
    *etu1 = *etu2; *etu2 = temp;
}

int comp_moyenne(float a, float b) {
    // On multiplie par 10 et on transtype le float en int 
    // pour garder la precision en comparant des pourcentages
    return (int)(b * 10) - (int)(a * 10);
}

void trier_par_moyenne(classe * classe) {
    // on trie les etudiants par moyenne
    for (i = 0; i < classe->nbEtu - 1; i++) {
        int mini = i;
        for (j = i + 1; j < classe->nbEtu; j++) {
            if ((comp_moyenne(classe->etudiants[mini].moyenne, classe->etudiants[j].moyenne)) > 0) 
                mini = j;
        }
        if (mini != i) echange_structure(&classe->etudiants[i], &classe->etudiants[mini]);
    }
}

float verif_cotes(float cote) {
    // cote >= 0 et cotes <= 20 a 0.5 pres!
    int decimales = (int)(((cote - (int)cote)) * 10);
    if (cote <= 20 && cote >= 0) {
        if ((decimales == 5) || decimales == 0) 
            return cote;
        else return -1;
    } else return -1;
}

void encoder_cotes(
    classe * classe, bool touteclasse, 
    int etudiant, bool reinitialiser) 
{
    // encoder une ou plusieurs cotes pour un etudiant ou toute la classe
    // reinitialiser met toutes les cotes a 0
    if (touteclasse) {
        for (i=0; i < classe->nbEtu; i++) {
            for (j = 0; j < NB_COTES; j++) {
                if (reinitialiser) {
                    classe->etudiants[i].cotes[j] = 0;
                } else {
                    do {
                        printf("Etudiant %d) Cote nr.%d: ", i, j+1);
                        scanf("%f", &classe->etudiants[i].cotes[j]);
                    } while ((int)(verif_cotes(classe->etudiants[i].cotes[j])) == -1);
                }
            }
        }
    } else {
        for (j = 0; j < NB_COTES; j++) {
            if (reinitialiser) {
                classe->etudiants[etudiant].cotes[j] = 0;
            } else {
                do {
                    printf("Cote nr.%d: ", j+1);
                    scanf("%f", &classe->etudiants[etudiant].cotes[j]);
                } while ((int)(verif_cotes(classe->etudiants[etudiant].cotes[j])) == -1);
            }
        }
    }
}

int choix_etudiant(classe * classe) {
    // on verifie que l'etudiant existe
    bool existe = false;
    int m = 0;
    do {
        printf("Matricule de l'etudiant: ");
        scanf("%d", &m);
        if (m >= 0 && m <= classe->nbEtu)
            existe = true;
    } while (!existe);
    if (existe) return m;
    else return -1;
}

void calculer_moyenne(classe * classe, int etudiant, bool touteclasse) {
    // calcule la moyenne des points d'un etudiant ou de toute la classe
    float somme;
    if (touteclasse) {
        for (i = 0; i < classe->nbEtu; i++) {
            somme = 0;
            for (j = 0; j < NB_COTES; j++) 
                somme += classe->etudiants[i].cotes[j];
            classe->etudiants[i].moyenne = ((somme/NB_COTES)/20)*100;
        }
    } else {
        somme = 0;
        for (i = 0; i < NB_COTES; i++) 
            somme += classe->etudiants[etudiant].cotes[i];
        classe->etudiants[etudiant].moyenne = ((somme/NB_COTES)/20)*100;
        printf("Moyenne des points: %2.1f%%\n", classe->etudiants[etudiant].moyenne);
    }
}

void modifier_etudiant(classe * classe, int etudiant) {
    // modifier, ajouter ou supprimer etudiants
    printf("\nmodifier?\n"
            "1) --> nom\n"
            "2) --> cotes\n"
            "3) --> matricule\n"
            "\najouter ou supprimer\n"
            "4) --> supprimer\n"
            "5) --> ajouter\n"
            "choix? : ");
    scanf("%d", &choix);
    switch (choix) {
        case 1 : 
            printf("\nchoisir nom: ");
            scanf("%s", classe->etudiants[etudiant].nom);
            break;
        case 2 : 
            printf("\nEntrer nouvelles cotes: \n");
            encoder_cotes(classe, false, etudiant, false);
            break;
        case 3 : 
            printf("\nEntrer nouveau matricule: ");
            scanf("%d", &classe->etudiants[etudiant].matr);
            break;
        case 4 : 
            classe->etudiants[etudiant].matr = 0;
            strcpy(classe->etudiants[etudiant].nom, "0");
            encoder_cotes(classe, false, etudiant, true);
            classe->nbEtu--;
            break;
        case 5 :
            modifier_etudiant(classe, etudiant);
            classe->nbEtu++;
            break;
        default : 
            printf("Saisie incorrecte\n");
    }
} 

void afficher_tout(classe * classe) {
    // affiche tous les etudiants et leur cotes
    for (i = 0; i < classe->nbEtu; i++) {
        printf("%d)\nMatricule = %d\nNom = %s\n", i+1, classe->etudiants[i].matr, classe->etudiants[i].nom);
        for (j = 0; j < NB_COTES; j++)
            printf("Cote %d : %2.1f/20\n", j + 1, classe->etudiants[i].cotes[j]);
        puts("\n");
    }
}
