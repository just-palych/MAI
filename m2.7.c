#include <stdio.h>
#include "math.h"


int dichotomy(double* res, double left_bound, double right_bound, double eps, double (*func)(double)) {
  if (func(left_bound) * func(right_bound) > 0) {
    *res = 0;
    return 1;
  }
  if(eps <= 0){
    return 2;
  }
  double mid;
  double f_mid;
  do {
    mid = (left_bound + right_bound) / 2;
    f_mid = func(mid);
    if (f_mid * (func(left_bound)) > 0) {
      left_bound = mid;
    }
    if (f_mid * (func(right_bound)) > 0) {
      right_bound = mid;
    }
  } while (fabs(f_mid) > eps);
  *res = mid;

  return 0;
}

double own(double x)
{
  return x * x - 2;
}

int main() {
  double res;
  dichotomy(&res, 1, 2, 1e-8, own);
  printf("%lf", res);
  return 0;
}