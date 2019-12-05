#include <stdio.h>

void vektorovy_soucet(const float* v1, const float* v2, float* v3, int len)
{
    for (int i = 0; i<len; i++)
    {
        v3[i] = v1[i] + v2[i];
    }
}

float skalarni_soucin(const float* v1, const float* v2, int len)
{
    float r;
    for (int i = 0; i<len; i++)
    {
        r += v1[i] * v2[i];
    }
    return r;
}

void vektorovy_soucin(const float* v1, const float* v2, float* v3, int len)
{
    for (int i = 0; i<len-2; i++)
    {
        v3[i] = v1[i+1]*v2[i+2] - v1[i+2]*v2[i+1];
    }
    v3[len-2] = v1[len-1]*v2[0] - v1[0]*v2[len-1];
    v3[len-1] = v1[0]*v2[1] - v1[1]*v2[0];
}

float slozeny_soucin(const float* v1, const float* v2, const float* v3, int len)
{
    float v4[len];
    vektorovy_soucin(v1,v2,v4,3);

    float r = skalarni_soucin(v4,v3,3);
    return r;
}


int main()
{
    float v1[3] = {1,0,0};
    float v2[3] = {0,1,0};
    float v3[3] = {0,0,1};
    float v4[3];

    vektorovy_soucin(v1,v2,v4,3);

    float dot = skalarni_soucin(v1,v3,3);

    printf("v1 + v2 = (");
    for (int i = 0; i<2; i++)
    {
        printf("%f,", v4[i]);
    }
    printf("%f)\n", v4[2]);

    printf("v1 * v3 = %f\n", dot);

    printf("(v1 x v2) * v3 = %f\n", slozeny_soucin(v1,v2,v3,3));

    return 0;
}