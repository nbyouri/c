#include <stdio.h>  // printf, sprintf, fprint, fopen, fgets, fscanf, fclose, fread, fwrite
#include <stdlib.h> // atoi, exit, qsort
#include <string.h> // strlen, strcpy, strcmp, strtok, strcat

// constantes
#define CSV "C'est pas sorcier.csv"
#define N_MAX_E 450      
#define N_MAX_CAR 2000
#define N_MAX_SD 7
#define N_MAX_TH 10
#define N_MAX_CAR_THEME 32
#define N_MAX_CAR_SD 32
#define N_MAX_CAR_TITRE 80
#define TAILLE(X) (int)(sizeof(X)/sizeof(X[0]))

// type C_CPS contenant le titre, le numero, 
// le theme, le sous theme et l'annee
typedef struct {
    char titre[N_MAX_CAR_TITRE];
    int num;
    int th;
    int sd;
    int ann;
} T_CPS;

// type T_Tab_CPS conteant le nombre et
// un tableau de T_CPS
typedef struct {
    int nb;
    T_CPS tab[N_MAX_E];
} T_Tab_CPS;

// type T_Theme contenant le nom, le num de sous theme 
// et le sous theme
typedef struct {
    char nom[N_MAX_CAR_THEME];
    int nbSD;
    char tabSD[N_MAX_SD][N_MAX_CAR_SD];//[N_MAX_SD]
} T_Theme;

// type T_Tab_theme qui contient le num de themes 
// et le tableau de T_Themes
typedef struct {
    int nbTh;
    T_Theme tab[N_MAX_TH];
} T_Tab_Theme;

static T_Tab_Theme themes;

// declaration de fonctions
void charger_cps(T_Tab_CPS *);
void lecture_cps(T_Tab_CPS *);
int  trouveTheme(T_Tab_Theme *, char *);
int  trouveSD(T_Tab_Theme *, int, char *);
int  comp_num(const void *, const void *);
int  comp_titres(const void *, const void *);
int  comp_themes_sousthemes_titre(const void *, const void *);
int  comp_annee_themes_sousthemes_titre(const void *, const void *);
void sauvegarder(T_Tab_CPS *);
void lire_binaire(T_Tab_CPS *);

// c'est ici que tout ce passe...
int main(void) {
    T_Tab_CPS cps;
    charger_cps(&cps); // si on sauvegarde..

    // tri qsort par numeros
    //qsort(cps.tab, (unsigned int)cps.nb, sizeof(cps.tab[0]), comp_num);

    // tri qsort par order alpha des titres
    //qsort(cps.tab, (unsigned int)cps.nb, sizeof(cps.tab[0]), comp_titres);

    // tri par nom de themes puis sous themes puis titre
    //qsort(cps.tab, (unsigned int)cps.nb, sizeof(cps.tab[0]), comp_themes_sousthemes_titre);

    // tri par annee puis theme puis sous theme puis titre
    //qsort(cps.tab, (unsigned int)cps.nb, sizeof(cps.tab[0]), comp_annee_themes_sousthemes_titre);
    //  f(base a trier (toujours un pointeur!), entier non signe, 
    //  taille d'un element de la base, fonction de comparaison retournant un entier et 
    //  avec deux pointeurs comme argument

    // on enregistre dans un fichier text
    sauvegarder(&cps);

    // chargement avec lecture fichier binaire
    //lire_binaire(&cps);

    // on affiche le resultat
    //lecture_cps(&cps);

    return 0;
}

// charge en memoire les differentes parties du fichier separees par ";"
void charger_cps(T_Tab_CPS * cps) {
    FILE *f;           
    int th, sd;                                     
    char s[N_MAX_CAR];                                      // chaine de caracteres
    if ((f = fopen(CSV, "rt")) == NULL)                     // si le fichier existe pas,
        exit(EXIT_FAILURE);                                 // on se casse 
    while (fgets(s, sizeof(s), f)) {                        // lecture fichier
        s[strlen(s)-1] = '\0';                              // dernier caractere nul
        strcpy(cps->tab[cps->nb].titre, strtok(s, ";"));    // titre
        cps->tab[cps->nb].num = atoi(strtok(NULL, ";"));    // numero
        strtok(NULL, ";"); // on ne veut pas du synopsis    // synopsis
        th = trouveTheme(&themes,strtok(NULL,";"));           // theme
        cps->tab[cps->nb].th = th;
        sd = trouveSD(&themes,th,strtok(NULL,";"));           // sous theme
        cps->tab[cps->nb].sd = sd;
        cps->tab[cps->nb].ann = atoi(strtok(NULL, ";"));    // annee
        cps->nb++;
    }
    fclose(f);                                              // on ferme le fichier
}

// affiche le tableau
void lecture_cps(T_Tab_CPS * cps) {
    int i = 0;
    // requiert une fenetre large!
    printf("      %-80s %-8s%-8s%-32s %5s\n%s%s\n", "titre", "num", "annee", "theme", "sous-theme",
            "-------------------------------------------------------------------------------------------",
            "----------------------------------------------------------------------------------");
    for (i = 0; i < cps->nb; i++) 
        printf("%03d : %-80s %-8d%-8d%-32s %5s\n", i,
                cps->tab[i].titre, cps->tab[i].num, cps->tab[i].ann,
                themes.tab[cps->tab[i].th].nom, themes.tab[cps->tab[i].th].tabSD[cps->tab[i].sd]);
}

int trouveSD(T_Tab_Theme * theme, int th, char sd[N_MAX_CAR_SD]){
    int i = 0;
    for (i = 0; i < theme->tab[th].nbSD; i++){
        if (strcmp(theme->tab[th].tabSD[i], sd) == 0) 
            return i;
    }
    strcpy(theme->tab[th].tabSD[theme->tab[th].nbSD], sd);
    theme->tab[th].nbSD++;
    return theme->tab[th].nbSD - 1;
}

