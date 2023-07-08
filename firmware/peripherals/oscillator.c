#include "oscillator.h"

#include <xc.h>

#include "oscillator.h"

void oscillator_initialize(void)
{
	OSCCON1bits.NOSC = 0b110;          // high-frequency internal oscillator
	OSCCON1bits.NDIV = 0b0000;         // 1:1 oscillator postscaler (f_clock = f_oscillator)
	OSCTUNEbits.HFTUN = 0b00000;       // use calibrated oscillator centre frequency
	oscillator_frequency(HFFRQ_8MHZ);  // set oscillator frequency to 8 MHz
}

void oscillator_frequency(HFFRQ frequency)
{
	OSCFRQbits.HFFRQ = frequency;   // 8 MHz oscillator
}
