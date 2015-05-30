#ifndef GBAGRAPHICS_H
#define GBAGRAPHICS_H 1

#include <stdint.h>

// Video Memory.
#define MEM_VRAM  0x6000000
// Object Attribute Memory (OAM) holds a sprite's attributes. See OAMEntryA.
#define OAM 0x7000000
// Vertical count (current scanline).
#define REG_VCOUNT  (* (volatile uint32_t*) 0x4000006)
// Display (screen) control register.
#define REG_DISPCNT (* (volatile uint32_t*) 0x4000000)
// VBlank/HBlank and VDraw/HDraw statuses and display interrupt register.
#define REG_DISPSTAT  (* (volatile uint32_t*) 0x4000004)
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

#define SET_DISPLAY_MODE(mode)  REG_DISPCNT = (mode)

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
  uint16_t unused[3];
  uint16_t rotationDataA;
  uint16_t unused[3];
  uint16_t rotationDataB;
  uint16_t unused[3];
  uint16_t rotationDataC;
  uint16_t unused[3];
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
