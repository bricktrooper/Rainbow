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
		case OPCODE_RGB:
		{
			RGB * colour = data;
			rgb_colour(colour->red, colour->green, colour->blue);
			return RESULT_SUCCESS;
		}
		case OPCODE_BRIGHTNESS:
		{
			//U8 * brightness = data;
			//rgb_brightness(*brightness);
			//return RESULT_SUCCESS;
			return RESULT_ERROR_OPCODE;
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
	rgb_brightness(RED, 255 / 4);
	rgb_brightness(GREEN, 64 / 2);
	rgb_brightness(BLUE, 255 / 4);

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
