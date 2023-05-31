#include "link.h"

#include "uart.h"

#define MAGIC   0xCE23

void link_receive(Header * header, void * data)
{
	do
	{
		header->magic = ~MAGIC;

		while (header->magic != MAGIC)
		{
			uart_receive(&header->magic, sizeof(header->magic));
		}

		uart_receive((U8 *)header + sizeof(header->magic), sizeof(Header) - sizeof(header->magic));
		uart_receive(data, header->length);
	}
	while (link_checksum(header, data) != header->checksum);
}

void link_transmit(Result result)
{
	Header header;
	header.magic = MAGIC;
	header.opcode = OPCODE_RESPONSE;
	header.length = sizeof(Result);
	header.checksum = link_checksum(&header, &result);

	uart_transmit(&header, sizeof(Header));
	uart_transmit(&result, sizeof(Result));
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
