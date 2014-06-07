#include "include.h"

student * grow(student * class, unsigned int nb) {
    student * temp;
    temp = (student *)realloc(class, (nb + 1) * sizeof(student));
    if (temp == NULL) {
        if (class != NULL)
            free(class);
        class = NULL;
        return NULL;
    }
    return temp;
}

void initialize(student * class, unsigned int nb) {
    // random number
    class[nb].num = arc4random() % 100;

    // random birthday
    class[nb].bd.day = arc4random() % 30;
    class[nb].bd.mon = arc4random() % 11;
    class[nb].bd.yea = 1990 + arc4random() % 6;

    // name = peter + random number
    char randomnum[MAX_CHAR];
    snprintf(randomnum, sizeof(randomnum), "%02d", arc4random() % 100);
    strlcpy(class[nb].name, "peter", sizeof(class[nb].name));
    strlcat(class[nb].name, randomnum, sizeof(class[nb].name));
}

