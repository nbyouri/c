#include <stdio.h>
#include <stdlib.h>

void initialiser_tab(int *, int, int);
void afficher_tab(int *, int);

void afficher_tab(int *tab, int nb) {
	int *p;
	for (p = tab; p < tab + nb; p++) printf("tab[%ld] = %d\n", p - tab, *p);
}

void initialiser_tab(int *tab, int nb, int n) {
	int i;
	for (i = nb; i < nb + n; i++) tab[i] = i+3;
}

int main(void) {
	int nb = 0;	// nombre d'elements
	int n = 0;  // nombre d'el en +
	int *tab;	// tableau d'entiers
	int *retab; // pointeur pour reallocation
	printf("Combien d'elements voulez vous dans votre tableau?: ");
	scanf("%d", &nb);
	if ((tab = malloc(nb)) == NULL)
		return -1;
	initialiser_tab(tab, 0, nb);
	afficher_tab(tab, nb);
	printf("Combien d'elements en plus voulez vous?: ");
	scanf("%d", &n);
	if ((retab = realloc(tab, n)) == NULL)
		return -1;
	tab = retab;
	initialiser_tab(tab, nb, n);
	afficher_tab(tab, nb + n);
	free(tab);
	return 0;
}