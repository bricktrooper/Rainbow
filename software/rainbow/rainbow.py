import log
import struct
import time

from . import uart
from . import link
from log import colours
from cli import ERROR, SUCCESS
from .link import Opcode
from .rgb import RGB

# ===================== UART ===================== #

def connect(port):
	return uart.connect(port)

def disconnect():
	return uart.disconnect()

# ===================== REQUESTS ===================== #

def ping(count = 1):
	for i in range(count):
		log.info(f"PING #{i + 1}")
		start = time.time_ns()
		if link.request(Opcode.PING, []) == ERROR:
			return ERROR
		if link.listen() == ERROR:
			return ERROR
		latency = time.time_ns() - start
		log.info("Latency: %.3f ms" % (float(latency) / 1e6))
	return SUCCESS

def cycle(speed):
	log.info(f"CYCLE {colours.YELLOW}speed{colours.RESET}: {speed}")
	payload = struct.pack("<B", speed)
	if link.request(Opcode.CYCLE, payload) == ERROR:
		return ERROR
	if link.listen() == ERROR:
		return ERROR
	return SUCCESS

def colour(red, green, blue):
	rgb = RGB(red, green, blue)
	log.info(f"COLOUR {rgb}")
	payload = rgb.pack()
	if link.request(Opcode.COLOUR, payload) == ERROR:
		return ERROR
	if link.listen() == ERROR:
		return ERROR
	return SUCCESS

def brightness(red, green, blue):
	rgb = RGB(red, green, blue)
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

def off():
	return colour(0, 0, 0)
