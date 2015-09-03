#include <stdint.h>
#include <stdlib.h>
#include "gbautils.h"
#include "config.h"
#include "player.h"

Player* create_player(uint32_t x, uint32_t y)
{
  Player* p = (Player*) malloc(sizeof(Player));
  p->x = x;
  p->y = y;
  p->score = 0;
  return p;
}

void set_paddle_x(Player* p, int32_t new_x)
{
  new_x = CLAMP(new_x, 0, SCREEN_WIDTH - PADDLE_WIDTH);
  p->x = new_x;
}

void set_paddle_y(Player* p, int32_t new_y)
{
  new_y = CLAMP(new_y, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
  p->y = new_y;
}
