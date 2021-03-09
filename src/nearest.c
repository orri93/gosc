#include <math.h>

#include <gos/nearest.h>

double gos_nearest_neighbor(double first, double second, double value) {
  double fd = fabs(first - value);
  double sd = fabs(second - value);
  return fd - sd;
}

#ifdef GOSC_NEAREST_NEIGHBOR_TIME_
time_t gos_nearest_neighbor_time(time_t first, time_t second, time_t value) {
  time_t fd = llabs(first - value);
  time_t sd = llabs(second - value);
  return fd - sd;
}
#endif
