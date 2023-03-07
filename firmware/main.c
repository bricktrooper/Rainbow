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
		//char byte;
		//uart_receive(&byte, 1);
		//led_on();
		//uart_transmit(&byte, 1);
		//led_off();
		for (U8 i = 0; i < 100; i++)
		{
			pwm_duty(i);
			//printf("PWM3CON 0x%02X, T2CLKCON 0x%02X, T2PR 0x%02X, PWM3DCH 0x%02X, PWM3DCL 0x%02X, T2CON 0x%02X\r\n", PWM3CON, T2CLKCON, T2PR, PWM3DCH, PWM3DCL, T2CON);
			_delay(10000);
		}

		for (U8 i = 100; i > 0; i--)
		{
			pwm_duty(i);
			//printf("PWM3CON 0x%02X, T2CLKCON 0x%02X, T2PR 0x%02X, PWM3DCH 0x%02X, PWM3DCL 0x%02X, T2CON 0x%02X\r\n", PWM3CON, T2CLKCON, T2PR, PWM3DCH, PWM3DCL, T2CON);
			_delay(10000);
		}
	}
}
