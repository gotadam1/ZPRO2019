#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n;
    scanf("%d", &n);
    int len = 0;
    bool binar[32];
    int cislo = n;

    while(n>0)
    {
        binar[len] = n%2;
        len++;
        n = n/2;
    }

    printf("cislo %d ve dvojkove soustave je ", cislo);
    for(int i = 0 ; i < len; i++)
    {
        printf("%d", binar[len -1 -i]);
    }
    printf("\n");

    return 0;
}