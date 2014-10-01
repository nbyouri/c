#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    DIR                 *dp;
    struct dirent       *ep;
    char                files[BUFSIZ];

    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            if ((dp = opendir(argv[i])) == NULL) {
                printf("impossible d'ouvrir %s\n", argv[i]);
                exit(EXIT_FAILURE);
            } else {
                printf("%s:\n", argv[i]);
                while ((ep = readdir(dp)) != NULL) {
                    if (ep->d_name[0] != '.') {
                        printf("%lu %s\n", ep->d_ino, ep->d_name);
                    }
                }
                puts("");
            }
        }
        closedir(dp);
    } else {
        printf("utilisation: ls <dossier> ..\n");
    }
    return EXIT_SUCCESS;
}
