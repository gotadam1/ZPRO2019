#include <stdio.h>

int main()
{
    FILE* soubor = fopen("vstup.txt", "r");
    if (soubor == NULL) {
        printf("chyba otevreni souboru\n");
        return 1;
    }

    // tabulka (histogram) poctu vyskytu pro kazdy znak
    int pocty_vyskytu[256];
    for (int i = 0; i < 256; i++)
        pocty_vyskytu[i] = 0;

    // dokud nedojdu na konec souboru
    while (!feof(soubor)) {
        // nacist znak
        int znak = fgetc(soubor);
        // pricist 1 v poli
        if (znak != EOF)
            pocty_vyskytu[znak]++;
    }

    fclose(soubor);

    // najit nejcastejsi znak
    int max = 0;
    for (int i = 0; i < 256; i++) {
        if (pocty_vyskytu[i] > pocty_vyskytu[max]) {
            max = i;
        }
    }
    printf("Nejcastejsi znak je '%c', pocet vyskytu: %d\n", max, pocty_vyskytu[max]);

    return 0;
}
