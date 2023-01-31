#include "led.h"

#include <xc.h>

#include "system.h"

#define LED        RA5
#define TRIS_LED   TRISA5

#define BLINK_DELAY_US   500000

void led_initialize(void)
{
	TRIS_LED = OUTPUT;
}

void led_on(void)
{
	LED = 1;
}

void led_off(void)
{
	LED = 0;
}

void led_blink(void)
{
	led_on();
	_delay(BLINK_DELAY_US);
	led_off();
	_delay(BLINK_DELAY_US);
}
