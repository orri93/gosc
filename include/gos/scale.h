#ifndef GOS_SCALE_H_
#define GOS_SCALE_H_

#include <gos/types.h>

#ifdef __cplusplus
extern "C" {
#endif

double gos_scale_value(gos_scale* scale, double value);
double gos_scale_reverse(gos_scale* scale, double value);

#ifdef __cplusplus
}
#endif

#endif
