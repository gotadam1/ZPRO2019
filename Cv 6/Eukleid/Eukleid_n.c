#include <stdio.h>


int main()
{
    int n;
    printf("Zadej pocet cisel ");
    scanf("%d", &n);

    int pole[n];

    printf("Zadej %d prirozenych cisel: ", n);
    for(int i = 0; i<n; i++)
    {
        scanf("%d", &pole[i]);
    }
    int c;

    for(n; n>1; n--)
    {
        while(pole[n-1]%pole[n-2] != 0)
        {
            c = pole[n-1]%pole[n-2];
            pole[n-1] = pole[n-2];
            pole[n-2] = c;
        }
        c = 0;
    }
    printf("Nejvetsi spolecny delitel techto cisel je %d\n", pole[0]);

    return 0;
}