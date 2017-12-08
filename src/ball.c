#include <stdlib.h>
#include <stdint.h>
#include "ball.h"
#include "config.h"
#include "gbagraphics.h"

Ball create_ball()
{
  Ball ball;
  set_default_ball_params(&ball);
  return ball;
}

void set_default_ball_params(Ball* ball)
{
  ball->x = SCREEN_WIDTH >> 1;
  ball->y = SCREEN_HEIGHT >> 1;
  ball->dx = (rand() % 3 + 1);
  ball->dy = (rand() % 3 + 1);
  // Randomly select a side.
  ball->dx *= (rand() % 2) ? 1 : -1;
  ball->dy *= (rand() % 2) ? 1 : -1;
}
