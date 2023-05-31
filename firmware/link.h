#ifndef LINK_H
#define LINK_H

#include "types.h"

typedef enum Opcode Opcode;
typedef enum Result Result;

typedef struct Header Header;
typedef struct Packet Packet;

enum Opcode
{
	OPCODE_PING       = 0x00,
	OPCODE_RESPONSE   = 0x01,
	OPCODE_RGB        = 0x02,
	OPCODE_BRIGHTNESS = 0x03,
	OPCODE_RAINBOW    = 0x04
} __attribute__((packed));

enum Result
{
	RESULT_SUCCESS = 0x0,
	RESULT_ERROR   = 0x1
} __attribute__((packed));

struct Header
{
	U16 magic;
	U8 opcode;
	U8 length;
	U8 checksum;
} __attribute__((packed));

void link_receive(Header * header, void * data);
void link_transmit(Result result);
U8 link_checksum(Header * header, void * data);

#endif /* LINK_H */
