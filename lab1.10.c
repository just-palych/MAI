#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



typedef enum
{
    fsc_ok,
    fsc_invalid_srting,
    fsc_invalid_base
}function_status_codes;

void get_string_safely_realloc(char** string, int* str_len, FILE* stream) 
{
  
  int size = 0;
  int a;
  while ((a = getc(stream)) != EOF && a != '\n') 
  {
    (*string)[size++] = (char) a;
    if (size >= *str_len) 
    {
      *str_len = *str_len * 2;
      *string = (char*) realloc(*string, *str_len);
      if (string == NULL || stream == NULL) 
      {
        perror("Memory error\n");
        return;
      }
    }
  }
  (*string)[size] = '\0';
}

bool if_lowercase_in_string(const char* string)
{
  for (int i = 0; string[i] != '\0'; i++) {
    if (string[i] >= 'a' && string[i] <= 'z') 
    {
      return true;
    }
  }
  return false;
}

int input_numbers(char** string, int* cap, long* max_, const int base) 
{
  char* endptr;
  long num;
  do {
    get_string_safely_realloc(string, cap, stdin);
    if (strcmp(*string, "Stop") == 0) 
    {
      break;
    }
    if (if_lowercase_in_string(*string)) 
    {
      printf("Ignored\n");
      continue;
    }
    num = strtol(*string, &endptr, base);
    if (endptr != *string + strlen(*string)) 
    {
      printf("Ignored\n");
      continue;
    }
    *max_ = abs(num) > *max_ ? num : *max_;
  } while (1);

  return 0;
}

function_status_codes find_max(char** string, int* cap, long* result) 
{
  printf(" Pls enter base: ");
  get_string_safely_realloc(string, cap, stdin);
  char* endptr;
  long base = strtol(*string, &endptr, 10);
  if (endptr != *string + strlen(*string)) 
  {
    return fsc_invalid_srting;
  }
  if (base < 2 || base > 36)
  {
    return fsc_invalid_base;
  }

  long max_ = 0;
  input_numbers(string, cap, &max_, base);
  *result = max_;
  return fsc_ok;
}

void show_number(long num, const int base) 
{
  if(num == 0)
  {
    printf("0\n");
    return;
  }
  char buff[66];
  buff[65] = 0;
  char* ptr = buff + 64;
  bool low_zero = false;
  if (num < 0) 
  {
    num *= -1;
    low_zero = true;
  }
  while (num > 0) 
  {
    int ost = num % base;
    num /= base;
    if (ost >= 0 && ost <= 9) 
    {
      *ptr = ost + '0';
    } 
    else if (ost >= 10) 
    {
      *ptr = ost + 'A' - 10;
    }
    ptr--;
  }
  if (low_zero) 
  {
    *ptr = '-';
    ptr--;
  }
  ptr++;
  printf("%s\n", ptr);
}



int main() 
{
  int buf = BUFSIZ;
  char* str = (char*)malloc(sizeof(char) * buf); 
  if (str == NULL)
  {
    printf("Memory error");
  }
  else
  {
    long result = 0;
    switch ((find_max(&str, &buf, &result))) 
    {
      case fsc_invalid_base:
        printf("Invalid base\n");
        return -1;
      case fsc_invalid_srting:
        printf("Incorrect entered base\n");
        return -1;
      case fsc_ok:
        printf("All s OK\n");
        break;
      default:
        printf("Bye bye\n");
        return -1;
  }
  if (result)
  {
    for(int i = 9; i <= 36; i+= 9) 
    {
      show_number(result, i);
    }
  }
  }
  free(str);
  return 0;
}