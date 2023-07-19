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

def cli_cycle(prefix, args):
	speed = parse_unsigned("speed", args.pop(0), 0, 255)
	if speed == ERROR:
		return ERROR

	uart.connect()
	result = cycle(speed)
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

def cli_off(prefix, args):
	uart.connect()
	result = colour(0, 0, 0)
	uart.disconnect()
	return result

SUBCOMMANDS = {
	"ping":
	{
		"handler":     cli_ping,
		"usage":       "[count]",
		"min":         0,
		"max":         1,
		"description": "Ping the controller"
	},
	"colour":
	{
		"handler":     cli_colour,
		"usage":       "<red> <green> <blue>",
		"min":         3,
		"max":         3,
		"description": "Set the RGB colour"
	},
	"brightness":
	{
		"handler":     cli_brightness,
		"usage":       "<red> <green> <blue>",
		"min":         3,
		"max":         3,
		"description": "Set the maximum brightness for each RGB channel"
	},
	"cycle":
	{
		"handler":     cli_cycle,
		"usage":       "<speed>",
		"min":         1,
		"max":         1,
		"description": "Transition through all colours repeatedly"
	},
	"reboot":
	{
		"handler":     cli_reboot,
		"usage":       "",
		"min":         0,
		"max":         0,
		"description": "Reboot the controller"
	},
	"off":
	{
		"handler":     cli_off,
		"usage":       "",
		"min":         0,
		"max":         0,
		"description": "Turn off all lights"
	},
}

# ===================== SCRIPT ===================== #

def main():
	log.suppress(log.Level.DEBUG)
	program = basename(argv.pop(0))
	prefix = f"{program}"
	command = Command("rainbow", 0)

	for name in SUBCOMMANDS:
		command.leaf(
			name = name,
			handler = SUBCOMMANDS[name]["handler"],
			usage = SUBCOMMANDS[name]["usage"],
			min = SUBCOMMANDS[name]["min"],
			max = SUBCOMMANDS[name]["max"],
			description = SUBCOMMANDS[name]["description"]
		)

	result = command.run(argv)
	exit(result)

if __name__ == "__main__":
	exit(main())
