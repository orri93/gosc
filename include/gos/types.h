#ifndef GOS_TYPES_H_
#define GOS_TYPES_H_

#include <stdint.h>
#include <time.h>

typedef struct gos_point_2d {
  double x;
  double y;
} gos_point_2d;

typedef struct gos_point_3d {
  double x;
  double y;
  double z;
} gos_point_3d;

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

typedef struct gos_point_2d_vector {
  gos_point_2d* points;
  int count;
} gos_point_2d_vector;

typedef struct gos_point_3d_vector {
  gos_point_3d* points;
  int count;
} gos_point_3d_vector;

typedef struct gos_matrix {
  double** data;
  int countd1;
  int countd2;
} gos_matrix;

typedef struct gos_time_series {
  time_t time;
  void* data;
} gos_time_series;

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

/* Dynamic */
typedef struct gos_dynamic_double_array {
  double* items;
  size_t used;
  size_t size;
} gos_dynamic_double_array;

/* Scale */
typedef struct gos_scale {
  gos_range_1d domain;
  gos_range_1d range;
} gos_scale;

/* Screen */
typedef struct gos_screen {
  int width;
  int height;
} gos_screen;

#endif
