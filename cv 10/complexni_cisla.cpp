#include <stdio.h>
#include <complex.h>

int main()
{
    float _Complex z1 = I;   // imaginarni jednotka
    float _Complex z2 = csqrt(-1);   // komplexni odmocnina
    float _Complex z3 = z1 + z2;

    // vypis: zvlast realna a imaginarni cast
    printf("z3 = %f + %fi\n", creal(z3), cimag(z3));

    return 0;
}
