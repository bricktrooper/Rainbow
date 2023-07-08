#include "system.h"

#include <xc.h>

#include "config.h"
#include "oscillator.h"
#include "interrupts.h"
#include "gpio.h"
#include "led.h"
#include "uart.h"
#include "pwm.h"
#include "rgb.h"

#define LED_DELAY_US   200000
#define LED_BLINKS     3

static void startup_indicator(void)
{
	for (int i = 0; i < LED_BLINKS; i++)
	{
		led_on();
		_delay(LED_DELAY_US);
		led_off();
		_delay(LED_DELAY_US);
	}
}

void system_initialize(void)
{
	// OSCILLATOR //

	oscillator_initialize();

	// INTERRUPTS //

	interrupts_initialize();

	// PERIPHERALS //

	gpio_initialize();
	uart_initialize();
	pwm_initialize();

	// DRIVERS //

	led_initialize();
	rgb_initialize();

	// FINALIZE //

	startup_indicator();       // flash status LED
	interrupts_global(true);   // unmask all interrupts
}

void system_abort(void)
{
	while (1)
	{
		led_blink();   // blink LED forever
	}
}

void system_fatal(void)
{
	system_abort();
}

//static Status read_sensors(Sensor_Group group, void ** data, U8 * length)
//{
//	Sensors sensors;

//	accel_read(&sensors.accel);
//	gyro_read(&sensors.gyro);
//	flex_read(&sensors.flex);
//	sensors.button = button_pressed();

//	Status status = STATUS_SUCCESS;

//	switch (group)
//	{
//		default:
//		{
//			status = STATUS_ERROR;
//			*data = NULL;
//			*length = 0;
//			break;
//		}

//		case SENSOR_GROUP_ALL:
//		{
//			*data = &sensors;
//			*length = sizeof(sensors);
//			break;
//		}

//		case SENSOR_GROUP_ACCEL:
//		{
//			*data = &sensors.accel;
//			*length = sizeof(sensors.accel);
//			break;
//		}

//		case SENSOR_GROUP_GYRO:
//		{
//			*data = &sensors.gyro;
//			*length = sizeof(sensors.gyro);
//			break;
//		}

//		case SENSOR_GROUP_FLEX:
//		{
//			*data = &sensors.flex;
//			*length = sizeof(sensors.flex);
//			break;
//		}

//		case SENSOR_GROUP_BUTTON:
//		{
//			*data = &sensors.button;
//			*length = sizeof(sensors.button);
//			break;
//		}
//	}

//	return status;
//}

//void system_service(U8 request)
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

//void system_reboot(void)
//{
//	WDTCONbits.SWDTEN = 1;   // enable watchdog timer to force reset
//}
