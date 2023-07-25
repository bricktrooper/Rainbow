#! /usr/local/bin/python3

import rainbow
import log

PORT = "/dev/cu.rainbow-shane-DevB"

log.suppress(log.Level.DEBUG)

rainbow.connect(PORT)

rainbow.brightness(255, 255, 255)

for red in range(256):
	rainbow.colour(red, 0, 0)
for green in range(256):
	rainbow.colour(0, green, 0)
for blue in range(256):
	rainbow.colour(0, 0, blue)

rainbow.off()

rainbow.disconnect()
