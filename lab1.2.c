#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef enum
{
    fsc_ok,
    fsc_invalid_parameter,
    fsc_overflow
}function_status_codes;

int simplicity(
    int value)
{
    if (value > 3)
    {
        if (value % 2 == 0)
        {
            return false;
        }
        for (int i = 3; i <= sqrt(value); i +=  2)
        {
            if (value % i == 0)
            {
                return false;
            }
        }
    }
    return true;
}

int char_to_double(char s[], double *huepsilon)
{
    *huepsilon = atof(s);
    if(*huepsilon > 1.0)
    {
        return -1;
    }
    if(*huepsilon == 0)
    {
        return -2;  
    }
    return 0;
}

double sum_n(int value)
{
    double sum = 1;
    for (int i = 2; i <= value; i++)
    {
        sum += 1.0 / i;
    }
    return sum;
}

double lim_e(double huepsilon)
{
    double buf, result  = 0;
    double value = 1;

    do
    {
        buf = result;
        value *= 2;
        result = pow((1 + 1 / value), value);

    } while (fabs(buf - result) > huepsilon);
    return result;

}

double sum_e(double huepsilon)
{
    double result_sum = 0;
    double buf_sum = -1;
    double factorial_n = 1;
    for (int value = 0; value <= 20; value++)
    {
        factorial_n *= value;
        if (value == 0)
            factorial_n  = 1;
        result_sum += 1.0 / factorial_n;
        if (fabs(result_sum - buf_sum) < huepsilon)
            break;
        buf_sum = result_sum;
    }
    return result_sum;
}

double eqt_e(double huepsilon)
{
    double value = 0.0;
    double first = 2.0;
    double second = 3.0;
    value = (first + second) / 2;

    while (fabs(log(value) - 1) > huepsilon)
    {
        value = (first + second) / 2;
        if (log(value) < 1)
            first = value;
        else
            second = value;
    }
    return value;
}

double lim_pi(double huepsilon)
{
    double result_limit = 4.0;
    double buf_limit = 0.0;
    int value = 2;
    do
    {
        buf_limit = result_limit;
        result_limit = result_limit * (4.0 * value * ( value - 1.0)) / pow(2.0 * value - 1.0, 2);
        value++;
    } while (fabs(buf_limit - result_limit) >= huepsilon);
    return result_limit;
}

double sum_pi(double huepsilon)
{
    double result_sum = 1.0;
    double buf_sum = 0;
    int value = 1;
    do
    {
        buf_sum = result_sum;
        value++;
        result_sum -= 1.0 / (2 * value - 1);
        value++;
        result_sum += 1.0 / (2 * value - 1);

    } while (fabs(buf_sum - result_sum) > huepsilon);
    return result_sum * 4;
}

double eqt_pi(double huepsilon)
{
    double value = 0;
    double first = 2;
    double second = 4;
    value = (second + first) / 2; 
    do
    {
        value = (second + first) / 2;
        if(sin(value) > 0)
            first = value;
        else
            second = value;
    } while (fabs(first - second) > huepsilon);
    return value;
}

double lim_ln(double huepsilon)
{
    double buf = 0.0;
    double result = 1.0;
    double value = 1;
    do
    {
        buf = result;
        value++;
        result = value * (pow(2.0, 1.0 / value) - 1.0);
        
    } while (fabs(buf - result) > huepsilon);
    return result;
}

double sum_ln(double huepsilon)
{
    double buf = 0;
    double result = 1;
    int value = 1;
    do
    {
        buf = result;
        value++;
        result -= 1.0 / value;
        value++;
        result += 1.0 / value;

    } while (fabs(buf - result) > huepsilon);
    return result;
}

double eqt_ln(double huepsilon)
{
    double first = 0.5;
    double second = 0.7;
    double value;
    do
    {
        value = (first + second) / 2.0;
        if (exp(value) > 2)
        {
            second = value;
        }   
        else
        {
            first = value;
        }    
    } while (fabs(exp(value) - 2) > huepsilon);
    return value;
}

