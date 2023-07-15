import log

from serial import Serial, STOPBITS_ONE, EIGHTBITS
from link import Header

def connect():
	pass

try:
	serial = Serial(
		port = "/dev/cu.rainbow-kyle-DevB",
		baudrate = 115200,
		timeout = 1
	)
except Exception as e:
	log.error(f"Error opening serial port: {e}")
	exit()

packet = bytearray()
packet.append(0x23)#magic1
packet.append(0xCE)#magic2
packet.append(0x00) #opcode
packet.append(0x00)#len
checksum = 0xCE ^ 0x23 ^ 0x00 ^ 0x00
packet.append(checksum)

for i in range(100):
	serial.write(packet)
	response = serial.read(5)
	header = Header()
	header.unpack(response)
	print(str(header), end = "")
	data = serial.read(header.length)
	print(int(data[0]))

serial.close()
