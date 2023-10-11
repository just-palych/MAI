#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <limits.h>

typedef enum {
    fsc_ok,
    fsc_invalid_parameter,
    fsc_overflow
} function_status_code;

char check_parameters(
    int argc, char* argv[]) 
{
    if (argc != 4 || (argv[3][0] != '-'))
    {
        return 'x';
    }
    if (argv[3][2])
    {
        return 'y';
    }
    double EPS = strtod(argv[1], NULL);
    if (EPS < 1E-15) 
    {
        return 'z';
    }
    double x = strtod(argv[2], NULL);
    if (!x && argv[2][0] != '0') 
    {
        return 'w';
    }
}

function_status_code sum_a (
    double EPS, double x, double *result) 
{
    double sum = 1, value = 1;
    int n = 1;
    do
    {
        value *= x / n;
        if (DBL_MAX - value < sum || INT_MAX - 1 == n) 
        {
            return fsc_overflow;
        }
        sum += value;
        n++;
    } while (fabs(value) >= EPS);
    
    *result = sum;
    return fsc_ok;
}

function_status_code sum_b (
    double EPS, double x, double *result) 
{
    double sum = 1, value = 1;
    int n = 0;
    do 
    {
        n += 2;
        value *= x * x / (n * (n - 1));
        if (-(DBL_MAX - value) > sum) 
        {
            return fsc_overflow;
        }
        sum -= value;
        n += 2;
        value *= x * x / (n * (n - 1));
        if (DBL_MAX - value < sum || INT_MAX - 4 <= n) {
            return fsc_overflow;
        }
        sum += value;
    } while (fabs(value) >= EPS);
    *result = sum;
    return fsc_ok;
}

function_status_code sum_c (
    double EPS, double x, double *result) 
{
    double sum = 1, value = 1;
    int n = 0;
    do {
        n++;
        value *= 9 * pow(x, 2) * pow(n, 2) / (3 * n - 1) / (3 * n - 2);
        if (DBL_MAX - value < sum || INT_MAX == n) 
        {
            return fsc_overflow;
        }
        sum += value;
    } while (fabs(value) >= EPS);
    *result = sum;
    return fsc_ok;
}

function_status_code sum_d (
    double EPS, double x, double *result) 
{
    double sum, first_sum, value = 0.5 * pow(x, 2);
    sum = -value;
    int n = 1;
    do {
        first_sum = sum;
        n++;
        value *= pow(x, 2) / (2 * n) * (2 * n - 1);
        if (DBL_MAX - value < sum || INT_MAX - 1 == n) 
        {
            return fsc_overflow;
        }
        sum += value;
        n++;
        value *= pow(x, 2) / (2 * n) * (2 * n - 1);
        if (-(DBL_MAX - value) > sum) 
        {
            return fsc_overflow;
        }
        sum -= value;
    } while (fabs(sum - first_sum) >= EPS);

    *result = sum;
    return fsc_ok;
}

int main(int argc, char* argv[]) 
{
    switch (check_parameters(argc, argv)){
        case 'x':
            printf("Imvalid input\n");
            return -1;

        case 'y':
            printf("Invalid input flag!\n");
            return -1;

        case 'z':
            printf("Invalid input EPS\n");
            return -1;

        case 'w':
            printf("Invalid input 'x'\n");
            return -1;
    }
    double EPS = strtod(argv[1], NULL);
    double x = strtod(argv[2], NULL);
    double sum;

    switch (argv[3][1]) {
        case 'a':
            if (sum_a(EPS, x, &sum) == fsc_ok) {
                printf("%.15f\n", sum);
            } else {
                printf("Overflow\n");
            }
            break;

        case 'b':
            if (sum_b(EPS, x, &sum) == fsc_ok) {
                printf("%.15f\n", sum);
            } else {
                printf("Overflow\n");
            }
            break;

        case 'c':
            if (sum_c(EPS, x, &sum) == fsc_ok) {
                printf("%.15f\n", sum);
            } else {
                printf("Overflow\n");
            }
            break;

        case 'd':
            if (sum_d(EPS, x, &sum) == fsc_ok) {
                printf("%.15f\n", sum);
            } else {
                printf("Overflow\n");
            }
            break;
        
        default:
            printf("Invalid input flag!\n");
            break;
    }

    return 0;
}