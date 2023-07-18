#include "timer2.h"

#include <xc.h>

void timer2_initialize(T2CKPS prescaler, U8 period)
{
	timer2_enable(false);        // disable timer
	T2CONbits.CKPS = T2CKPS_1;   // clock prescaler
	T2CLKCONbits.CS = 0b0001;    // Fosc/4 clock source
	T2PR = period;               // timer period
	timer2_interrupt(false);     // disable interrupt
	PIR4bits.TMR2IF = 0;         // reset interrupt flag
}

void timer2_enable(bool enable)
{
	T2CONbits.ON = enable;
}

void timer2_interrupt(bool enable)
{
	PIE4bits.TMR2IE = enable;
}
