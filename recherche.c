#include <stdio.h>
#include <string.h>

int main(void) {
    typedef struct {
       char nom[15];
       int matri;
    } etudiant;
    
    etudiant tab[2] = { 
        { "youri", 2 },
        { "marine", 4 },
    };

    int mat = 2;
    char nom[] = "marine";
    for (int i = 0; i < (sizeof(tab)/sizeof(tab[0])); i++) {
        if (mat == tab[i].matri)
            printf("1) Matricule %d = Etudiant nr.%d\n { %s, %d },\n", 
                    mat, i+1, tab[i].nom, tab[i].matri);
        if (strcmp(nom, tab[i].nom) == 0) {
            printf("2) Matricule %d = Etudiant nr.%d\n { %s, %d },\n", 
                    mat, i+1, tab[i].nom, tab[i].matri);
            }
    }

    return 0;
}
