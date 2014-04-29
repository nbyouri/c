#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define taille(X) sizeof(X)/sizeof(X[0])
#define MAX 20

void read_file(const char *);
void create_file(const char *);
void addtofile(const char *, const char *);

void read_file(const char *filename) {
	FILE *file;
	char s[MAX];
	if ((file = fopen(filename, "rt")) == NULL)
		exit(EXIT_FAILURE);
	while (fgets(s, sizeof(s), file)) {
		printf("%s", s);
	}
}

void create_file(const char *filename) {
	FILE *file;
	if ((file = fopen(filename, "wt")) == NULL)
		exit(EXIT_FAILURE);
	fclose(file);
}

void addtofile(const char *filename, const char *line) {
	FILE *file;
	if ((file = fopen(filename, "at")) == NULL)
		exit(EXIT_FAILURE);
	fprintf(file, "%s\n", line);
	fclose(file);
}

int main(void) {
	char filename[] = "lel.txt";
	char line[MAX] = "youri";
	char adjectif[4][MAX] = { "cool", "keks", "sexy", "ok" };
	create_file(filename);
	for (int i = 0; i < taille(adjectif); i++) {
		strcat(line, adjectif[i]);
		addtofile(filename, line);
	}
	read_file(filename);
	return 0;
}
