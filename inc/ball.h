#ifndef H_BALL
#define H_BALL 1

#include <stdint.h>

typedef struct {
  uint32_t x;
  uint32_t y;
  int32_t dx;
  int32_t dy;
} Ball;

/**
 * Create the game's ball object.
 * @param x The x coordinate.
 * @param y The y coordinate.
 * @return The new game ball.
 */
Ball* create_ball(uint32_t x, uint32_t y);
/**
 * Set some parameters on the game ball.
 * @param ball Pointer to the game ball.
 * @param x The x coordinate.
 * @param y The y coordinate.
 */
void set_default_ball_params(Ball* ball, uint32_t x, uint32_t y);

#endif
