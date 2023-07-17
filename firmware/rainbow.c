#include <xc.h>

#include "system.h"
#include "led.h"
#include "uart.h"
#include "rgb.h"
#include "link.h"

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
			rgb_rainbow(false);
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
		case OPCODE_RAINBOW:
		{
			rgb_rainbow(true);
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
	rgb_brightness(255, 48, 255);

	while (1)
	{
		Header header;
		U8 payload [4];
		bool ready = link_state_machine(&header, payload, sizeof(payload));

		if (ready)
		{
			Result result = link_verify(&header, payload);

			if (result == RESULT_SUCCESS)
			{
				result = service(header.opcode, payload);
			}

			link_respond(result);
		}
	}
}

void __interrupt() isr()
{
	if (PIR3bits.RC1IF)
	{
		uart_rx_service();
	}

	if (PIR3bits.TX1IF)
	{
		uart_tx_service();
	}

	if (PIR0bits.TMR0IF)
	{
		rgb_rainbow_update();
		PIR0bits.TMR0IF = 0;
	}
}
