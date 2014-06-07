#include "include.h"

void write_file(const char * filename, const char * mode, student * class, unsigned int nb) {
    FILE *f;

    // text file
    if (!strncmp(mode, "wt", MAX_CHAR)) {
        // quit if it fails to open
        if ((f = fopen(filename, mode)) == NULL) {
            error("Failed to open file");
            // otherwise, write data to it
        } else {
            print_students(f, class, nb);
            // close the file
            fclose(f);
        }


    // binary file
    } else if (!strncmp(mode, "wb", MAX_CHAR)) {
        if ((f = fopen(filename, mode)) == NULL) {
           error("Failed to open file\n");
        } else {
            fwrite(class, nb, sizeof(student), f);
            fclose(f);
        }
    } else {
        printf("invalid file write mode\n");
    }
}
