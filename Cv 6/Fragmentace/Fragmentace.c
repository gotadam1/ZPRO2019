#include <stdio.h>

int main()
{
    int n;
    printf("zadejte cislo: ");
    scanf("%d", &n);

    int pole[32];
    int len = 0;
    int prvocislo = 2;
    int cislo = n;

    while (prvocislo <= n)
    {
        if (n % prvocislo == 0)
        {
            pole[len] = prvocislo;
            len++;
            n = n/prvocislo;
        }
        else
        {
            prvocislo++;
        }
    }
    
    printf("rozklad %d na prvocisla je ", cislo);
    for(int i=0; i < len; i++)
    {
        printf("%d ", pole[i]);
    }

    return 0;
}