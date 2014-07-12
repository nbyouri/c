#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <math.h>

#define PRINT_(type)  PRINT_##type
#define PRINT_int     "%d"
#define PRINT_double  "%f"
#define PRINT_char    "%c"
#define PRINT(type, expr) printf(#expr " = " PRINT_(type) "\n", expr)

void multiplications(int *, int, ...);

void multiplications(int *res, int nb, ...) {
	int i;
	*res = 1;
	va_list ap;
	va_start(ap, nb);
	for (i = 0; i < nb; i++)
		*res *= va_arg(ap, int);
	va_end(ap);
}

int main(void) {
	// random
	// srand(time(NULL));
	// printf("%d\n", (rand() % 100));
	srandom(time(NULL));
	printf("%d\n", (arc4random() % 100));


	// safe string input
	char chaine[6];
	printf ("Tapez 5 caractères : ");
	scanf ("%5s", chaine);
	scanf ("%*[^\n]");
	getchar ();
	printf("%s\n", chaine);

	// variable arg functions
	int res;
	multiplications(&res, 2, 3, 2);
	printf("%d\n", res);

	// macros
	PRINT(double, 4.0 * atan(1.0));
	return 0;
}