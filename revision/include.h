// include.h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHAR 20

// structures

typedef struct {
    unsigned int num;
    struct {
        unsigned int day;
        unsigned int mon;
        unsigned int yea;
    } bd;
    char name[MAX_CHAR];
} student;

typedef struct {
    unsigned int num;
    unsigned int nb;
    unsigned int *lst;
} id_num;

// function prototypes

student * grow(student *, unsigned int);
void initialize(student *, unsigned int);
void print_students(student *, unsigned int);
id_num * index_num(student *, unsigned int, unsigned int *);
int sort_index_num(const void *, const void *);
void search_num(student *, id_num *, unsigned int);
