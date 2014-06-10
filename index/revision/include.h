// include.h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_CHAR 20
#define MAX_CHAR_BIG 40
#define DATA_DIR "data/"

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

static struct stat st;

// function prototypes

void error(const char *) __attribute__ ((noreturn));
void * grow(student *, unsigned int);
void initialize(student *, unsigned int);
void print_students(FILE *, student *, unsigned int, bool);
void * index_num(student *, unsigned int, unsigned int *);
int sort_index_num(const void *, const void *);
int sort_num(const void *, const void *);
void search_num(student *, id_num *, unsigned int);
void write_file(const char *, const char *, student *, unsigned int);
void * read_file(const char *, const char *, student *, unsigned int *);
