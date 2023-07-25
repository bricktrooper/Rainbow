#! /usr/local/bin/python3

import rainbow
import log

from log import colours
from cli import Command, ERROR, SUCCESS
from os.path import basename
from sys import argv
from rainbow.utilities import parse_int, parse_rgb, UINT8_MAX
from rainbow.rgb import RGB

# ===================== CONSTANTS ===================== #

MAX_PINGS = 100

# default settings
BRIGHTNESS = RGB(255, 128, 255)
CYCLE_SPEED = 175

# ===================== SUBCOMMANDS ===================== #

def cli_ping(prefix, args):
	count = 1
	if len(args) > 0:
		count = args.pop(0)
	port = None
	if len(args) > 0:
		port = args.pop(0)

	count = parse_int("count", count, 0, MAX_PINGS)
	if count == None:
		return ERROR

	log.info(f"PING {colours.MAGENTA}count{colours.RESET}: {count}")
	if rainbow.connect(port) == ERROR:
		return ERROR
	result = rainbow.ping(count)
	rainbow.disconnect()
	return result

def cli_colour(prefix, args):
	red = args.pop(0)
	green = args.pop(0)
	blue = args.pop(0)
	port = None
	if len(args) > 0:
		port = args.pop(0)

	rgb = parse_rgb(red, green, blue)
	if rgb is None:
		return ERROR

	if rainbow.connect(port) == ERROR:
		return ERROR
	result = rainbow.colour(rgb.red, rgb.green, rgb.blue)
	rainbow.disconnect()
	return result

def cli_cycle(prefix, args):
	speed = args.pop(0)
	port = None
	if len(args) > 0:
		port = args.pop(0)

	speed = parse_int("speed", speed, 0, UINT8_MAX)
	if speed == None:
		return ERROR

	if rainbow.connect(port) == ERROR:
		return ERROR
	result = rainbow.cycle(speed)
	rainbow.disconnect()
	return result

def cli_brightness(prefix, args):
	red = args.pop(0)
	green = args.pop(0)
	blue = args.pop(0)
	port = None
	if len(args) > 0:
		port = args.pop(0)

	rgb = parse_rgb(red, green, blue)
	if rgb is None:
		return ERROR

	if rainbow.connect(port) == ERROR:
		return ERROR
	result = rainbow.brightness(rgb.red, rgb.green, rgb.blue)
	rainbow.disconnect()
	return result

def cli_reboot(prefix, args):
	port = None
	if len(args) > 0:
		port = args.pop(0)
	if rainbow.connect(port) == ERROR:
		return ERROR
	result = rainbow.reboot()
	rainbow.disconnect()
	return result

def cli_off(prefix, args):
	port = None
	if len(args) > 0:
		port = args.pop(0)
	if rainbow.connect(port) == ERROR:
		return ERROR
	result = rainbow.off()
	rainbow.disconnect()
	return result

def cli_default(prefix, args):
	port = None
	if len(args) > 0:
		port = args.pop(0)
	if rainbow.connect(port) == ERROR:
		return ERROR
	result = SUCCESS
	result |= rainbow.brightness(BRIGHTNESS.red, BRIGHTNESS.green, BRIGHTNESS.blue)
	result |= rainbow.cycle(CYCLE_SPEED)
	rainbow.disconnect()
	return result

def cli_port(prefix, args):
	port = args.pop(0)
	rainbow.set_default_port(port)
	return SUCCESS

SUBCOMMANDS = {
	"ping":
	{
		"handler":     cli_ping,
		"usage":       "[count] [port]",
		"min":         0,
		"max":         2,
		"description": "Ping the controller"
	},
	"colour":
	{
		"handler":     cli_colour,
		"usage":       "<red> <green> <blue> [port]",
		"min":         3,
		"max":         4,
		"description": "Set the RGB colour taking brightness into account"
	},
	"brightness":
	{
		"handler":     cli_brightness,
		"usage":       "<red> <green> <blue> [port]",
		"min":         3,
		"max":         4,
		"description": "Set the maximum brightness for each RGB channel"
	},
	"cycle":
	{
		"handler":     cli_cycle,
		"usage":       "<speed> [port]",
		"min":         1,
		"max":         2,
		"description": "Transition through all colours repeatedly"
	},
	"reboot":
	{
		"handler":     cli_reboot,
		"usage":       "[port]",
		"min":         0,
		"max":         1,
		"description": "Reboot the controller"
	},
	"off":
	{
		"handler":     cli_off,
		"usage":       "[port]",
		"min":         0,
		"max":         1,
		"description": "Turn off all lights"
	},
	"default":
	{
		"handler":     cli_default,
		"usage":       "[port]",
		"min":         0,
		"max":         1,
		"description": "Set default brightness and cycle at default speed"
	},
	"port":
	{
		"handler":     cli_port,
		"usage":       "<port>",
		"min":         1,
		"max":         1,
		"description": "Set default serial port"
	},
}

# ===================== SCRIPT ===================== #

def main():
	log.suppress(log.Level.DEBUG)

	program = basename(argv.pop(0))
	prefix = f"{program}"
	command = Command(prefix, 0)

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
