#! /usr/local/bin/python3

import rainbow
import log

from cli import Command, ERROR, SUCCESS
from sys import argv

prefix = argv.pop(0)
command = Command(prefix, 1, 1)

if command.verify(argv, 1, 1) == ERROR:
    log.info(f"Usage: {prefix} <port>")
    exit(ERROR)

port = argv.pop(0)

log.suppress(log.Level.DEBUG)

rainbow.connect(port)

rainbow.brightness(255, 255, 255)
rainbow.cycle(255)
rainbow.ping(100)
rainbow.off()

rainbow.disconnect()
