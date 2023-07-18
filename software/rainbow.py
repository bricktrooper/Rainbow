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
	log.info("RAINBOW")
	uart.connect()
	result = link.rainbow()
	uart.disconnect()
	return result

def main():
	#log.suppress(log.Level.DEBUG)
	program = argv.pop(0)
	prefix = f"{program}"
	command = Command(prefix, 1)
	command.leaf(ping, "ping", "[count]", 0, 1)
	command.leaf(rainbow, "rainbow", "", 0, 0)
	result = command.run(argv)
	exit(result)

if __name__ == "__main__":
	exit(main())
