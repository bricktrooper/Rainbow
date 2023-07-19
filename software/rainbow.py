#! /usr/local/bin/python3

import log
import uart
import link
import struct

from log import colours
from link import Opcode
from os.path import basename
from cli import Command, ERROR, SUCCESS
from sys import argv
from rgb import RGB

# ===================== UTILITIES ===================== #

def parse_unsigned(name, string, min, max):
	value = None

	try:
		value = int(string)
	except ValueError:
		log.error(f"'{name}' must be an integer")
		return ERROR

	if value < min or value > max:
		log.error(f"'{name}' must be between {min} and {max}")
		return ERROR

	return value

# ===================== REQUESTS ===================== #

def ping():
	log.info(f"PING")
	if link.request(Opcode.PING, []) == ERROR:
		return ERROR
	if link.listen() == ERROR:
		return ERROR
	return SUCCESS

def rainbow(speed):
	log.info(f"RAINBOW {colours.YELLOW}speed{colours.RESET}: {speed}")
	payload = struct.pack("<B", speed)
	if link.request(Opcode.RAINBOW, payload) == ERROR:
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

# ===================== CLI SUBCOMMANDS ===================== #

MAX_PINGS = 100

def cli_ping(prefix, args):
	count = 1
	if len(args) > 0:
		count = parse_unsigned("count", args.pop(0), 0, MAX_PINGS)
		if count == ERROR:
			return ERROR

	log.info(f"PING {colours.MAGENTA}count{colours.RESET}: {count}")
	uart.connect()
	for i in range(count):
		if ping() == ERROR:
			return ERROR
	uart.disconnect()
	return SUCCESS

def cli_colour(prefix, args):
	red = args.pop(0)
	green = args.pop(0)
	blue = args.pop(0)

	red = parse_unsigned("red", red, 0, 255)
	if red == ERROR:
		return ERROR
	green = parse_unsigned("green", green, 0, 255)
	if green == ERROR:
		return ERROR
	blue = parse_unsigned("blue", blue, 0, 255)
	if blue == ERROR:
		return ERROR

	uart.connect()
	result = colour(red, green, blue)
	uart.disconnect()
	return result

def cli_rainbow(prefix, args):
	speed = parse_unsigned("speed", args.pop(0), 0, 255)
	if speed == ERROR:
		return ERROR

	uart.connect()
	result = rainbow(speed)
	uart.disconnect()
	return result

def cli_brightness(prefix, args):
	red = args.pop(0)
	green = args.pop(0)
	blue = args.pop(0)

	red = parse_unsigned("red", red, 0, 255)
	if red == ERROR:
		return ERROR
	green = parse_unsigned("green", green, 0, 255)
	if green == ERROR:
		return ERROR
	blue = parse_unsigned("blue", blue, 0, 255)
	if blue == ERROR:
		return ERROR

	uart.connect()
	result = brightness(red, green, blue)
	uart.disconnect()
	return result

def cli_reboot(prefix, args):
	uart.connect()
	result = reboot()
	uart.disconnect()
	return result

# ===================== SCRIPT ===================== #

def main():
	log.suppress(log.Level.DEBUG)
	program = basename(argv.pop(0))
	prefix = f"{program}"

	command = Command("rainbow", 1)
	command.leaf(cli_ping,       "ping",       "[count]",              0, 1, "Ping the controller")
	command.leaf(cli_colour,     "colour",     "<red> <green> <blue>", 3, 3, "Set the RGB colour")
	command.leaf(cli_brightness, "brightness", "<red> <green> <blue>", 3, 3, "Set the maximum brightness for each RGB channel")
	command.leaf(cli_rainbow,    "rainbow",    "<speed>",              1, 1, "Cycle through the colours in a rainbow")
	command.leaf(cli_reboot,     "reboot",     "",                     0, 0, "Reboot the controller")

	result = command.run(argv)
	exit(result)

if __name__ == "__main__":
	exit(main())
