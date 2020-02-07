#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// struktura pro datum
typedef struct
{
    int den;
    int mesic;
    int rok;
}
datum;

// struktura pro data
typedef struct
{
	char nazev[19];
    char typ[14];
    char kod[19];
    char odpovedna [18];
    datum date;
    char kontrolujici [21];
    char stav[14];
}
data_typ;

// dopredna deklarace
typedef struct uzel uzel;

struct uzel
{
	// datova polozka
	data_typ* data;
	// ukazatel na nasledujici prvek
	uzel* naslednik;
};

typedef struct
{
	uzel* zacatek;
	uzel* konec;
}
spojovy_seznam;

// funkce pro kontrolu platnosti data
bool zkontrolovat_datum(datum date)
{
    //spravny pocet dni
    bool d;
    if (date.mesic == 1 || date.mesic == 3 || date.mesic == 5 || date.mesic == 7 || date.mesic == 8 || date.mesic == 10 || date.mesic == 12)
    {
        d = (date.den < 32 && date.den > 0);
    }
    else if (date.mesic == 4 || date.mesic == 6 || date.mesic == 9 || date.mesic == 11)
    {
        d = (date.den < 31 && date.den > 0);
    }
    else if (date.mesic == 2)
    {
        if (date.rok % 4 == 0)
        {
            d = (date.den < 30 && date.den > 0);
        }
        else
        {
            d = (date.den < 29 && date.den > 0);
        }  
    }
    
    //spravny pocet mesicu
    bool m = false;
    if (date.mesic < 13 && date.mesic > 0)
    {
        m = true;
    }

    //platny rok
    bool r = false;
    if (date.rok > 1900 && date.rok < 2021)
    {
        r = true;
    }

    //kontrola, zda datum neni z budoucnosti
    bool c = true;
    if (date.rok == 2020)
    {
        if ((date.mesic == 2 && date.den < 4) || date.mesic < 2)
        {
            c = true;
        }
        else
        {
            c = false;
        }
        
    }
    return m&&d&&r&&c;
}

// funkce pro vytvoreni data z textu
datum vytvor_datum(char* date)
{
    datum d;
    sscanf(date, "%d.%d.%d" , &d.den, &d.mesic , &d.rok );
    return d;
}

// funkce pro prevod a vypsani data ve spravnem formatu
void vypis_datum(datum date)
{
    if (date.den == 0 && date.mesic == 0 && date.rok == 0)
    {
        printf("               ");
    }
    else
    {
            printf(" %d.%d.%d    ", date.den, date.mesic, date.rok);
        if(date.den < 10 && date.mesic < 10)
        {
            printf("  ");
        }  
        else if(date.den < 10 || date.mesic < 10)
        {
            printf(" ");
        }
    }
}

// funkce pro prevod a vypsani data ve spravnem formatu do souboru
void fvypis_datum(datum date, FILE* soubor)
{
    if (date.den == 0 && date.mesic == 0 && date.rok == 0)
    {
        fprintf(soubor, "               ");
    }
    else
    {
            fprintf(soubor, " %d.%d.%d    ", date.den, date.mesic, date.rok);
        if(date.den < 10 && date.mesic < 10)
        {
            fprintf(soubor, "  ");
        }  
        else if(date.den < 10 || date.mesic < 10)
        {
            fprintf(soubor, " ");
        }
    }
}

// funkce pro vypis dat
void vypis_data(data_typ* data)
{
	printf("%s;%s;%s;%s;",
			data->nazev,
			data->typ,
			data->kod,
			data->odpovedna
    );
    vypis_datum(data->date);
    printf(";%s;%s\n",
    data->kontrolujici,
    data->stav
    );

}

