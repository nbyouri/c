#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int                 i;
    struct stat         info;

    if (argc >= 2) {
        for (i = 1; i < argc; i++) {
            if (stat(argv[i], &info) == -1) {
                printf("Failed to stat %s\n", argv[i]);
                return -1;
            } else {
                struct passwd *pw = getpwuid(info.st_uid);
                struct group  *gr = getgrgid(info.st_gid);
                printf("%s:\nOwner: %s\nGroup: %s\nSize: %llu bytes\nInode: %llu\n\n", 
                        argv[i], pw->pw_name, gr->gr_name, info.st_size, info.st_ino);
            }
        }
    } else {
        printf("utilisation: ls <fichiers> ..\n");
    }
    return EXIT_SUCCESS;
}
