#ifndef LINK_H
#define LINK_H

#include <stdbool.h>

#include "types.h"

#define MAX_DATA_LENGTH   256

typedef enum Opcode Opcode;
typedef enum Result Result;
typedef enum State State;

typedef struct Header Header;
typedef struct Packet Packet;
typedef struct RGB RGB;


enum State
{
	STATE_MAGIC,    // waiting for magic number
	STATE_HEADER,   // waiting for rest of header
	STATE_DATA,     // waiting for data
	STATE_READY     // entire packet received and valid
};

enum Opcode
{
	OPCODE_PING       = 0x00,
	OPCODE_COLOUR     = 0x01,
	OPCODE_BRIGHTNESS = 0x02,
	OPCODE_RAINBOW    = 0x03,
	OPCODE_RESPONSE   = 0xFF
} __attribute__((packed));

enum Result
{
	RESULT_SUCCESS           = 0x00,
	RESULT_ERROR_CHECKSUM    = 0x01,
	RESULT_ERROR_OPCODE      = 0x02,
	RESULT_ERROR_DATA_LENGTH = 0x03,
} __attribute__((packed));

struct Header
{
	U16 magic;   // must be the first field
	U8 opcode;   // opcode must always be the first field after magic
	U8 length;   // MAX_DATA_LENGTH == 256
	U8 checksum;
} __attribute__((packed));

struct RGB
{
	U8 red;
	U8 green;
	U8 blue;
} __attribute__((packed));

Result link_receive(Header * header, void * data, U8 length);
void link_transmit(Result result);
Result link_verify(Header * header, void * data);
bool link_state_machine(Header * header, void * data, U8 length);
void link_state_machine_reset(void);

#endif /* LINK_H */
