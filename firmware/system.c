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

#define LED_DELAY_US   200000
#define LED_BLINKS     3

#define NEWLINE   "\r\n"
#define COLON     ": "

static char * system_abort_reasons [ABORT_count] = {
	"NULL POINTER"
};

static void startup_indicator(void)
{
	for (int i = 0; i < LED_BLINKS; i++)
	{
		led_on();
		_delay(LED_DELAY_US);
		led_off();
		_delay(LED_DELAY_US);
	}
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
	while (1)
	{
		led_blink();   // blink LED

		// dump abort reason to UART
		if (abort < ABORT_count)
		{
			char * reason = system_abort_reasons[abort];

			if (caller != NULL)
			{
				uart_transmit(caller, strlen(caller));
				uart_transmit(COLON, sizeof(COLON) - 1);
			}

			uart_transmit(reason, strlen(reason));
			uart_transmit(NEWLINE, sizeof(NEWLINE) - 1);
		}
	}
}

//void system_reboot(void)
//{
//	WDTCONbits.SWDTEN = 1;   // enable watchdog timer to force reset
//}
