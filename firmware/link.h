#ifndef LINK_H
#define LINK_H

#include <stdbool.h>

#include "types.h"

typedef enum Opcode Opcode;
typedef enum Result Result;

typedef struct Header Header;
typedef struct Packet Packet;
typedef struct RGB RGB;

enum Opcode
{
	OPCODE_PING       = 0x00,
	OPCODE_COLOUR     = 0x01,
	OPCODE_BRIGHTNESS = 0x02,
	OPCODE_RAINBOW    = 0x03,
	OPCODE_REBOOT     = 0x04,

	OPCODE_count,
	OPCODE_RESPONSE   = 0xFF
} __attribute__((packed));

enum Result
{
	RESULT_SUCCESS              = 0x00,
	RESULT_ERROR_CHECKSUM       = 0x01,
	RESULT_ERROR_OPCODE         = 0x02,
	RESULT_ERROR_PAYLOAD_LENGTH = 0x03
} __attribute__((packed));

struct Header
{
	U16 magic;   // must be the first field
	U8 opcode;   // opcode must always be the first field after magic
	U8 length;   // length of payload
	U8 checksum;
} __attribute__((packed));

struct RGB
{
	U8 red;
	U8 green;
	U8 blue;
} __attribute__((packed));

bool link_listen(Header * header, void * payload, U8 length);
Result link_listen_blocking(Header * header, void * payload, U8 length);
void link_respond(Result result);
Result link_verify(Header * header, void * payload);

#endif /* LINK_H */
