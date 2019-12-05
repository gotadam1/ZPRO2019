#include <stdio.h>


int main()
{
    int a;
    int b;
    printf("Zadej dve prirozena cisla: ");
    scanf("%d %d", &a, &b);
    int c;


    while(a%b != 0)
    {
        c = a%b;
        a = b;
        b = c;
    }

    printf("Nejvetsi spolecny delitel techto cisel je %d\n", b);

    return 0;
}