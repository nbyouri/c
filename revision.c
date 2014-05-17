// revision.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

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
student * addstudent(student *, unsigned int);
indexer * index_year(student *, unsigned int, unsigned int *);
void initialize_student(student *, unsigned int);
void printindex(indexer *, unsigned int);
void search_year(student *, indexer *, unsigned int);
void printstudent(student);

int sort_index(const void * a, const void * b) {
    return (int)(((indexer *)a)->year - ((indexer *)b)->year);
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
    char name[] = "peter";
    char randomstr[MAX];
    stud[nb].num = nb;
    snprintf(randomstr, sizeof(randomstr), 
            "%s%02d", name, arc4random() % 100);
    strlcpy(stud[nb].name, randomstr, sizeof(stud[nb].name));
    stud[nb].bd.day = arc4random() % 32;
    stud[nb].bd.mon = arc4random() % 13;
    stud[nb].bd.yea = 1980 + arc4random() % 16;
}

void printstudent(student c) {
    printf("id : %02d :: name : %s :: birthdate = %02d/%02d/%04d\n",
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
                break;
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
    printf("search by year (0=end) : ");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &key.year);
    if (key.year != 0) {
        temp = (indexer *)bsearch(&key, idtab, 
                nbi, sizeof(indexer), sort_index);
        if (temp == NULL)
            printf("not found\n");
        else
            for (i = 0; i < temp->nb; i++)
                printstudent(stud[temp->lst[i]]);
    }
}

int main(void) {
	// variables
    student * compsci = NULL;
    indexer * indxtab = NULL;
    unsigned int i = 0;
    unsigned int nbs = 0;
    unsigned int nbi = 0;

    // random seed
    srandom((unsigned)time(NULL));

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

