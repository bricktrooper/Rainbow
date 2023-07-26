#! /usr/local/bin/python3

import rainbow
import log

from cli import Command, ERROR, SUCCESS
from sys import argv

log.suppress(log.Level.DEBUG)

prefix = argv.pop(0)
command = Command(prefix, 0, 1)

if command.verify(argv, 0, 1) == ERROR:
    log.info(f"Usage: {prefix} [port]")
    exit(ERROR)

port = None
if len(argv) > 0:
	port = argv.pop(0)

if rainbow.connect(port) == ERROR:
	exit(ERROR)
if rainbow.brightness(255, 255, 255) == ERROR:
	exit(ERROR)

for red in range(256):
	if rainbow.colour(red, 0, 0) == ERROR:
		exit(ERROR)
for green in range(256):
	if rainbow.colour(0, green, 0) == ERROR:
		exit(ERROR)
for blue in range(256):
	if rainbow.colour(0, 0, blue) == ERROR:
		exit(ERROR)

if rainbow.off() == ERROR:
	exit(ERROR)

rainbow.disconnect()
