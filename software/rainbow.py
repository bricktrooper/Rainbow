#! /usr/local/bin/python3

import rainbow
import log

from log import colours
from cli import Command
from os.path import basename
from sys import argv

# ===================== CLI SUBCOMMANDS ===================== #

def cli_ping(prefix, args):
	count = 1
	if len(args) > 0:
		count = args.pop(0)
	log.info(f"PING {colours.MAGENTA}count{colours.RESET}: {count}")
	rainbow.connect()
	result = rainbow.ping(count)
	rainbow.disconnect()
	return result

def cli_colour(prefix, args):
	red = args.pop(0)
	green = args.pop(0)
	blue = args.pop(0)
	rainbow.connect()
	result = rainbow.colour(red, green, blue)
	rainbow.disconnect()
	return result

def cli_cycle(prefix, args):
	speed = args.pop(0)
	rainbow.connect()
	result = rainbow.cycle(speed)
	rainbow.disconnect()
	return result

def cli_brightness(prefix, args):
	red = args.pop(0)
	green = args.pop(0)
	blue = args.pop(0)
	rainbow.connect()
	result = rainbow.brightness(red, green, blue)
	rainbow.disconnect()
	return result

def cli_reboot(prefix, args):
	rainbow.connect()
	result = rainbow.reboot()
	rainbow.disconnect()
	return result

def cli_off(prefix, args):
	rainbow.connect()
	result = rainbow.colour(0, 0, 0)
	rainbow.disconnect()
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
