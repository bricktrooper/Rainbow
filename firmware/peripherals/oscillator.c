#include "oscillator.h"

#include <xc.h>

#include "oscillator.h"

#define MHZ   1000000

void oscillator_initialize(void)
{
	OSCCON1bits.NOSC = 0b110;               // high-frequency internal oscillator
	OSCCON1bits.NDIV = 0b0000;              // 1:1 oscillator postscaler (f_clock = f_oscillator)
	OSCTUNEbits.HFTUN = 0b00000;            // use calibrated oscillator centre frequency
	oscillator_set_frequency(HFFRQ_32MHZ);  // set oscillator frequency to 32 MHz
}

void oscillator_set_frequency(HFFRQ frequency)
{
	OSCFRQbits.HFFRQ = frequency;
}

U32 oscillator_get_frequency(void)
{
	HFFRQ frequency = OSCFRQbits.HFFRQ;

	switch (frequency)
	{
		case HFFRQ_32MHZ: return 32 * MHZ;
		case HFFRQ_16MHZ: return 16 * MHZ;
		case HFFRQ_12MHZ: return 12 * MHZ;
		case HFFRQ_8MHZ:  return 8 * MHZ;
		case HFFRQ_4MHZ:  return 4 * MHZ;
		case HFFRQ_2MHZ:  return 2 * MHZ;
		case HFFRQ_1MHZ:  return 1 * MHZ;
		default:          return 0;
	}
}
