#ifndef H_PLAYER
#define H_PLAYER  1

#include <stdint.h>

typedef struct {
  uint32_t x;
  uint32_t y;
  uint32_t score;
} Player;

/**
 * Create a player.
 * @param x Their starting x coordinate.
 * @param y Their starting y coordinate.
 * @return The player object.
 */
Player create_player(uint32_t x, uint32_t y);
/**
 * Set a player's x coordinate.
 * @param p The player.
 * @param new_x The new x coordinate.
 */
void set_paddle_x(Player* p, int32_t new_x);
/**
 * Set a player's y coordinate.
 * @param p The player.
 * @param new_y The new y coordinate.
 */
void set_paddle_y(Player* p, int32_t new_y);

#endif
