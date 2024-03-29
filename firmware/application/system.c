#include "system.h"

#include <xc.h>
#include <stddef.h>
#include <string.h>

#include "config.h"
#include "oscillator.h"
#include "interrupts.h"
#include "gpio.h"
#include "led.h"
#include "uart.h"
#include "pwm.h"
#include "rgb.h"

#define COLON   ": "

static char * abort_reasons [ABORT_count] = {
	"RX_OVERRUN",
	"RX_BUFFER_OVERFLOW",
	"TX_BUFFER_OVERFLOW",
	"PAYLOAD_OVERFLOW",
	"INVALID_BAUD_RATE",
};

static inline void startup_indicator(void)
{
	led_blink(3);
}

void system_initialize(void)
{
	// OSCILLATOR //

	oscillator_initialize();

	// INTERRUPTS //

	interrupts_initialize();

	// PERIPHERALS //

	gpio_initialize();
	uart_initialize();
	pwm_initialize();

	// DRIVERS //

	led_initialize();
	rgb_initialize();

	// FINALIZE //

	startup_indicator();       // flash status LED
	interrupts_global(true);   // unmask all interrupts
}

void system_abort(Abort abort, char const * caller)
{
	rgb_off();   // turn RGB lights off

	while (1)
	{
		led_blink(1);   // blink LED

		// dump abort reason to UART
		if (abort < ABORT_count)
		{
			char * reason = abort_reasons[abort];

			if (caller != NULL)
			{
				uart_transmit(caller, (U8)strlen(caller));
				uart_transmit(COLON, sizeof(COLON) - 1);
			}

			uart_transmit(reason, (U8)strlen(reason));
			uart_transmit(NEWLINE, sizeof(NEWLINE) - 1);
		}
	}
}

void system_reboot(void)
{
	// enable watchdog timer to force reset
	WDTCON0bits.SWDTEN = 1;
}

// ===================== INTERRUPT SERVICE ===================== //

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
