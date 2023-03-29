#include <xc.h>

#include "system.h"
#include "led.h"
#include "uart.h"
#include "pwm.h"

#include <stdio.h>

void main(void)
{
	system_initialize();

	while (1)
	{
		for (U8 i = 0; i < 255; i++)
		{
			pwm_duty(PWM3, i);
			_delay(10000);
		}

		for (U8 i = 255; i > 0; i--)
		{
			pwm_duty(PWM3, i);
			_delay(10000);
		}
	}
}
