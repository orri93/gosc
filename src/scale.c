#include <gos/scale.h>

#include <gos/geometry.h>

double gos_scale_value(gos_scale* scale, double value) {
  double dd = gos_geometry_distance_1d(&scale->domain);
  double rd = gos_geometry_distance_1d(&scale->range);
  double r = (value - scale->domain.from) / dd;
  return scale->range.from + r * rd;
}

double gos_scale_reverse(gos_scale* scale, double value) {
  double dd = gos_geometry_distance_1d(&scale->domain);
  double rd = gos_geometry_distance_1d(&scale->range);
  double r = (value - scale->range.from) / rd;
  return scale->domain.from + r * dd;
}
