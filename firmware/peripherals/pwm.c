#include "pwm.h"

#include <xc.h>

#include "system.h"

void pwm_initialize(void)
{
	TRISC0 = INPUT;   // disable RC0 output temporarily
	ANSELCbits.ANSC0 = DIGITAL;
	PWM3CONbits.PWM3POL = 0;   // active high output waveform
	T2CLKCONbits.CS = 0b0001;   // Fosc/4
	T2PR = 0x65;   // PWM period for Timer 2
	PWM3DCH = 0;
	PWM3DCL = 0;
	PIR4bits.TMR2IF = 0;
	T2CONbits.CKPS = 0b100;   // 1:16 prescaler
	T2CONbits.ON = 1;
	while (PIR4bits.TMR2IF == 0);
	TRISC0 = OUTPUT;
	RC0PPS = 0x0B;
	PWM3CONbits.PWM3EN = 1;
}

void pwm_duty(U8 value)
{
	U32 duty = ((U32)value * 4 * (T2PR + 1)) / 255;
	PWM3DCH = (U8)(duty >> 2);
	PWM3DCL = (U8)(duty << 6);
}
