#include <stdint.h>
#include "gbabios.h"

void cpu_fast_cpy(volatile void* src, void* dst, uint32_t len)
{
  // 0x0C is the index for CpuFastSet.
  __asm__ volatile("swi 0x0C<<16" ::: "r0", "r1", "r2");
}

void cpu_fast_set(volatile void* src, void* dst, uint32_t len)
{
  // Set the fill bit flag to 1.
  len |= 1 << 24;
  // 0x0C is the index for CpuFastSet.
  __asm__ volatile("swi 0x0C<<16" ::: "r0", "r1", "r2");
}