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
	purge()
	return SUCCESS

def disconnect():
	global serial
	serial.close()
	log.success(f"Closed serial port '{serial.port}'")
	serial = None

def purge():
	global serial
	serial.reset_output_buffer()
	serial.reset_input_buffer()
	while True:
		size = len(serial.read(1024))
		if size == 0:
			break
		log.verbose(f"Discarding {size} B from serial port")

def transmit(data):
	global serial
	length = serial.write(data)
	serial.flushOutput()
	message = f"Transmitted {length}/{len(data)} B"
	if length < len(data):
		log.warning(message)
	else:
		log.debug(message)

def receive(length):
	global serial
	data = serial.read(length)
	message = f"Received {len(data)}/{length} B"
	if length < len(data):
		log.warning(message)
	else:
		log.debug(message)
	return data

def dump():
	global serial
	while True:
		data = serial.read(1)
		print(data.decode("utf-8"), end = "", flush = True)
