// revision.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20
#define MAX_SHORT 10
#define MAX_BIG 100

// data structures

typedef struct {
    unsigned int num;
    char name[MAX];
    struct {
        unsigned int day;
        unsigned int mon;
        unsigned int yea;
    } bd;
} student;

typedef struct {
    unsigned int year;
    unsigned int nb;
    unsigned int * lst;
} indexer;

// function declarations

int sort_index(const void *, const void *);
int sort_years(const void *, const void *);
student * addstudent(student *, unsigned int);
indexer * index_year(student *, unsigned int, unsigned int *);
void initialize_student(student *, unsigned int);
void printindex(indexer *, unsigned int);
void search_year(student *, indexer *, unsigned int);
void printstudent(FILE *, student);
void write_text_file(student *, unsigned int, const char *);
void read_text_file(const char *);

int sort_index(const void * a, const void * b) {
    return (int)(((indexer *)a)->year - ((indexer *)b)->year);
}

int sort_years(const void * a, const void * b) {
    student * p1 = (student *)a;
    student * p2 = (student *)b;
    char s1[MAX_SHORT];
    char s2[MAX_SHORT];
    snprintf(s1, sizeof(s1), "%d", p1->bd.yea * 10000 + p1->bd.mon * 100 + p1->bd.day);
    snprintf(s2, sizeof(s2), "%d", p2->bd.yea * 10000 + p2->bd.mon * 100 + p2->bd.day);
    return strncmp(s1, s2, sizeof(s1));
}

student * addstudent(student * c, unsigned int n) {
    // expand the array
    student * p;
    p = (student *)realloc(c, (n+1) * sizeof(student));
    if (p == NULL) {
        if (c != NULL)
            free(c);
        c = NULL;
        return NULL;
    }
    return p;
}

void initialize_student(student * stud, unsigned int nb) {
    char lettres[] = "abcdefghijklmnopqrstuvwxyz";
    char randomstr[MAX];
    stud[nb].num = nb;
    char name[MAX_SHORT];
    unsigned int i = 0;
    for (i = 0; i < sizeof(name); i++) 
        name[i] = lettres[arc4random() % strlen(lettres)];
    name[strlen(name)] = '\0';
    snprintf(randomstr, sizeof(randomstr), 
            "%s%02d", name, arc4random() % 100);
    strlcpy(stud[nb].name, randomstr, sizeof(stud[nb].name));
    stud[nb].bd.day = 1 + arc4random() % 31;
    stud[nb].bd.mon = 1 + arc4random() % 12;
    stud[nb].bd.yea = 1990 + arc4random() % 6;
}

void printstudent(FILE * fname, student c) {
    fprintf(fname, "id : %02d :: name : %s :: birthdate = %02d/%02d/%04d\n",
            c.num, c.name, c.bd.day, 
            c.bd.mon, c.bd.yea);
}

indexer * index_year(student * st, unsigned int nb, unsigned int * nbkey) {
    indexer * idtab = (indexer *)malloc((nb + 1) * sizeof(indexer));
    unsigned int i = 0;
    unsigned int j = 0;
    int found = 0;
    *nbkey = 0;
    for (i = 0; i < nb; i++) {
        found = -1;
        for (j = 0; j < *nbkey; j++) {	
            if (st[i].bd.yea == idtab[j].year) {
                found = (int)j;
                break;  // we stop looping 
            }
        }
        if (found == -1) { // if not found
            idtab = (indexer *)realloc(idtab, (*nbkey + 1) * sizeof(indexer));
            idtab[*nbkey].nb = 1;
            idtab[*nbkey].year = st[i].bd.yea;
            idtab[*nbkey].lst = (unsigned int *)malloc(sizeof(int));
            idtab[*nbkey].lst[0] = i;
            (*nbkey)++;
        } else {
            idtab[found].lst = (unsigned int *)realloc(idtab[found].lst, 
                    (idtab[found].nb + 1) * sizeof(int));
            idtab[found].lst[idtab[found].nb] = i;
            idtab[found].nb++;
        }
    }
    qsort(idtab, *nbkey, sizeof(indexer), sort_index);
    return idtab;
}

void printindex(indexer * id, unsigned int nbkey) {
    unsigned int i = 0;
    unsigned int j = 0;
    for (i = 0; i < nbkey; i++) {
        printf("year : %d\n", id[i].year);
        for (j = 0; j < id[i].nb; j++)
            printf("student array index: %d\n", id[i].lst[j]);
        puts("\n");
    }
}

void search_year(student * stud, indexer * idtab, unsigned int nbi) {
    indexer * temp, key;
    unsigned int i = 0;
    char line[MAX];
    do {
        printf("search by year (0=end) : ");
        fgets(line, sizeof(line), stdin);
        if (sscanf(line, "%d", &key.year) != 1)
            printf("wrong choice!\n");
        else
            if (key.year != 0) {
                temp = (indexer *)bsearch(&key, idtab, 
                        nbi, sizeof(indexer), sort_index);
                if (temp == NULL)
                    printf("not found\n");
                else
                    for (i = 0; i < temp->nb; i++)
                        printstudent(stdout, stud[temp->lst[i]]);
            }
    } while (key.year != 0);
}

void write_text_file(student * stud, unsigned int nb, const char * fname) {
    FILE *f;
    unsigned int i = 0;
    if ((f = fopen(fname, "wt")) == NULL)
        printf("failed to write to text file: %s\n", fname);
    else
        for (i = 0; i < nb; i++) 
            printstudent(f, stud[i]);
    fclose(f);
}

void read_text_file(const char * fname) {
    FILE *f;
    char s[MAX_BIG];
    if ((f = fopen(fname, "rt")) == NULL)
        printf("failed to open file");
    else
        while (fgets(s, sizeof(s), f))
            printf("%s", s);
    fclose(f);
}

int main(void) {
    // variables
    student * compsci = NULL;
    indexer * indxtab = NULL;
    unsigned int i = 0;
    unsigned int nbs = 0;
    unsigned int nbi = 0;

    // terrible random seed
    //srandom((unsigned)time(NULL));

    // initialize 100 students
    for (i = 0; i < 100; i++) {
        if ((compsci = addstudent(compsci, nbs)) == NULL) {
            printf("failed to allocate enough memory for a new student\n");
            nbs = 0;
            return -1;
        } else {
            initialize_student(compsci, nbs);
            nbs++;
        }
    }

    // print initialized students
    for (i = 0; i < nbs; i++) {
        printf("%02d) %s :: %02d/%02d/%04d\n", 
                compsci[i].num, compsci[i].name, compsci[i].bd.day, 
                compsci[i].bd.mon, compsci[i].bd.yea);
    }

    // create index by year
    if ((indxtab = index_year(compsci, nbs, &nbi)) == NULL) {
        nbi = 0;
        printf("failed to index\n");
        return -1;
    } else {
        // if the index was properly created, search
        printindex(indxtab, nbi);
        search_year(compsci, indxtab, nbi);
    }

    // write and read the sorted student array to a text file
    qsort(compsci, nbs, sizeof(compsci[0]), sort_years);
    write_text_file(compsci, nbs, "compsci.txt");
    read_text_file("compsci.txt");

    // free allocated memory
    free(compsci);
    compsci = NULL;
    for (i = 0; i < nbi; i++) {
        free(indxtab[i].lst);
        indxtab[i].lst = NULL;
    }
    free(indxtab);
    indxtab = NULL;
    return 0;
}

