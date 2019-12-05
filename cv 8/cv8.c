#include <stdio.h>

void soucin_matic(int r, int s, int t, const float A[r][s], const float B[s][t], float C[r][t])
{
    for (int i = 0; i < r; i++)
    for (int j = 0; j < t; j++)
    {
        // napred vynulovat vysledek
        C[i][j] = 0;
        // vypocet skalarniho soucinu i-teho radku A a j-teho sloupce B
        for (int k = 0; k < s; k++)
            C[i][j] += A[i][k] * B[k][j];
    }
}

void secti_matice(int r, int s, const float m1[r][s], const float m2[r][s], float m3[r][s])
{
    for (int i = 0; i < r; i++)
    for (int j = 0; j < s; j++)
    {
        m3[i][j] = m1[i][j] + m2[i][j];
    }
}

int main()
{
    printf("Zadej pocet radku a pocet sloupcu: ");
    int m, n;
    scanf("%d%d", &m, &n);

    // matice m x n
    float A[m][n];
    float B[m][n];
    float C[m][n];

    printf("Zadej prvky matice A (po radcich):\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%f", &A[i][j]);
        }
    }

    printf("Zadej prvky matice B (po radcich):\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%f", &B[i][j]);
        }
    }

    // spocitat C = A + B
    secti_matice(m, n, A, B, C);

    // vypis matice C
    printf("Matice C = A + B je:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f\t", C[i][j]);
        }
        printf("\n");
    }
}
