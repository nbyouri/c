#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * absfirst(_Complex double);
char op(_Complex double);
void cplxinfo(char *, _Complex double);

char op(_Complex double x) {
    return signbit(cimag(x)) != 0 ? '-' : '+';
}

// pas de module si == 1 dans formes trigonometrique, 
// exponentielle, cartesiennes
char * absfirst(_Complex double x) {
    char * ret = malloc(BUFSIZ * sizeof(char));
    double abs = cabs(x);
    snprintf(ret, BUFSIZ, "%2.3f", abs);
    if (ret[0] == '1')
        strlcpy(ret, "", BUFSIZ);
    return ret;
}

void cplxinfo(char * str, _Complex double x) {
    double rel = creal(x);
    double ima = cimag(x);
    double arg = carg(x);
    double abs = cabs(x);
    char * abs_f = absfirst(x);

    printf("%s: %2.3f %c %2.3fi (forme algebrique)\n", 
            str, rel, op(x), fabs(ima));

    printf("\treel = %2.3f\n\timaginaire = %2.3f\n"
            "\tmodule = %2.3f\n\targument = %2.3f\n"
            "\tforme exponentielle : %se^(%2.3fi)\n"
            "\tforme cartesienne : %s(cos(%2.3f) + i sin(%2.3f))\n"
            "\tforme trigonometrique : %scis(%2.3f)\n\n",
            rel, ima, abs, arg, abs_f, arg, abs_f, arg, arg, abs_f, arg);
}

int main(void) {
    double complex u = -sqrt(2)/2 + sqrt(2)/2 * I;
    double complex v = -sqrt(3)/2 - sqrt(3)/2 * I;
    double complex w = -2 / (2 - 3 * I);
    double complex x = (3 - 2 * I)/2;
    double complex y = 0 - 3.0 * I;
    double complex z = 3.0 - 2.0 * I;

    cplxinfo("z", z);
    cplxinfo("y", z);
    cplxinfo("z/y", z/y);
    cplxinfo("x", x);
    cplxinfo("x ^ 2", cpow(x, 2));
    cplxinfo("w", w);
    cplxinfo("x * w", x*w);
    cplxinfo("x / w", x/w);
    cplxinfo("v", v);
    cplxinfo("v^13", cpow(v, 13));
    cplxinfo("-v", -v);
    cplxinfo("sqrt(v)", csqrt(v));
    cplxinfo("u", u);
    cplxinfo("u^19", cpow(u, 19));

    return 0;
}


