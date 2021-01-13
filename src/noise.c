#include <stdlib.h>

#include <gos/noise.h>

// Hashing
#define GOS_NOISE_X_PRIME 1619
#define GOS_NOISE_Y_PRIME 31337

int gos_noise_random_maximum_integer(int maximum) {
  return (int)(((long)maximum * (long)rand()) / RAND_MAX);
}

double gos_noise_white(int seed, int x, int y) {
  int n;
  long l;
  n = seed;
  n ^= GOS_NOISE_X_PRIME * x;
  n ^= GOS_NOISE_Y_PRIME * y;
  l = n * n * n * 60493;
  return (double)l / 2147483648.0;
}
