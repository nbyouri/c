#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HEX "hex : 0x%x\n"
#define OCT "oct : %o\n"

int main(void) {
    int  num = 0;
    char choice;
    char line[BUFSIZ];
    bool hex = true;

    do {
        printf("enter number to convert (0) to quit: ");
        fgets(line, sizeof(line), stdin);

        if (sscanf(line, "%d", &num) != 1)
            printf("wrong choice!\n");

        else if (num != 0) {
            printf("hex or octal ? (h/o): ");
            fgets(line, sizeof(line), stdin);

            if (sscanf(line, "%c", &choice) != 1) 
                printf("wrong choice\n");
            else {
                if (choice == 'h')
                    hex = true;
                else if (choice == 'o') 
                    hex = false;
                else {
                    printf("wrong choice!\n");
                    break;
                }

                printf(hex ? HEX : OCT, num);
            }
        }
    } while (num != 0);

    return 0;
}
