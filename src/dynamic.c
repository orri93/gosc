#include <stdlib.h>

#include <gos/dynamic.h>

#ifndef GOS_DOUBLE_ARRAY_GROW
#define GOS_DOUBLE_ARRAY_GROW 2
#endif

bool gos_dynamic_double_array_initialize(
  gos_dynamic_double_array* a, size_t s) {
  a->used = 0;
  a->items = (double*)malloc(s * sizeof(double));
  if (a->items != NULL) {
    a->size = s;
    return true;
  } else {
    a->size = 0;
    return false;
  }
}

bool gos_dynamic_double_array_initialize_zero(
  gos_dynamic_double_array* a, size_t s) {
  a->used = 0;
  a->items = (double*)calloc(s, sizeof(double));
  if (a->items != NULL) {
    a->size = s;
    return true;
  } else {
    a->size = 0;
    return false;
  }
}

bool gos_dynamic_double_array_add(gos_dynamic_double_array* a, double v) {
  double* o;
  size_t ns;
  if (a->used >= a->size) {
    o = a->items;
    ns = GOS_DOUBLE_ARRAY_GROW * a->size;
    a->items = (double*)realloc(o, ns * sizeof(double));
    if (a->items != NULL) {
      a->size = ns;
    } else {
      a->items = o;
      return false;
    }
  }
  a->items[a->used++] = v;
  return true;
}

void gos_dynamic_double_array_shutdown(gos_dynamic_double_array* a) {
  if (a->items != NULL) {
    free(a->items);
    a->items = NULL;
  }
  a->used = 0;
  a->size = 0;
}
