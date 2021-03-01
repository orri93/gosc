#ifndef GOS_SCREEN_H_
#define GOS_SCREEN_H_

#include <stddef.h>

#include <gos/types.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t gos_screen_index(gos_screen* screen, int x, int y);

#ifdef __cplusplus
}
#endif

#endif
