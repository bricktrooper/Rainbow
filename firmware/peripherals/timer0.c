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

enum T0CS
{
	T0CS_LC1               = 0b111,   // LC1 output
	T0CS_SOSC              = 0b110,   // SOSC
	T0CS_MFINTOSC          = 0b101,   // MFINTOSC (500 kHz)
	T0CS_LFINTOSC          = 0b100,   // LFINTOSC
	T0CS_HFINTOSC          = 0b011,   // HFINTOSC
	T0CS_FOSC4             = 0b010,   // FOSC/4
	T0CS_T0CKIPPS_INVERTED = 0b001,   // T0CKIPPS (Inverted)
	T0CS_T0CKIPPS_TRUE     = 0b000    // T0CKIPPS (True)
};

void timer0_initialize(T0CKPS prescaler, U8 period)
{
	timer0_enable(false);             // disable timer
	T0CON0bits.T016BIT = 0;           // 8 b mode
	T0CON0bits.T0OUTPS = T0OUTPS_1;   // 1:1 output postscaler
	T0CON1bits.T0CS = T0CS_FOSC4;     // Fosc/4 clock source
	T0CON1bits.T0ASYNC = 0;           // synchronize input clock to Fosc/4 (max frequency)
	T0CON1bits.T0CKPS = prescaler;    // 1:1 prescaler
	timer0_period(period);            // timer period
	timer0_interrupt(false);          // disable interrupt
	PIR0bits.TMR0IF = 0;              // reset interrupt flag (set when TMR0L == TMR0H)
}

void timer0_enable(bool enable)
{
	T0CON0bits.T0EN = enable;
}

void timer0_interrupt(bool enable)
{
	PIE0bits.TMR0IE = enable;
}

bool timer0_expired(void)
{
	return PIR0bits.TMR0IF;
}

void timer0_period(U8 period)
{
	TMR0H = period;   // TMR0H is the period only in timer 0's 8 b mode
}
