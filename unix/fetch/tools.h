#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xmalloc.h>
#include <fetch.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <progressmeter.h>

typedef struct Dlfile {
    char *buf;
    size_t size;
} Dlfile;

int quit(const char *);
void help(void) __attribute__((noreturn));
void output_file(const char *, const char *);
Dlfile * download(const char *);