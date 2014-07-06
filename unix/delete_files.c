#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

#define DIRE "dir"

int main(void) {
    DIR                 *dp;
    struct dirent       *ep;
    char                files[BUFSIZ];

    if ((dp = opendir(DIRE)) == NULL) {
        printf("couldn't open dir\n");
        exit(EXIT_FAILURE);
    } else {
        while((ep = readdir(dp)) != NULL) {
            if (ep->d_name[0] != '.') {
                snprintf(files, BUFSIZ, "%s/%s", DIRE, ep->d_name);
                if (unlink(files) < 0) {
                    printf("couldn't delete %s\n", ep->d_name);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    closedir(dp);
    return 0;
}
