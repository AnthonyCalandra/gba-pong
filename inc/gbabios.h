#ifndef H_GBABIOS
#define H_GBABIOS  1

#include <stdint.h>
#include <stdlib.h>

/**
 * This function waits until the GBA is in the VBlank region. This is useful
 * for updating graphics as the VBlank region does not draw to the screen;
 * necessary to keep graphics synchronized and to prevent tearing.
 *
 * The VBlankIntrWait() BIOS function puts the CPU to sleep until the interrupt
 * is fired, which then means the GBA can begin its drawing routines.
 */
inline void vblank_intr_wait()
{
  // 0x5 is VBlankIntrWait in the function table.
  __asm__ volatile("swi 0x5");
}

/**
 * Call the GBA BIOS' CpuFastSet function with the fill bit set.
 * @param src The source address of the value to set from.
 * @param dst The destination address to write to.
 * @param len The length in words to write. Note that the hardware will round
 *  up the length to the next 8-word multiple. For example, if len == 1 (word),
 *  the CpuFastSet call will actually set the next 8 (words).
 */
void cpu_fast_set(volatile const void* const src, void* const dst, uint32_t len);

 /**
  * See cpu_fast_set doc. This function just sets the src pointer to a location
  * pointing to a constant `0` and calls CpuFastSet.
  *
  * @param src The source address of the value to set from.
  * @param dst The destination address to write to.
  * @param len The length in words to write. Note that the hardware will round
  *  up the length to the next 8-word multiple. For example, if len == 1 (word),
  *  the CpuFastSet call will actually set the next 8 (words).
  */
void cpu_zero_memory(void* const dst, uint32_t len);

/**
 * Call the GBA BIOS' CpuFastSet function with the fill bit unset.
 * @param src The source address of the value to copy from.
 * @param dst The destination address to copy to.
 * @param len The length in words to copy. Note that the hardware will round
 *  up the length to the next 8-word multiple. For example, if len == 1 (word),
 *  the CpuFastSet call will actually copy the next 8 (words).
 */
void cpu_fast_cpy(volatile const void* const src, void* const dst, uint32_t len);

#endif
