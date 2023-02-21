#include <xc.h>

#include "system.h"
#include "led.h"
#include "uart.h"

#include <stdio.h>

void main(void)
{
	system_initialize();

	while (1)
	{
		char byte;
		uart_receive(&byte, 1);
		led_on();
		uart_transmit(&byte, 1);
		led_off();
	}
}
