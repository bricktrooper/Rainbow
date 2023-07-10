#include <xc.h>

#include "system.h"
#include "led.h"
#include "uart.h"
#include "rgb.h"
#include "link.h"

//void service(Header * header, void * data)
//{
//	Command command = request & MASK_COMMAND;
//	U8 metadata = request & MASK_METADATA;

//	switch (command)
//	{
//		case COMMAND_PING:
//		{
//			link_respond(STATUS_SUCCESS, NULL, 0);
//			break;
//		}
//		case COMMAND_ACCEL_RANGE:
//		{
//			Status status = accel_set_range(metadata);
//			link_respond(status, NULL, 0);
//			break;
//		}
//		case COMMAND_GYRO_RANGE:
//		{
//			Status status = gyro_set_range(metadata);
//			link_respond(status, NULL, 0);
//			break;
//		}
//		case COMMAND_SENSORS:
//		{
//			void * data;
//			U8 length;
//			Status status = read_sensors(metadata, &data, &length);
//			link_respond(status, data, length);
//			break;
//		}
//		case COMMAND_BATTERY:
//		{
//			U16 voltage = battery_voltage();
//			link_respond(STATUS_SUCCESS, &voltage, sizeof(voltage));
//			break;
//		}
//		case COMMAND_RESET:
//		{
//			link_respond(STATUS_SUCCESS, NULL, 0);
//			system_reboot();
//			break;
//		}
//		default:
//		{
//			link_respond(STATUS_ERROR, NULL, 0);
//			break;
//		}
//	}
//}

void main(void)
{
	system_initialize();
	ABORT(ABORT_RX_OVERRUN);

	while (1)
	{
		//link_receive(&header, data)
		//service();
	}
}
