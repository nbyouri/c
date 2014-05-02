#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAR 20
#define MAX 10

void afficher_tab(char **, int);
void initialiser(char **, int, int);

void afficher_tab(char **tab, int nb) {
	for (int i = 0; i < nb; printf("%s\n", *(tab + i++)));
}

void initialiser(char **tab, int nb, int n) {
	int i = 0;
	for (i = nb; i < nb + n; i++) {
		printf("chaine nr.%d? : ", i);
		tab[i] = malloc(MAX_CAR);
		scanf("%s", tab[i]);
	}
}

int main(void) {
	char **tab;
	char **retab;
	int nb;
	int n;

	// allocation initiale
	printf("Combien de chaines de car? : ");
	scanf("%d", &nb);
	if ((tab = malloc(MAX * sizeof(char **))) == NULL)
		return -1;
	initialiser(tab, 0, nb);
	afficher_tab(tab, nb);

	// reallocation; on rajoute des elements
	printf("Combien de chaines voulez vous en plus? : ");
	scanf("%d", &n);
	if ((retab = realloc(tab, (unsigned int)n)) == NULL)
		return -1;
	tab = retab;
	initialiser(tab, nb, n);
	afficher_tab(tab, n+nb);
	free(tab);
	return 0;
}
