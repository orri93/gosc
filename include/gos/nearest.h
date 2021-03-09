#ifndef GOS_NEAREST_H_
#define GOS_NEAREST_H_

#ifdef GOSC_NEAREST_NEIGHBOR_TIME_
#include <time.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

double gos_nearest_neighbor(double first, double second, double value);

#ifdef GOSC_NEAREST_NEIGHBOR_TIME_
time_t gos_nearest_neighbor_time(time_t first, time_t second, time_t value);
#endif

#ifdef __cplusplus
}
#endif

#endif
