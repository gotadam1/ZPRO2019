#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int den;
    int mesic;
    int rok;
}
datum;

bool zkontrolovat_datum(datum* date)
{
    bool d;
    if (date->mesic == 1 || date->mesic == 3 || date->mesic == 5 || date->mesic == 7 || date->mesic == 8 || date->mesic == 10 || date->mesic == 12)
    {
        d = (date->den < 32 && date->den > 0);
    }
    else if (date->mesic == 4 || date->mesic == 6 || date->mesic == 9 || date->mesic == 11)
    {
        d = (date->den < 31 && date->den > 0);
    }
    else if (date->mesic == 2)
    {
        if (date->rok % 4 == 0)
        {
            d = (date->den < 30 && date->den > 0);
        }
        else
        {
            d = (date->den < 29 && date->den > 0);
        }  
    }
    else
    {
        d = 0;
    }
    
    bool m;
    if (date->mesic < 12 && date->mesic > 0)
    {
        m = 1;
    }

    bool r;
    if (date->rok > 1900 && date->rok < 2021)
    {
        r = 1;
    }

    bool c = 1;
    if (date->rok = 2020)
    {
        if ((date->mesic == 2 && date->den < 4) || date->mesic < 2)
        {
            c = 1;
        }
        else
        {
            c = 0;
        }
        
    }
    return c&&d&&m&&r;
}

void vytvor_datum (datum* d, char* date)
{
    scanf(date, "%d.%d.%d", d->den, d->mesic , d->rok );
}

int main()
{
    datum* date;
    vytvor_datum(date, "1.12.2019");

    printf("%d \n", date->den);
    printf("%d \n", date->mesic);
    printf("%d \n", date->rok);

    return 0;
}