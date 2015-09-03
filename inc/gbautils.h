#ifndef UTILS_H
#define UTILS_H 1

#include <stdint.h>
#include <stdbool.h>
#include "gbagraphics.h"

/**
 * Clamp a value, n, between a and b.
 */
#define CLAMP(n, a, b) (((n) < (a) ? (a) : (n)) > (b) ? (b) : ((n) < (a) ? (a) : (n)))

/**
 * Utility function that checks if a given coordinate is within screen bounds.
 * @param x The x coordinate.
 * @param y The y coordinate.
 * @return True if the point is within screen bounds.
 */
bool within_screen_bounds(uint32_t x, uint32_t y);

#endif
