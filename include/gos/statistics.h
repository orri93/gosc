#ifndef GOS_STATISTICS_H_
#define GOS_STATISTICS_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

double gos_statistics_sum(double* i, size_t s);
double gos_statistics_sd(double* i, double a, size_t s);

#ifdef __cplusplus
}
#endif

#endif
