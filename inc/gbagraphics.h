#ifndef GBAGRAPHICS_H
#define GBAGRAPHICS_H 1

#include <stdint.h>
#include "gbaio.h"

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 160

/**
 * Video Memory.
 */
#define MEM_VRAM_ADDR  0x6000000
#define MEM_VRAM ((volatile uint16_t*) MEM_VRAM_ADDR)
/**
 * Object Attribute Memory (OAM) holds a sprite's attributes. See OAMEntryA.
 */
#define OAM 0x7000000

/**
 * The Register Vertical Count keeps track of the current scanline being drawn
 * by the GBA. Note that it includes the VBlank section as well, making the range
 * of vertical_count: [0, 227].
 *
 * NOTE: The last 8 bits are unused.
 */
#define REG_VCOUNT_ADDR  0x4000006
#define REG_VCOUNT (* (volatile uint16_t*) REG_VCOUNT_ADDR)

/**
 * The Register Display Controller is responsible for the graphical settings
 * of the GBA. The following is a short description of each of its fields:
 *   - [0-2] video_mode: set 0-2 for tiled modes; 3-5 for bitmapped modes.
 *   - [3] is_gbc_cartridge: read-only flag; set high is GBC or low for GBA.
 *   - [4] page_select: select buffer to show on screen (modes 4 and 5 only support page flipping).
 *   - [5] allow_oam_hblank: if flag set high, allow OAM access in HBlank.
 *   - [6] obj_mapping_mode: set flag high for 1D memory layout of tiles; low for 2D.
 *   - [7] force_screen_blank: if flag set high, clear screen.
 *   - [8-C] bg_renders: enable rendering of corresponding bg (0-3) and sprites.
 *   - [D-F] window_renders: enable use of windows 1/2, and object window, respectively.
 */
#define REG_DISPCNT_ADDR 0x4000000
#define REG_DISPCNT (* (volatile uint16_t*) REG_DISPCNT_ADDR)
#define DISPCNT_TOGGLE_PAGE 16
#define M4_PAGE1 ((void*) 0x6000000)
#define M4_PAGE2 ((void*) 0x600A000)
#define M4_PAGE_SIZE_IN_WORDS (0x2800)

/**
 * The Register Display Status contains information related to the drawing status
 * of the GBA. The following is a short description of each of its fields:
 *   - [0] in_vblank: read-only; set high if the GBA is in the VBlank section.
 *   - [1] in_hblank: read-only; set high if the GBA is in the HBlank section.
 *   - [2] in_trigger: read-only; set high if current scanline == scanline trigger.
 *   - [3] vblank_interrupt_req: if set high, interrupt fired at VBlanks.
 *   - [4] hblank_interrupt_req: if set high, interrupt fired at HBlanks.
 *   - [5] vcount_interrupt_req: if set high, fire interrupt if current scanline == scanline trigger.
 *   - [6-7] unused.
 *   - [8-F] vcount_trigger: VCount trigger value.
 */
#define REG_DISPSTAT_ADDR  0x4000004
#define REG_DISPSTAT (* (volatile uint16_t*) REG_DISPSTAT_ADDR)

/**
 * Pointer to the mode 4, 256 byte-sized, palette.
 */
#define M4_PALETTE ((uint16_t*) 0x5000000)

/**
 * Display modes:
 *   - Modes 0-2: Sprite modes.
 *   - Modes 3-5: Bitmap modes.
 * Use by setting REG_DISPCNT to desired mode.
 */
#define DCNT_MODE0  0
#define DCNT_MODE1  1
#define DCNT_MODE2  2
#define DCNT_MODE3  3
#define DCNT_MODE4  4
#define DCNT_MODE5  5

#define DCNT_BG0  0x100
#define DCNT_BG1  0x200
#define DCNT_BG2  0x400
#define DCNT_BG3  0x800
#define DCNT_OBJ  0x1000

#define ROTATE_0_DEG  0
#define ROTATE_90_DEG 1
#define ROTATE_180_DEG 2
#define ROTATE_270_DEG 3
#define ROTATE_360_DEG 0

/**
 * Pointer to video memory in 16-bit chunks.
 */
typedef volatile uint16_t* VideoBuffer;
extern VideoBuffer _video_buffer;

/**
 * This function waits until the GBA is in the VBlank region. This is useful
 * for updating graphics as the VBlank region does not draw to the screen;
 * necessary to keep graphics synchronized and to prevent tearing.
 *
 * This is a waste of battery. Use VBlankIntrWait for proper video syncing.
 */
inline void vsync()
{
  while (REG_VCOUNT >= 160);
  while (REG_VCOUNT < 160);
}

/**
 * Return the pixel at the given (x, y) coordinate.
 */
inline uint16_t* m4_get_pixel(uint32_t x, uint32_t y)
{
  // Divide by 2 since the buffer is storing 2 pixels per index.
  return (uint16_t*) &_video_buffer[(y * SCREEN_WIDTH + x) >> 1];
}

/**
 * Flip between page 1 located at MEM_VRAM or page 2 at MEM_VRAM + 0xA000.
 * While flipping, clear the old page from two frames ago.
 */
void flip_vid_page();
/**
 * Draws a mode 4 pixel.
 */
void m4_draw_pixel(uint32_t x, uint32_t y, uint32_t color_index);
/**
 * Draws a line from (x0, y0) to (x1, y1) using Bresenham's
 * line-drawing algorithm.
 */
void m4_draw_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color_index);
/**
 * Modified Bresenham algorithm for drawing filled-in circles.
 */
void m4_draw_circle_fill(int32_t x0, int32_t y0, uint32_t radius, uint32_t color_index);
/**
 * Bresenham algorithm for drawing circles.
 */
void m4_draw_circle(int32_t x0, int32_t y0, uint32_t radius, uint32_t color_index);
/**
 * Draw a rectangle starting from (x0, y0) to (x1, y1) filled-in.
 */
void m4_draw_rect_fill(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color_index);
/**
 * Draw a rectangle starting from (x0, y0) to (x1, y1).
 */
void m4_draw_rect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color_index);
/**
 * Draws a triangle which can also be rotated 90, 180, 270, or 360 degrees.
 */
void m4_draw_triangle(int32_t x, int32_t y, uint32_t base, uint32_t height, uint32_t rot, uint32_t color_index);
/**
 * Draws a filled-in triangle which can also be rotated 90, 180, 270, or 360 degrees.
 */
void m4_draw_triangle_fill(int32_t x, int32_t y, uint32_t base, uint32_t height, uint32_t rot, uint32_t color_index);
/**
 * Print a string to the canvas. Credit to TONC for the original code.
 */
void m4_puts(int32_t x, int32_t y, TextWriter* gptxt, const char* str, uint8_t color_index);

#endif
