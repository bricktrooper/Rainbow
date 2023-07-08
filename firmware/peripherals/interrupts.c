#include "interrupts.h"

#include <xc.h>

void interrupts_initialize(void)
{
	interrupts_global(false);       // mask all interrupts
	interrupts_peripheral(true);    // enable peripherial interrupts
}

void interrupts_global(bool enable)
{
	INTCONbits.GIE = enable;
}

void interrupts_peripheral(bool enable)
{
	INTCONbits.PEIE = enable;
}