double lim_root_of_2(double huepsilon)
{
    double buf = 0;
    double result = -0.5;
    int value = 0;
    do
    {
        buf = result;
        value++;
        result = (2.0 * buf - pow(buf, 2.0) + 2) / 2;

    } while (fabs(buf - result) > huepsilon);
    return result; 
}

double sum_root_of_2(double huepsilon)
{
    double buf = 0;
    double result = 0;
    int k = 2;
    result = pow(2.0, 1.0 / 4.0);
    do
    {
        buf = result;
        k++;
        double power = 1.0 / pow(2,k);
        result *= pow(2, power);
        
    } while (fabs(buf - result) > huepsilon);
    return result;
}

double eqt_root_of_2(double huepsilon)
{
    double first = 1.2;
    double second = 1.5;
    double value = (first + second) / 2;
    do
    {
        value = (first + second) / 2;
        if(pow(value, 2) > 2)
            second = value;
        else
            first = value;
    } while (fabs(pow(value, 2) - 2) > huepsilon);
    return value;
}

double lim_y(double huepsilon)
{
    double buf = 0;
    double result = 1;
    int value = 1;
    do
    {
        buf = result;
        value *= 2;
        result = sum_n(value) - log(value);
    } while (fabs(buf - result) > huepsilon);
    return result;
}

double sum_y(double huepsilon)
{
    double buf = 0;
    double result = 0.5;
    int k = 2;
    double l = 0;

    do
    {
        buf = result;
        k++;
        l = sqrt(k);
        if (fmod(l,1.0) == 0)
            {
                k++;
                l = (int)pow(k, 1. / 2.0);
            }
        result += 1.0 / pow((int)l, 2.0) - 1.0 / k;
    }while (fabs(buf - result) > huepsilon);
    return result - pow(M_PI, 2)/6;
}



double eqt_y(double huepsilon)
{
    int p = 2;
    double result = log(2) * 0.5;
    double buf = 0;
    double product = 0.5;
    do
    {
        buf = result;
        do
        {
            p++;
        } while (!simplicity(p));
        product *= (p - 1.0) / p;
        result = log(p) * product;
    } while (fabs(buf - result) > huepsilon);
    return (-log(result));
}








int main(int argc, char* argv[])
{
    char flag;
    double epsilon = 0;
    if(*argv[1] == '-')
    {
        printf("!!!11111 epsilon < 0 \n");
        return 1;
    }
    switch ((char_to_double(argv[1], &epsilon)))
    {
        case 0:
            flag = argv[2][0];
            break;
        case -1:
            printf("overflow\n");
            break;
        case -2:
            printf("!!!!!!1!! epsilon = 0\n");
            break;
        default:
            break;
    }
    switch (flag)
    {
        case 'e':
        {   
            printf("The results of calculating the number e are obtained \n");
            printf("by lim %f\n", lim_e(epsilon));
            printf("by sum %f\n", sum_e(epsilon));
            printf("by eqt %f\n", eqt_e(epsilon));
        }
            break;
        case 'p':
        {
            printf("The results of calculating the number pi are obtained \n");
            printf("by lim %f\n", lim_pi(epsilon));
            printf("by sum %f\n", sum_pi(epsilon));
            printf("by eqt %f\n", eqt_pi(epsilon));
        }
            break;
        case 'l':
        {
            printf("The results of calculating the number ln2 are obtained \n");
            printf("by lim %f\n", lim_ln(epsilon));
            printf("by sum %f\n", sum_ln(epsilon));
            printf("by eqt %f\n", eqt_ln(epsilon));
        }
            break;
        case 'r':
        {
            printf("The results of calculating the number 2^0.5 are obtained \n");
            printf("by lim %f\n", lim_root_of_2(epsilon));
            printf("by sum %f\n", sum_root_of_2(epsilon));
            printf("by eqt %f\n", eqt_root_of_2(epsilon));
        }
            break;
        case 'y':
        {
            printf("The results of calculating the number y are obtained \n");
            printf("by lim %f\n", lim_y(epsilon));
            printf("by sum %f\n", sum_y(epsilon));
            printf("by eqt %f\n", eqt_y(epsilon));
        }
            break;
        default:
            printf("bye bye\n");
            break;
    }
    return 0;
    
}