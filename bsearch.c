#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define taille(X) sizeof(X)/sizeof(X[0])

typedef struct {
	int id;
	char *nom;
	char sexe;
	int age;
} Personne;

typedef struct {
	int id;
	int ref;
} ID;

int cmp_id(const void *, const void *);
ID * index_primaire(const Personne *, int);
void afficher_index_primaire(const ID *, int);
void recherche_par_id(const Personne *, int, const ID *);
void afficherPersonne(const Personne *, int);

int main(void) {
	Personne tbPers[] = { 
		{33,  "nicolas", 'm', 29},
        {125, "antoine", 'm', 24},
        {65,  "nicole",  'f', 53},
        {111, "zoe",     'f', 29},
        {812, "serge",   'm', 79},
        {59,  "agnes",   'f', 55},
        {99,  "julie",   'f', 65},
        {3,   "nicolas", 'm', 18},
        {8,   "zoe",     'f', 57},
        {93,  "amelie",  'f', 33},
        {1,   "antoine", 'm', 12},
        {10,  "zoe",     'f', 61},
        {21,  "nicole",  'f', 33}
    };
    int nbPers = taille(tbPers);
    ID *idtab = NULL;
    idtab = index_primaire(tbPers, nbPers);
    afficher_index_primaire(idtab, nbPers);
    recherche_par_id(tbPers, nbPers, idtab);
	free(idtab);
	return 0;
}

int cmp_id(const void *a, const void *b) {
	ID * p1 = (ID *)a;
	ID * p2 = (ID *)b;
	return p1->id - p2->id;
}

ID * index_primaire(const Personne * p, int nb) {
	ID *idtab = (ID *)malloc(nb * sizeof(ID));
	int i = 0;
	for (i = 0; i < nb; i++) {
		idtab[i].id = p[i].id;
		idtab[i].ref = i;
	}
	qsort(idtab, nb, sizeof(ID), cmp_id);
	return idtab;
}

void afficher_index_primaire(const ID * idtab, int nb) {
	int i = 0;
	printf("----index-primaire----\n");
	for (i = 0; i < nb; i++) printf("id = %d, indice = %d\n", idtab[i].id, idtab[i].ref);
}

void recherche_par_id(const Personne * p, int nb, const ID * idtab) {
	ID * idtabP, chercheP;
	printf("----recherche_par_id----\n");
	printf("Entrer un id : "); 
	scanf("%d", &chercheP.id);
	 while (chercheP.id != 0) {
		idtabP = (ID *)bsearch(&chercheP, idtab, nb, sizeof(ID), cmp_id);
		if (idtabP == NULL)
			printf("non trouve\n");
		else
			afficherPersonne(p, idtabP->ref);
		printf("identifiant (0=fin) : "); scanf("%d", &chercheP.id);
	} 
}

void afficherPersonne(const Personne * p, int i) {
	printf("nom : %s, sexe : %c, age : %d\n", p[i].nom, p[i].sexe, p[i].age);
}
