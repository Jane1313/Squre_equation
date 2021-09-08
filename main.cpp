#include <iostream>

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


const double ALMOST_NULL = 0.001; // 1e-15
const int INF_ROOTS = -1;


///---------------------------------------------------------------------
//! Solves a square equation ax^2 + bx + c = 0
//!
//! @param [in]  a   a-coefficient
//! @param [in]  b   b-coefficient
//! @param [in]  c   c-coefficient
//! @param [out] x1  Pointer to the 1st root
//! @param [out] x2  Pointer to the 2nd root
//!
//! @return Number of roots
//!
//! @note   In case of infinite number of roots, returns INF_ROOTS.
///---------------------------------------------------------------------

int Solve_Squre_Equation (double, double, double, double*, double*);

///---------------------------------------------------------------------
//! Checks if two values are equal
//!
//! @param [in]  val1   1st value
//! @param [in]  val2   2nd value
//!
//! @return 1 - values are equal, 0 - values aren't equal
///---------------------------------------------------------------------

int Is_Equal (double, double);

///---------------------------------------------------------------------
//! Tests the programm
//!
//! @param [in]  nTest      number of test
//! @param [in]  a          a-coefficient
//! @param [in]  b          b-coefficient
//! @param [in]  c          c-coefficient
//! @param [in] nRootsRef  How many roots should there be
//! @param [in] x1ref      what should be the 1st root
//! @param [in] x2ref      what should be the 2nd root
//!
//! @return 1 - the test was successful, 0 - the test wasn't successful
///---------------------------------------------------------------------

int Unit_Test (int, double, double, double, int, double, double);

///---------------------------------------------------------------------
//! Introduces values for testing
//!
//! @return Number of errors
///---------------------------------------------------------------------

int Run_Unit_Test ();

///---------------------------------------------------------------------
//! Clears the input buffer
///---------------------------------------------------------------------

void Clear_Buffer();

///---------------------------------------------------------------------
//! Enters coefficients a, b, c
//!
//! @param [in]  a   Pointer to the a-coefficient
//! @param [in]  b   Pointer to the b-coefficient
//! @param [in]  c   Pointer to the c-coefficient
//!
//! @return Nothing
///---------------------------------------------------------------------

void Enter_Coef (double*, double*, double*);

///---------------------------------------------------------------------
//! Outputs the roots of a square equation
//!
//! @param [in]  nRoots   number of roots
//! @param [in]  x1       the 1st root
//! @param [in]  x2       the 2nd root
//!
//! @return 0 - right programm, 1 - ERROR
///---------------------------------------------------------------------

int Output_Roots (int, double, double);


int main()
{
    printf ("Welcome to my programm (solver of squre equation)!\nJane Bachilo, 1 cours\n\n");

    int errors = Run_Unit_Test();   ///Тестирование
    printf ("Number of errors: %d\n\n", errors);

    double a = 1, b = 2, c = 3;  ///Ввод значений
    Enter_Coef (&a, &b, &c);

    double x1 = NAN, x2 = NAN;   ///Решение уравнения
    int nRoots = Solve_Squre_Equation (a, b, c, &x1, &x2);

    Output_Roots (nRoots, x1, x2);   ///Вывод корней

    printf ("%lg %lg %lg", a, b, c);
    return 0;
}


void Enter_Coef (double* a, double* b, double* c) //a, b и c - указатели
{
    printf ("Enter coefficients a, b, c:\n");
    int ok = 0;
    while (ok == 0)
    {
        int nPrav = scanf ("%lg %lg %lg", a, b, c);
        printf ("a_enter = %lg\n", *a);
        if (nPrav < 3)
        {
            printf ("INVALID ENTRY!!!\n\nTry again:\n");
            Clear_Buffer();
        }
        else
            ok = 1;
    }
}

// тесты из файла

// 1e-20 x^2 + 2e-20*x + 1e-20 = 0

int Output_Roots (int nRoots, double x1, double x2)
{
    switch (nRoots)
    {
        case 0:
            printf ("No roots\n");
            return 0;
        case 1:
            printf ("x1 = %lg\n", x1);
            return 0;
        case 2:
            printf ("x1 = %lg, x2 = %lg\n", x1, x2);
            return 0;
        case INF_ROOTS:
            printf ("Any number can be the root\n");
            return 0;
        default:
            printf ("main(): ERROR: nRoots = %d\n", nRoots);
            return 1;
    }
}

int Solve_Squre_Equation (double a, double b, double c, double* x1, double* x2)
{
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));

    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (Is_Equal(a, 0))
    {
        if (Is_Equal(b, 0))
        {
            if (Is_Equal(c, 0))
                return INF_ROOTS;
            else
                return 0;
        }
        else
        {
            *x1 = -c/b;
            printf ("x1 = %lg", *x1);
            return 1;
        }
    }
    else
    {
        double d = b*b - 4*a*c;
        if (Is_Equal(d, 0))
        {
            *x1 = *x2 = -b/(2*a);
            printf ("x1 = %lg\n", *x1);
            printf ("a = %lg\n", a);
            return 1;
        }
        else if (d < 0)
        {
            return 0;
        }
        else
        {
            double sqrt_d = sqrt(d);
            *x1 = (-b + sqrt_d) / (2*a);
            *x2 = (-b - sqrt_d) / (2*a);
            return 2;
        }
    }
}

int Is_Equal (double val1, double val2)
{
    if (isnan(val1) && isnan(val2))
        return 1;
    else
        if ((isnan(val1) && !isnan(val2)) || (!isnan(val1) && isnan(val2)))
            return 0;
        else
            return (fabs (val1 - val2) < ALMOST_NULL)? 1 : 0;
}

int Unit_Test (int nTest, double a, double b, double c, int nRootsRef, double x1ref, double x2ref)
{
    double x1 = NAN, x2 = NAN;
    int nRoots = Solve_Squre_Equation (a, b, c, &x1, &x2);
    if (nRoots != nRootsRef || !Is_Equal (x1, x1ref) || !Is_Equal (x2, x2ref))
    {
        printf ("Test %d FAILED!\n", nTest);
        printf ("nRoots = %d, x1 = %lg, x2 = %lg\nShould be: %d, %lg, %lg\n\n", nRoots, x1, x2, nRootsRef, x1ref, x2ref);
        return 0;
    }
    else
        return 1;
}

int Run_Unit_Test()
{
    struct DataTest
    {
        double a;
        double b;
        double c;
        int nRoots;
        double x1;
        double x2;
    };
    const int NUMBER_TESTS = 8;
    DataTest data [NUMBER_TESTS] =
    {
        {1,     8,    7,         2,     -1,     -7},
        {1,    -8,    7,         2,      7,      1},
        {1,    -2,    1,         1,      1,      1},
        {0,    -2,    1,         1,    0.5,    NAN},
        {1,    -2,   81,         0,    NAN,    NAN},
        {3, 0.756, -4.5,         2, -1.105, -1.357},
        {0,     0,    0, INF_ROOTS,    NAN,    NAN},
        {0,     0,    2,         0,    NAN,    NAN}
    };
    int nFailed = 0;
    for (int i = 0; i < 2; i++)
    {
        if (Unit_Test(i + 1, data[i].a, data[i].b, data[i].c, data[i].nRoots, data[i].x1, data[i].x2) == 0) nFailed++;
    }
    return nFailed;
}

void Clear_Buffer()
{
    while (getchar() != '\n') {;}
}

