#include "uart.h"

#include <xc.h>
#include <stddef.h>

#include "system.h"
#include "pps.h"
#include "queue.h"

#define RX_BUFFER_SIZE   16
#define TX_BUFFER_SIZE   16

static Queue rx_queue;
static Queue tx_queue;

static U8 rx_buffer [RX_BUFFER_SIZE];
static U8 tx_buffer [TX_BUFFER_SIZE];

static bool non_blocking_rx = false;
static bool non_blocking_tx = false;

void uart_initialize(void)
{
	TX1STAbits.TX9 = 0;     // 8 b transmission
	TX1STAbits.SYNC = 0;    // asynchronous mode
	TX1STAbits.SENDB = 0;   // no break characters
	TX1STAbits.BRGH = 1;    // high baud rate
	TX1STAbits.TXEN = 1;    // enable transmitter

	RC1STAbits.RX9 = 0;    // 8 b reception
	RC1STAbits.CREN = 1;   // continuous reception
	RC1STAbits.SPEN = 1;   // enable serial port

	BAUD1CONbits.SCKP = 0;    // idle TX high
	BAUD1CONbits.BRG16 = 1;   // 16 b baud rate generator
	BAUD1CONbits.WUE = 0;     // disable wake-up
	BAUD1CONbits.ABDEN = 0;   // disable auto-baud detect

	// 115900 bps @ 32 MHz (~115200 bps)
	SP1BRGH = 0;
	SP1BRGL = 68;

	RX1DTPPS = PPSI_RC5;          // use RC5 for RX1
	TRISCbits.TRISC5 = INPUT;     // configure RC5 as input
	ANSELCbits.ANSC5 = DIGITAL;   // configure RC5 as digital

	RC4PPS = PPSO_TX1;            // use RC4 for TX1
	TRISCbits.TRISC4 = OUTPUT;    // configure RC4 as output
	ANSELCbits.ANSC4 = DIGITAL;   // configure RC4 as digital

	uart_non_blocking(false, false);                          // disable non-blocking mode for RX and TX
	queue_initialize(&rx_queue, rx_buffer, RX_BUFFER_SIZE);   // initialize RX queue (used for non-blocking mode)
	queue_initialize(&tx_queue, tx_buffer, TX_BUFFER_SIZE);   // initialize TX queue (used for non-blocking mode)
}

void uart_non_blocking(bool rx, bool tx)
{
	PIE3bits.RC1IE = rx;
	PIE3bits.TX1IE = tx;

	non_blocking_rx = rx;
	non_blocking_tx = tx;
}

static void clear_rx_overrun(void)
{
	RC1STAbits.CREN = 0;
	RC1STAbits.CREN = 1;
}

void uart_transmit(void const * data, U8 size)
{
	char * bytes = (char *)data;

	for (int i = 0; i < size; i++)
	{
		while (!PIR3bits.TX1IF);   // wait for the TX register to empty
		TX1REG = bytes[i];	       // write byte to TX register to start transmission
	}
}

void uart_receive(void * data, U8 size)
{
	char * bytes = (char *)data;

	for (int i = 0; i < size; i++)
	{
		// detect overrun errors
		if (RC1STAbits.OERR)
		{
			ABORT(ABORT_RX_OVERRUN);
			//clear_rx_overrun();
		}

		while (!PIR3bits.RC1IF);   // wait for a byte to arrive in the RX register
		bytes[i] = RC1REG;         // read byte from RX register to clear RC1IF
	}
}

void uart_write(void * data, U8 size)
{
	char * bytes = (char *)data;
	U8 i = 0;

	while (i < size)
	{
		// try to push next byte to queue
		bool result = queue_push(&tx_queue, bytes[i]);

		// move to next byte if push was successful
		if (result)
		{
			i++;
		}
		else
		{
			ABORT(ABORT_TX_BUFFER_OVERFLOW);
		}
	}

	PIE3bits.TX1IE = 1;   // enable TX interrupt since there is new data to send
}

void uart_read(void * data, U8 size)
{
	char * bytes = (char *)data;
	U8 i = 0;

	while (i < size)
	{
		// try to pop next byte from queue
		U8 byte;
		bool result = queue_pop(&rx_queue, &byte);

		// save byte if pop was successful
		if (result)
		{
			bytes[i] = byte;
			i++;
		}
	}
}

U8 uart_peek(void)
{
	return rx_queue.length;
}

void putch(char byte)
{
	if (non_blocking_tx)
	{
		uart_write(&byte, 1);
	}
	else
	{
		uart_transmit(&byte, 1);
	}
}

char getch(void)
{
	char byte;

	if (non_blocking_rx)
	{
		uart_read(&byte, 1);
	}
	else
	{
		uart_receive(&byte, 1);
	}

	return byte;
}

void uart_echo(void)
{
	putch(getch());
}

#include "led.h"
void __interrupt() isr()
{
	if (PIR3bits.RC1IF)
	{
		U8 byte = RC1REG;                            // read byte and clear RC1IF flag
		bool result = queue_push(&rx_queue, byte);   // push byte to RX queue

		if (!result)
		{
			ABORT(ABORT_RX_BUFFER_OVERFLOW);
		}
	}
	if (PIR3bits.TX1IF)
	{
		U8 byte;
		bool result = queue_pop(&tx_queue, &byte);   // pop byte from TX queue

		if (result)
		{
			TX1REG = byte;   // load the byte for transmission
		}

		PIE3bits.TX1IE = result;  // disable TX interrupt if there is no more data to send
	}
}
