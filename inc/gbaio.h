#ifndef GBAIO_H
#define GBAIO_H 1

#include <stdint.h>
#include <stdbool.h>

#define KEY_A 0x0001
#define KEY_B 0x0002
#define KEY_SELECT  0x0004
#define KEY_START 0x0008
#define KEY_RIGHT 0x0010
#define KEY_LEFT  0x0020
#define KEY_UP  0x0040
#define KEY_DOWN  0x0080
#define KEY_R 0x0100
#define KEY_L 0x0200

static uint32_t current_key = 0;
static uint32_t previous_key = 0;

inline void poll_key()
{
  previous_key = current_key;
  current_key = ~(REG_KEYINPUT) & 0x3FF;
}

inline uint32_t current_key_state()
{
  return current_key;
}

inline uint32_t previous_key_state()
{
  return previous_key;
}

inline bool is_key_down(uint32_t key)
{
  return (bool) current_key & key;
}

inline bool is_key_up(uint32_t key)
{
  return (bool) ~(current_key) & key;
}

inline bool was_key_down(uint32_t key)
{
  return (bool) previous_key & key;
}

inline bool was_key_up(uint32_t key)
{
  return (bool) ~(previous_key) & key;
}

#endif
