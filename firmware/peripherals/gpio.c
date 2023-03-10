#include "gpio.h"

#include <xc.h>

void gpio_initialize(void)
{
	// INPUT (1) / OUTPUT (0) //

	// configure all pins as outputs
	TRISA = 0b00000000;
	TRISC = 0b00000000;

	// set all pins as digital
	ANSELA = 0b00000000;
	ANSELC = 0b00000000;

	// set all pins to low
	PORTA = 0b00000000;
	PORTC = 0b00000000;
}
