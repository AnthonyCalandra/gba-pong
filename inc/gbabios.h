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
 *
 * TODO: Use this in-place of the current vsync.
 */
inline void vsync2()
{
  // 0x5 is VBlankIntrWait in the function table.
  __asm__ volatile("swi 0x5");
}

/**
 * See cpu_fast_set doc. This function just sets the src pointer to a location
 * pointing to the constant `0` and calls CpuFastSet.
 *
 * Note: This kinda sucks cause the inline assembly code is clobbering registers
 * but YOLO.
 *
 * @param src The source address of the value to set from.
 * @param dst The destination address to write to.
 * @param len The length in words to write. Note that the hardware will round
 *  up the length to the next 8-word multiple. For example, if len == 1 (word),
 *  the CpuFastSet call will actually set the next 8 (words).
 */
inline void cpu_zero_memory(void* dst, uint32_t len)
{
  // Set the fill bit flag to 1.
  len |= 1 << 24;
  volatile uint32_t* tmp = (volatile uint32_t*) malloc(sizeof(volatile uint32_t));
  *tmp = 0;
  __asm__ volatile(
    "ldr r0, %[tmp]\n" // Load address that points to 0 into first argument of CpuFastSet.
    "ldr r1, %[dst]\n" // Load the destination address into second argument of CpuFastSet.
    "mov r2, %[len]\n" // The length is the third argument to CpuFastSet.
    "swi 0xC" // 0xC is the index for CpuFastSet in the function table.
    :: [tmp] "m" (tmp), [dst] "m" (dst), [len] "r" (len)
    : "r0", "r1", "r2", "cc", "memory"
  );
  free((uint32_t*) tmp);
}

/**
 * Call the GBA BIOS' CpuFastSet function with the fill bit set.
 * @param src The source address of the value to set from.
 * @param dst The destination address to write to.
 * @param len The length in words to write. Note that the hardware will round
 *  up the length to the next 8-word multiple. For example, if len == 1 (word),
 *  the CpuFastSet call will actually set the next 8 (words).
 */
 inline void cpu_fast_set(void* src, void* dst, uint32_t len)
 {
   // Set the `fill` bit flag to 1.
   len |= 1 << 24;
   // 0xC is the index for CpuFastSet in the function table.
   __asm__ volatile("swi 0xC" ::: "r0", "r1", "r2");
 }

/**
 * Call the GBA BIOS' CpuFastSet function with the fill bit unset.
 * @param src The source address of the value to copy from.
 * @param dst The destination address to copy to.
 * @param len The length in words to copy. Note that the hardware will round
 *  up the length to the next 8-word multiple. For example, if len == 1 (word),
 *  the CpuFastSet call will actually copy the next 8 (words).
 */
inline void cpu_fast_cpy(volatile void* src, void* dst, uint32_t len)
{
  // 0xC is the index for CpuFastSet in the function table.
  __asm__ volatile("swi 0xC" ::: "r0", "r1", "r2");
}

#endif
