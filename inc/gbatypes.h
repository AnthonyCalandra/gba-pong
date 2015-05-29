#ifndef GBATYPES_H
#define GBATYPES_H  1

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

inline uint16_t to_rgb16(uint16_t rgb)
{
  RGB16 color;
  color.rgb = rgb;
  return color.rgb;
}

inline uint16_t to_rgb16(uint8_t red, uint8_t green, uint8_t blue)
{
  RGB16 color;
  color.red = red;
  color.green = green;
  color.blue = blue;
  return color.rgb;
}

#endif
