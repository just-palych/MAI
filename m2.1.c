#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


typedef enum {
  fsc_ok,
  fsc_inv_num_arg,
  fsc_inv_flag,
  fsc_un_flag,
  fsc_inv_num,
  fsc_mem_er
} function_status_code;

function_status_code flag_compare(int argc, char* argv[]);

function_status_code l_fl(int argc, char* argv[]);
function_status_code r_fl(int argc, char* argv[]);
function_status_code u_fl(int argc, char* argv[]);
function_status_code n_fl(int argc, char* argv[]);
function_status_code c_fl(int argc, char* argv[]);


unsigned long long str_length(const char* str) {
  if (str == NULL) {
    return 0;
  }
  unsigned long long size = 0;
  for (; str[size] != 0; size++);
  return size;
}


int reverse_str(const char* buf, char* value) {
  if (buf == NULL || value == NULL) {
    return -1;
  }

  unsigned long long len = str_length(buf);
  for (int i = 0; i <= len / 2; i++) {
    value[i] = buf[len - 1 - i];
    value[len - 1 - i] = buf[i];
  }
  value[len] = '\0';
  return 0;
}

int str_register(const char* buf, char* value) {
  if (buf == NULL || value == NULL) {
    return -1;
  }
  unsigned long long i = 0;
  for (; buf[i] != '\0'; i++) {
    if (i & 1) {
      value[i] = toupper(buf[i]);
    } else {
      value[i] = buf[i];
    }
  }
  value[i] = '\0';
  return 0;
}

function_status_code l_fl(int argc, char* argv[]) {
  if (argc != 3) {
    return fsc_inv_num_arg;
  }

  printf("Length =  %lld\n", str_length(argv[2]));
  return fsc_ok;
}

function_status_code r_fl(int argc, char* argv[]) {
  if (argc != 3) {
    return fsc_inv_num_arg;
  }
  char* string = (char*) malloc(sizeof(char) * (str_length(argv[2]) + 1));
  if (string == NULL) {
    return fsc_mem_er;
  }
  reverse_str(argv[2], string);
  printf("Final string: %s\n", string);
  free(string);
  return fsc_ok;
}

function_status_code u_fl(int argc, char* argv[]) {
  if (argc != 3) {
    return fsc_inv_num_arg;
  }
  char* string = (char*) malloc(sizeof(char) * (str_length(argv[2]) + 1));
  if (string == NULL) {
    return fsc_mem_er;
  }
  str_register(argv[2], string);
  printf("Final string: %s\n", string);
  free(string);
  return fsc_ok;
}


function_status_code flag_compare(int argc, char* argv[]) {
  char* flag = argv[1] + 1;
  if (flag[0] == 0 || flag[1] != 0) {
    return fsc_un_flag;
  }
  switch (*flag) {
    case 'l':
      return l_fl(argc, argv);
    case 'r':
      return r_fl(argc, argv);
    case 'u':
      return u_fl(argc, argv);
    case 'n':
      return n_fl(argc, argv);
    case 'c':
      return c_fl(argc, argv);
  }
  return fsc_un_flag;
}


int str_shuffle(const char* buf, char* value) {
  if (buf == NULL || value == NULL) {
    return -1;
  }
  int count = 0;
  for (int i = 0; buf[i] != '\0'; i++) {
    if (isdigit(buf[i])) {
      value[count++] = buf[i];
    }
  }
  for (int i = 0; buf[i] != '\0'; i++) {
    if (isalpha(buf[i])) {
      value[count++] = buf[i];
    }
  }
  for (int i = 0; buf[i] != '\0'; i++) {
    if (!isalnum(buf[i])) {
      value[count++] = buf[i];
    }
  }
  value[count] = '\0';
  return 0;
}

function_status_code n_fl(int argc, char* argv[]) {
  if (argc != 3) {
    return fsc_inv_num_arg;
  }
  char* string = (char*) malloc(sizeof(char) * (str_length(argv[2]) + 1));
  if (string == NULL) {
    return fsc_mem_er;
  }
  str_shuffle(argv[2], string);
  printf("Final string: %s\n", string);
  free(string);
  return fsc_ok;
}

char* str_cpy(const char* buf, char* value) {
  int i = 0;
  for (; buf[i] != '\0'; i++) {
    value[i] = buf[i];
  }
  value[i] = '\0';
  return value + i;
}


int rand_comp(const void* i, const void* j) {
  return rand() % 2 ? 1 : -1;
}

int cat_string_rand_order(int seed, char* strings_arr[], int str_cnt, char* value) {
  srand(seed);
  char** arr = (char**) malloc(sizeof(char*) * str_cnt);
  if (arr == NULL) {
    return -1;
  }
  for (int i = 0; i < str_cnt; i++) {
    arr[i] = strings_arr[i];
  }

  qsort(arr, str_cnt, sizeof(char*), rand_comp);
  *value = '\0';
  char* ptr = value;
  for (int i = 0; i < str_cnt; i++) {
    ptr = str_cpy(arr[i], ptr);
  }
  free(arr);
  return 0;
}

function_status_code num(char *str)
{
    for (int i = 0; i < str_length(str); i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return 1;
        }
        return 0;
    } 
}

function_status_code c_fl(int argc, char* argv[]) {
  if (argc <= 3) {
    return fsc_inv_num_arg;
  }

  if (num(argv[2])) {
    return fsc_inv_num;
  }
  int seed = strtol(argv[2], NULL, 10);
  unsigned long long size = 0;
  for (int i = 3; i < argc; i++) {
    size += str_length(argv[i]);
  }
  char* string = (char*) malloc(sizeof(char) * (size + 1));
  if (string == NULL) {
    return fsc_mem_er;
  }

  if(cat_string_rand_order(seed, argv + 3, argc - 3, string) == 0) {
    printf("Finaal string: %s\n", string);
  }

  free(string);
  return fsc_ok;
}

function_status_code input(int argc, char* argv[]) {
  if (argc <= 2) {
    return fsc_inv_num_arg;
  }
  if (argv[1][0] != '-' && argv[1][0] != '/' ) {
    return fsc_inv_flag;
  }

  return flag_compare(argc, argv);
}


int main(int argc, char* argv[]) {

  switch (input(argc, argv)) {
    case fsc_ok:
      printf("All is ok\n");
      break;
    case fsc_inv_flag:
      printf("Invalid flag\n");
      break;
    case fsc_inv_num_arg:
      printf("Invalid number of arg\n");
      break;
    case fsc_inv_num:
      printf("Invalid number\n");
      break;
    case fsc_un_flag:
      printf("Flag is not described\n");
      break;
    default:
      printf("Unknown error\n");
  }
  return 0;
}