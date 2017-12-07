#include <stdlib.h>
#include <stdint.h>
#include "ball.h"
#include "config.h"

Ball create_ball(uint32_t x, uint32_t y)
{
  Ball ball;
  set_default_ball_params(&ball, x, y);
  return ball;
}

void set_default_ball_params(Ball* ball, uint32_t x, uint32_t y)
{
  ball->x = x;
  ball->y = y;
  // FIXME: % is SLOW!!!
  ball->dx = (rand() % 3 + 1);
  ball->dy = (rand() % 3 + 1);
  // Randomly select a side.
  ball->dx *= (rand() % 2) ? 1 : -1;
  ball->dy *= (rand() % 2) ? 1 : -1;
}
