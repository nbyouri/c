#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAR 20
#define MAX 10

void afficher_tab(char **, int);

void afficher_tab(char **tab, int nb) {
	for (int i = 0; i < nb; printf("%s\n", *(tab + i++)));
}

int main(void) {
	char **tab;
	int nb;
	int i;
	printf("Combien de chaines de car? : ");
	scanf("%d", &nb);
	if ((tab = (char **)malloc(MAX * sizeof(char **))) == NULL)
		return -1;
	for (i = 0; i < nb; i++) {
		printf("chaine nr.%d? : ", i);
		tab[i] = malloc(MAX_CAR);
		scanf("%s", tab[i]);
	}
	afficher_tab(tab, nb);
	free(tab);
	return 0;
}
