import log
import uart
import link

from link import Header, Opcode
from cli import Command, ERROR, SUCCESS
from sys import argv

def ping(prefix, args):
	log.info("PING")
	uart.connect()
	for i in range(100):
		link.ping()
	uart.disconnect()
	#return result

def rainbow(prefix, args):
	log.info("RAINBOW")
	uart.connect()
	link.rainbow()
	uart.disconnect()
	#return result

def main():
	log.suppress(log.Level.DEBUG)
	program = argv.pop(0)
	prefix = f"{program}"
	command = Command(prefix, 1)
	command.leaf(ping, "ping", "", 0, 0)
	command.leaf(rainbow, "rainbow", "", 0, 0)
	result = command.run(argv)
	exit(result)

if __name__ == "__main__":
	exit(main())
