#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>

typedef enum
{
    fsc_ok,
    fsc_invalid_input,
    fsc_overflow,
    fsc_memory_error
} function_status_code;



int main(int argc, char* argv[])
{
    printf("\n-------part 1-------\n");
    int buf;
    int max_pos, min_pos = 0;
    int arr[100]={0};
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int max = a;
    int min = b;
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        arr[i] = a + rand() % (b - a + 1);
        printf("%d  ", arr[i]);
        if (max <= arr[i])
        {
            max = arr[i];
            max_pos = i;
        }
        if (min >= arr[i])
        {
            min = arr[i];
            min_pos = i;            
        } 
    }
    printf("\n");
    printf(" max = %d\n", max);
    printf(" min = %d\n", min);
    buf = arr[max_pos];
    arr[max_pos] = arr[min_pos];
    arr[min_pos] = buf;
    for (int i = 0; i < 100; i++)
    {
        printf("%d  ", arr[i]);
    }
    printf("\n");
//////////////////////////////////
    printf("\n-------part 2-------\n");
    
    int a_size = rand() % (9991) + 10;
    int b_size = rand() % (9991) + 10;

    int* a_array;
    int* b_array;
    a_array = (int*)malloc(sizeof(int) * a_size);
    if (a_array == NULL)
    {
        return fsc_memory_error;
    }
    b_array = (int*)malloc(sizeof(int) * b_size);
    if (b_array == NULL)
    {
        return fsc_memory_error;
    }

    for (int i = 0; i < a_size; i++)
    {
        a_array[i] = rand() % (-1999) + 1000;
        printf("%d ", a_array[i]);
    }
    printf("\n");
    printf("\n");

    for (int i = 0; i < b_size; i++)
    {
        b_array[i] = rand() % (-1999) + 1000;
        printf("%d ", b_array[i]);
    }
    printf("\n");
    printf("\n");

    int* c_array;
    c_array = (int*)malloc(sizeof(int) * a_size);
    if (c_array == NULL)
    {
        return fsc_memory_error;
    } 

    int part_a;
    int part_b = 0;
    int part_c;
    int min_diff = INT_MAX;

    for (int i = 0; i < a_size; i++)
    {
        part_a = a_array[i];


        for (int j = 0; j < b_size; j++)
        {
           if (abs(abs(a_array[i]) - abs(b_array[j])) < min_diff)
           {
                min_diff = abs(abs(a_array[i]) - abs(b_array[j]));
                part_b = b_array[i];
           }
        }
        c_array[i] = part_a + part_b;
        printf("%d ", c_array[i]);
    }

    free(a_array);
    free(b_array);
    free(c_array);
    return 0;
}