#include "rgb.h"

#include <xc.h>
#include <stdbool.h>

#include "pwm.h"

#define PWM_CHANNEL_RED     PWM3
#define PWM_CHANNEL_GREEN   PWM4
#define PWM_CHANNEL_BLUE    PWM5

#define RAMP_DELAY_US            20000
#define RAINBOW_SOLID_DELAY_US   500000

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
	rgb_off();
	rgb_brightness(PWM_MAX, PWM_MAX, PWM_MAX);
}

#include "uart.h"
#include <stdio.h>

void rgb_set(Colour colour, U8 value)
{
	U8 brightness = get_brightness(colour);
	U8 duty = (U8)(((U16)value * brightness) / PWM_MAX);   // scale PWM value
	PWM_Channel channel = get_channel(colour);
	pwm_duty(channel, duty);
}

void rgb_fade_in(Colour colour)
{
	for (U8 i = 0; i < PWM_MAX; i++)
	{
		rgb_set(colour, i);
		_delay(RAMP_DELAY_US);
	}
}

void rgb_fade_out(Colour colour)
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
}

void rgb_rainbow(void)
{
	rgb_set(RED, 255);

	rgb_fade_in(GREEN);
	_delay(RAINBOW_SOLID_DELAY_US);

	rgb_fade_out(RED);
	_delay(RAINBOW_SOLID_DELAY_US);

	rgb_fade_in(BLUE);
	_delay(RAINBOW_SOLID_DELAY_US);

	rgb_fade_out(GREEN);
	_delay(RAINBOW_SOLID_DELAY_US);

	rgb_fade_in(RED);
	_delay(RAINBOW_SOLID_DELAY_US);

	rgb_fade_out(BLUE);
	_delay(RAINBOW_SOLID_DELAY_US);
}

void rgb_brightness(U8 red, U8 green, U8 blue)
{
	red_brightness = red;
	green_brightness = green;
	blue_brightness = blue;
}
