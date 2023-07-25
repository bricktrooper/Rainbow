#include <xc.h>

#include "system.h"
#include "uart.h"
#include "rgb.h"
#include "link.h"

#define PAYLOAD_BUFFER_SIZE    4

static Result service(Opcode opcode, void * payload)
{
	switch (opcode)
	{
		case OPCODE_PING:
		{
			return RESULT_SUCCESS;
		}
		case OPCODE_COLOUR:
		{
			// disable cycle if needed
			if (rgb_cycling())
			{
				rgb_cycle(false);
			}

			RGB * colour = payload;
			rgb_colour(colour->red, colour->green, colour->blue);
			return RESULT_SUCCESS;
		}
		case OPCODE_BRIGHTNESS:
		{
			RGB * brightness = payload;
			rgb_brightness(brightness->red, brightness->green, brightness->blue);
			return RESULT_SUCCESS;
		}
		case OPCODE_CYCLE:
		{
			U8 speed = *(U8 *)payload;
			rgb_cycle(false);
			rgb_cycle_speed(speed);
			rgb_cycle(true);
			return RESULT_SUCCESS;
		}
		case OPCODE_REBOOT:
		{
			link_respond(RESULT_SUCCESS);   // send last response before reboot
			while (uart_peek_tx() > 0);     // wait for response packet to be transmitted
			system_reboot();                // trigger reboot
			while (1);                      // do nothing until reboot happens
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
	rgb_default();

	while (1)
	{
		// run RX state machine
		Header header;
		U8 payload [PAYLOAD_BUFFER_SIZE];
		bool ready = link_listen(&header, payload, PAYLOAD_BUFFER_SIZE);

		if (ready)
		{
			Result result = link_verify(&header, payload);

			if (result == RESULT_SUCCESS)
			{
				result = service(header.opcode, payload);
			}

			link_respond(result);
		}

		// update cycle state machine if neeed
		if (rgb_cycling())
		{
			rgb_cycle_update();
		}
	}
}
