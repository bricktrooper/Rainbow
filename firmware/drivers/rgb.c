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

#define DEFAULT_RED_BRIGHTNESS     PWM_MAX
#define DEFAULT_GREEN_BRIGHTNESS   PWM_MAX
#define DEFAULT_BLUE_BRIGHTNESS    PWM_MAX

#define DEFAULT_CYCLE_SPEED   175

static U8 red_brightness = DEFAULT_RED_BRIGHTNESS;
static U8 green_brightness = DEFAULT_GREEN_BRIGHTNESS;
static U8 blue_brightness = DEFAULT_BLUE_BRIGHTNESS;

static bool cycling = false;

static inline PWM_Channel get_pwm_channel(RGB_Channel channel)
{
	switch (channel)
	{
		case RED:   return PWM_CHANNEL_RED;
		case GREEN: return PWM_CHANNEL_GREEN;
		case BLUE:  return PWM_CHANNEL_BLUE;
	}
}

static inline PWM_Channel get_brightness(RGB_Channel channel)
{
	switch (channel)
	{
		case RED:   return red_brightness;
		case GREEN: return green_brightness;
		case BLUE:  return blue_brightness;
	}
}

void rgb_initialize()
{
	rgb_off();
	rgb_brightness(red_brightness, green_brightness, blue_brightness);
	timer0_initialize(T0CKPS_1024, 0);      // timer settings for cycle
	rgb_cycle_speed(DEFAULT_CYCLE_SPEED);   // set default period for timer0
}

void rgb_set(RGB_Channel channel, U8 value)
{
	U8 brightness = get_brightness(channel);
	U8 duty = (U8)(((U16)value * brightness) / PWM_MAX);   // scale PWM value
	PWM_Channel pwm = get_pwm_channel(channel);
	pwm_duty(pwm, duty);
}

void rgb_brighten(RGB_Channel channel)
{
	for (U8 i = 0; i < UINT8_MAX; i++)
	{
		rgb_set(channel, i);
		_delay(RAMP_DELAY_US);
	}
}

void rgb_fade(RGB_Channel channel)
{
	for (U8 i = UINT8_MAX; i > 0; i--)
	{
		rgb_set(channel, i);
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
	rgb_cycle(false);
}

void rgb_brightness(U8 red, U8 green, U8 blue)
{
	red_brightness = red;
	green_brightness = green;
	blue_brightness = blue;
}

void rgb_cycle(bool enable)
{
	cycling = enable;
	timer0_enable(enable);

	if (!enable)
	{
		timer0_reset();
	}
}

bool rgb_cycling(void)
{
	return cycling;
}

void rgb_cycle_speed(U8 speed)
{
	U8 period = UINT8_MAX - speed;

	// period == 0 doesn't work for some reason, so 1 is the fastest
	if (period == 0)
	{
		period = 1;
	}

	timer0_period(period);
}

void rgb_cycle_update(void)
{
	if (!timer0_expired())
	{
		return;
	}

	static U8 value = 0;
	static RGB_Channel channel = RED;
	static bool fade = false;

	rgb_set(channel, value);

	if (fade)
	{
		if (value > 0)
		{
			value--;
		}
		else
		{
			channel = (channel + 1) % 3;   // cycle through red, green, and blue
			fade = false;
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
			channel = (channel + 1) % 3;   // cycle through red, green, and blue
			fade = true;
		}
	}

	timer0_reset();
}

void rgb_single_cycle(void)
{
	for (int i = 0; i < 256 * 6; i++)
	{
		rgb_cycle_update();
	}
}

void rgb_default(void)
{
	rgb_brightness(DEFAULT_RED_BRIGHTNESS, DEFAULT_GREEN_BRIGHTNESS, DEFAULT_BLUE_BRIGHTNESS);
	rgb_cycle_speed(DEFAULT_CYCLE_SPEED);
	rgb_cycle(true);
}
