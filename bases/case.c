#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct {
    char boisson[10];
    int nombre;
} commande[] = {
    { "soda", 0 },
    { "cafe", 0 },
    { "eau", 0 },
    { "biere", 0 },
};

int main(void) {
    char choix;
    bool rester = true;

    while (rester) {
        system("clear");
        printf("a) soda\n"
                "b) cafe\n"
                "c) eau\n"
                "d) biere\n"
                "e) quitter\n");
        scanf("%c", &choix);
        switch (choix) {
            case 'a' : commande[0].nombre++; break;
            case 'b' : commande[1].nombre++; break;
            case 'c' : commande[2].nombre++; break;
            case 'd' : commande[3].nombre++; break;
            case 'e' : rester = false; 
            default : printf("Mauvais choix!\n"); break;
        }
    }
    printf("Commande:\n");
    for (int i = 0; i<4; i++) {
        printf("%s : %d\n", commande[i].boisson, commande[i].nombre);
    }
    return EXIT_SUCCESS;
}
