#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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

    // v cyklu jsme nedosli ke znaku EOF ani k '\n' - radek je delsi nez (maxDelka - 1)
    // (vypisujeme maxDelka - 1, protoze posledni znak musi byt '\0', ktery ale uzivatel nezadava)
    printf("Chyba: radek je delsi nez maximalni povolena delka %d znaku.\n", maxDelka - 1);
    return false;
}

bool getLine(char* string, int maxDelka)
{
    for (int i = 0; i < maxDelka; i++) {
        // precti znak z terminalu
        int znak = getchar();

        // zkontroluj, jestli neni konec vstupu
        if (znak != EOF && znak != '\n')
            string[i] = znak;
        else {
            // konec vstupu - ukonci string a prerus cyklus
            string[i] = '\0';
            return true;
        }
    }

    // v cyklu jsme nedosli ke znaku EOF ani k '\n' - vstup je delsi nez (maxDelka - 1)
    // (vypisujeme maxDelka - 1, protoze posledni znak musi byt '\0', ktery ale uzivatel nezadava)
    printf("Chyba: vstup je delsi nez maximalni povolena delka %d znaku.\n", maxDelka - 1);
    return false;
}

int countWord(const char *string,const char *slovo)
{
	int count = 0;
	for(int i = 0; i < strlen(string); i++)
	{
		bool r = true;
		for(int n = 0; n < strlen(slovo); n++)
		{
			if(slovo[n] != string[i+n])
			{
				r = false;
				break;
			}
		}
		if(r == true)
		{
			count++;
		}
	}
	return count;
}

void sToUpper(char *string)
{
	for(int i = 0; i < strlen(string); i++)
	{
		string[i] = toupper(string[i]);
	}
}

void strAppend(char *string, const char *appendix)
{
	for(int i = 0; i < strlen(appendix); i++)
	{
		strncat(string, &appendix[i], 1);
	}		
}

int main()
{
    FILE* soubor = fopen("text.txt", "r");
    if (soubor == NULL)
    {
        printf("chyba otevreni souboru\n");
        return 1;
    }
    
    char slovo[100];
    getLine(slovo, 100);

    char fstring[1000];
    fgetLine(soubor, fstring, 1000);
    fclose(soubor);
    
    sToUpper(fstring);
    sToUpper(slovo);
    
	char out[1000] = "\0";
	for(int i = 0; i <= countWord(fstring, slovo); i++)
	{
		strAppend(out, slovo);	
	}
	
	FILE* output = fopen("output.txt", "r+");
    if (soubor == NULL)
    {
        printf("chyba otevreni souboru\n");
        return 1;
    }
	
    fprintf(output, "%s", out);
    fclose(output);
    return 0;
}
