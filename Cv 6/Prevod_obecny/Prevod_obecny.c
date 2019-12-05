#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n;
    int b;
    scanf("%d", &n);
    scanf("%d", &b);
    int len = 0;
    int vysledek[32];
    int cislo = n;

    while(n>0)
    {
        vysledek[len] = n%b;
        len++;
        n = n/b;
    }

    printf("cislo %d v soustave %d je ", cislo, b);
    for(int i = 0 ; i < len; i++)
    {
        printf("%d", vysledek[len -1 -i]);
    }
    printf("\n");

    return 0;
}