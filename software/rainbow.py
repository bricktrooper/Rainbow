#! /usr/local/bin/python3

import log
import uart
import link

from cli import Command, ERROR, SUCCESS
from sys import argv

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

# ===================== SUBCOMMANDS ===================== #

MAX_PINGS = 100

def ping(prefix, args):
	count = 1
	if len(args) > 0:
		count = parse_unsigned("count", args.pop(0), 0, MAX_PINGS)
		if count == ERROR:
			return ERROR

	uart.connect()
	for i in range(count):
		if link.ping() == ERROR:
			return ERROR
	uart.disconnect()
	return SUCCESS

def colour(prefix, args):
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
	result = link.colour(red, green, blue)
	uart.disconnect()
	return result

def rainbow(prefix, args):
	speed = parse_unsigned("speed", args.pop(0), 0, 255)
	if speed == ERROR:
		return ERROR

	uart.connect()
	result = link.rainbow(speed)
	uart.disconnect()
	return result

def brightness(prefix, args):
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
	result = link.brightness(red, green, blue)
	uart.disconnect()
	return result

def reboot(prefix, args):
	uart.connect()
	result = link.reboot()
	uart.disconnect()
	return result

# ===================== SCRIPT ===================== #

def main():
	log.suppress(log.Level.DEBUG)
	program = argv.pop(0)
	prefix = f"{program}"

	command = Command(prefix, 1)
	command.leaf(ping, "ping", "[count]", 0, 1)
	command.leaf(colour, "colour", "<red> <green> <blue>", 3, 3)
	command.leaf(brightness, "brightness", "<red> <green> <blue>", 3, 3)
	command.leaf(rainbow, "rainbow", "<speed>", 1, 1)
	command.leaf(reboot, "reboot", "", 0, 0)

	result = command.run(argv)
	exit(result)

if __name__ == "__main__":
	exit(main())
