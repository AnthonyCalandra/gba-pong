#include <stdint.h>
#include <stdlib.h>
#include "gba.h"
#include "player.h"

Player* create_player()
{
  Player* p = (Player*) malloc(sizeof(Player));
  p->paddle_x = 25;
  p->paddle_y = 60;
  p->score = 0;
  return p;
}

uint32_t get_paddle_x(Player* p)
{
  return p->paddle_x;
}

void set_paddle_x(Player* p, int32_t new_x)
{
  new_x = CLAMP(new_x, 0, SCREEN_WIDTH);
  p->paddle_x = new_x;
}

uint32_t get_paddle_y(Player* p)
{
  return p->paddle_y;
}

void set_paddle_y(Player* p, int32_t new_y)
{
  new_y = CLAMP(new_y, 0, SCREEN_HEIGHT);
  p->paddle_y = new_y;
}

uint32_t get_score(Player* p)
{
  return p->score;
}

void set_score(Player* p, uint32_t new_score)
{
  p->score += new_score;
}
