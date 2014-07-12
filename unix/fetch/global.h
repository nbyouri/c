#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xmalloc.h>
#include <fetch.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <progressmeter.h>
#include <sys/stat.h>
#include <errno.h>

// Rename libxmalloc's fatal to quit
#define quit    fatal
#define help    quit("./fetch -s <url> -o <output file name>\n")

// Structure for files
typedef struct Dlfile {
    char *buf;
    size_t size;
} Dlfile;

void output_file(const char *, const char *);
Dlfile * download(const char *);
void check_file(const char *);
