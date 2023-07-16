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
			//rgb_rainbow();
			return RESULT_SUCCESS;
		}
		default:
		{
			return RESULT_ERROR_OPCODE;
		}
	}
}

#include <stdio.h>
#include "timer0.h"
void main(void)
{
	system_initialize();
	uart_non_blocking(true, true);
	rgb_brightness(255, 64, 255);
	timer0_initialize(T0CKPS_8192, 255);
	timer0_enable(true);

	while (1)
	{
		//rgb_rainbow_update();
		continue;

		Header header;
		U8 data [4];

		bool ready = link_state_machine(&header, data, sizeof(data));

		if (ready)
		{
			link_state_machine_reset();
			Result result = link_verify(&header, data);

			if (result == RESULT_SUCCESS)
			{
				result = service(header.opcode, data);
			}

			link_transmit(result);
		}
	}
}
