#include <stdio.h>

typedef struct
{
	//zadefinujeme zlomek
    int citatel;
    int jmenovatel;
}
zlomek;

int nsd(int a, int b)
{
	
//pomoci eukleidova algorytmu najdeme NSD

	int c = 0;
	while(a % b != 0)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return b;
}

zlomek soucin(zlomek q1, zlomek q2)
{
	//zadefinujeme soucin zlomku
	zlomek q3;
	q3.citatel = q1.citatel * q2.citatel;
	q3.jmenovatel = q1.jmenovatel * q2.jmenovatel;
	return q3;
}

zlomek podil(zlomek q1, zlomek q2)
{
	
	zlomek q;
	
	if(q2.citatel == 0)
	{
		printf("\nChyba deleni nulou\n");
		return q;
	}
	
	//zadefinujeme podil zlomku
	q.citatel = q1.citatel * q2.jmenovatel;
	q.jmenovatel = q1.jmenovatel * q2.citatel;
	return q;
}

zlomek zakladni_tvar(zlomek q)
{
	int nd = nsd(q.citatel, q.jmenovatel);
	//prevedeme zlomek na zakladni tvar
	q.citatel = q.citatel/nd;
	q.jmenovatel = q.jmenovatel/nd;
	
	return q;
}

zlomek soucet(zlomek q1, zlomek q2)
{
	int nd = nsd(q1.jmenovatel,q2.jmenovatel);
	int a = q1.jmenovatel/nd;
	int b = q2.jmenovatel/nd;
	
	zlomek q;
	q.citatel = q2.citatel*a + q1.citatel*b;
	q.jmenovatel = q1.jmenovatel*q2.jmenovatel/nd;
	
	return q;
}

zlomek rozdil(zlomek q1, zlomek q2)
{
	int nd = nsd(q1.jmenovatel,q2.jmenovatel);
	int a = q1.jmenovatel/nd;
	int b = q2.jmenovatel/nd;
	
	zlomek q;
	q.citatel = q1.citatel*b - q2.citatel*a;
	q.jmenovatel = q1.jmenovatel*q2.jmenovatel/nd;
	
	return q;
}

int main()
{
	zlomek q1;
	zlomek q2;
	
	//nacteme zlomky a zkontrolujeme znamenka a deleni nulou
	printf("Zadej 2 cela cisla pro prvni zlomek:");
	scanf("%d %d", &q1.citatel, &q1.jmenovatel);
	if(q1.citatel<0 && q1.jmenovatel<0)
	{
		q1.citatel = -q1.citatel;
		q1.jmenovatel = -q1.jmenovatel;
	}
	if(q1.jmenovatel == 0)
	{
		printf("Chyba deleni nulou");
		return 0;
	}
	printf("Zadej 2 cela cisla pro druhy zlomek:");
	scanf("%d %d", &q2.citatel, &q2.jmenovatel);
	if(q2.citatel<0 && q2.jmenovatel<0)
	{
		q2.citatel = -q2.citatel;
		q2.jmenovatel = -q2.jmenovatel;
	}
	if(q2.jmenovatel == 0)
	{
		printf("Chyba deleni nulou");
		return 0;
	}
	
	
	//vytisknememe vysledky
	printf("%d/%d + %d/%d = %d/%d,\n", q1.citatel, q1.jmenovatel, q2.citatel, q2.jmenovatel, zakladni_tvar(soucet(q1,q2)).citatel, zakladni_tvar(soucet(q1,q2)).jmenovatel);
	printf("%d/%d - %d/%d = %d/%d,\n", q1.citatel, q1.jmenovatel, q2.citatel, q2.jmenovatel, zakladni_tvar(rozdil(q1,q2)).citatel, zakladni_tvar(rozdil(q1,q2)).jmenovatel);
	printf("%d/%d * %d/%d = %d/%d,\n", q1.citatel, q1.jmenovatel, q2.citatel, q2.jmenovatel, zakladni_tvar(soucin(q1,q2)).citatel, zakladni_tvar(soucin(q1,q2)).jmenovatel);
	printf("(%d/%d) / (%d/%d) = %d/%d,\n", q1.citatel, q1.jmenovatel, q2.citatel, q2.jmenovatel, zakladni_tvar(podil(q1,q2)).citatel, zakladni_tvar(podil(q1,q2)).jmenovatel);
    return 0;
}
