#include "rgb.h"

#include <xc.h>

#include "pwm.h"

#define PWM_CHANNEL_RED     PWM3
#define PWM_CHANNEL_GREEN   PWM4
#define PWM_CHANNEL_BLUE    PWM5

#define RAINBOW_TRANISTION_DELAY_US   20000
#define RAINBOW_SOLID_DELAY_US        200000

static U8 red_brightness = RGB_MAX_BRIGHTNESS;
static U8 green_brightness = RGB_MAX_BRIGHTNESS;
static U8 blue_brightness = RGB_MAX_BRIGHTNESS;

void rgb_initialize(void)
{
	rgb_off();
}

static inline PWM_Channel colour_channel(Colour colour)
{
	switch (colour)
	{
		case RED:   return PWM_CHANNEL_RED;
		case GREEN: return PWM_CHANNEL_GREEN;
		case BLUE:  return PWM_CHANNEL_BLUE;
	}
}

void rgb_set(Colour colour, U8 value)
{
	PWM_Channel channel = colour_channel(colour);
	pwm_duty(channel, value);
}

void rgb_colour(U8 red, U8 green, U8 blue)
{
	rgb_set(RED, red);
	rgb_set(GREEN, green);
	rgb_set(BLUE, blue);
}

void rgb_off(void)
{
	rgb_colour(0, 0, 0);
}

void rgb_rainbow(void)
{
	rgb_set(RED, red_brightness);

	// fade in green
	for (U8 i = 0; i < green_brightness; i++)
	{
		rgb_set(GREEN, i);
		_delay(RAINBOW_TRANISTION_DELAY_US);
	}

	_delay(RAINBOW_SOLID_DELAY_US);

	// fade out red
	for (U8 i = red_brightness; i > 0; i--)
	{
		rgb_set(RED, i);
		_delay(RAINBOW_TRANISTION_DELAY_US);
	}

	_delay(RAINBOW_SOLID_DELAY_US);

	// fade in blue
	for (U8 i = 0; i < blue_brightness; i++)
	{
		rgb_set(BLUE, i);
		_delay(RAINBOW_TRANISTION_DELAY_US);
	}

	_delay(RAINBOW_SOLID_DELAY_US);

	// fade out green
	for (U8 i = green_brightness; i > 0; i--)
	{
		rgb_set(GREEN, i);
		_delay(RAINBOW_TRANISTION_DELAY_US);
	}

	_delay(RAINBOW_SOLID_DELAY_US);

	// fade in red
	for (U8 i = 0; i < red_brightness; i++)
	{
		rgb_set(RED, i);
		_delay(RAINBOW_TRANISTION_DELAY_US);
	}

	_delay(RAINBOW_SOLID_DELAY_US);

	// fade out blue
	for (U8 i = blue_brightness; i > 0; i--)
	{
		rgb_set(BLUE, i);
		_delay(RAINBOW_TRANISTION_DELAY_US);
	}

	_delay(RAINBOW_SOLID_DELAY_US);
}

void rgb_brightness(U8 value)
{
	red_brightness = value;
	green_brightness = value;
	blue_brightness = value;
}
