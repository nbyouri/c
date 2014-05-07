#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 25
#define MAX_CAR 20

typedef struct {
	int id;
	char name[MAX_CAR];
	char sex;
	int age;
} student;

typedef struct {
	int id;
	int ref;
} index_tab;

typedef struct {
	char name[MAX_CAR];
	char sex;
	int  nb;
	int  *lst;
} index_keys;

typedef struct {
	int nbKeys;
	index_keys *keys;
} index_sex_names;

static student class[MAX] = {
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
    {21,  "nicole",  'f', 33},
};

int initialize_class(int);
index_tab * primary_index_tab(const student *, int);
int cmp_id(const void *, const void *);
int comp_sexe_nom(const void *, const void *);
void print_index_tab(const index_tab *, int);
void print_index_tab_secondary(const index_sex_names *);
void search(const student *, int, const index_tab *);
void search_sex_name(const student *, const index_sex_names *);
void printf_student(const student *, int);
index_sex_names * secondary_index(const student *, int);

int main(void) {
	// int size = initialize_class(0);
	// index_tab * idtab = primary_index_tab(class, size);
	// print_index_tab(idtab, size);
	// search(class, size, idtab);

	// int size_two = initialize_class(size);
	// printf("%d\n", size_two);
	// idtab = primary_index_tab(class, size_two);
	// print_index_tab(idtab, size_two);
	// search(class, size_two, idtab);

	//int size = initialize_class(0);
	int size = 13;
	index_sex_names * idtab = secondary_index(class, size);
	print_index_tab_secondary(idtab);
	search_sex_name(class, idtab);
	free(idtab);
	printf("%lu\n", sizeof(student));
	return 0;
}

// int initialize_class(int nb) {
// 	int stay = 1;
// 	char name[MAX_CAR];
// 	printf("enter 0 as id to leave\n");
// 	while (stay) {
// 		if (nb == MAX) printf("class is full");
// 		else {
// 			printf("ID? : "); 
// 			scanf("%d", &class[nb].id);
// 			if (class[nb].id == 0) stay = 0;
// 			else {
// 				printf("Name? : ");
// 				scanf("%s", name);
// 				strcpy(class[nb].name, name);
// 				printf("Age? : ");
// 				scanf("%d", &class[nb].age);
// 				printf("Sex? : ");
// 				scanf("%s", &class[nb].sex);
// 				nb++;
// 			}
// 		}
// 	}
// 	return nb;
// }

int cmp_id(const void *a, const void *b) {
	return ((index_tab *)a)->id - ((index_tab *)b)->id;
}

int comp_sexe_nom(const void *a, const void *b) {
	index_keys * p1 = (index_keys *)a;
	index_keys * p2 = (index_keys *)b;
	if (p1->sex == p2->sex)
		return strcmp(p1->name, p2->name);
	else
		return p1->sex - p2->sex;
}

index_tab * primary_index_tab(const student * s, int nb) {
	index_tab * idtab = malloc((unsigned)nb * sizeof(index_tab));
	int i = 0;
	for (i = 0; i < nb; i++) {
		idtab[i].id = s[i].id;
		idtab[i].ref = i;
	}
	qsort(idtab, (unsigned)nb, sizeof(index_tab), cmp_id);
	return idtab;
}

index_sex_names * secondary_index(const student * s, int nb) {
	index_sex_names * idtab = malloc((unsigned)nb * sizeof(index_sex_names));
	idtab->nbKeys = 0;
	idtab->keys = NULL;
	int i, j, found;
	for (i = 0; i < nb; i++) {
		found = -1;
		for (j = 0; j < idtab->nbKeys; j++) {
			if ((s[i].sex == idtab->keys[j].sex) && strcmp(s[i].name, idtab->keys[j].name) == 0) {
				found = j;
				break;
			}
		}
		if (found == -1) {
			idtab->keys = realloc(idtab->keys, (unsigned)(idtab->nbKeys + 1) * sizeof(index_keys));
			idtab->keys[idtab->nbKeys].nb = 1;
			idtab->keys[idtab->nbKeys].lst = malloc(sizeof(int));
			idtab->keys[idtab->nbKeys].sex = s[i].sex;
			strcpy(idtab->keys[idtab->nbKeys].name, s[i].name);
			idtab->keys[idtab->nbKeys].lst[0] = i;
			idtab->nbKeys++;
		} else {
			idtab->keys[found].lst = realloc(idtab->keys[found].lst, (unsigned)(idtab->keys[found].nb + 1) * sizeof(int));
			idtab->keys[found].lst[idtab->keys[found].nb] = i;
			idtab->keys[found].nb++;
		}
	}
	qsort(idtab->keys, (unsigned)idtab->nbKeys, sizeof(index_keys), comp_sexe_nom);
	return idtab;
}

void print_index_tab(const index_tab * idtab, int nb) {
	int i = 0;
	for (i = 0; i < nb; i++) printf("id = %d, indice = %d\n", idtab[i].id, idtab[i].ref);
}

void print_index_tab_secondary(const index_sex_names * idtab) {
	int i,j = 0;
	for (i = 0; i < idtab->nbKeys; i++) { 
		printf("sex : %c, name : %s\n", idtab->keys[i].sex, idtab->keys[i].name);
		for (j = 0; j < idtab->keys[i].nb; j++)
			printf("indice : %d\n", idtab->keys[i].lst[j]);
	}
	puts("\n");
}

void search(const student * s, int nb, const index_tab * idtab) {
	index_tab * tempindex_tab, searchkey;
	printf("search by id : ");
	scanf("%d", &searchkey.id);
	while (searchkey.id != 0) {
		tempindex_tab = (index_tab *)bsearch(&searchkey, idtab, (unsigned)nb, sizeof(index_tab), cmp_id);
		if (tempindex_tab == NULL)
			printf("id not found\n");
		else 
			printf_student(s, tempindex_tab->ref);
		printf("id (0=end) : "); 
		scanf("%d", &searchkey.id);
	}
}

void search_sex_name(const student * s, const index_sex_names * idtab) {
	index_keys * tempindex_tab, searchkey;
	int i = 0;
	printf("search by sex and name : ");
	scanf("%s", &searchkey.sex);
	while (searchkey.sex != '*') {
		printf("nom : ");
		scanf("%s", searchkey.name);
		tempindex_tab = (index_keys *)bsearch(&searchkey, idtab->keys, (unsigned)idtab->nbKeys, sizeof(index_keys), comp_sexe_nom);
		if (tempindex_tab == NULL) printf("not found\n");
		else
			for (i = 0; i < tempindex_tab->nb; i++)
				printf_student(s, tempindex_tab->lst[i]);
		printf("sex ? : (* = end) : "); 
		scanf("%s", &searchkey.sex);
	}
}

void printf_student(const student * s, int i) {
	printf("%s, age = %d\n", s[i].name, s[i].age);
}
