#include <stdio.h>
#include <stdlib.h>

#define P_EAU 1
#define P_FAN 1.2
#define P_COC 1.2
#define P_SPR 1.2
#define P_ORA 1.5
#define QTTBO 20
#define false 0
#define true  1

int i;
char choix;
int eaux = QTTBO;
int fantas = QTTBO;
int cocas = QTTBO;
int sprites = QTTBO;
int oranges = QTTBO;
float prixtotal = 0;
float sommejour = 0;
int allume = true;
int rester = true;

void menu_principal(void);

int main(void) {
    menu_principal();
    return 0;
}

void menu_principal(void) {
    if (allume) {
        while (rester) {
            system("clear");
            printf("Distributeur de boissons:\n"
                    "=========================\n"
                    "Boissons restantes:\n"
                    "a) Eau: €%d (%d rest.)\n"
                    "b) Fanta: €%.2f (%d rest.)\n"
                    "c) Coca: €%.2f (%d rest.)\n"
                    "d) Sprite: €%.2f (%d rest.)\n"
                    "e) Jus d'orange: €%.2f (%d rest.)\n" 
                    "q) Quitter et payer.\n"
                    "=========================\n"
                    "Choix? : ",
                    P_EAU, eaux, P_FAN, fantas, P_COC, cocas, 
                    P_SPR, sprites, P_ORA, oranges);
            scanf("%s", &choix); 
            switch (choix) {
                case 'a' : 
                    if (eaux > 0) {
                        eaux--; prixtotal += P_EAU;
                    } break;
                case 'b' :
                    if (fantas > 0) {
                        fantas--; prixtotal += P_FAN;
                    } break;
                case 'c' :
                    if (cocas > 0) {
                        cocas--; prixtotal += P_COC;
                    } break;
                case 'd' :
                    if (sprites > 0) {
                        sprites--; prixtotal += P_SPR;
                    } break;
                case 'e' :
                    if (oranges > 0) {
                        oranges--; prixtotal += P_ORA;
                    } break;
                case 'q' :
                    rester = false; break;
                default :
                    puts("\n"); break;
            }
        }
        if (prixtotal > 0) 
            printf("Veuiller payer €%.2f\n", prixtotal);
        sommejour += prixtotal;
        if ( eaux == 0 && fantas == 0 && cocas == 0
                && sprites == 0 && oranges == 0) {
            allume = false; 
            printf("\n\n\nLa machine s'eteind...\n\n\n");
            printf("aujourd'hui: €%.2f.\n", sommejour);
        }
    }
}
