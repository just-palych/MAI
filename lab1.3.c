#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef enum
{
    fsc_ok,
    fsc_invalid_parameter,
    fsc_overflow,
    triangle,
    not_triangle,
    divisible,
    not_divisible, 
    too_many_args,
    too_few_args,
    d_low_zero,
    fsc_zero_roots,
    fsc_no_roots
}function_status_codes;

double max( double a, double b)
{
    return a > b ? a : b;
}

double min( double a, double b)
{
    return a < b ? a : b;
}
function_status_codes comparison(
    long long a, long long b)
{   
    if (a % b == 0)
    {
        return divisible;
    }
    else
    {
        return not_divisible;
    }
}

function_status_codes triangle_check(double huepsilon,
    double a, double b, double c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return fsc_invalid_parameter;
    }
    double max_count = max(a, max(b,c));
    double min_count = min(a, min(b,c));
    double mid_count = a + b + c - max_count - min_count;
    if (fabs(max_count * max_count - min_count * min_count - mid_count * mid_count) < huepsilon)
    {
        return triangle;
    }
    else
    {
        return not_triangle;
    }
}
function_status_codes m_flag(int argc, char* argv[])
{   
    long long first  = strtoll(argv[2], NULL, 10); 
    long long second  = strtoll(argv[3], NULL, 10); 
    if (second == 0 || first == 0)
    {
        return fsc_invalid_parameter;
    }
    else
    {
        switch (comparison(first, second))
        {
        case  divisible:
            printf("Divisible\n");
            break;
        case not_divisible:
            printf("Not divisible\n");
        default:
            break;
        }
    }
}

function_status_codes t_flag(int argc, char* argv[])
{   
    double epsilon = fabs(strtod(argv[2], NULL));
    double first = strtod(argv[3], NULL);
    double second = strtod(argv[4], NULL);
    double third = strtod(argv[5], NULL);

        switch (triangle_check(epsilon, first, second, third)) //  проверка на количество аргументов
        {
        case triangle:
            printf("is triangle\n");
            break;
        case not_triangle:
            printf("not tringle\n");
            break;
        default:
            break;
        }
}



function_status_codes quad(double a , double b, double c, double huepsilon, double *x1, double *x2)
{
    double d = b * b - 4 * a * c;
    if (fabs(d) < huepsilon)
    {
        d = 0;
    } 
    else if (d < -huepsilon)
    {
        return d_low_zero;
    }
    *x1 = (-b + sqrt(d)) / (2 * a);
    *x2 = (-b - sqrt(d)) / (2 * a);
    return fsc_ok;
}



function_status_codes q_flag(int argc, char* argv[])
{
    double x1;
    double x2;
    double huepsilon = fabs(strtod(argv[2], NULL));
    double a = strtod(argv[3], NULL);
    double b = strtod(argv[4], NULL);   
    double c = strtod(argv[5], NULL);
    double buf;
    
    int count = 0;
    for (int i = 0; i < 3; i++) {
        //printf("%lf %lf %lf : ", a, b, c);
        if (quad(a, b, c, huepsilon, &x1, &x2) != fsc_ok)
        {
            count++;
        }
        else
        {
            printf("X1 = %lf X2 = %lf\n", x1, x2);
        }
        buf = b;
        b = c;
        c = buf;
        //printf("%lf %lf %lf : ", a, b, c);
        if (quad(a, b, c, huepsilon, &x1, &x2) != fsc_ok)
        {
            count++;
        }
        else
        {
            printf("X1 = %lf X2 = %lf\n", x1, x2);
        }
        buf = a;
        a = b;
        b = buf;
    }
    if (count == 6)
    {
        return fsc_no_roots;
    }
    return fsc_ok;
    

    
}

function_status_codes input(int argc, char* argv[])
{
    char flag;
    if (argv[1][0] == '-' || argv[1][0] == '/') 
    {
        flag = argv[1][1];
    }
    bool some  = true;
    switch (flag)
    {
    case  'q':
        
        if (argc > 6)
        {
            return too_many_args;
        }
        if (argc <6)
        {
            return too_few_args;
        }
        if (strtod(argv[3], NULL) == 0 || strtod(argv[4], NULL) == 0 || strtod(argv[5], NULL) == 0)
        {
            some = false;
            return fsc_invalid_parameter;
        }
        if (some)
        {
            q_flag(argc, argv);
        }
          
        break;
    case  't':
        if (argc > 6)
        {
            return too_many_args;
        }
        if (argc <6)
        {
            return too_few_args;
        }
        if (strtod(argv[3], NULL) == 0 || strtod(argv[4], NULL) == 0 || strtod(argv[5], NULL) == 0)
        {
            some = false;
            return fsc_invalid_parameter;
        }
        if (some)
        {
            t_flag(argc, argv);
        } 
        break;
    case  'm':
        if (argc > 4)
        {
            return too_many_args;
        }
        if (argc < 4)
        {
            return too_few_args;
        }
        if (argc == 4)
        {
            m_flag(argc, argv);
        }   
        break;
    default:
        printf("Invalid flag\n");
        break;
    }
}
int main(int argc, char* argv[])
{   
    switch (input(argc, argv))
    {
    case too_few_args:
        printf("Too few arguments\n");
        break;
    case too_many_args:
        printf("Too many arguments\n");
        break;
    case fsc_invalid_parameter:
        printf("Invalid arg\n");
        break;
    case fsc_no_roots:
        printf("Zero roots");
    default:
        printf("ALL IS OK\n");
        break;
    }
}