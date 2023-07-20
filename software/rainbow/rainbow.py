import log
import struct

from . import uart
from . import link

from log import colours
from cli import ERROR, SUCCESS
from .link import Opcode
from .rgb import RGB

# ===================== CONSTANTS ===================== #

UINT8_MAX = 255
MAX_PINGS = 100

# ===================== UART ===================== #

def connect():
	uart.connect()

def disconnect():
	uart.disconnect()

# ===================== UTILITIES ===================== #

def parse_unsigned(name, string, min, max):
	value = None

	try:
		value = int(string)
	except ValueError:
		log.error(f"'{name}' must be an integer")
		return None

	if value < min or value > max:
		log.error(f"'{name}' must be between {min} and {max}")
		return None

	return value

def parse_rgb(red, green, blue):
	red = parse_unsigned("red", red, 0, UINT8_MAX)
	if red == None:
		return None
	green = parse_unsigned("green", green, 0, UINT8_MAX)
	if green == None:
		return None
	blue = parse_unsigned("blue", blue, 0, UINT8_MAX)
	if blue == None:
		return None
	return RGB(red, green, blue)

# ===================== REQUESTS ===================== #

def ping(count = 1):
	count = parse_unsigned("count", count, 0, MAX_PINGS)
	if count == ERROR:
		return ERROR
	log.info(f"PING")
	for i in range(count):
		if link.request(Opcode.PING, []) == ERROR:
			return ERROR
		if link.listen() == ERROR:
			return ERROR
	return SUCCESS

def cycle(speed):
	speed = parse_unsigned("speed", speed, 0, UINT8_MAX)
	if speed == None:
		return None
	log.info(f"CYCLE {colours.YELLOW}speed{colours.RESET}: {speed}")
	payload = struct.pack("<B", speed)
	if link.request(Opcode.CYCLE, payload) == ERROR:
		return ERROR
	if link.listen() == ERROR:
		return ERROR
	return SUCCESS

def colour(red, green, blue):
	rgb = parse_rgb(red, green, blue)
	if rgb is None:
		return ERROR
	log.info(f"COLOUR {rgb}")
	payload = rgb.pack()
	if link.request(Opcode.COLOUR, payload) == ERROR:
		return ERROR
	if link.listen() == ERROR:
		return ERROR
	return SUCCESS

def brightness(red, green, blue):
	rgb = parse_rgb(red, green, blue)
	if rgb is None:
		return ERROR
	log.info(f"BRIGHTNESS {rgb}")
	payload = rgb.pack()
	if link.request(Opcode.BRIGHTNESS, payload) == ERROR:
		return ERROR
	if link.listen() == ERROR:
		return ERROR
	return SUCCESS

def reboot():
	if link.request(Opcode.REBOOT, []) == ERROR:
		return ERROR
	if link.listen() == ERROR:
		return ERROR
	return SUCCESS
