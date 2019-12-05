#include <stdio.h>

int main(){
	int exp = 0;
	float x = 0.9;
	while(x>10)
	{
		exp++;
		x = x/10;
		
		printf("%f*10^%d\n", x, exp);	
	}
	while(x<0)
	{
		exp--;
		x *= 10;
		
		printf("%f*10^%d\n", x, exp);
	}
	return 0;
}
