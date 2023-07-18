import struct
import log
import uart

from log import colours
from enum import IntEnum
from cli import ERROR, SUCCESS
from rgb import RGB

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
	ERROR_PAYLOAD_LENGTH = 0x03

OPCODES = {
	"PING":         { "opcode": Opcode.PING,       "length": 0},
	"COLOUR":       { "opcode": Opcode.COLOUR,     "length": RGB.SIZE},
	"BRIGHTNESS":   { "opcode": Opcode.BRIGHTNESS, "length": RGB.SIZE},
	"RAINBOW":      { "opcode": Opcode.RAINBOW,    "length": 1},
	"RESPONSE":     { "opcode": Opcode.RESPONSE,   "length": 1}
}

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
		self.payload = []

		if length is not None and length > Header.MAX_PAYLOAD_LENGTH:
			log.error(f"Payload length cannot exceed 255")
			exit(ERROR)

	def __str__(self):
		string = ""
		string += "%s%-8s%s : 0x%X\n" % (colours.MAGENTA, "magic", colours.RESET, self.magic)
		string += "%s%-8s%s : 0x%X\n" % (colours.MAGENTA, "opcode", colours.RESET, self.opcode)
		string += "%s%-8s%s : %u\n" % (colours.MAGENTA, "length", colours.RESET, self.length)
		string += "%s%-8s%s : 0x%X\n" % (colours.MAGENTA, "checksum", colours.RESET, self.checksum)

		payload = []
		for i in self.payload:
			payload.append(hex(i))

		string += "%s%-8s%s : %s" % (colours.MAGENTA, "payload", colours.RESET, str(payload))
		return string

	def print(self):
		print(str(self))

	def unpack(self, payload, offset = 0):
		fields = struct.unpack_from(Header.FORMAT, payload, offset)
		self.magic = fields[0]
		self.opcode = Opcode(fields[1])
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
	# verify opcode
	if header.opcode != Opcode.RESPONSE:
		log.error("Expected opcode '0x%X' but received '0x%X'" % (Opcode.RESPONSE, header.opcode))
		return ERROR

	# verify checksum
	checksum = calculate_checksum(header, payload)
	if header.checksum != checksum:
		log.error("Expected checksum '0x%X' but received '0x%X'" % (checksum, header.checksum))
		return ERROR

	# verify payload length
	name = Opcode(header.opcode).name
	length = OPCODES[name]["length"]
	if header.length != length:
		log.error("Expected length '0x%X' but received '0x%X'" % (length, header.length))
		return ERROR

	return SUCCESS

def request(opcode, payload):
	length = OPCODES[opcode.name]["length"]
	if length != len(payload):
		log.error(f"Opcode '{opcode.name}' requires length '{length}' but found '{len(payload)}'")
		return ERROR

	header = Header()
	header.magic = Header.MAGIC
	header.opcode = Opcode(opcode)
	header.length = length
	header.checksum = calculate_checksum(header, payload)
	header.payload = bytes(payload)

	log.debug(f"{header.opcode.name}:\n{header}")
	uart.transmit(header.pack() + header.payload)

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

	# receive payload
	payload = uart.receive(header.length)
	if len(payload) != header.length:
		log.error(f"Did not receive payload")
		return ERROR
	header.payload = payload

	log.debug(f"{header.opcode.name}:\n{header}")

	# verify response packet
	if verify(header, payload) == ERROR:
		log.error(f"Received invalid response packet")
		return ERROR

	result = Result(struct.unpack("<B", payload)[0])
	log.success(f"Response: {result.name}")
	return header, payload

# ===================== REQUESTS ===================== #

def ping():
	log.info("PING")
	if request(Opcode.PING, []) == ERROR:
		return ERROR
	if listen() == ERROR:
		return ERROR
	return SUCCESS

def rainbow(speed):
	log.info(f"RAINBOW {colours.MAGENTA}speed{colours.RESET}: {speed}")
	payload = struct.pack("<B", speed)
	if request(Opcode.RAINBOW, payload) == ERROR:
		return ERROR
	if listen() == ERROR:
		return ERROR
	return SUCCESS

def colour(red, green, blue):
	rgb = RGB(red, green, blue)
	log.info(f"COLOUR {rgb}")
	payload = rgb.pack()
	if request(Opcode.COLOUR, payload) == ERROR:
		return ERROR
	if listen() == ERROR:
		return ERROR
	return SUCCESS

def brightness(red, green, blue):
	rgb = RGB(red, green, blue)
	log.info(f"BRIGHTNESS {rgb}")
	payload = rgb.pack()
	if request(Opcode.BRIGHTNESS, payload) == ERROR:
		return ERROR
	if listen() == ERROR:
		return ERROR
	return SUCCESS
