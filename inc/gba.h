#ifndef GBA_H
#define GBA_H 1

#include <stdint.h>

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 160

#define MEM_IO  0x4000000
#define MEM_VRAM  0x6000000
#define OAM 0x7000000

#define REG_DISPCNT (* (volatile uint16_t*) 0x4000000)
#define REG_DISPSTAT  (* (volatile uint16_t*) 0x4000004)
#define REG_VCOUNT  (* (volatile uint16_t*) 0x4000006)

#define VIDEO_BUFFER ((uint16_t*) MEM_VRAM)

#define DCNT_MODE0  0
#define DCNT_MODE1  1
#define DCNT_MODE2  2
#define DCNT_MODE3  3
#define DCNT_MODE4  4
#define DCNT_MODE5  5

#define DCNT_BG0  0x100
#define DCNT_BG1  0x200
#define DCNT_BG2  0x400
#define DCNT_BG3  0x800
#define DCNT_OBJ  0x1000

#define SetDisplayMode(mode)  REG_DISPCNT = (mode)

typedef union {
  uint16_t rgb;
  struct {
    uint8_t red : 5;
    uint8_t green : 5;
    uint8_t blue : 5;
    uint8_t unused : 1;
  } __attribute__((packed));
} RGB16;

inline uint16_t toRGB16(uint16_t rgb) {
  RGB16 color;
  color.rgb = rgb;
  return color.rgb;
}

inline uint16_t toRGB16(uint8_t red, uint8_t green, uint8_t blue) {
  RGB16 color;
  color.red = red;
  color.green = green;
  color.blue = blue;
  return color.rgb;
}

#endif
