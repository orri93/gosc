#ifndef GOS_DYNAMIC_H_
#define GOS_DYNAMIC_H_

#include <stdbool.h>

#include <gos/types.h>

#ifdef __cplusplus
extern "C" {
#endif

bool gos_dynamic_double_array_initialize(
  gos_dynamic_double_array* a, size_t s);
bool gos_dynamic_double_array_initialize_zero(
  gos_dynamic_double_array* a, size_t s);

bool gos_dynamic_double_array_add(gos_dynamic_double_array* a, double v);

void gos_dynamic_double_array_shutdown(gos_dynamic_double_array* a);

#ifdef __cplusplus
}
#endif


#endif
