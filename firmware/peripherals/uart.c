#include "uart.h"

#include <xc.h>
#include <stddef.h>

#include "system.h"

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

	SP1BRGH = 0;   // 117600 bps @ 8 MHz (~115200 bps)
	SP1BRGL = 16;

	RX1DTPPS = 0x15;              // use RC5 for RX1
	TRISCbits.TRISC5 = INPUT;     // configure RC5 as input
	ANSELCbits.ANSC5 = DIGITAL;   // configre RC5 as digital

	RC4PPS = 0x0F;                // use RC4 for TX1
	TRISCbits.TRISC4 = OUTPUT;    // configure RC4 as output
	ANSELCbits.ANSC4 = DIGITAL;   // configre RC4 as digital
}

void uart_transmit(void const * data, U8 size)
{
	//if (data == NULL)
	//{
	//	system_fatal();
	//}

	char * bytes = (char *)data;      // cast data element to char pointer

	for (int i = 0; i < size; i++)
	{
		while (!PIR3bits.TX1IF);   // Wait for the the TX register to empty.
		TX1REG = bytes[i];	       // Write 8 b data into the TX register to start the transmission.
	}
}

void uart_receive(void * data, U8 size)
{
	//if (data == NULL)
	//{
	//	system_fatal();
	//}

	char * bytes = (char *)data;

	for (int i = 0; i < size; i++)
	{
		// Detect and clear overrun errors
		if (RC1STAbits.OERR)
		{
			RC1STAbits.CREN = 0;
			RC1STAbits.CREN = 1;
		}

		while (!PIR3bits.RC1IF);   // Wait for a byte to arrive in the RX register.
		bytes[i] = RC1REG;         // Read the byte from the RX register to clear RC1IF.
	}
}

void putch(char byte)
{
	uart_transmit(&byte, 1);
}
