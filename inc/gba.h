#ifndef GBA_H
#define GBA_H 1

#include <stdint.h>
#include <stdbool.h>

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 160

#define MEM_IO  0x4000000
#define MEM_VRAM  0x6000000
#define OAM 0x7000000

#define REG_DISPCNT (* (volatile uint16_t*) 0x4000000)
#define REG_DISPSTAT  (* (volatile uint16_t*) 0x4000004)
#define REG_VCOUNT  (* (volatile uint16_t*) 0x4000006)
#define REG_KEYINPUT  (* (volatile uint16_t*) 0x40000130)

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

#define SET_DISPLAY_MODE(mode)  REG_DISPCNT = (mode)

#define KEY_A 0x0001
#define KEY_B 0x0002
#define KEY_SELECT  0x0004
#define KEY_START 0x0008
#define KEY_RIGHT 0x0010
#define KEY_LEFT  0x0020
#define KEY_UP  0x0040
#define KEY_DOWN  0x0080
#define KEY_R 0x0100
#define KEY_L 0x0200

static uint32_t current_key = 0;
static uint32_t previous_key = 0;

inline void poll_key()
{
  previous_key = current_key;
  current_key = ~(REG_KEYINPUT) & 0x3FF;
}

inline uint32_t current_key_state()
{
  return current_key;
}

inline uint32_t previous_key_state()
{
  return previous_key;
}

inline bool is_key_down(uint32_t key)
{
  return (bool) current_key & key;
}

inline bool is_key_up(uint32_t key)
{
  return (bool) ~(current_key) & key;
}

inline bool was_key_down(uint32_t key)
{
  return (bool) previous_key & key;
}

inline bool was_key_up(uint32_t key)
{
  return (bool) ~(previous_key) & key;
}

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
