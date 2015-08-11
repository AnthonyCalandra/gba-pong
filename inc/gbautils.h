#ifndef UTILS_H
#define UTILS_H 1

#include <stdint.h>
#include <stdbool.h>
#include "gbagraphics.h"

#define CLAMP(n, a, b) (((n) < (a) ? (a) : (n)) > (b) ? (b) : ((n) < (a) ? (a) : (n)))

inline bool within_screen_bounds(uint32_t x, uint32_t y)
{
  return x < SCREEN_WIDTH && y < SCREEN_HEIGHT;
}

#endif