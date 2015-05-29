#ifndef GBA_H
#define GBA_H 1

#include <stdint.h>

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 160

#define MEM_IO  0x4000000
#define MEM_VRAM  0x6000000
#define OAM 0x7000000

#define REG_DISPCNT (* (volatile uint32_t*) 0x4000000)
#define REG_DISPSTAT  (* (volatile uint32_t*) 0x4000004)
#define REG_VCOUNT  (* (volatile uint32_t*) 0x4000006)
#define REG_KEYINPUT  (* (volatile uint32_t*) 0x40000130)

#define VIDEO_BUFFER ((uint16_t*) MEM_VRAM)

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

#include "gbatypes.h"
#include "gbaio.h"

#endif
