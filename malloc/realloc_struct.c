#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_MARK 3
#define MAX_CHAR 20

static struct class {
    int nbs;
    struct student {
        int id;
        char name[MAX_CHAR];
        int marks[MAX_MARK];
        struct {
            int day;
            int mon;
            int yea;
        } birthdate;
    } * students;
} compsci;

struct index {
    int year;
    int nb;
    int *lst;
};

static struct index * indexer = NULL;
static int counter = 0; 

struct student initializestudent(void);
void addstudent(struct class *, int *);
void liststudents(struct class *);

struct student initializestudent(void) {
    struct student c;
    int randomnum = arc4random() % MAX_CHAR;
    char *randomstr;
    c.id = ++counter;
    randomstr = malloc(2);
    char nom[] = "peter";
    strncpy(c.name, nom, sizeof(nom));
    sprintf(randomstr, "%d", randomnum);
    strncat(c.name, randomstr, strlen(randomstr));
    randomnum = arc4random() % MAX_CHAR;
    return c;
}

void addstudent(struct class * c, int * nb) {
    c->students = (struct student *)realloc(c->students, (unsigned)(*nb + 3) * sizeof(struct class));
    if (c == NULL) {
        printf("Failed to allocate enough memory.\n");
        exit(EXIT_FAILURE);
    }
}

void liststudents(struct class * c) {
    int i = 0;
    for (i = 0; i < c->nbs; i++) {
        printf("Student nr.%d\n"
            "Name : %s\n", i, c->students[i].name);
    }
}

int main(void) {
    compsci.nbs = 0;
    int nb = 0;
    int ch = 0;
    bool stay = true;
    srandom((unsigned)time(NULL));
    while (stay) {
        printf("1. Add a student\n"
            "2. Sort students\n"
            "3. Print the student\n"
            "4. Search a student\n"
            "0. Exit\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1 :
                if (compsci.nbs == nb)
                    addstudent(&compsci, &nb);
                compsci.students[compsci.nbs] = initializestudent();
                compsci.nbs++;
                break;
            case 2 : break;
            case 3 : 
                liststudents(&compsci);
                break;
            case 4 : break;
            case 0 : stay = false; break;
            default  : printf("Wrong choice\n");
        }
    }
    //free(compsci);
    free(indexer);
    return 0;
}
