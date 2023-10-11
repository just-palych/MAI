#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


typedef enum
{
    fsc_ok,
    fsc_invalid_parameter,
    fsc_overflow
}function_status_codes;

function_status_codes numbers(
    unsigned long value,
    char result[100])
{
    unsigned long buf =  value;
    int len = 0;
    char* buf_str;
    while (buf > 0)
    {
        buf /= 10;
        len++;
    }
    int count = len * 2;
    result[count - 1] = '\0';
    while (count > 0)
    {   
        if (count % 2 == 0)
        {
            result[count - 2] = (value % 10) + '0';
            value /= 10;
        }
        else
        {
            result[count - 2] = ' ';
        }
        count--;
    }
    return fsc_ok;
}

function_status_codes checking_for_simplicity(
    unsigned long value,
    int *result)
{
    if (value > 3)
    {
        if (value % 2 == 0)
        {
            return *result = false;
        }
        for (int i = 3; i <= sqrt(value); i +=  2)
        {
            if (value % i == 0)
            {
                return *result = false;
            }
        }
    }
    return *result = true;
}

function_status_codes checking_for_multiplicity( 
    int value,
    int result[100])
{
    for (int i = 0; i < 100; i++)
    {
        result[i] = 0;
    }
    
    if ( value > 100 || value < 1)
    {
        return fsc_invalid_parameter;
    }
    int buf = value;
    while (value < 100)
    {
        result[value - 1] = 1;
        value += buf;
    }
    return fsc_ok;
}

function_status_codes power(
    int value,
    unsigned long result[10][10])
{
    if (value > 10)
    {
        return fsc_overflow;
    }
    for (int i = 0; i < value; i++)
    {
        for (int j = 0; j < value; j++)
        {   
            result[i][j] = 0;
        }
    }
    for (int i = 0; i < value; i++)
    {
        for (int j = 0; j < value; j++)
        {   
            if (j == 0)
            {
                result[i][j] = i+1;
            }
            else 
            {
                result[i][j] =  result[i][j-1] * (i+1);
            }
        }
    }
    return fsc_ok;
}

function_status_codes progression(
    unsigned long value,
    unsigned long *result)
{
    if (value > 92681)
    {
        return fsc_overflow;
    }
    *result = (1 + value) * value / 2;
    return fsc_ok;
} 

function_status_codes factorial(
    unsigned int value,
    unsigned long *result)
{
    function_status_codes recursive_status_code;

    if (value > 20)
    {
        return fsc_invalid_parameter;
    }

    if (value == 0 || value == 1)
    {
        *result = 1;
        return fsc_ok;
    }

    recursive_status_code = factorial(value - 1, result);
    if (recursive_status_code == fsc_ok)
    {
        *result *= value;
    }

    return recursive_status_code;
}



int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid number of parameters\n");
    }
    
    const int value = atoi(argv[1]);
    char flag;
    if ('-' != argv[2][0] && '/' != argv[2][0])
    {
        printf("Invalid flag!!!1!\n");
    }
    else
    {
        flag = argv[2][1];
    } 
    if (value < 1)
    {
        printf("Invalid parameter!!\n"); 
        flag = 'x';
    }   
    switch (flag)
    {
        case 'f':
            unsigned long factorial_result;
            switch (factorial(value, &factorial_result))
            {
                case fsc_ok:
                    printf("%u! = %lu\n", value, factorial_result);
                    break;
                case fsc_overflow:
                    printf("Overflow detected!!1!1\n");
                    break;
                case fsc_invalid_parameter:
                    printf("Invalid parameter detected!!1!1\n");
                    break;
            }
            break;
        case 'a':
            unsigned long arithmetic_progression_result;
            switch (progression(value, &arithmetic_progression_result))
            {
                case  fsc_ok:
                    printf("%lu\n", arithmetic_progression_result);
                    break;
                case fsc_overflow:
                    printf("Overflow detected!!1!1\n");
                    break;
                case fsc_invalid_parameter:
                    printf("Invalid parameter detected!!1!1\n");
                    break;
                default:
                    break;
            }
            break;
        case 'e':
            unsigned long power_result[10][10];
            switch (power(value, power_result))
            {
                case fsc_ok:
                    for (int i = 0; i < value; i++)
                    {
                        for (int j = 0; j < value; j++)
                        {
                            if (power_result[j][i] != 0){
                                printf("%lu", power_result[j][i]);
                                printf("           ");
                            }
                        }
                        printf("\n");
                    }
                    break;
                case fsc_overflow:
                    printf("Overflow detected!!1!1\n");
                    break;
                case fsc_invalid_parameter:
                    printf("Invalid parameter detected!!1!1\n");
                    break;
                default:
                    break;
            }
            break;
        case 'h':
            int checking_m_result[100];
            switch (checking_for_multiplicity(value, checking_m_result))
            {
                case fsc_ok:
                    for (int i = 0; i < 100; i++)
                    {
                        if (checking_m_result[i] == 1)
                        {
                            printf("%d\n", i + 1);
                        }   
                    }
                    break;
                case fsc_overflow:
                    printf("Overflow detected!!1!1\n");
                    break;
                case fsc_invalid_parameter:
                    printf("Invalid parameter detected!!1!1\n");
                    break;         
                default:
                    break;
            }
            break;
        case 'p':
            int checking_s_result;
            checking_for_simplicity(value, &checking_s_result);
            
            
                if (checking_s_result == true)
                {
                    printf("%u", value);
                    printf(" is simple\n");
                }
                else
                {
                    printf("%u", value);
                    printf(" is not simple\n");
                }   
                 
        case 's':
            char numbers_result[100];
            switch (numbers(value, numbers_result))
            {
                case fsc_ok:
                    printf("%s\n", numbers_result );
                    break;
                case fsc_overflow:
                    printf("Overflow detected!!1!1\n");
                    break;
                case fsc_invalid_parameter:
                    printf("Invalid parameter detected!!1!1\n");
                    break;
                default:
                    break;
            }
            break;
        case 'x':
            printf("Bye bye\n");
            break;
        default:
            printf("Invalid flag\n");
            break;
    }
    return 0;
}