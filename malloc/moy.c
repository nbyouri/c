// moyenne.c

#include <stdio.h>
#include <stdlib.h>

float plusgrand(float *, int);
float pluspetit(float *, int);

int main(void) {
	int nb = 0;
	int i = 0;
	float *tab = {0};
	float moyenne = 0;
	printf("De combien de nombres voulez vous faire la moyenne? : ");
	scanf("%d", &nb);
	if ((tab = malloc((unsigned)nb * sizeof(float))) == NULL)
		return -1;
	for (i = 0; i < nb; i++) {
		printf("Saiser le nombre suivant: ");
		scanf("%f", &tab[i]);
		moyenne += tab[i];
	}
	printf("La moyenne est: %2.1f%%\n", ((moyenne/nb)/20) * 100);
	printf("Plus grand nombre: %2.1f\n", plusgrand(tab, nb));
	printf("Plus petit nombre: %2.1f\n", pluspetit(tab, nb));
	free(tab);
	return 0;
}

float pluspetit(float *tab, int nb) {
	int i = 0;
	int min = 0;
	for (i = 0; i < nb; i++) {
		if (tab[i] < tab[min])
			min = i;
	}
	return tab[min];
}

float plusgrand(float *tab, int nb) {
	int i = 0;
	int max = 0;
	for (i = 0; i < nb; i++) {
		if (tab[i] > tab[max])
			max = i;
	}
	return tab[max];
}
