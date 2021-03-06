#ifndef GOS_NEAREST_H_
#define GOS_NEAREST_H_

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

double gos_nearest_neighbor(double first, double second, double value);
time_t gos_nearest_neighbor_time(time_t first, time_t second, time_t value);

#ifdef __cplusplus
}
#endif

#endif
