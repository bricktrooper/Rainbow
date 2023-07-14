#include "interrupts.h"

#include <xc.h>

void interrupts_initialize(void)
{
	interrupts_peripheral(true);    // enable peripherial interrupts
	interrupts_global(true);        // unmask all interrupts
}

void interrupts_global(bool enable)
{
	INTCONbits.GIE = enable;
}

void interrupts_peripheral(bool enable)
{
	INTCONbits.PEIE = enable;
}
