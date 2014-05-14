#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_MARK 3
#define MAX_CHAR 20

struct student {
    int id;
    char name[MAX_CHAR];
    float marks[MAX_MARK];
    float percent;
    struct {
        int day;
        int mon;
        int yea;
    } birthdate;
};

struct indexer {
    int year;
    unsigned int nb;
    int *lst;
};

void initialize_student(struct student *, unsigned int);
struct student * addstudent(struct student *, unsigned int);
void liststudents(struct student *, unsigned int);
void sortstudents(struct student *, unsigned int);
int  sortbirthdate(const void *, const void *);
int  sortindexyear(const void *, const void *);
float calcpercent(float *);
struct indexer * index_year(struct student *, unsigned int, unsigned int *);
void printindex(struct indexer *, unsigned int);
void searchyear(struct student *,  struct indexer *, unsigned int);
void printstudent(struct student);

void initialize_student(struct student * c, unsigned int n) {
    // put random data in struct fields
    int randomnum = arc4random() % MAX_CHAR;
    char randomstr[MAX_CHAR];
    int i = 0;
    char nom[] = "peter";
    // id
    c[n].id = (int)n;
    // name
    strncpy(c[n].name, nom, sizeof(nom));
    snprintf(randomstr, sizeof(randomstr), "%02d", randomnum);
    strncat(c[n].name, randomstr, strlen(randomstr));
    // marks
    for (i = 0; i < MAX_MARK; c[n].marks[i++] = arc4random() % 100);
    // perecent
    c[n].percent = calcpercent(c[n].marks);
    // birthdate = 1980 -> 1995
    c[n].birthdate.day = arc4random() % 32;
    c[n].birthdate.mon = arc4random() % 13;
    c[n].birthdate.yea = 1980 + arc4random() % 16;
}

struct student * addstudent(struct student * c, unsigned int n) {
    // expand the array
    struct student * p;
    p = (struct student *)realloc(c, (n+1) * sizeof(struct student));
    if (p == NULL) {
        if (c != NULL)
            free(c);
        c = NULL;
        return NULL;
    }
    return p;
}

void liststudents(struct student * c, unsigned int nbs) {
    unsigned int i = 0;
    for (i = 0; i < nbs; i++)
        printf("id : %02d :: name : %s \n"
                "\t-> percent : %02.1f%% :: birthdate = %02d/%02d/%04d\n",
                c[i].id, c[i].name, c[i].percent, c[i].birthdate.day, 
                c[i].birthdate.mon, c[i].birthdate.yea);
}

void sortstudents(struct student * c, unsigned int nb) {
    qsort(c, nb, sizeof(c[0]), sortbirthdate);
}

int sortbirthdate(const void * a, const void * b) {
    struct student * p1 = (struct student *)a;
    struct student * p2 = (struct student *)b;
    char s1[MAX_CHAR];
    char s2[MAX_CHAR];
    int birthdate1 = (p1->birthdate.yea * 10000) 
        + (p1->birthdate.mon * 100) 
        + p1->birthdate.day;
    int birthdate2 = (p2->birthdate.yea * 10000) 
        + (p2->birthdate.mon * 100) 
        + p2->birthdate.day;
    snprintf(s1, sizeof(s1), "%d", birthdate1);
    snprintf(s2, sizeof(s2), "%d", birthdate2);
    return strncmp(s2, s1, MAX_CHAR);
}

int sortindexyear(const void * a, const void * b) {
    return ((struct indexer *)a)->year - ((struct indexer *)b)->year;
}

float calcpercent(float * marks) {
    int i = 0;
    float result = 0;
    for (i = 0; i < MAX_MARK; i++)
        result += marks[i];
    return result/MAX_MARK;
}

