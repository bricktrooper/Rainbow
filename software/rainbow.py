import log
import uart
import link

from link import Header, Opcode
from cli import Command, ERROR, SUCCESS
from sys import argv

def ping(prefix, args):
	log.info("PING")
	uart.connect()

	uart.disconnect()
	return ERROR

def main():
	program = argv.pop(0)
	prefix = f"{program}"
	command = Command(prefix, 1)
	command.leaf(ping, "ping", "", 0, 0)
	#result = command.run(argv)

	uart.connect()
	link.request(Opcode.RAINBOW, [])
	link.listen()
	uart.disconnect()

	exit()



	uart.connect()

	packet = bytearray()
	packet.append(0x23)#magic1
	packet.append(0xCE)#magic2
	packet.append(Opcode.PING) #opcode
	packet.append(0x00)#length
	checksum = 0xCE ^ 0x23 ^ Opcode.PING ^ 0x00
	packet.append(checksum)
	print(packet)

	for i in range(1):
		uart.transmit(packet)
		response = uart.receive(5)
		header = Header()
		header.unpack(response)
		print(str(header))
		data = uart.receive(header.length)
		print(int(data[0]))

	uart.disconnect()


if __name__ == "__main__":
	exit(main())
