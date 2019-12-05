#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct
{
    float x;
    float y;
}
point2d;

bool point2d_eq(point2d p1, point2d p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

bool point2d_ne(point2d p1, point2d p2)
{
    return ! point2d_eq(p1, p2);
}

float point2d_vzdalenost(point2d p)
{
	return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

float point2d_vzdalenostDvou(point2d p1, point2d p2)
{
	return sqrt(pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2));
}

float point2d_obvod(point2d p1, point2d p2, point2d p3)
{
	
	return point2d_vzdalenostDvou(p1, p2)+point2d_vzdalenostDvou(p2, p3)+point2d_vzdalenostDvou(p1, p3);
}

float point2d_obsah(point2d p1, point2d p2, point2d p3)
{
	float s = point2d_obvod(p1, p2, p3)/2;
	float a = point2d_vzdalenostDvou(p1, p2);
	float b = point2d_vzdalenostDvou(p2, p3);
	float c = point2d_vzdalenostDvou(p1, p3);
	
	return sqrt(s*(s-a)*(s-b)*(s-c));
}

int main()
{
	point2d a = {0, 3};
	point2d b = {0, 0};
	point2d c = {4, 0};
	
	printf("%f\n", point2d_obsah(a,b,c));
	
	
	return 0;
}
