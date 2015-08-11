#include <stdlib.h>
#include "gba.h"
#include "player.h"

void update(Player* p1, Player* p2)
{
  uint32_t p1_x = get_paddle_x(p1);
  uint32_t p1_y = get_paddle_y(p1);
  m4_draw_rect_fill(p1_x, p1_y, p1_x + 10, p1_x + 50, 1);
}

int main()
{
  REG_DISPCNT = DCNT_BG2 | DCNT_MODE4;
  M4_PALETTE[0] = to_rgb16(255, 255, 255);
  M4_PALETTE[1] = to_rgb16(0, 0, 0);
  // TODO: initialize with random colors???
  M4_PALETTE[2] = to_rgb16(255, 0, 0);
  M4_PALETTE[3] = to_rgb16(0, 255, 0);
  M4_PALETTE[4] = to_rgb16(0, 0, 255);

  Player* player = create_player();
  Player* computer = create_player();
  uint32_t currentFrame = 0;
  while (1)
  {
    vsync();
    poll_key();
    if (is_key_down(KEY_DOWN))
    {
      set_paddle_y(player, get_paddle_y(player) + 10);
    }
    else if (is_key_down(KEY_UP))
    {
      set_paddle_y(player, get_paddle_y(player) - 10);
    }

    uint32_t p1_x = get_paddle_x(player);
    uint32_t p1_y = get_paddle_y(player);
    if (++currentFrame == 1)
    {
      currentFrame = 0;
    }

    flip_vid_page();
    m4_draw_rect_fill(p1_x, p1_y, p1_x + 5, p1_y + 5, 1);
  }

  free(player);
  free(computer);
  player = NULL;
  computer = NULL;
  return 0;
}
