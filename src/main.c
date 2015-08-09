#include "gba.h"

int main()
{
  REG_DISPCNT = DCNT_BG2 | DCNT_MODE4;
  M4_PALETTE[0] = to_rgb16(255, 255, 255);
  M4_PALETTE[1] = to_rgb16(0, 0, 0);
  // TODO: initialize with random colors???
  M4_PALETTE[2] = to_rgb16(255, 0, 0);
  M4_PALETTE[3] = to_rgb16(0, 255, 0);
  M4_PALETTE[4] = to_rgb16(0, 0, 255);

  m4_draw_line(10, 10, -50, -50, 1);
  m4_draw_rect_fill(100, 100, 300, 300, 3);
  m4_draw_triangle_fill(230, 170, 10, 10, 3, 4);
  m4_draw_triangle(0, 0, 10, 10, 0, 4);

  while(1);

  return 0;
}
