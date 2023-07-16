#include "timer0.h"

#include <xc.h>

enum T0OUTPS
{
	T0OUTPS_16 = 0b1111,
	T0OUTPS_15 = 0b1110,
	T0OUTPS_14 = 0b1101,
	T0OUTPS_13 = 0b1100,
	T0OUTPS_12 = 0b1011,
	T0OUTPS_11 = 0b1010,
	T0OUTPS_10 = 0b1001,
	T0OUTPS_9  = 0b1000,
	T0OUTPS_8  = 0b0111,
	T0OUTPS_7  = 0b0110,
	T0OUTPS_6  = 0b0101,
	T0OUTPS_5  = 0b0100,
	T0OUTPS_4  = 0b0011,
	T0OUTPS_3  = 0b0010,
	T0OUTPS_2  = 0b0001,
	T0OUTPS_1  = 0b0000
};

void timer0_initialize(T0CKPS prescaler, U8 period)
{
	timer0_enable(false);             // disable timer
	T0CON0bits.T016BIT = 0;           // 8 b mode
	T0CON0bits.T0OUTPS = T0OUTPS_1;   // 1:1 output postscaler
	T0CON1bits.T0CS = 0b010;          // Fosc/4 clock source
	T0CON1bits.T0ASYNC = 0;           // synchronize input clock to Fosc/4 (max frequency)
	T0CON1bits.T0CKPS = prescaler;    // 1:1 prescaler
	TMR0H = period;                   // timer period (8 b mode only)
	PIE0bits.TMR0IE = 1;              // enable interrupt
	PIR0bits.TMR0IF = 0;              // reset interrupt flag (set when TMR0L == TMR0H)
}

void timer0_enable(bool enable)
{
	T0CON0bits.T0EN = enable;
}
