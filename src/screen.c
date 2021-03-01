#include <gos/screen.h>

size_t gos_screen_index(gos_screen* screen, int x, int y) {
  return x + y * ((size_t)screen->width);
}
