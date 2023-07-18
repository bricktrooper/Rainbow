import struct
import log
import uart

from log import colours
from enum import IntEnum
from cli import ERROR, SUCCESS

class RGB:
	FORMAT = "<BBB"   # little endian
	SIZE = struct.calcsize(FORMAT)

	def __init__(self, red = 0, green = 0, blue = 0):
		self.red = red
		self.green = green
		self.blue = blue

	def __str__(self):
		string = ""
		string += "%s%-5s%s : %u\n" % (colours.RED, "red", colours.RESET, self.red)
		string += "%s%-5s%s : %u\n" % (colours.GREEN, "green", colours.RESET, self.green)
		string += "%s%-5s%s : %u" % (colours.BLUE, "blue", colours.RESET, self.blue)
		return string

	def print(self):
		print(str(self))

	def unpack(self, data, offset = 0):
		fields = struct.unpack_from(RGB.FORMAT, data, offset)
		self.red = fields[0]
		self.green = fields[1]
		self.blue = fields[2]

	def pack(self):
		return struct.pack(
			self.FORMAT,
			self.red,
			self.green,
			self.blue,
		)

class Opcode(IntEnum):
	PING       = 0x00
	COLOUR     = 0x01
	BRIGHTNESS = 0x02
	RAINBOW    = 0x03
	RESPONSE   = 0xFF

class Result(IntEnum):
	SUCCESS              = 0x00
	ERROR_CHECKSUM       = 0x01
	ERROR_OPCODE         = 0x02
	ERROR_PAYLAOD_LENGTH = 0x03

OPCODES = {
	"PING":         { "opcode": Opcode.PING,       "length": 0},
	"COLOUR":       { "opcode": Opcode.COLOUR,     "length": RGB.SIZE},
	"BRIGHTNESS":   { "opcode": Opcode.BRIGHTNESS, "length": RGB.SIZE},
	"RAINBOW":      { "opcode": Opcode.RAINBOW,    "length": 0},
	"RESPONSE":     { "opcode": Opcode.RESPONSE,   "length": 1}
}

def opcode_name(opcode):
	for i in OPCODES:
		if OPCODES[i]["opcode"] == opcode:
			return i
	log.error("No such opcode '0x%X'" % (opcode))
	return ERROR

class Header:
	FORMAT = "<HBBB"   # little endian
	SIZE = struct.calcsize(FORMAT)
	MAGIC = 0xCE23
	MAGIC_FORMAT = "<H"
	MAGIC_SIZE = struct.calcsize(MAGIC_FORMAT)
	MAX_PAYLOAD_LENGTH = 255

	def __init__(self, magic = 0, opcode = 0, length = 0, checksum = 0):
		self.magic = magic
		self.opcode = opcode
		self.length = length
		self.checksum = checksum

		if length is not None and length > Header.MAX_PAYLOAD_LENGTH:
			log.error(f"Payload length cannot exceed 255")
			exit(ERROR)

	def __str__(self):
		string = ""
		string += "%s%-8s%s : 0x%X\n" % (colours.MAGENTA, "magic", colours.RESET, self.magic)
		string += "%s%-8s%s : 0x%X\n" % (colours.MAGENTA, "opcode", colours.RESET, self.opcode)
		string += "%s%-8s%s : %u\n" % (colours.MAGENTA, "length", colours.RESET, self.length)
		string += "%s%-8s%s : 0x%X" % (colours.MAGENTA, "checksum", colours.RESET, self.checksum)
		return string

	def print(self):
		print(str(self))

	def unpack(self, payload, offset = 0):
		fields = struct.unpack_from(Header.FORMAT, payload, offset)
		self.magic = fields[0]
		self.opcode = fields[1]
		self.length = fields[2]
		self.checksum = fields[3]

	def pack(self):
		return struct.pack(
			self.FORMAT,
			self.magic,
			self.opcode,
			self.length,
			self.checksum
		)

def calculate_checksum(header, payload):
	checksum = header.checksum   # cancel out XOR of checksum (A (+) A = 0)

	data = header.pack()
	for i in range(Header.SIZE):
		checksum ^= data[i]

	for i in range(header.length):
		checksum ^= payload[i]

	return checksum

def verify(header, payload):
	# verify checksum
	checksum = calculate_checksum(header, payload)
	if header.checksum != checksum:
		log.error("Expected checksum '0x%X' but received '0x%X'" % (checksum, header.checksum))
		return ERROR

	# verify payload length
	length = OPCODES[opcode_name(header.opcode)]["length"]
	if header.length != length:
		log.error("Expected length '0x%X' but received '0x%X'" % (length, header.length))
		return ERROR

	# verify opcode
	if header.opcode != Opcode.RESPONSE:
		log.error("Expected opcode '0x%X' but received '0x%X'" % (Opcode.RESPONSE, header.opcode))
		return ERROR

	return SUCCESS

def request(opcode, payload):
	name = opcode_name(opcode)
	length = OPCODES[name]["length"]
	if length != len(payload):
		log.error(f"Opcode '{name}' requires length '{length}' but found '{len(payload)}'")
		return ERROR

	header = Header()
	header.magic = Header.MAGIC
	header.opcode = opcode
	header.length = length
	header.checksum = calculate_checksum(header, payload)
	log.verbose(f"Request:\n{header}")

	uart.transmit(header.pack())
	uart.transmit(payload)

def listen():
	# wait for magic number to be received
	data = None

	magic = ~Header.MAGIC
	while magic != Header.MAGIC:
		data = uart.receive(Header.MAGIC_SIZE)
		if len(data) != Header.MAGIC_SIZE:
			log.error(f"Did not receive magic number")
			return ERROR
		fields = struct.unpack(Header.MAGIC_FORMAT, data)
		magic = fields[0]

	# receive rest of header and combine with magic
	data += uart.receive(Header.SIZE - Header.MAGIC_SIZE)
	if len(data) != Header.SIZE:
		log.error(f"Did not receive header")
		return ERROR

	# unpack entire header
	header = Header()
	header.unpack(data)
	log.verbose(f"Response:\n{header}")

	# receive payload
	payload = uart.receive(header.length)
	if len(payload) != header.length:
		log.error(f"Did not receive payload")
		return ERROR

	# verify response packet
	if verify(header, payload) == ERROR:
		log.error(f"Received invalid response packet")
		return ERROR

	log.success(f"Received response packet")
	return header, payload

def ping():
	if request(Opcode.PING, []) == ERROR:
		return ERROR
	if listen() == ERROR:
		return ERROR
	return SUCCESS

def rainbow():
	if request(Opcode.RAINBOW, []) == ERROR:
		return ERROR
	if listen() == ERROR:
		return ERROR
	return SUCCESS
