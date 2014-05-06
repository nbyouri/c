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

void initialiser(char **tab, int nb, int nb2) {
	int i = 0;
	for (i = nb; i < nb + nb2; i++) {
		printf("chaine nr.%d? : ", i);
		tab[i] = malloc(MAX_CAR);
		scanf("%s", tab[i]);
	}
}

int main(void) {
	char **tab;
	char **retab;
	int nb = 0;
	int nb2 = 0;
	int i = 0;

	// allocation initiale
	printf("Combien de chaines de car? : ");
	scanf("%d", &nb);
	if ((tab = malloc(MAX * sizeof(char **))) == NULL)
		return -1;
	initialiser(tab, 0, nb);
	afficher_tab(tab, nb);

	// reallocation; on rajoute des elements
	printf("Combien de chaines voulez vous en plus? : ");
	scanf("%d", &nb2);
	if ((retab = realloc(tab, (unsigned long)(nb + nb2) * sizeof(char **))) == NULL)
		return -1;
	tab = retab;
	initialiser(tab, nb, nb2);
	afficher_tab(tab, nb + nb2);

	// liberation des elements en memoire
	for (i = 0; i < (nb + nb2); free(tab[i++]));
	free(tab);
	tab = NULL;

	return 0;
}
