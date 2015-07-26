#include "gba.h"

int main(){

  REG_DISPCNT = DCNT_BG2 | DCNT_MODE3;

  for (uint32_t x = 0; x < SCREEN_WIDTH; x++) {
    for (uint32_t y = 0; y < SCREEN_HEIGHT; y++) {
      VIDEO_BUFFER[y*SCREEN_WIDTH + x] = to_rgb16(255, 255, 255);
    }
  }

  while(1);

  return 0;
}
