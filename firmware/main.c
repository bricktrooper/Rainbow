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
	rgb_brightness(255 / 4, 64 / 2, 255 / 4);

	while(1)
	{
		rgb_rainbow();
	}

	while (1)
	{
		Header header;
		U8 data [4];
		Result result = link_receive(&header, data, sizeof(data));
		led_on();

		if (result == RESULT_SUCCESS)
		{
			result = service(header.opcode, data);
		}

		link_transmit(result);
		led_off();
	}
}
