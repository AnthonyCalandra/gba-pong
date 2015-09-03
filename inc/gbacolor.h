#ifndef GBACOLOR_H
#define GBACOLOR_H  1

#include <stdint.h>

/**
 * The GBA stores red, green, and blue color components as 5-bits each and in
 * BGR format. The 16th bit is unused. Can be accessed through its individual
 * color components or as a single, packed 16-bit value.
 */
typedef union
{
  uint16_t rgb;
  struct
  {
    uint8_t red : 5;
    uint8_t green : 5;
    uint8_t blue : 5;
    uint8_t unused : 1;
  } __attribute__((packed));
} RGB16;

/**
 * This function sets an RGB color by a packed red, green, and blue value.
 *
 * @return The color as an RGB16 structure.
 */
inline uint16_t to_rgb16_packed(uint16_t rgb)
{
  RGB16 color;
  color.rgb = rgb;
  return color.rgb;
}

/**
 * This function sets an RGB color by its red, green, and blue components.
 *
 * @return The color as an RGB16 structure.
 */
inline uint16_t to_rgb16(uint8_t red, uint8_t green, uint8_t blue)
{
  RGB16 color;
  color.red = red;
  color.green = green;
  color.blue = blue;
  return color.rgb;
}

typedef uint8_t RGB8;

#endif
