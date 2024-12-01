#include <stdio.h>
#include <stdlib.h>
#include "sfI.h"

void Inputpar(double **x, double **y, double *a, int *n)
{
    printf("Enter the number of points:\n=>");
    scanf("%d", n);
    *x = (double *)malloc(*n * sizeof(double));
    *y = (double *)malloc(*n * sizeof(double));
    for (int i = 0; i < (*n); i++)
    {
        printf("\n Enter the coordonates of the %d. point ( First Abscissa then ordinate)\n=>", i + 1);
        scanf("%lf", &(*x)[i]);
        scanf("%lf", &(*y)[i]);
    }
    printf("\nEnter X:\n=>");
    scanf("%lf", a);
}

double CenterInterp(double a, double *x, double *y, int n)
{
    double P = 0, L;
    for (int i = 0; i < n + 1; i++)
    {
        L = 1;
        for (int j = 0; j < n + 1; j++)
        {
            if (j == i)
            {
                continue;
            }
            L *= (a - x[j]) / (x[i] - x[j]);
        }
        P += L * y[i];
    }
    return P;
}
double delta(double *y, double *x, int i, int derece)
{
    if (derece == 0)
        return y[i];
    return (delta(y, x, i + 1, derece - 1) - delta(y, x, i, derece - 1)) / (x[i + derece] - x[i]);
}

double Ileri_Interp(double a, double *x, double *y, int *n)
{
    int derece = *n - 1; // polinomun derecesi, nokta sayisina -1 'e esit
    double carpim, P = y[0];
    for (int i = 1; i <= *n; i++)
    {
        carpim = 1;
        for (int j = 0; j < i; j++)
        {
            carpim *= a - x[j];
        }
        P += carpim * delta(y, x, 0, i);
    }
    return P;
}

double nabla(double *y, double *x, int i, int derece)
{
    if (derece == 0)
        return y[i];
    return (nabla(y, x, i, derece - 1) - nabla(y, x, i - 1, derece - 1)) / (x[i] - x[i - derece]);
}

double Geri_Interp(double a, double *x, double *y, int *n)
{
    int derece = *n - 1; // polinomun derecesi, nokta sayisina -1 'e esit
    double carpim, P = y[*n - 1];
    for (int i = 1; i <= *n; i++)
    {
        carpim = 1;
        for (int j = 0; j < i; j++)
        {
            carpim *= a - x[*n - 1 - j];
        }
        P += carpim * nabla(y, x, *n - 1, derece);
    }
    return P;
}

void menu(void)
{
    double *x;
    double *y;
    double a;
    int n, Islem_turu, i; // Yanlis islem_turu girildiginde i while donguyu tekrarliyor
    Inputpar(&x, &y, &a, &n);
    printf("\n\nEnter:\n1. For Merkez Sonlu Fark Interpolation\n2. For Ileri Sonlu Fark Interpolation\n3. For Geri Sonlu Fark Interpolation\n=>");
    do
    {
        i = 0; // default case'e girmezsek donguyu tek bir defa calisir
        scanf("%d", &Islem_turu);
        switch (Islem_turu)
        {
        case 1:
        {
            printf("The result is: %.3lf", CenterInterp(a, x, y, n));
            break;
        }
        case 2:
        {
            printf("The result is: %.3lf", Ileri_Interp(a, x, y, &n));
            break;
        }
        case 3:
        {
            printf("The result is: %.3lf", Geri_Interp(a, x, y, &n));
            break;
        }
        default:
        {
            printf("\nWRONG INPUT\nPlease enter 1, 2, 3 or 4\n");
            i = 1;
            break;
        }
        }
    } while (i);
}