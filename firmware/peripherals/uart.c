#include "uart.h"

#include <xc.h>
#include <stddef.h>

#include "system.h"
#include "pps.h"
#include "queue.h"
#include "oscillator.h"

// size can range from 0 to 255
#define RX_BUFFER_SIZE   16
#define TX_BUFFER_SIZE   UINT8_MAX

static U32 baud_rate = DEFAULT_BAUD_RATE;

static Queue rx_queue;
static Queue tx_queue;

static U8 rx_buffer [RX_BUFFER_SIZE];
static U8 tx_buffer [TX_BUFFER_SIZE];

static bool rx_interrupt = false;
static bool tx_interrupt = false;

void uart_initialize(void)
{
	TX1STAbits.TX9 = 0;     // 8 b transmission
	TX1STAbits.SYNC = 0;    // asynchronous mode
	TX1STAbits.SENDB = 0;   // no break characters
	TX1STAbits.BRGH = 1;    // high baud rate
	TX1STAbits.TXEN = 1;    // enable transmitter

	RC1STAbits.RX9 = 0;     // 8 b reception
	RC1STAbits.CREN = 1;    // continuous reception
	RC1STAbits.SPEN = 1;    // enable serial port

	BAUD1CONbits.SCKP = 0;    // idle TX high
	BAUD1CONbits.BRG16 = 1;   // 16 b baud rate generator
	BAUD1CONbits.WUE = 0;     // disable wake-up
	BAUD1CONbits.ABDEN = 0;   // disable auto-baud detect

	RX1DTPPS = PPSI_RC5;          // use RC5 for RX1
	TRISCbits.TRISC5 = INPUT;     // configure RC5 as input
	ANSELCbits.ANSC5 = DIGITAL;   // configure RC5 as digital

	RC4PPS = PPSO_TX1;            // use RC4 for TX1
	TRISCbits.TRISC4 = OUTPUT;    // configure RC4 as output
	ANSELCbits.ANSC4 = DIGITAL;   // configure RC4 as digital

	uart_set_baud_rate(115200);   // set baud rate (must be done after setting BGRH and BRG16)

	uart_interrupts(true, true);                              // enable non-blocking mode for RX and TX (uses interrupts)
	queue_initialize(&rx_queue, rx_buffer, RX_BUFFER_SIZE);   // initialize RX queue (used for non-blocking mode)
	queue_initialize(&tx_queue, tx_buffer, TX_BUFFER_SIZE);   // initialize TX queue (used for non-blocking mode)
}

void uart_interrupts(bool rx, bool tx)
{
	PIE3bits.RC1IE = rx;
	PIE3bits.TX1IE = tx;

	rx_interrupt = rx;
	tx_interrupt = tx;
}

static void clear_rx_overrun(void)
{
	RC1STAbits.CREN = 0;
	RC1STAbits.CREN = 1;
}

void uart_transmit(void const * data, U8 length)
{
	char * bytes = (char *)data;

	for (int i = 0; i < length; i++)
	{
		while (!PIR3bits.TX1IF);   // wait for the TX register to empty
		TX1REG = bytes[i];	       // write byte to TX register to start transmission
	}
}

void uart_receive(void * data, U8 length)
{
	char * bytes = (char *)data;

	for (int i = 0; i < length; i++)
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

void uart_push(void * data, U8 length)
{
	char * bytes = (char *)data;
	U8 i = 0;

	while (i < length)
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

	// enable TX interrupt since there is new data to send
	PIE3bits.TX1IE = 1;
}

void uart_pop(void * data, U8 length)
{
	char * bytes = (char *)data;
	U8 i = 0;

	while (i < length)
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

void uart_read(void * data, U8 length)
{
	if (rx_interrupt)
	{
		uart_pop(data, length);   // non-blocking
	}
	else
	{
		uart_receive(data, length);   // blocking
	}
}

void uart_write(void * data, U8 length)
{
	if (tx_interrupt)
	{
		uart_push(data, length);   // non-blocking
	}
	else
	{
		uart_transmit(data, length);   // blocking
	}
}

U8 uart_peek_rx(void)
{
	return rx_queue.length;
}

U8 uart_peek_tx(void)
{
	return tx_queue.length;
}

void putch(char byte)
{
	uart_write(&byte, 1);
}

char getch(void)
{
	char byte;
	uart_read(&byte, 1);
	return byte;
}

void uart_echo(void)
{
	putch(getch());
}

void uart_rx_service(void)
{
	U8 byte = RC1REG;                            // read byte and clear RC1IF flag
	bool result = queue_push(&rx_queue, byte);   // push byte to RX queue

	if (!result)
	{
		ABORT(ABORT_RX_BUFFER_OVERFLOW);
	}
}

void uart_tx_service(void)
{
	U8 byte;

	// pop byte from TX queue
	bool result = queue_pop(&tx_queue, &byte);

	if (result)
	{
		// load the byte for transmission
		TX1REG = byte;
	}

	// disable TX interrupt if there is no more data to send
	PIE3bits.TX1IE = result;
}

void uart_set_baud_rate(U32 rate)
{
	if (rate > MAX_BAUD_RATE)
	{
		ABORT(ABORT_INVALID_BAUD_RATE);
	}

	U32 k = 0;
	bool BRGH = TX1STAbits.BRGH;
	bool BRG16 = BAUD1CONbits.BRG16;

	if (BRG16 & BRGH)
	{
		k = 4;
	}
	else if (BRG16 ^ BRGH)
	{
		k = 16;
	}
	else   // BRG16 == 0 && BRGH == 0
	{
		k = 64;
	}

	U32 f = oscillator_get_frequency();
	U16 spbrg = (U16)((f / (k * rate)) - 1);

	SP1BRGH = (U8)(spbrg >> 8);
	SP1BRGL = (U8)(spbrg & 0xFF);

	baud_rate = rate;
}

U32 uart_get_baud_rate(void)
{
	return baud_rate;
}

void uart_purge_rx(void)
{
	queue_reset(&rx_queue);
}

void uart_purge_tx(void)
{
	queue_reset(&tx_queue);
}
