#include <stdio.h>

typedef struct
{
	//zadefinujeme zlomek
    int citatel;
    int jmenovatel;
}
zlomek;

zlomek soucin(zlomek q1 ,zlomek q2)
{
	//zadefinujeme soucin zlomki
	zlomek q3;
	q3.citatel = q1.citatel * q2.citatel;
	q3.jmenovatel = q1.jmenovatel * q2.jmenovatel;
	return q3;
}

zlomek podil(zlomek q1 ,zlomek q2)
{
	//zadefinujeme podil zlomku
	zlomek q3;
	q3.citatel = q1.citatel * q2.jmenovatel;
	q3.jmenovatel = q1.jmenovatel * q2.citatel;
	return q3;
}

zlomek zakladni_tvar(zlomek q)
{
	int a = 0;
	int c = q.citatel;
	int j = q.jmenovatel;
	
	//pomoci eukleidova algorytmu najdeme NSD
	while(c % j != 0)
	{
		a = c % j;
		c = j;
		j = a;
	}
	
	//úrevedeme zlomek na zakladni tvar
	q.citatel = q.citatel/j;
	q.jmenovatel = q.jmenovatel/j;
	
	return q;
}

zlomek soucet(zlomek q1 ,zlomek q2)
{
	int a = 0;
	int b = q1.jmenovatel;
	int c = q2.jmenovatel;
	//pomoci eukleidova algorytmu najdeme NSD
	while(a % b != 0)
	{
		a = b % c;
		b = c;
		c = a;
	}
	//a secteme patricne upravene zlomky
	a = q1.jmenovatel/c;
	b = q2.jmenovatel/c;
	
	zlomek q;
	q.citatel = q2.citatel*a + q1.citatel*b;
	q.jmenovatel = q1.jmenovatel*q2.jmenovatel/c;
	
	return q;
}

zlomek rozdil(zlomek q1 ,zlomek q2)
{
		int a = 0;
	int b = q1.jmenovatel;
	int c = q2.jmenovatel;
	
	//pomoci eukleidova algorytmu najdeme NSD
	while(a % b != 0)
	{
		a = b % c;
		b = c;
		c = a;
	}
	//a odecteme patricne upravene zlomky
	a = q1.jmenovatel/c;
	b = q2.jmenovatel/c;
	
	zlomek q;
	q.citatel = q2.citatel*a - q1.citatel*b;
	q.jmenovatel = q1.jmenovatel*q2.jmenovatel/c;
	
	return q;
}

int main()
{
	zlomek q1;
	zlomek q2;
	
	//nacteme zlomky a zkontrolujeme znamenka a deleni nulou
	printf("Zadej 2 cela cisla pro prvni zlomek:");
	scanf("%d %d", &q1.citatel, &q1.jmenovatel);
	if(q1.citatel<0 and q1.jmenovatel<0)
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
	if(q2.citatel<0 and q2.jmenovatel<0)
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
