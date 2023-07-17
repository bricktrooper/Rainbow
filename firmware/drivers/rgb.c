#include "rgb.h"

#include <xc.h>
#include <stdbool.h>

#include "pwm.h"
#include "timer0.h"

#define PWM_CHANNEL_RED     PWM3
#define PWM_CHANNEL_GREEN   PWM4
#define PWM_CHANNEL_BLUE    PWM5

#define RAMP_DELAY_US           20000
#define SOLID_COLOUR_DELAY_US   5000000

static U8 red_brightness = 0;
static U8 green_brightness = 0;
static U8 blue_brightness = 0;

static inline PWM_Channel get_channel(Colour colour)
{
	switch (colour)
	{
		case RED:   return PWM_CHANNEL_RED;
		case GREEN: return PWM_CHANNEL_GREEN;
		case BLUE:  return PWM_CHANNEL_BLUE;
	}
}

static inline PWM_Channel get_brightness(Colour colour)
{
	switch (colour)
	{
		case RED:   return red_brightness;
		case GREEN: return green_brightness;
		case BLUE:  return blue_brightness;
	}
}

void rgb_initialize()
{
	timer0_initialize(T0CKPS_1024, 32);   // timer settings for rainbow
	rgb_brightness(PWM_MAX, PWM_MAX, PWM_MAX);
	rgb_off();
}

void rgb_set(Colour colour, U8 value)
{
	U8 brightness = get_brightness(colour);
	U8 duty = (U8)(((U16)value * brightness) / PWM_MAX);   // scale PWM value
	PWM_Channel channel = get_channel(colour);
	pwm_duty(channel, duty);
}

void rgb_brighten(Colour colour)
{
	for (U8 i = 0; i < PWM_MAX; i++)
	{
		rgb_set(colour, i);
		_delay(RAMP_DELAY_US);
	}
}

void rgb_fade(Colour colour)
{
	for (U8 i = PWM_MAX; i > 0; i--)
	{
		rgb_set(colour, i);
		_delay(RAMP_DELAY_US);
	}
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
	rgb_rainbow(false);
}

void rgb_brightness(U8 red, U8 green, U8 blue)
{
	red_brightness = red;
	green_brightness = green;
	blue_brightness = blue;
}

void rgb_rainbow(bool enable)
{
	timer0_enable(enable);
}

void rgb_rainbow_update(void)
{
	static U8 value = 0;
	static Colour colour = RED;
	static bool fade = false;

	rgb_set(colour, value);

	if (fade)
	{
		if (value > 0)
		{
			value--;
		}
		else
		{
			colour = (colour + 1) % 3;   // cycle through red, green, and blue
			fade = false;
			_delay(SOLID_COLOUR_DELAY_US);
		}
	}
	else
	{
		if (value < PWM_MAX)
		{
			value++;
		}
		else
		{
			colour = (colour + 1) % 3;   // cycle through red, green, and blue
			fade = true;
			_delay(SOLID_COLOUR_DELAY_US);
		}
	}
}

void rgb_rainbow_cycle(void)
{
	for (int i = 0; i < 256 * 6; i++)
	{
		rgb_rainbow_update();
	}
}
