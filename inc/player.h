#ifndef H_PLAYER
#define H_PLAYER  1

#include <stdint.h>

typedef struct {
  uint32_t paddle_x;
  uint32_t paddle_y;
  uint32_t score;
} Player;

Player* create_player();
uint32_t get_paddle_x(Player* p);
void set_paddle_x(Player* p, int32_t new_x);
uint32_t get_paddle_y(Player* p);
void set_paddle_y(Player* p, int32_t new_y);
uint32_t get_score(Player* p);
void set_score(Player* p, uint32_t new_score);

#endif