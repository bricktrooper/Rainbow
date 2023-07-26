import log

from cli import ERROR, SUCCESS

UINT8_MAX = 255

def parse_int(name, string):
	try:
		value = int(string)
		return value
	except ValueError:
		log.error(f"'{name}' must be an integer")
		return None

def verify_range(name, value, min, max):
	if value < min or value > max:
		log.error(f"'{name}' must be between {min} and {max}")
		return ERROR
	return SUCCESS
