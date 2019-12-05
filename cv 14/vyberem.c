#include <stdio.h>

int argmax(int n, float* pole)
{
    int vysledek = 0;
    for (int i = 0; i < n; i++) {
        if (pole[i] > pole[vysledek])
            vysledek = i;
    }
    return vysledek;
}

void serad_pole(int n, float* pole)
{
    for (int i = 0; i < n - 1; i++) {
        int m = argmax(n - i, pole + i);
        // prehodit pole[i] a pole[m + i]
        float pomocna = pole[i];
        pole[i] = pole[m + i];
        pole[m + i] = pomocna;
    }
}

int main()
{
    printf("Zadej pocet cisel: ");
    int n;
    scanf("%d", &n);

    // pole o velikosti n
    float pole[n];

    // nacist n cisel do pole
    for (int i = 0; i < n; i++) {
        scanf("%f", &pole[i]);
    }

    serad_pole(n, pole);

    // vypis n cisel
    for (int i = 0; i < n; i++) {
        printf("%f ", pole[i]);
    }
    printf("\n");

    return 0;
}
