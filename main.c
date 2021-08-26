#include <stdio.h>
#include <stdlib.h>

int Solve_squre_equation (double a, double b, double c, double* x1, double* x2)
{
    if (cmp_with_0(a))
    {
        if (cmp_with_0(b))
        {
            if (cmp_with_0(c)) return SS_INF_ROOTS; else return 0;
        }
        else
        {
            *x1 = -c/b;
            return 1;
        }
    }
    else
    {
        double D = b*b - 4*a*c;
        if (cmp_with_0(D))
        {
            *x1 = *x2 = -b/(2*a);
            return 1;
        }
        else if (D < 0)
        {
            return 0;
        }
             else
             {
                double sqrt_D = sqrt(D);
                *x1 = (-b + sqrt_D) / (2*a);
                *x2 = (-b - sqrt_D) / (2*a);
                return 2;
             }
    }
}

int cmp_with_0 (double val)
{
    if (fabs(val) < 0.001) return 1; else return 0;
}

int main()
{
    printf ("Welcome to my programm (solver of squre equation)!\nJane Bachilo, 1 kurs");
    double a = NAN, b = NAN, c = NAN;
    printf ("Enter coefficients a, b, c:\n");
    scanf ("%lg %lg %lg", &a, &b, &c);
    double x1 = NAN, x2 = NAN;
    int nRoots = Solve_squre_equation (a, b, c, &x1, &x2);
    /*D = b*b - 4*a*c;
    if (D < 0)
    {
        printf("Net korney\n");
    }
    else if (cmp_with_0(D))
    {
        printf("x1 = x2 = %lg\n", (-b)/(2*a));
    }
         else
         {
             printf("x1 = %lg, x2 = %lg\n", (-b+sqrt(D))/(2*a), (-b-sqrt(D))/(2*a));
         }*/
    switch (nRoots)
    {
        case 0: printf ("No roots");
                break;
        case 1: printf ("x1 = %lg", x1);
                break;
        case 2: printf ("x1 = %lg, x2 = %lg", x1, x2);
                break;
        case SS_INF_ROOTS: printf ("Any number can be the root");
                           break;
        default: printf ("main(): ERROR: nRoots = %d", nRoots);
                 return 1;
    }
    return 0;
}
