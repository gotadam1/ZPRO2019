#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct
{
    float x;
    float y;
}
point2d;

float point2d_vzdalenost(point2d p)
{
	return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

float point2d_vzdalenostDvou(point2d p1, point2d p2)
{
	return sqrt(pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2));
}

float obvod_nuhelniku(int N, point2d *souradnice)
{
	float r = 0;
	//obvod spocitame jako sumu vsech stran
	for(int i = 0; i < (N-1); i++)
	{
		r += point2d_vzdalenostDvou(souradnice[i], souradnice[i+1]);
		//printf("%f\n", r);
	}
	r += point2d_vzdalenostDvou(souradnice[N-1], souradnice[0]);
	return r;
}

float obsah_nuhelniku(int N, point2d *souradnice)
{
	float r = souradnice[0].x*(souradnice[1].y-souradnice[N-1].y);
	//obsah spocitame pomoci L´Huillierovych vzorcu
	for(int i = 1; i < (N-1); i++)
	{
		r += souradnice[i].x*(souradnice[i+1].y-souradnice[i-1].y);
	}
	r += souradnice[N-1].x*(souradnice[0].y-souradnice[N-2].y);
	
	return r/2;
}

// funkce pro nacteni jednoho radku textu ze souboru
bool fgetLine(FILE* soubor, char* string, int maxDelka)
{
    for (int i = 0; i < maxDelka; i++) {
        // precti znak z terminalu
        int znak = fgetc(soubor);

        // kontrola jestli nedoslo k chybe cteni
        if (ferror(soubor)) {
            printf("Chyba: neslo precist cely radek\n");
            return false;
        }

        // zkontroluj, jestli neni konec vstupu
        if (znak != EOF && znak != '\n')
            string[i] = znak;
        else {
            // konec vstupu - ukonci string a prerus cyklus
            string[i] = '\0';
            return true;
        }
    }
}

int argmax_3(int N, point2d *souradnice)
{
	int vysledek = 0;
	for (int i = 0; i < N; i++) {
        if (point2d_vzdalenost(souradnice[i]) > point2d_vzdalenost(souradnice[vysledek]))
            vysledek = i;
    }
    return vysledek;
}

void serad_pole_3(int N, point2d *souradnice)
{
    for (int i = 0; i < N - 1; i++) {
        int m = argmax_3(N - i, souradnice + i);
        // prehodit souradnice[i] a souradnice[m + i]
        point2d pomocna = souradnice[i];
        souradnice[i] = souradnice[m + i];
        souradnice[m + i] = pomocna;
    }
}

int main()
{
    FILE* soubor = fopen("data.txt", "r");
    if (soubor == NULL) {
        printf("chyba otevreni souboru\n");
        return 1;
    }

    char radek[1000];
    fgetLine(soubor, radek, 1000);

    // zpracovat 1. radek
    int N = 0;
    sscanf(radek, "N = %d", &N);

    if (N <= 0) {
        printf("chyba: N musi byt kladne.\n");
        fclose(soubor);
        return 1;
    }

    // pole pro ukladani bodu ze souboru
    point2d souradnice[N];

    for (int i = 0; i < N; i++) {
        fgetLine(soubor, radek, 1000);
        int pocet = sscanf(radek, "%f%f", &souradnice[i].x, &souradnice[i].y);
        if (pocet != 2) {
            printf("chyba: nacteno jen %d hodnot\n", pocet);
            fclose(soubor);
            return 1;
        }
    }

    float obvod = obvod_nuhelniku(N, souradnice);
    float obsah = obsah_nuhelniku(N, souradnice);
    printf("Obvod %d-uhelniku je %f.\n", N, obvod);
    printf("Obsah %d-uhelniku je %f.\n", N, obsah);
    
    serad_pole_3(N, souradnice);
    for(int i = 0; i < N; i++)
    {
    	printf("%f   %f\n", souradnice[i].x, souradnice[i].y);
	}

    fclose(soubor);
    return 0;
}