// funkce pro vypis dat do souboru
void fvypis_data(data_typ* data, FILE* soubor)
{
	fprintf(soubor, "%s;%s;%s;%s;",
			data->nazev,
			data->typ,
			data->kod,
			data->odpovedna
    );
    fvypis_datum(data->date, soubor);
    fprintf(soubor, ";%s;%s\n",
    data->kontrolujici,
    data->stav
    );

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

// funkce pro nacteni dat z radku, rovnou zknotroluje, zda jsou na radku vsechna data
int extrahuj_data(data_typ* data, char* string)
{
    // diky predem danemu formatu maji data presne umisteni v radku
    for(int i = 0; i < 18; i++)
    {
        data->nazev[i] = string[i];
    }
    for(int i = 19; i < 32; i++)
    {
        data->typ[i-19] = string[i];
    }
    for(int i = 33; i < 51; i++)
    {
        data->kod[i-33] = string[i];
    }
    for(int i = 52; i < 69; i++)
    {
        data->odpovedna[i-52] = string[i];
    }
    char d[17];
    for(int i = 70; i < 86; i++)
    {
        d[i-70] = string[i];
    }
    data->date = vytvor_datum(d);
    for(int i = 87; i < 107; i++)
    {
        data->kontrolujici[i-87] = string[i];
    }
    for(int i = 108; i < 121; i++)
    {
        data->stav[i-108] = string[i];
    }

    // kontrola zda nechybi klicova data
    if (data->nazev[1] == ' '||
    data->typ[1] == ' '||
    data->kod[1] == ' '||
    data->odpovedna[1] == ' ')
    {
        return 1;
    }
    // zda nechybi data kontroly pokud kontrola probehla
    else if((data->date.den != 0 &&
    data->date.mesic != 0 &&
    data->date.rok != 0 &&
    data->kontrolujici[1] != ' ' &&
    (data->stav[1] != ' ' || data->stav[0] != '\0')) 
    
    ||
    
    (data->date.den == 0 &&
    data->date.mesic == 0 &&
    data->date.rok == 0 &&
    data->kontrolujici[1] == ' ' &&
    (data->stav[1] == ' '|| data->stav[0] == '\0')) )
    {
        return 0;
    }
    else
    {
        return 1;
    }
    
    


}

uzel* vytvor_prvek(data_typ* data)
{
	// dynamicka alokace
	uzel* novy = malloc(sizeof(uzel));
	if (novy == NULL) {
		printf("chyba alokace\n");
		return NULL;
	}
	// zapis dat
	novy->data = data;
	novy->naslednik = NULL;
	return novy;
}

void vloz_na_zacatek(spojovy_seznam* s, data_typ* data)
{
	// napred zajistime, ze existuje specialni prvek
	if (s->zacatek == NULL) {
		// vytvorime specialni prvek
		uzel* novy = vytvor_prvek(NULL);
		if (novy == NULL) {
			free(data);
			return;
		}
		// nastavime zacatek a konec
		s->zacatek = novy;
		s->konec = novy;
	}
	// pokracujeme jako pred tim...
	uzel* novy = vytvor_prvek(data);
	if (novy == NULL) {
		free(data);
		return;
	}
	// vlozeni do seznamu
	novy->naslednik = s->zacatek;
	s->zacatek = novy;
}

void vloz_na_konec(spojovy_seznam* s, data_typ* data)
{
	if (s->zacatek == NULL) {
		vloz_na_zacatek(s, data);
	}
	else {
		// dynamicka alokace
		uzel* novy = vytvor_prvek(s->konec->data);
		if (novy == NULL)
			return;
		// vlozeni do seznamu
		novy->naslednik = NULL;
		s->konec->naslednik = novy;
		// prepsat data
		s->konec->data = data;
		// aktualizovat ukazatel na konec
		s->konec = novy;
	}
}

// funkce pro vypsani dat ze seznamu
void vypis_seznam(spojovy_seznam s)
{
	uzel* aktualni = s.zacatek;
	while (aktualni != s.konec) {
		vypis_data(aktualni->data);
		aktualni = aktualni->naslednik;
	}
}

// funkce pro vypsani dat ze seznamu do souboru
void fvypis_seznam(spojovy_seznam s, FILE* soubor)
{
	uzel* aktualni = s.zacatek;
	while (aktualni != s.konec) {
		fvypis_data(aktualni->data, soubor);
		aktualni = aktualni->naslednik;
	}
}

// funkce pro vypsani polozek jejichy stav neni OK
void vypis_nOK(spojovy_seznam s)
{
    uzel* aktualni = s.zacatek;
	while (aktualni != s.konec) {
		if(aktualni->data->stav[1] != 'O' && aktualni->data->stav[2] != 'K')
        {
            vypis_data(aktualni->data);
        }
		aktualni = aktualni->naslednik;
	}
}

// funkce pro odstraneni jednoho prvku ze seznamu
void vyjmout_prvek(uzel* u, spojovy_seznam* s)
{
    uzel* aktualni = s->zacatek;
    if(s->zacatek == s->konec)
    {
        s->zacatek = NULL;
        s->konec = NULL;
    }
    else
    {
        uzel* aktualni = s->zacatek;
        if(aktualni == u)
        {
            s->zacatek = u->naslednik;
        }
        else
        {
            while(aktualni->naslednik != u)
            {
                aktualni = aktualni->naslednik;
            }
        }
        if(s->konec == u)
        {
            s->konec = aktualni;
        }
        else
        {
            aktualni->naslednik = u->naslednik;
        }
    }
}

// funkce pro zruseni seznamu
void zrus_seznam(spojovy_seznam* s)
{
	while (s->zacatek != NULL) {
		uzel* aktualni = s->zacatek;
		s->zacatek = aktualni->naslednik;
		free(aktualni->data);
		free(aktualni);
	}
	s->konec = NULL;
}

// funkce pro kontrolu formatu inventarniho cisla
bool zkontroluj_cislo(char* string)
{
    int x;
    int y;
    sscanf(string," Z8-%d/%d  ", &x, &y);
    if(x > 9999999 && x < 100000000 && y > 99 && y < 1000)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// funkce pro zjisteni hodnoty inventarniho cisla
int velikost_inv_cisla(char* string)
{
    int x;
    int y;
    sscanf(string, " Z8-%d/%d  ", &x, &y);
    return x;
}

// funkce hledajici inventarni cislo s nejvyssi hodnotou
int max_inv(spojovy_seznam* s)
{
    // pokud je seznam neprazdny, muzeme hledat maximum
    if (s->zacatek != NULL) {
        // inicializace dosavadniho maxima na zacatek seznamu
        int m = velikost_inv_cisla(s->zacatek->data->kod);
        // porovnani s ostatnimi uzly
        uzel* aktualni = s->zacatek;
	    while (aktualni != s->konec) {
		    if(velikost_inv_cisla(aktualni->data->kod) > m)
            {
               m = velikost_inv_cisla(aktualni->data->kod);
            }
		    aktualni = aktualni->naslednik;
	    }
        // vraceni vysledneho maxima
        return m;
    }
    else {
        // maximum prazdneho seznamu dava nesmyslny vysledek
        return 0;
    }
}

// funkce hledajici polozku jejiz inventarni cislo ma nejvyssi hodnotu
uzel* max(spojovy_seznam* s)
{
    uzel* aktualni = s->zacatek;
    while(velikost_inv_cisla(aktualni->data->kod) != max_inv(s))
    {
        aktualni = aktualni->naslednik;
    }
    return aktualni;
}

// funkce pro serazeni seznamu sestupne podle hodnoty inventarniho cisla
void prerovnat_seznam(spojovy_seznam* s)
{
    spojovy_seznam* r;
    r->zacatek = max(s);
    vyjmout_prvek(max(s), s);
    uzel* aktualni = r->zacatek;
    while(s->zacatek != NULL)
    {
        aktualni->naslednik = max(s);
        vyjmout_prvek(max(s), s);
        aktualni = aktualni->naslednik;
    }
    r->konec = aktualni;
    s->zacatek = r->zacatek;
    s->konec = r->konec;

}

int main()
{
	spojovy_seznam s;
	s.zacatek = NULL;
	s.konec = NULL;
	
	FILE* soubor = fopen("seznam.txt", "r");
	if (soubor == NULL) {
		printf("chyba otevreni souboru\n");
		return 1;
	}
	
	while (!feof(soubor)) {
		// precteni radku ze souboru
		char radek[1000];
		fgetLine(soubor, radek, 1000);
		// preskocit hlavicku
		if (radek[0] == '#')
			continue;
		// vytvorit data
		data_typ* data = malloc(sizeof(data_typ));
		if (data == NULL) {
			printf("chyba alokace\n");
			fclose(soubor);
			return 1;
		}
		// zpracovani radku
        int i = extrahuj_data(data, radek);

        // kontola poctu polozek
        if (i == 1) 
        {
			printf("chyba: na radku chybi polozky.\n");
			free(data);
			continue;
        }
        // kontrola formatu inventarniho cisla
        else if (zkontroluj_cislo(data->kod) == false)
        {
            printf("chyba: chybne inventarni cislo.\n");
			free(data);
			continue;
        }
        // kontrola, zda datum kontroly ma spravny format, nebo zda kontrola jeste nebyla provedena
        else if (zkontrolovat_datum(data->date) == false &&
        data->date.den != 0 &&
        data->date.mesic != 0 &&
        data->date.rok != 0 &&
        data->kontrolujici[1] != ' ' &&
        (data->stav[1] != ' ' || data->stav[0] != '\0'))
        {
            printf("chyba: chybne datum.\n");
			free(data);
			continue;
        }
		// vlozit data do seznamu
		vloz_na_konec(&s, data);
	}
	
    prerovnat_seznam(&s);

    // zapsani usporadaneho seznamu do noveho souboru
    FILE* soubor_out = fopen("output.txt", "w");
    if (soubor_out == NULL) {
        printf("chyba otevreni souboru\n");
        return 1;
    }
    fprintf(soubor_out, "# Nazev polozky   ; Typ polozky ; Inventarni cislo ; Odpovedna osoba ; Datum kontroly ; Kontrolujici osoba ; Stav polozky\n");
    fvypis_seznam(s,soubor_out);

	// vypsat polozky, ktere nejsou OK
	vypis_nOK(s);

    return 0;
}