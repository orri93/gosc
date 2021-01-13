#include <gos/screen.h>

int gos_screen_index(gos_screen* screen, int x, int y) {
  return x + y * screen->width;
}
