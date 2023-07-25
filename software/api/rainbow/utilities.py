import log

from .rgb import RGB

UINT8_MAX = 255

def parse_int(name, string, min, max):
	value = None

	try:
		value = int(string)
	except ValueError:
		log.error(f"'{name}' must be an integer")
		return None

	if value < min or value > max:
		log.error(f"'{name}' must be between {min} and {max}")
		return None

	return value

def parse_rgb(red, green, blue):
	red = parse_int("red", red, 0, UINT8_MAX)
	if red == None:
		return None
	green = parse_int("green", green, 0, UINT8_MAX)
	if green == None:
		return None
	blue = parse_int("blue", blue, 0, UINT8_MAX)
	if blue == None:
		return None
	return RGB(red, green, blue)