struct indexer * index_year(struct student * c, unsigned int nbs, unsigned int * nbkey) {
    struct indexer * id = (struct indexer *)malloc(nbs * sizeof(struct indexer));
    *nbkey = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    int found = 0;
    for (i = 0; i < nbs; i++) {
        found = -1;
        for (j = 0; j < *nbkey; j++) {
            if (c[i].birthdate.yea == id[j].year) {
                found = (int)j;
                break;
            }
        }
        if (found == -1) {
            id = (struct indexer *)realloc(id, ((*nbkey) + 1) * sizeof(struct indexer));
            id[*nbkey].nb = 1;
            id[*nbkey].lst = (int *)malloc(sizeof(int));
            id[*nbkey].year = c[i].birthdate.yea;
            id[*nbkey].lst[0] = (int)i;
            (*nbkey)++;
        } else {
            id[found].lst = (int *)realloc(id[found].lst, (unsigned)(id[found].nb + 1) * sizeof(int));
            id[found].lst[id[found].nb] = (int)i;
            id[found].nb++;
        }
    }
    qsort(id, (*nbkey), sizeof(id[0]), sortindexyear);
    return id;
}

void printindex(struct indexer * id, unsigned int nbkey) {
    unsigned int i = 0;
    unsigned int j = 0;
    for (i = 0; i < nbkey; i++) {
        printf("year : %d\n", id[i].year);
        for (j = 0; j < id[i].nb; j++)
            printf("student array index: %d\n", id[i].lst[j]);
        puts("\n");
    }
}

void searchyear(struct student * c,  struct indexer * id, unsigned int nbkey) {
    struct indexer * temp, key;
    unsigned int i = 0;
    char input[MAX_CHAR];
    printf("Search by year (0=end): ");
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &key.year) != 1)
        printf("wrong choice\n");
    while (key.year != 0) {
        temp = (struct indexer *)bsearch(&key, id, nbkey, sizeof(temp[0]), sortindexyear);
        if (temp == NULL)
            printf("not found\n");
        else
            for (i = 0; i < temp->nb; i++)
                printstudent(c[temp->lst[i]]);
        printf("year (0=end) : ");
        scanf("%d", &key.year);
    }
}

void printstudent(struct student c) {
    printf("id : %02d :: name : %s \n"
                "\t-> percent : %02.1f%% :: birthdate = %02d/%02d/%04d\n",
                c.id, c.name, c.percent, c.birthdate.day, 
                c.birthdate.mon, c.birthdate.yea);
}

int main(void) {
    struct student * compsci = NULL;
    struct indexer * indextab = NULL;
    unsigned int nbs = 0;
    unsigned int nbi = 0;
    unsigned int cho = 0;
    unsigned int i = 0;
    bool stay = true;
    char input[MAX_CHAR];
    srandom((unsigned)time(NULL));
    while (stay) {
        printf("1. Add a student\n"
                "2. Sort students\n"
                "3. Print the student\n"
                "4. Search a student\n"
                "5. Add 20 students at once\n"
                "0. Exit\n");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%1d", &cho) != 1)
            printf("wrong choice\n");
        switch (cho) {
            case 1 :
                if ((compsci = addstudent(compsci, nbs)) == NULL) {
                    nbs = 0;
                    printf("failed to add a student");
                    break;
                }
                initialize_student(compsci, nbs);
                nbs++;
                break;
            case 2 : 
                sortstudents(compsci, nbs);
                break;
            case 3 : 
                liststudents(compsci, nbs);
                break;
            case 4 : 
                if ((indextab = index_year(compsci, nbs, &nbi)) == NULL) {
                    nbi = 0;
                    printf("failed to create index");
                    break;
                }
                printindex(indextab, nbi);
                searchyear(compsci, indextab, nbi);
                break;
            case 5 :
                for (i = 0; i < 20; i++) { 
                    if ((compsci = addstudent(compsci, nbs)) == NULL) {
                        nbs = 0;
                        printf("failed to add a student");
                        break;
                    }
                    initialize_student(compsci, nbs);
                    nbs++;
                }
                break;
            case 0 : stay = false; break;
            default  : printf("Wrong choice\n");
        }
    }
    // free the allocated pointers
    free(compsci);
    compsci = NULL;
    for (i = 0; i < nbi; i++) {
        free(indextab[i].lst);
        indextab[i].lst = NULL;
    }
    free(indextab);
    indextab = NULL;
    return 0;
}
