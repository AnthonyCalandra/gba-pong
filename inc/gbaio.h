#ifndef GBAIO_H
#define GBAIO_H 1

#include <stdint.h>
#include <stdbool.h>

#define MEM_IO  0x4000000
#define REG_KEYINPUT  (* (volatile uint32_t*) 0x4000130)

/**
 * Key codes.
 */
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

/**
 * Maintain state of the current and previous keys in order to implement
 * key states (is up, is down, held, etc.).
 */
extern uint16_t _current_key;
extern uint16_t _previous_key;

/**
 * Poll user input asynchronously.
 */
inline uint32_t async_poll_key(uint32_t key)
{
  return ~(REG_KEYINPUT) & key;
}

/**
 * Poll user input synchronously.
 */
inline void poll_key()
{
  _previous_key = _current_key;
  // The bits in the REG_KEYINPUT register is set to high when a key is up and
  // low when a key is down.
  _current_key = ~(REG_KEYINPUT) & 0x03FF;
}

inline uint32_t current_key_state()
{
  return _current_key;
}

inline uint32_t previous_key_state()
{
  return _previous_key;
}

inline uint32_t is_key_down(uint32_t key)
{
  return _current_key & key;
}

inline uint32_t is_key_up(uint32_t key)
{
  return ~(_current_key) & key;
}

inline uint32_t was_key_down(uint32_t key)
{
  return _previous_key & key;
}

inline uint32_t was_key_up(uint32_t key)
{
  return ~(_previous_key) & key;
}

inline uint32_t is_key_transition(uint32_t key)
{
  return (_current_key ^ _previous_key) & key;
}

inline uint32_t is_key_held(uint32_t key)
{
  return (_current_key & _previous_key) & key;
}

inline uint32_t is_key_hit(uint32_t key)
{
  return (_current_key & ~(_previous_key)) & key;
}

/**
 * Credit to TONC for the font system.
 */
typedef struct
{
  volatile uint16_t* dst;
  uint32_t* font;
  uint8_t* char_map;
  uint8_t* char_width;
  int8_t dx, dy;
  uint16_t flags;
} TextWriter;

extern uint8_t txt_lut[256];
extern TextWriter* gptxt;

/**
 * Initializes the font and text writer. Use free_text_writer to free the
 * memory allocated by this function.
 */
void initialize_text_writer();
/**
 * Similar to printf in the C Standard Library, with the exception that it prints
 * to the game canvas.
 * @param x The x coordinate to begin drawing.
 * @param y The y coordinate to begin drawing.
 * @param color_index The color located at the index in the palette table to use.
 * @param format The string format; same as the Standard Library's printf format.
 * @param ... Arguments to the format.
 */
void gba_printf(int32_t x, int32_t y, uint8_t color_index, const char* format, ...);
/**
 * Frees the font and text writer memory. Should always be called before the
 * game ends.
 */
void free_text_writer();

#endif
