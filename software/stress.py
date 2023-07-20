#! /usr/local/bin/python3

import rainbow
import log

PORT = "/dev/cu.rainbow-kyle-DevB"

log.suppress(log.Level.DEBUG)

rainbow.connect(PORT)

rainbow.brightness(255, 255, 255)
rainbow.cycle(255)
rainbow.ping(100)
rainbow.off()

rainbow.disconnect()
