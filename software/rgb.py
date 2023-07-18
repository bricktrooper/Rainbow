import struct

from log import colours

class RGB:
	FORMAT = "<BBB"   # little endian
	SIZE = struct.calcsize(FORMAT)

	def __init__(self, red = 0, green = 0, blue = 0):
		self.red = red
		self.green = green
		self.blue = blue

	def __str__(self):
		string = ""
		string += "%s%s%s: %u, " % (colours.RED, "red", colours.RESET, self.red)
		string += "%s%s%s: %u, " % (colours.GREEN, "green", colours.RESET, self.green)
		string += "%s%s%s: %u" % (colours.BLUE, "blue", colours.RESET, self.blue)
		return string

	def print(self):
		print(str(self))

	def unpack(self, data, offset = 0):
		fields = struct.unpack_from(RGB.FORMAT, data, offset)
		self.red = fields[0]
		self.green = fields[1]
		self.blue = fields[2]

	def pack(self):
		return struct.pack(
			self.FORMAT,
			self.red,
			self.green,
			self.blue,
		)
