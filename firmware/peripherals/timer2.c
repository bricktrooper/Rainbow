#include "timer2.h"

#include <xc.h>

void timer2_init(T2CKPS prescaler, U8 period)
{
	timer2_enable(false);           // disable timer
	T2CLKCONbits.CS = 0b0001;       // Fosc/4 clock source
	T2PR = period;                  // timer period
	PIR4bits.TMR2IF = 0;            // reset timer interrupt flag
	T2CONbits.CKPS = 0b000;         // 1:1 prescaler
}

void timer2_enable(bool enable)
{
	T2CONbits.ON = enable;
}
