import struct
import log

from log import colours
from enum import IntEnum

#define MAX_DATA_LENGTH   256

class Opcode(IntEnum):
	PING       = 0x00
	COLOUR     = 0x01
	BRIGHTNESS = 0x02
	RAINBOW    = 0x03
	RESPONSE   = 0xFF

class Result(IntEnum):
	SUCCESS           = 0x00
	ERROR_CHECKSUM    = 0x01
	ERROR_OPCODE      = 0x02
	ERROR_DATA_LENGTH = 0x03

class Header:
	FORMAT = "HBBB"
	SIZE = struct.calcsize(FORMAT)
	MAGIC = 0xCE23

	def __init__(self, magic = None, opcode = None, length = None, checksum = None):
		self.magic = magic
		self.opcode = opcode
		self.length = length   # MAX_DATA_LENGTH == 256
		self.checksum = checksum

	def __str__(self):
		string = ""
		string += "%s%-8s%s : 0x%X\r\n" % (colours.MAGENTA, "magic", colours.RESET, self.magic)
		string += "%s%-8s%s : 0x%X\r\n" % (colours.MAGENTA, "opcode", colours.RESET, self.opcode)
		string += "%s%-8s%s : %u\r\n" % (colours.MAGENTA, "length", colours.RESET, self.length)
		string += "%s%-8s%s : 0x%X\r\n" % (colours.MAGENTA, "checksum", colours.RESET, self.checksum)
		return string

	def unpack(self, data, offset = 0):
		# little endian
		fields = struct.unpack_from(f"<{Header.FORMAT}", data, offset)
		self.magic = fields[0]
		self.opcode = fields[1]
		self.length = fields[2]
		self.checksum = fields[3]

class RGB:
	FORMAT = "BBB"
	SIZE = struct.calcsize(FORMAT)

	def __init__(self, red = None, green = None, blue = None):
		self.red = red
		self.green = green
		self.blue = blue

	def __str__(self):
		string = ""
		string += "%s%-5s%s : %u\r\n" % (colours.RED, "red", colours.RESET, self.red)
		string += "%s%-5s%s : %u\r\n" % (colours.GREEN, "green", colours.RESET, self.green)
		string += "%s%-5s%s : %u\r\n" % (colours.BLUE, "blue", colours.RESET, self.blue)
		return string

	def unpack(self, data, offset = 0):
		# little endian
		fields = struct.unpack_from(f"<{RGB.FORMAT}", data, offset)
		self.red = fields[0]
		self.green = fields[1]
		self.blue = fields[2]

#def receive():
#	# wait for magic number to be received
#	log.debug("Listening for magic number")
#	magic = ~Header.MAGIC
#	while magic != Header.MAGIC:
#		uart_receive(&header->magic, sizeof(header->magic))

#	// receive rest of header
#	uart_receive((U8 *)header + sizeof(header->magic), sizeof(Header) - sizeof(header->magic));

#	// receive data
#	if (length < header->length)
#	{
#		ABORT(ABORT_RX_BUFFER_OVERFLOW);
#	}

#	uart_receive(data, header->length);

#	// verify checksum
#	if (link_checksum(header, data) != header->checksum)
#	{
#		return RESULT_ERROR_CHECKSUM;
#	}

#	// verify data length
#	if (link_data_length(header->opcode) != header->length)
#	{
#		return RESULT_ERROR_DATA_LENGTH;
#	}

#	// packet is valid
#	return RESULT_SUCCESS;

#void link_transmit(Result result);
#U8 link_checksum(Header * header, void * data);
#U8 link_data_length(Opcode opcode);
