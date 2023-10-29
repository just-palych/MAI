#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>
#include <malloc.h>

double m_eps() {
  int i = 0;
  double eps = 1.0;

  while (1.0f + eps > 1.0f) {
    eps = eps / 2.0f;
    i++;
  }
  return eps;
}

unsigned long long gcd(unsigned long long a, unsigned long long b) {
  if (a % b == 0) {
    return b;
  }
  if (b % a == 0) {
    return a;
  }
  if (a > b) {
    return gcd(a % b, b);
  }
  return gcd(a, b % a);
}

bool check_base(double num, unsigned int base, double eps) {
  if (base < 2) {
    return 0;
  }
  if (num <= 0 || num >= 1) {
    return 0;
  }

  eps = m_eps();
  unsigned long long denom = 1, numer = 1;
  while (fabs(num - floor(num)) >= eps) {
    denom *= 10;
    num *= 10;
    numer = floor(num);
  }
  denom = denom / gcd(denom, numer);

  unsigned int t_base = base;
  while (t_base < denom) {
    t_base *= base;
  }

  if (t_base == denom) {
    return true;
  }

  return false;
}

int check_base_multiple_nums(int** result, int count, unsigned int base, ...) {
  *result = (int*) malloc(sizeof(int) * count);
  if(*result == NULL){
    return -1;
  }
  va_list a;
  va_start(a, base);
  double eps = m_eps();
  for (int i = 0; i < count; i++) {
    double temp = va_arg(a, double);
    (*result)[i] = check_base(temp, base, eps);
  }
  va_end(a);
  return 0;
}




void print_arr(int const* arr, size_t count) {
  for (int i = 0; i < count; i++) {
    printf("%s ", arr[i] ? "yes" : "no");
  }
  putchar('\n');
}

int main() {
  int* result;
  if (check_base_multiple_nums(&result, 4, 5, (double) 0.2, (double) 0.4, (double) 0.3, (double) 0.24) == 0) {
    print_arr(result, 4);
    free(result);
  }

  if (check_base_multiple_nums(&result, 4, 2, (double) 0.2, (double) 0.4, (double) 0.3, (double) 0.24) == 0) {
    print_arr(result, 4);
    free(result);
  }

  if (check_base_multiple_nums(&result, 4, 10, (double) 0.125, (double) 0.625, (double) 0.5, (double) 0.25) == 0) {
    print_arr(result, 4);
    free(result);
  }

  return 0;
}