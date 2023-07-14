#include <xc.h>

#include "system.h"
#include "led.h"
#include "uart.h"
#include "rgb.h"
#include "link.h"

static Result service(Opcode opcode, void * data)
{
	switch (opcode)
	{
		case OPCODE_PING:
		{
			return RESULT_SUCCESS;
		}
		case OPCODE_COLOUR:
		{
			RGB * colour = data;
			rgb_colour(colour->red, colour->green, colour->blue);
			return RESULT_SUCCESS;
		}
		case OPCODE_BRIGHTNESS:
		{
			RGB * brightness = data;
			rgb_brightness(brightness->red, brightness->green, brightness->blue);
			return RESULT_SUCCESS;
		}
		case OPCODE_RAINBOW:
		{
			rgb_rainbow();
			return RESULT_SUCCESS;
		}
		default:
		{
			return RESULT_ERROR_OPCODE;
		}
	}
}

void main(void)
{
	system_initialize();
	uart_asynchronous(true, false);
	rgb_brightness(64, 64, 64);

	while (1)
	{
		char string [3];
		uart_write("hello", 5);
		//uart_read(string, sizeof(string));
		//uart_transmit(string, sizeof(string));
		rgb_rainbow();
		//uart_echo();
		//Header header;
		//U8 data [4];
		//Result result = link_receive(&header, data, sizeof(data));
		//led_on();

		//if (result == RESULT_SUCCESS)
		//{
		//	result = service(header.opcode, data);
		//}

		//link_transmit(result);
		//led_off();
	}
}
