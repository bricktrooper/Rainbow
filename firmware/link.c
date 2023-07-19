#include "link.h"

#include "uart.h"
#include "system.h"
#include "led.h"

#define MAGIC   0xCE23

#define STATE_MACHINE_RETRIES   500

typedef enum State State;

enum State
{
	STATE_MAGIC,     // waiting for magic number
	STATE_HEADER,    // waiting for rest of header
	STATE_PAYLOAD,   // waiting for payload
	STATE_READY      // entire packet received and valid
};

static State state = STATE_MAGIC;

static inline U8 get_payload_length(Opcode opcode)
{
	switch (opcode)
	{
		case OPCODE_PING:       return 0;
		case OPCODE_COLOUR:     return sizeof(RGB);
		case OPCODE_BRIGHTNESS: return sizeof(RGB);
		case OPCODE_CYCLE:      return 1;
		case OPCODE_RESPONSE:   return 1;
		default:                return 0;
	}
}

static bool valid_opcode(U8 opcode)
{
	return opcode < OPCODE_count;
}

static U8 calculate_checksum(Header * header, void * payload)
{
	U8 checksum = header->checksum;   // cancel out XOR of checksum (A (+) A = 0)

	for (U8 i = 0; i < sizeof(Header); i++)
	{
		U8 * bytes = (U8 *)header;
		checksum ^= bytes[i];
	}

	for (U8 i = 0; i < header->length; i++)
	{
		U8 * bytes = (U8 *)payload;
		checksum ^= bytes[i];
	}

	return checksum;
}

bool link_listen(Header * header, void * payload, U8 length)
{
	bool ready = false;
	static U16 retries = STATE_MACHINE_RETRIES;

	switch (state)
	{
		case STATE_MAGIC:
		{
			U8 const length = sizeof(header->magic);

			if (uart_peek_rx() < length)
			{
				break;
			}

			uart_read(&header->magic, length);

			if (header->magic != MAGIC)
			{
				break;
			}

			led_on();               // visual indicator that a packet was discovered
			state = STATE_HEADER;   // fall through
			retries = UINT16_MAX;
		}
		case STATE_HEADER:
		{
			retries--;

			// reset state machine after retries expire
			if (retries == 0)
			{
				state = STATE_MAGIC;
				break;
			}

			U8 const length = sizeof(Header) - sizeof(header->magic);

			if (uart_peek_rx() < length)
			{
				break;
			}

			uart_read(&header->opcode, length);

			if (header->length > length)
			{
				ABORT(ABORT_PAYLOAD_OVERFLOW);
			}

			state = STATE_PAYLOAD;   // fall through
			retries = UINT16_MAX;
		}
		case STATE_PAYLOAD:
		{
			retries--;

			// reset state machine after retries expire
			if (retries == 0)
			{
				state = STATE_MAGIC;
				break;
			}

			if (uart_peek_rx() < header->length)
			{
				break;
			}

			uart_read(payload, header->length);
			state = STATE_READY;   // fall through
		}
		case STATE_READY:
		{
			/*
			There is nothing to do here since the entire packet is received.
			The packet should be verified by the caller.
			The state machine resets here and starts looking for the next magic number.
			*/

			ready = true;
			state = STATE_MAGIC;   // reset state machine
			break;
		}
		default:
		{
			state = STATE_MAGIC;
			break;
		}
	}

	if (state == STATE_MAGIC)
	{
		led_off();
	}

	return ready;
}

Result link_listen_blocking(Header * header, void * payload, U8 length)
{
	// wait for magic number to be received
	do
	{
		uart_receive(&header->magic, sizeof(header->magic));
	}
	while (header->magic != MAGIC);

	// receive rest of header
	uart_receive((U8 *)header + sizeof(header->magic), sizeof(Header) - sizeof(header->magic));

	// receive payload
	if (length < header->length)
	{
		ABORT(ABORT_PAYLOAD_OVERFLOW);
	}

	uart_receive(payload, header->length);

	// verify checksum
	if (calculate_checksum(header, payload) != header->checksum)
	{
		return RESULT_ERROR_CHECKSUM;
	}

	// verify payload length
	if (get_payload_length(header->opcode) != header->length)
	{
		return RESULT_ERROR_PAYLOAD_LENGTH;
	}

	// packet is valid
	return RESULT_SUCCESS;
}

void link_respond(Result result)
{
	Header header;
	header.magic = MAGIC;
	header.opcode = OPCODE_RESPONSE;
	header.length = sizeof(Result);
	header.checksum = calculate_checksum(&header, &result);

	uart_write(&header, sizeof(Header));
	uart_write(&result, header.length);
}

Result link_verify(Header * header, void * payload)
{
	// verify opcode
	if (!valid_opcode(header->opcode))
	{
		return RESULT_ERROR_OPCODE;
	}

	// verify checksum
	if (calculate_checksum(header, payload) != header->checksum)
	{
		return RESULT_ERROR_CHECKSUM;
	}

	// verify payload length
	if (get_payload_length(header->opcode) != header->length)
	{
		return RESULT_ERROR_PAYLOAD_LENGTH;
	}

	// packet is valid
	return RESULT_SUCCESS;
}
