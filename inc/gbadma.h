#ifndef H_GBADMA
#define H_GBADMA  1

#define REG_DMA_SRC ((volatile void*) 0x40000B0)
#define REG_DMA_DST ((volatile void*) 0x40000B4)
#define REG_DMA_CNT ((volatile uint32_t*) 0x40000B8)

#define DMA_DEST_INC 0
#define DMA_DEST_DEC 1
#define DMA_DEST_FIXED 2
#define DMA_DEST_RESET 3
#define DMA_SRC_INC 0
#define DMA_SRC_DEC 1
#define DMA_SRC_FIXED 2
#define DMA_HALFWORD_CHUNK 0
#define DMA_WORD_CHUNK 1

/**
 * Zero memory routine using Direct Memory Access (DMA) hardware. Similar
 * to cpu_zero_memory but this function halts the CPU.
 * @param dst The destination address to being zeroing.
 * @param len The length in words.
 */
void dma_zero_memory(void* dst, uint32_t len);

#endif