int trouveTheme(T_Tab_Theme * theme, char *nomTh){
    int i = 0;
    for (i = 0; i < theme->nbTh; i++){
        if (strcmp(theme->tab[i].nom,nomTh) == 0)
            return i;
    }
    strcpy(theme->tab[theme->nbTh].nom,nomTh);
    theme->tab[theme->nbTh].nbSD = 0;
    theme->nbTh++;
    return theme->nbTh - 1;
}

int comp_num(const void *a, const void *b) {
    // comparaison par numeros, on compare p1 qui est l'argument 
    // a transtype en T_CPS.
    T_CPS *p1 = (T_CPS *)a;
    T_CPS *p2 = (T_CPS *)b;
    return p1->num - p2->num;
}

int comp_titres(const void *a, const void *b) {
    // comparaison des titres
    T_CPS *p1 = (T_CPS *)a;
    T_CPS *p2 = (T_CPS *)b;
    return strcasecmp(p1->titre, p2->titre);
}

int comp_themes_sousthemes_titre(const void *a, const void *b) {
    T_CPS * p1 = (T_CPS *)a;
    T_CPS * p2 = (T_CPS *)b;
    char s1[N_MAX_CAR_THEME+N_MAX_CAR_SD+N_MAX_CAR_TITRE];
    char s2[N_MAX_CAR_THEME+N_MAX_CAR_SD+N_MAX_CAR_TITRE];
    strcpy(s1, themes.tab[p1->th].nom);          // le theme
    strcat(s1, themes.tab[p1->th].tabSD[p1->sd]);// + le sous theme
    strcat(s1, p1->titre);                       // + le titre
    strcpy(s2, themes.tab[p2->th].nom);          // idem pour la deuxieme chaine
    strcat(s2, themes.tab[p2->th].tabSD[p2->sd]);         
    strcat(s2, p2->titre);   
    return strcasecmp(s1, s2);                       // on compare
}

int comp_annee_themes_sousthemes_titre(const void *a, const void *b) {
    // variables
    T_CPS * p1 = (T_CPS *)a;
    T_CPS * p2 = (T_CPS *)b;
    char s1[N_MAX_CAR_THEME+N_MAX_CAR_SD+N_MAX_CAR_TITRE+4];
    char s2[N_MAX_CAR_THEME+N_MAX_CAR_SD+N_MAX_CAR_TITRE+4];

    // on met tout ensemble dans deux chaines de caracteres a comparer
    sprintf(s1, "%d", p1->ann);                  // on met l'annee en premier dans la chaine
    strcat(s1, themes.tab[p1->th].nom);          // + le theme
    strcat(s1, themes.tab[p1->th].tabSD[p1->sd]);// + le sous theme
    strcat(s1, p1->titre);                       // + le titre
    sprintf(s2, "%d", p2->ann);                  // idem pour la deuxieme chaine
    strcat(s2, themes.tab[p2->th].nom);         
    strcat(s2, themes.tab[p2->th].tabSD[p2->sd]);         
    strcat(s2, p2->titre);   
    return strcasecmp(s1, s2);                       // on compare
}

void sauvegarder(T_Tab_CPS * cps) {
    //int i = 0;
    FILE *f;
    FILE *f2;
    // fichier texte
    //if ((f = fopen("data.txt", "wt")) == NULL)
    //    exit(EXIT_FAILURE);
    //fprintf(f, "      %-80s %-8s%-8s%-32s %5s\n%s%s\n", "titre", "num", "annee", "theme", "sous-theme",
    //    "-------------------------------------------------------------------------------------------",
    //    "----------------------------------------------------------------------------------");
    //for (i = 0; i < cps->nb; i++) 
    //fprintf(f, "%03d : %-80s %-8d%-8d%-32s %5s\n", i,
    //    cps->tab[i].titre, cps->tab[i].num, cps->tab[i].ann,
    //    themes->tab[cps->tab[i].th].nom, themes->tab[cps->tab[i].th].tabSD[cps->tab[i].sd]);


    // fichiers binaires
    if ((f = fopen("cps.bin", "wb")) == NULL)
        exit(EXIT_FAILURE);
    fwrite(cps->tab, sizeof(cps->tab), 1, f);
    if ((f2 = fopen("themes.bin", "wb")) == NULL)
        exit(EXIT_FAILURE);
    fwrite(themes.tab, sizeof(themes.tab), 1, f2);
    fclose(f);
    fclose(f2);
}

void lire_binaire(T_Tab_CPS * cps) {
    int i = 0;
    FILE *f;
    FILE *f2;
    if ((f = fopen("cps.bin", "rb")) == NULL)
        exit(EXIT_FAILURE);
    fread(cps->tab, sizeof(cps->tab), 1, f);
    if ((f2 = fopen("themes.bin", "rb")) == NULL)
        exit(EXIT_FAILURE);
    fread(themes.tab, sizeof(themes.tab), 1, f2);
    printf("      %-80s %-8s%-8s%-32s %5s\n%s%s\n", "titre", "num", "annee", "theme", "sous-theme",
            "-------------------------------------------------------------------------------------------",
            "----------------------------------------------------------------------------------");
    for (i = 0; i < TAILLE(cps->tab); i++) 
        printf("%03d : %-80s %-8d%-8d%-32s %5s\n", i,
                cps->tab[i].titre, cps->tab[i].num, cps->tab[i].ann,
                themes.tab[cps->tab[i].th].nom, themes.tab[cps->tab[i].th].tabSD[cps->tab[i].sd]);
    fclose(f);
    fclose(f2);
}
