#include <stdint.h>
#include <stdlib.h>
#include "gbadma.h"

void dma_zero_memory(void* dst, uint16_t len)
{
  volatile void* src = REG_DMA_SRC;
  volatile void* dma_dst = REG_DMA_DST;
  volatile uint32_t* cnt = REG_DMA_CNT;
  volatile uint32_t* val = (volatile uint32_t*) malloc(sizeof(uint32_t));
  *val = 0;
  src = val;
  dma_dst = dst;
  // Clear REG_DMA_CNT.
  *cnt &= 0;
  // Use 32 bit (word) chunks for transfer length, fixed-length source.
  *cnt = (DMA_HALFWORD_CHUNK << 0x1A) | (DMA_SRC_FIXED << 17) | (len & 0xFFFF);
  // Enable DMA0.
  *cnt |= 1 << 0x1F;
  free((uint32_t*) val);
  val = NULL;
}