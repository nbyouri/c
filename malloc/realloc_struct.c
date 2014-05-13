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

// struct index {
//     int year;
//     int nb;
//     int *lst;
// };

void initialize_student(struct student *, unsigned int);
struct student * addstudent(struct student *, unsigned int);
void liststudents(struct student *, unsigned int);
void sortstudents(struct student *, unsigned int);
int  sortid(const void *, const void *);
int  sortbirthdate(const void *, const void *);
float calcpercent(float *);

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
    c[n].birthdate.day = arc4random() % 31;
    c[n].birthdate.mon = arc4random() % 12;
    c[n].birthdate.yea = 1980 + arc4random() % 16;
}

struct student * addstudent(struct student * c, unsigned int n) {
    // expand the array
    struct student * p;
    p = realloc(c, (n+1) * sizeof(struct student));
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
    // by id
    // qsort(c, nb, sizeof(c[0]), sortid);
    // by birthdate
    qsort(c, nb, sizeof(c[0]), sortbirthdate);
}

int sortid(const void * a, const void * b) {
    struct student * p1 = (struct student *)a;
    struct student * p2 = (struct student *)b;
    return p2->id - p1->id;
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
    printf("%d, %d\n", birthdate2, birthdate1);
    return strncmp(s2, s1, MAX_CHAR);
}

float calcpercent(float * marks) {
    int i = 0;
    float result = 0;
    for (i = 0; i < MAX_MARK; i++)
        result += marks[i];
    return result/MAX_MARK;
}

int main(void) {
    struct student * compsci = NULL;
    unsigned int nbs = 0;
    int ch = 0;
    int i = 0;
    bool stay = true;
    srandom((unsigned)time(NULL));
    while (stay) {
        printf("1. Add a student\n"
                "2. Sort students\n"
                "3. Print the student\n"
                "4. Search a student\n"
                "5. Add 20 students at once\n"
                "0. Exit\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1 :
                if ((compsci = addstudent(compsci, nbs)) == NULL) {
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
            case 4 : break;
            case 5 :
                for (i = 0; i < 20; i++) { 
                    if ((compsci = addstudent(compsci, nbs)) == NULL) {
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
    free(compsci);
    compsci = NULL;
    // free(indexer);
    // indexer = NULL;
    return 0;
}
