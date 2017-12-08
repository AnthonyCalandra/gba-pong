#ifndef H_BALL
#define H_BALL 1

#include <stdint.h>

typedef struct {
  int32_t x;
  int32_t y;
  int32_t dx;
  int32_t dy;
} Ball;

/**
 * Create the game's ball object.
 * @return The new game ball.
 */
Ball create_ball();
/**
 * Set some parameters on the game ball.
 * @param ball Pointer to the game ball.
 */
void set_default_ball_params(Ball* ball);

#endif
