#include "link.h"

#include "uart.h"
#include "system.h"

#define MAGIC   0xCE23

Result link_receive(Header * header, void * data, U8 length)
{
	// wait for magic number to be received
	do
	{
		uart_receive(&header->magic, sizeof(header->magic));
	}
	while (header->magic != MAGIC);

	// receive rest of header
	uart_receive((U8 *)header + sizeof(header->magic), sizeof(Header) - sizeof(header->magic));

	// receive data
	if (length < header->length)
	{
		ABORT(ABORT_RX_BUFFER_OVERFLOW);
	}

	uart_receive(data, header->length);

	// verify checksum
	if (link_checksum(header, data) != header->checksum)
	{
		return RESULT_ERROR_CHECKSUM;
	}

	// verify data length
	if (link_data_length(header->opcode) != header->length)
	{
		return RESULT_ERROR_DATA_LENGTH;
	}

	// packet is valid
	return RESULT_SUCCESS;
}

void link_transmit(Result result)
{
	Header header;
	header.magic = MAGIC;
	header.opcode = OPCODE_RESPONSE;
	header.length = link_data_length(header.opcode);
	header.checksum = link_checksum(&header, &result);

	uart_transmit(&header, sizeof(Header));
	uart_transmit(&result, header.length);
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

U8 link_data_length(Opcode opcode)
{
	switch (opcode)
	{
		case OPCODE_PING:       return 0;
		case OPCODE_RGB:        return sizeof(RGB);
		case OPCODE_BRIGHTNESS: return sizeof(U8);
		case OPCODE_RAINBOW:    return 0;
		case OPCODE_RESPONSE:   return sizeof(Result);
	}
}
