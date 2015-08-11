#ifndef H_GBABIOS
#define H_GBABIOS  1

#include <stdint.h>
#include <stdlib.h>

/**
 * See cpu_fast_set doc. This function just sets the src pointer to a location
 * pointing to the constant `0`. Inlined since it's used for the page flipping
 * routine.
 */
 inline void cpu_zero_memory(void* dst, uint32_t len)
 {
   volatile uint32_t* tmp = (volatile uint32_t*) malloc(sizeof(volatile uint32_t));
   *tmp = 0;
   // Set the fill bit flag to 1.
   len |= 1 << 24;
   __asm__ volatile(
     "ldr r0, %[tmp]\n" // Load address that points to 0 into first argument of CpuFastSet.
     "ldr r1, %[dst]\n" // Load the destination address into second argument of CpuFastSet.
     "mov r2, %[len]\n" // The length is the third argument to CpuFastSet.
     "swi 0x0C<<16" // 0x0C is the index for CpuFastSet.
     :: [tmp] "m" (tmp), [dst] "m" (dst), [len] "r" (len)
     : "r0", "r1", "r2"
   );
   free((uint32_t*) tmp);
   tmp = NULL;
 }

/**
 * Call the GBA BIOS' CpuFastSet function with the fill bit set.
 * @param src The source address of the value to set from.
 * @param dst The destination address to write to.
 * @param len The length in 8-word chunks to write.
 */
void cpu_fast_set(volatile void* src, void* dst, uint32_t len);
/**
 * Call the GBA BIOS' CpuFastSet function with the fill bit unset.
 * @param src The source address of the value to copy from.
 * @param dst The destination address to copy to.
 * @param len The length in 8-word chunks to copy.
 */
void cpu_fast_cpy(volatile void* src, void* dst, uint32_t len);

#endif