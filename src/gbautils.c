#include <stdint.h>
#include <stdbool.h>
#include "gbautils.h"
#include "gbagraphics.h"

bool within_screen_bounds(uint32_t x, uint32_t y)
{
  return x < SCREEN_WIDTH && y < SCREEN_HEIGHT;
}
