#include "pwm.h"

#include <xc.h>

#include "system.h"
#include "pps.h"

void pwm_initialize(void)
{
	TRISC0 = OUTPUT;   // set RC0 to output
	TRISC1 = OUTPUT;   // set RC1 to output
	TRISC2 = OUTPUT;   // set RC2 to output

	ANSELCbits.ANSC0 = DIGITAL;   // configure RC0 as digital
	ANSELCbits.ANSC1 = DIGITAL;   // configure RC1 as digital
	ANSELCbits.ANSC2 = DIGITAL;   // configure RC2 as digital

	RC0PPS = PPSO_PWM3;   // connect RC0 to PWM3
	RC1PPS = PPSO_PWM4;   // connect RC1 to PWM4
	RC2PPS = PPSO_PWM5;   // connect RC2 to PWM5

	// active high output waveform
	PWM3CONbits.PWM3POL = 0;
	PWM4CONbits.PWM4POL = 0;
	PWM5CONbits.PWM5POL = 0;

	// TIMER 2 //

	T2CLKCONbits.CS = 0b0001;       // user Fosc/4
	T2PR = 0x65;                    // timer period
	PIR4bits.TMR2IF = 0;            // reset timer
	T2CONbits.CKPS = 0b100;         // 1:16 prescaler
	T2CONbits.ON = 1;               // enable timer
	while (PIR4bits.TMR2IF == 0);   // wait for first timer interrupt

	// enable all PWM channels
	PWM3CONbits.PWM3EN = 1;
	PWM4CONbits.PWM4EN = 1;
	PWM5CONbits.PWM5EN = 1;

	// turn off all channels (duty cycle = 0)
	pwm_duty(PWM3, 0);
	pwm_duty(PWM4, 0);
	pwm_duty(PWM5, 0);
}

void pwm_duty(PWM_Channel channel, U8 value)
{
	U32 duty = ((U32)value * 4 * (T2PR + 1)) / 255;
	U8 high = (U8)(duty >> 2);
	U8 low = (U8)(duty << 6);

	switch (channel)
	{
		case PWM3:
		{
			PWM3DCH = high;
			PWM3DCL = low;
			break;
		}
		case PWM4:
		{
			PWM4DCH = high;
			PWM4DCL = low;
			break;
		}
		case PWM5:
		{
			PWM5DCH = high;
			PWM5DCL = low;
			break;
		}
		default:
		{
			break;
		}
	}
}
