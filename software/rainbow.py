import log
import uart
import link

from cli import Command, ERROR, SUCCESS
from sys import argv

def ping(prefix, args):
	count = 1
	if len(args) > 0:
		try:
			count = int(args.pop(0))
		except ValueError:
			log.error(f"Ping count must be an integer")
			return ERROR

	log.info("PING")
	uart.connect()
	result = SUCCESS

	for i in range(count):
		result |= link.ping()

	uart.disconnect()
	return result

def rainbow(prefix, args):
	speed = None
	if len(args) > 0:
		try:
			speed = int(args.pop(0))
		except ValueError:
			log.error(f"Rainbow speed must be an integer")
			return ERROR

	if speed < 0 or speed > 255:
		log.error(f"Rainbow speed must be between 0 and 255")
		return ERROR

	log.info("RAINBOW")
	uart.connect()
	result = link.rainbow(speed)
	uart.disconnect()
	return result

def main():
	#log.trace(module = True, caller = True)

	program = argv.pop(0)
	prefix = f"{program}"

	command = Command(prefix, 1)
	command.leaf(ping, "ping", "[count]", 0, 1)
	command.leaf(rainbow, "rainbow", "<speed>", 1, 1)

	result = command.run(argv)
	exit(result)

if __name__ == "__main__":
	exit(main())
