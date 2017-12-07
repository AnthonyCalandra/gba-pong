#ifndef H_GBAINTERRUPT
#define H_GBAINTERRUPT 1

typedef void (*interrupt_service_routine)(void);
#define REG_ISR_MAIN (*(volatile interrupt_service_routine*) 0x3007FFC)
#define REG_IME (*(volatile uint32_t*) 0x4000208)
#define REG_IE (*(volatile uint16_t*) 0x4000200)
#define REG_IF (*(volatile uint16_t*) 0x4000202)
#define REG_IFBIOS (*(volatile uint16_t*) 0x3007FF8)

#define IE_VBLANK_INTERRUPT (1 << 0)
#define DISPSTAT_VBLANK_IRQ_ENABLE (1 << 3)

/**
 * The ISR for the VBlankIntrWait interrupt.
 *
 * NOTE: This function is required to be compiled as ARM code. Compiling
 *      as THUMB code it won't work properly.
 */
void vblankintrwait_isr();
/**
 * Used to register the ISR for handling the VBlank interrupts.
 */
void register_vblank_isr();

#endif
