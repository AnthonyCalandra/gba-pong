#ifndef GBAIO_H
#define GBAIO_H 1

#include <stdint.h>
#include <stdbool.h>

#define MEM_IO  0x4000000
#define REG_KEYINPUT  (* (volatile uint32_t*) 0x40000130)

// Key codes.
#define KEY_A 0x1
#define KEY_B 0x2
#define KEY_SELECT  0x4
#define KEY_START 0x8
#define KEY_RIGHT 0x10
#define KEY_LEFT  0x20
#define KEY_UP  0x40
#define KEY_DOWN  0x80
#define KEY_R 0x100
#define KEY_L 0x200

// Maintain state of the current and previous keys in order to implement
// key states (is up, is down, held, etc.).
static uint32_t current_key = 0;
static uint32_t previous_key = 0;

/*
 * This function polls user input synchronously.
 */
inline void poll_key()
{
  previous_key = current_key;
  // The bits in the REG_KEYINPUT register is set to high when a key is up and
  // low when a key is down.
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
