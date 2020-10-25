#include <math.h>

#include <gos/statistics.h>

double gos_statistics_sum(double* i, size_t s) {
  size_t n;
  double sum = 0.0;
  for (n = 0; n < s; n++) {
    sum += i[n];
  }
  return sum;
}

double gos_statistics_sd(double* i, double a, size_t s) {
  size_t n;
  double d, sds = 0.0;
  for (n = 0; n < s; n++) {
    d = i[n] - a;
    sds += d * d;
  }
  return sqrt(sds / ((double)s));
}
