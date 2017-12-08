#include <stdlib.h>
#include <stdbool.h>
#include "gba.h"
#include "config.h"
#include "player.h"
#include "ball.h"

/**
 * Flag which is used to determine whether the player/omputer won a round.
 */
static bool restart = false;

void draw(Player* player, Player* computer, Ball* ball)
{
  m4_draw_rect_fill(player->x - PADDLE_WIDTH, player->y + PADDLE_HEIGHT, player->x, player->y, 4);
  m4_draw_rect_fill(computer->x, computer->y, computer->x + PADDLE_WIDTH, computer->y + PADDLE_HEIGHT, 2);
  m4_draw_circle_fill(ball->x, ball->y, BALL_RADIUS, 1);
  gba_printf(0, SCREEN_HEIGHT - 10, 4, "Score: %d", player->score);
  gba_printf(SCREEN_WIDTH - 32, SCREEN_HEIGHT - 10, 2, "Score: %d", computer->score);
}

/**
 * Handle collisions between the ball, player, computer, and boundaries.
 *
 * FIXME: Collision detection here is very basic and currently sucks.
 */
void check_collisions(Player* player, Player* computer, Ball* ball)
{
  // Ball is out of bounds on the computer's side.
  if (ball->x >= SCREEN_WIDTH)
  {
    player->score++;
    restart = true;
    return;
  }

  // Ball is out of bounds on the player's side.
  if (ball->x <= 0)
  {
    computer->score++;
    restart = true;
    return;
  }

  // Ball hitting top or bottom of screen.
  if (ball->y - BALL_RADIUS <= 0 || ball->y + BALL_RADIUS >= SCREEN_HEIGHT)
  {
    ball->dy *= -1;
    return;
  }

  // Ball hitting the top or bottom of player's paddle.
  if ((ball->y + BALL_RADIUS == player->y || ball->y - BALL_RADIUS == player->y + PADDLE_HEIGHT) &&
    (ball->x >= player->x && ball->x <= player->x + PADDLE_WIDTH))
  {
    ball->dy *= -1;
    return;
  }

  // Ball hitting the top or bottom of computer's paddle.
  if ((ball->y + BALL_RADIUS == computer->y || ball->y - BALL_RADIUS == computer->y + PADDLE_HEIGHT) &&
    (ball->x >= computer->x && ball->x <= computer->x + PADDLE_WIDTH))
  {
    ball->dy *= -1;
    return;
  }

  // Ball hitting player's paddle on the front.
  if (ball->x - BALL_RADIUS == player->x &&
    (ball->y >= player->y && ball->y <= player->y + PADDLE_HEIGHT)
  )
  {
    ball->dx *= -1;
    return;
  }

  // Ball hitting computer's paddle on the front.
  if (ball->x + BALL_RADIUS == computer->x &&
    (ball->y >= computer->y && ball->y <= computer->y + PADDLE_HEIGHT)
  )
  {
    ball->dx *= -1;
    return;
  }
}

void show_title_screen()
{
  // P
  m4_draw_rect_fill(50, 10, 55, 40, 1);
  m4_draw_rect_fill(55, 10, 70, 15, 1);
  m4_draw_rect_fill(70, 10, 75, 25, 1);
  m4_draw_rect_fill(55, 20, 70, 25, 1);
  // O
  m4_draw_rect_fill(80, 10, 85, 25, 1);
  m4_draw_rect_fill(100, 10, 105, 25, 1);
  m4_draw_rect_fill(80, 10, 105, 15, 1);
  m4_draw_rect_fill(80, 20, 105, 25, 1);
  // N
  m4_draw_rect_fill(110, 10, 115, 25, 1);
  m4_draw_rect_fill(130, 10, 135, 25, 1);
  m4_draw_rect_fill(110, 10, 135, 15, 1);
  // G
  m4_draw_rect_fill(140, 10, 145, 25, 1);
  m4_draw_rect_fill(145, 10, 160, 15, 1);
  m4_draw_rect_fill(160, 10, 165, 40, 1);
  m4_draw_rect_fill(145, 20, 160, 25, 1);
  m4_draw_rect_fill(140, 35, 160, 40, 1);

  // TODO: Newline characters need to be used instead.
  gba_printf(5, 50, 1, "You are the player on the left with");
  gba_printf(5, 60, 1, "the blue paddle. The computer is on");
  gba_printf(5, 70, 1, "the right with the red paddle. Your");
  gba_printf(5, 80, 1, "goal is to bounce the ball past the");
  gba_printf(5, 90, 1, "computer's paddle, scoring a point.");
  gba_printf(5, 100, 1, "Beware! The computer will also try to");
  gba_printf(5, 110, 1, "bounce the ball past your paddle!");
  gba_printf(10, 140, 2, "Press the Start button to begin.");
  do
  {
    poll_key();
  } while (!is_key_down(KEY_START));
}

int main()
{
  register_vblank_isr();
  initialize_text_writer();
  srand(RAND_SEED);
  REG_DISPCNT = DCNT_BG2 | DCNT_MODE4;
  // Initialize the palette with your basic RGB, black, and white colors.
  M4_PALETTE[0] = to_rgb16(255, 255, 255);
  M4_PALETTE[1] = to_rgb16(0, 0, 0);
  M4_PALETTE[2] = to_rgb16(255, 0, 0);
  M4_PALETTE[3] = to_rgb16(0, 255, 0);
  M4_PALETTE[4] = to_rgb16(0, 0, 255);

  show_title_screen();

  Player player = create_player(PADDLE_PLAYER_X, PADDLE_PLAYER_Y);
  Player computer = create_player(PADDLE_COMP_X, PADDLE_COMP_Y);
  Ball ball = create_ball();
  while (1)
  {
    vblank_intr_wait();
    poll_key();
    ball.x += ball.dx;
    ball.y += ball.dy;
    // This random formula I just made up seems to be good enough...
    set_paddle_y(&computer, (uint32_t) (ball.y + 10) * 0.75);
    if (is_key_down(KEY_DOWN))
    {
      set_paddle_y(&player, player.y + PLAYER_SPEED);
    }
    else if (is_key_down(KEY_UP))
    {
      set_paddle_y(&player, player.y - PLAYER_SPEED);
    }

    check_collisions(&player, &computer, &ball);
    if (restart)
    {
      set_default_ball_params(&ball);
      restart = false;
    }

    // Flip current page so we can begin drawing!
    flip_vid_page();
    draw(&player, &computer, &ball);
  }

  free_text_writer();
  return 0;
}
