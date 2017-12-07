#include "gbabios.h"

void cpu_fast_set(volatile const void* const src, void* const dst, uint32_t len)
{
  // Set the `fill` bit flag to 1.
  len |= 1 << 24;
  // 0xC is the index for CpuFastSet in the function table.
  __asm__ volatile("swi 0xC" ::: "r0", "r1", "r2");
}

void cpu_zero_memory(void* const dst, uint32_t len)
{
  // Use static data for our source since this function fills in 0s every time.
  static volatile uint32_t zero_value = 0;
  volatile uint32_t* src = &zero_value;
  // Set the fill bit flag to 1.
  len |= 1 << 24;
  __asm__ volatile(
    "ldr r0, %[src]\n" // Load address that points to 0 into first argument of CpuFastSet.
    "ldr r1, %[dst]\n" // Load the destination address into second argument of CpuFastSet.
    "mov r2, %[len]\n" // The length is the third argument to CpuFastSet.
    "swi 0xC" // 0xC is the index for CpuFastSet in the function table.
    :: [src] "m" (src), [dst] "m" (dst), [len] "r" (len)
    : "r0", "r1", "r2", "cc", "memory"
  );
}

void cpu_fast_cpy(volatile const void* const src, void* const dst, uint32_t len)
{
    // Set the `fill` bit flag to 0.
    len |= 1 << 24;
  // 0xC is the index for CpuFastSet in the function table.
  __asm__ volatile("swi 0xC" ::: "r0", "r1", "r2");
}
