#include <string.h>
#include "macros.h"
#include "gbainterrupt.h"
#include "gbagraphics.h"

ARM void vblankintrwait_isr() {
    // Acknowledge we have handled the interrupt.
    REG_IF = IE_VBLANK_INTERRUPT;
    REG_IFBIOS |= IE_VBLANK_INTERRUPT;
}

void register_vblank_isr() {
    // Store the main ISR.
    REG_ISR_MAIN = vblankintrwait_isr;
    // VBlankIntrWait required the DISPSTAT to be set properly.
    REG_DISPSTAT |= DISPSTAT_VBLANK_IRQ_ENABLE;
    // Enable the VBlank interrupt.
    REG_IE |= IE_VBLANK_INTERRUPT;
    // Enable all interrupts.
    REG_IME = 1;
}
