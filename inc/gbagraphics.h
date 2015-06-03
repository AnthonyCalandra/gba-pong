#ifndef GBAGRAPHICS_H
#define GBAGRAPHICS_H 1

#include <stdint.h>

// Video Memory.
#define MEM_VRAM  0x6000000
// Object Attribute Memory (OAM) holds a sprite's attributes. See OAMEntryA.
#define OAM 0x7000000

/*
 * The Register Vertical Count keeps track of the current scanline being drawn
 * by the GBA. Note that it includes the VBlank section as well, making the range
 * of vertical_count: [0, 227].
 *
 * NOTE: The last 8 bits are unused.
 */
#define REG_VCOUNT_ADDR  0x4000006
#define REG_VCOUNT  (* (volatile uint16_t*) REG_VCOUNT_ADDR)

/*
 * The Register Display Controller is responsible for the graphical settings
 * of the GBA. The following is a short description of each of its fields:
 *   - [0-2] video_mode: set 0-2 for tiled modes; 3-5 for bitmapped modes.
 *   - [3] is_gbc_cartridge: read-only flag; set high is GBC or low for GBA.
 *   - [4] page_select: select buffer to show on screen (modes 4 and 5 only support double buffering).
 *   - [5] allow_oam_hblank: if flag set high, allow OAM access in HBlank.
 *   - [6] obj_mapping_mode: set flag high for 1D memory layout of tiles; low for 2D.
 *   - [7] force_screen_blank: if flag set high, clear screen.
 *   - [8-C] bg_renders: enable rendering of corresponding bg (0-3) and sprites.
 *   - [D-F] window_renders: enable use of windows 1/2, and object window, respectively.
 */
#define REG_DISPCNT_ADDR 0x4000000
#define REG_DISPCNT (* (volatile uint16_t*) REG_DISPCNT_ADDR)

/*
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

// Pointer to video memory in 16-bit chunks.
#define VIDEO_BUFFER ((uint16_t*) MEM_VRAM)

/*
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

#define SET_DISPLAY_MODE(mode)  (* (volatile uint32_t*) REG_DISPCNT_ADDR) = (mode)

/*
 * A SpriteAttributes object contains a sprite's attributes such as: coordinates,
 * rotation information, color information, flags, and drawing priorities.
 */
typedef struct
{
  uint16_t attributes[3];
  uint16_t unused;
} OAMEntryA, SpriteAttributes;

/*
 * A RotationData object contains the SpriteAttributes of four different sprites
 * and the rotation data. TODO: complete rotation documentation.
 *
 * A RotationData object is equivalent to four SpriteAttribute objects in memory.
 */
typedef struct
{
  uint16_t unused1[3];
  uint16_t rotationDataA;
  uint16_t unused2[3];
  uint16_t rotationDataB;
  uint16_t unused3[3];
  uint16_t rotationDataC;
  uint16_t unused4[3];
  uint16_t rotationDataD;
} OAMEntryB, RotationData;

/*
 * This function waits until the GBA is in the VBlank region. This is useful
 * for updating graphics as the VBlank region does not draw to the screen;
 * necessary to keep graphics synchronized and to prevent tearing.
 */
inline void vsync()
{
  while (REG_VCOUNT >= 160);
  while (REG_VCOUNT < 160);
}

#endif
