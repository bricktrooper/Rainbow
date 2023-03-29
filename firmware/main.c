#include <xc.h>

#include "system.h"
#include "led.h"
#include "uart.h"
#include "rgb.h"

#include <stdio.h>

void main(void)
{
	system_initialize();

	while (1)
	{
		rgb_rainbow();
	}
}
