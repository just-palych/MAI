#include <string.h>
#include "stdio.h"
#include "math.h"

typedef enum{
    fcs_ok = 1,
    fcs_not_number,
    fcs_invalid_input,
}function_status_codes;

function_status_codes double_number_checker(char *s)
{
    int buf  = strlen(s);
    if (buf > 1)
    {
        for (int i = 0; i < buf; ++i) 
        {
            if ((s[i] < '0' || s[i] > '9') && s[i] != '.')
            {
                return fcs_not_number;
            }
        }
        return fcs_ok;
    }
    else if (s[0] < '0' || s[0] > '9')
        {
            return fcs_not_number;
        }
        return fcs_ok;
    
}

double str_to_d(char* number){
    unsigned long long digits = strlen(number);
    int dot_flag = 0;
    double result = 0;
    int j = 0;
    for (int i = 0; i < digits; ++i)
    {
        if(number[i] == '.')
        {
            dot_flag = 1;
            i++;
        }
        if(!dot_flag)
        {
            result = result * 10 + (number[i] - '0');
        }
        else
        {
            j++;
            result += (number[i] - '0') * pow(10, -j);
        }
    }
    return result;
}

double a_func(double x)
{
    return log(1 + x) / x;
}

double b_func(double x)
{
    return pow(M_E, -x*x/2);
}

double c_func(double x)
{
    return log(1/(1 - x));
}

double d_func(double x)
{
    return pow(x, x);
}

double integral(double (*func)(double), double epsilon, int side)
{
    double a = 0.0, b = 1.0;
    double res = 0;
    double acc = 2.0;
    double buf;
    do{
        double step = (b - a) / acc;
        buf = res;
        res = 0;
        if (side == 1) 
        {
            for (double cur = b; cur > a + epsilon; cur -= step) 
            {
                res += step * func(cur);
            }
        }
        else
        {
            for (double cur = a; cur < b - epsilon; cur += step) 
            {
                res += step * func(cur);
            }
        }
        acc++;
    }while (fabs(buf - res) > epsilon);
    return res;
}


function_status_codes format_validation(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Invalid input!\n");
        return fcs_invalid_input;
    }
    if(double_number_checker(argv[1]) == fcs_not_number)
    {
        printf("Not a number !\n");
        return fcs_not_number;
    }
    return fcs_ok;
}

void printer(double epsilon)
{
    printf("a. %.20f\n", integral(a_func, epsilon, 1));
    printf("b. %.20f\n", integral(b_func, epsilon, 1));
    printf("c. %.20f\n", integral(c_func, epsilon, 0));
    printf("d. %.20f\n", integral(d_func, epsilon, 1));
}



int main(int argc, char **argv)
{
    if(format_validation(argc, argv) == fcs_ok)
    {
        printer(str_to_d(argv[1]));
    }
    return 0;
}