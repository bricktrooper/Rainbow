#include "rgb.h"

#include <xc.h>

#include "pwm.h"

#define RAINBOW_TRANISTION_DELAY_US   20000
#define RAINBOW_SOLID_DELAY_US        200000

void rgb_initialize(void)
{
	rgb_off();
}

void rgb_red(U8 value)
{
	pwm_duty(PWM3, value);
}

void rgb_green(U8 value)
{
	pwm_duty(PWM4, value);
}

void rgb_blue(U8 value)
{
	pwm_duty(PWM5, value);
}

void rgb_colour(U8 red, U8 green, U8 blue)
{
	rgb_red(red);
	rgb_green(green);
	rgb_blue(blue);
}

void rgb_off(void)
{
	rgb_colour(0, 0, 0);
}

void rgb_rainbow(U8 brightness)
{
	rgb_red(brightness);

	// fade in green
	for (U8 i = 0; i < brightness; i++)
	{
		rgb_green(i);
		_delay(RAINBOW_TRANISTION_DELAY_US);
	}

	_delay(RAINBOW_SOLID_DELAY_US);

	// fade out red
	for (U8 i = brightness; i > 0; i--)
	{
		rgb_red(i);
		_delay(RAINBOW_TRANISTION_DELAY_US);
	}

	_delay(RAINBOW_SOLID_DELAY_US);

	// fade in blue
	for (U8 i = 0; i < brightness; i++)
	{
		rgb_blue(i);
		_delay(RAINBOW_TRANISTION_DELAY_US);
	}

	_delay(RAINBOW_SOLID_DELAY_US);

	// fade out green
	for (U8 i = brightness; i > 0; i--)
	{
		rgb_green(i);
		_delay(RAINBOW_TRANISTION_DELAY_US);
	}

	_delay(RAINBOW_SOLID_DELAY_US);

	// fade in red
	for (U8 i = 0; i < brightness; i++)
	{
		rgb_red(i);
		_delay(RAINBOW_TRANISTION_DELAY_US);
	}

	_delay(RAINBOW_SOLID_DELAY_US);

	// fade out blue
	for (U8 i = brightness; i > 0; i--)
	{
		rgb_blue(i);
		_delay(RAINBOW_TRANISTION_DELAY_US);
	}

	_delay(RAINBOW_SOLID_DELAY_US);
}
