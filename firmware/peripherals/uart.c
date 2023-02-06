#include "uart.h"

#include <xc.h>
#include <stddef.h>

#include "system.h"

void uart_initialize(void)
{
	RC1STAbits.RX9 = 0;    // 8 b reception.
	RC1STAbits.CREN = 1;   // Continuous reception.
	RC1STAbits.SPEN = 1;   // Enable serial port.

	TX1STAbits.TX9 = 0;     // 8 b transmission.
	TX1STAbits.SYNC = 0;    // Asynchronous mode.
	TX1STAbits.SENDB = 0;   // No break characters.
	TX1STAbits.TXEN = 0;    // Enable transmitter.
	TX1STAbits.BRGH = 1;    // High baud rate.

	BAUD1CONbits.SCKP = 0;    // Idle TX high.
	BAUD1CONbits.BRG16 = 1;   // 16 b baud rate generator.
	BAUD1CONbits.WUE = 0;     // Disable wake-up.
	BAUD1CONbits.ABDEN = 0;   // Disable auto-baud detect.

	// 9615 bps @ 8 MHz (~9600 bps).
	SP1BRGH = 0;
	SP1BRGL = 207;
}

void uart_transmit(void const * data, U8 length)
{
	//if (data == NULL)
	//{
	//	system_fatal();
	//}

	char * bytes = (char *)data;      // cast data element to char pointer

	for (int i = 0; i < length; i++)
	{
		while (!PIR3bits.TX1IF);   // Wait for the the TX register to empty.
		TX1REG = bytes[i];	       // Write 8 b data into the TX register to start the transmission.
	}
}

void uart_receive(void * data, U8 length)
{
	//if (data == NULL)
	//{
	//	system_fatal();
	//}

	char * bytes = (char *)data;

	for (int i = 0; i < length; i++)
	{
		// Detect and clear overrun errors
		if (RC1STAbits.OERR)
		{
			RC1STAbits.CREN = 0;
			RC1STAbits.CREN = 1;
		}

		while (!PIR3bits.RC1IF);   // Wait for a byte to arrive in the RX register.
		bytes[i] = RC1REG;          // Read the byte from the RX register to clear RC1IF.
	}
}

void putch(char byte)
{
	uart_transmit(&byte, 1);
}
