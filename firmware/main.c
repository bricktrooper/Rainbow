#include <xc.h>

#include "system.h"
#include "led.h"
#include "uart.h"
#include "rgb.h"

void main(void)
{
	system_initialize();

	while (1)
	{
		rgb_rainbow(32);
		//uart_echo();
	}
}
