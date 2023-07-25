#include "timer2.h"

#include <xc.h>

enum T2CS
{
	T2CS_RESEREVED        = 0b1111,   // reserved
	T2CS_LC4              = 0b1110,   // LC4 output
	T2CS_LC3              = 0b1101,   // LC3 output
	T2CS_LC2              = 0b1100,   // LC2 output
	T2CS_LC1              = 0b1011,   // LC1 output
	T2CS_ZCD1             = 0b1010,   // ZCD1 output
	T2CS_NCO1             = 0b1001,   // NCO1 output
	T2CS_CLKR             = 0b1000,   // CLKR
	T2CS_SOSC             = 0b0111,   // SOSC
	T2CS_MFINTOSC_31KHZ25 = 0b0110,   // MFINTOSC (31.25 kHz)
	T2CS_MFINTOSC_500KHZ  = 0b0101,   // MFINTOSC (500 kHz)
	T2CS_LFINTOSC         = 0b0100,   // LFINTOSC
	T2CS_HFINTOSC         = 0b0011,   // HFINTOSC (32 MHz)
	T2CS_FOSC             = 0b0010,   // FOSC
	T2CS_FOSC4            = 0b0001,   // FOSC/4
	T2CS_T2CKIPPS         = 0b0000,   // T2CKIPPS
};

void timer2_initialize(T2CKPS prescaler, U8 period)
{
	timer2_enable(false);           // disable timer
	T2CONbits.CKPS = T2CKPS_1;      // 1:1 clock prescaler
	T2CLKCONbits.CS = T2CS_FOSC4;   // Fosc/4 clock source
	T2PR = period;                  // timer period
	timer2_interrupts(false);       // disable interrupt
	PIR4bits.TMR2IF = 0;            // reset interrupt flag
}

void timer2_enable(bool enable)
{
	T2CONbits.ON = enable;
}

void timer2_interrupts(bool enable)
{
	PIE4bits.TMR2IE = enable;
}
