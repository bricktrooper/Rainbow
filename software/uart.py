import log

from serial import Serial
from cli import ERROR, SUCCESS

serial = None

BAUDRATE = 115200
TIMEOUT_S = 1
PORT = "/dev/cu.rainbow-kyle-DevB"

def connect():
	global serial
	try:
		serial = Serial(
			port = PORT,
			baudrate = BAUDRATE,
			timeout = TIMEOUT_S
		)
	except Exception as exception:
		log.error(f"Failed to open serial port '{PORT}': {exception}")
		return ERROR

	log.success(f"Opened serial port '{PORT}'")
	return SUCCESS

def disconnect():
	global serial
	serial.close()
	log.success(f"Closed serial port '{serial.port}'")
	serial = None

def transmit(data):
	global serial
	serial.write(data)

def receive(length):
	global serial
	return serial.read(length)
