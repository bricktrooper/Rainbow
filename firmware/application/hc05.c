#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "system.h"
#include "uart.h"
#include "led.h"
#include "oscillator.h"

typedef enum AT_ROLE AT_ROLE;
typedef enum CMODE CMODE;

enum AT_ROLE
{
	SLAVE = 0,
	MASTER = 1,
};

enum CMODE
{
	BIND = 0,
	ANY = 1,
	SLAVE_LOOP = 2,
};

static U8 count = 1;

// ===================== UTILITIES ===================== //

static void wait(void)
{
	_delay(10000000);
}

static void verify(void)
{
	led_on();
	while (uart_peek_tx() > 0);          // wait for TX data to be transmitted
	char response [4];
	uart_read(response, sizeof(response));   // receive response from HC-05
	led_off();

	if (strncmp(response, "OK" NEWLINE, sizeof(response)))
	{
		// abort and blink error code
		while (1)
		{
			led_blink(count);
			wait();
		}
	}

	count++;
}

// ===================== AT COMMANDS ===================== //

static void at_ping(void)
{
	printf("AT" NEWLINE);
	verify();
}

static void at_role(AT_ROLE role)
{
	printf("AT+ROLE=%u" NEWLINE, role);
	verify();
}

static void at_uart(U32 baud_rate, U8 stop_bits, bool parity)
{
	printf("AT+UART=%lu,%u,%u" NEWLINE, baud_rate, stop_bits, parity);
	verify();
}

static void at_cmode(CMODE cmode)
{
	printf("AT+CMODE=%u" NEWLINE, cmode);
	verify();
}

static void at_rmaad(void)
{
	// remove all paired devices
	printf("AT+RMAAD" NEWLINE);
	verify();
}

static void at_pswd(char const * password)
{
	printf("AT+PSWD=%s" NEWLINE, password);
	verify();
}

static void at_orgl(void)
{
	// default settings
	printf("AT+ORGL" NEWLINE);
	verify();
}

static void at_name(char const * name)
{
	printf("AT+NAME=%s" NEWLINE, name);
	verify();
}

static void at_reset(void)
{
	printf("AT+RESET" NEWLINE);
	// don't wait for response because reset exits AT command mode
}

// ===================== SCRIPT ===================== //

void hc05(char const * name)
{
	system_initialize();
	led_off();

	U32 baud_rate = uart_get_baud_rate();   // get baud rate before it is changed for AT mode
	uart_set_baud_rate(38400);              // change baud rate temporarily for AT commands
	wait();

	at_ping();                      // ping HC-05
	at_orgl();                      // restore default settings
	at_role(SLAVE);                 // configure as slave
	at_cmode(ANY);                  // connect to any Bluetooth device
	at_uart(baud_rate, 0, false);   // UART settings
	at_name(name);                  // Bluetooth wireless name

	uart_set_baud_rate(baud_rate);   // restore original baud rate

	// blink LED slowly to indicate end of program
	while (1)
	{
		led_on();
		wait();
		led_off();
		wait();
	}
}
