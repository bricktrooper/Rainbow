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
			U8 speed = *(U8 *)payload;
			rgb_rainbow(false);
			rgb_rainbow_speed(speed);
			rgb_rainbow(true);
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
	rgb_brightness(255, 48, 200);

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

		rgb_rainbow_update();
	}
}

void __interrupt() isr()
{
	if (PIR3bits.RC1IF)
	{
		uart_rx_service();
	}
	else if (PIR3bits.TX1IF)
	{
		uart_tx_service();
	}
}
