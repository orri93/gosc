#ifndef GOS_TYPES_H_
#define GOS_TYPES_H_

#include <stdint.h>

typedef struct gos_point_2d {
  double x;
  double y;
} gos_point_2d;

typedef struct gos_range_1d {
  double from;
  double to;
} gos_range_1d;

typedef struct gos_range_2d {
  gos_range_1d first;
  gos_range_1d second;
} gos_range_2d;

typedef struct gos_generation_1d {
  gos_range_1d range;
  double noise;
} gos_generation_1d;

typedef struct gos_vector {
  double* data;
  int count;
} gos_vector;

typedef struct gos_matrix {
  double** data;
  int countd1;
  int countd2;
} gos_matrix;

typedef struct gos_color {
  double a;
  double b;
  double c;
} gos_color;

typedef struct gos_rgb {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} gos_rgb;

typedef struct gos_rgb_gradient {
  gos_rgb* gradient;
  int count;
} gos_rgb_gradient;

#endif
