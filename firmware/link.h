#ifndef LINK_H
#define LINK_H

#include "types.h"

typedef enum Opcode Opcode;

typedef struct Header Header;
typedef struct Packet Packet;

enum Opcode
{
	OPCODE_PING    = 0x00,
	OPCODE_RGB     = 0x01,
	OPCODE_RAINBOW = 0x02
} __attribute__((packed));

struct Header
{
	U16 magic;
	U8 opcode;
	U8 length;
	U8 checksum;
} __attribute__((packed));

void link_receive(Header * header, void * data);
void link_transmit(Opcode opcode, void * data, U8 length);
U8 link_checksum(Header * header, void * data);

#endif /* LINK_H */
