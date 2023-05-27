#include "link.h"

#include "uart.h"

#define MAGIC   0xBEEF

void link_receive(Header * header, void * data)
{
	do
	{
		U16 byte = ~MAGIC;

		while (byte != MAGIC)
		{
			uart_receive(&byte, 1);
		}

		uart_receive((U8 *)header + sizeof(header->magic), sizeof(Header) - sizeof(header->magic));
		uart_receive(data, header->length);
	}
	while (link_checksum(header, data) != header->checksum);
}

void link_transmit(Opcode opcode, void * data, U8 length)
{
	Header header;
	header.magic = MAGIC;
	header.opcode = opcode;
	header.length = length;
	header.checksum = link_checksum(&header, data);

	uart_transmit(&header, sizeof(Header));
	uart_transmit(data, length);
}

U8 link_checksum(Header * header, void * data)
{
	U8 checksum = header->checksum;   // cancel out XOR of checksum

	for (U8 i = 0; i < sizeof(Header); i++)
	{
		U8 * bytes = (U8 *)header;
		checksum ^= bytes[i];
	}

	for (U8 i = 0; i < header->length; i++)
	{
		U8 * bytes = (U8 *)data;
		checksum ^= bytes[i];
	}

	return checksum;
}
