#include "uart.h"

#include <xc.h>
#include <stddef.h>

#include "system.h"
#include "pps.h"

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

			// clear overrun error
			//RC1STAbits.CREN = 0;
			//RC1STAbits.CREN = 1;
		}

		while (!PIR3bits.RC1IF);   // wait for a byte to arrive in the RX register
		bytes[i] = RC1REG;         // read byte from RX register to clear RC1IF
	}
}

void putch(char byte)
{
	uart_transmit(&byte, 1);
}

void uart_echo(void)
{
	char byte;
	uart_receive(&byte, 1);
	uart_transmit(&byte, 1);
}
