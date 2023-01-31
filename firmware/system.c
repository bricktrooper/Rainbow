#include "system.h"

#include <xc.h>

#include "config.h"
#include "gpio.h"
#include "led.h"

#define LED_DELAY_US   50000
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

	OSCCON1bits.NOSC = 0b110;     // High-frequency internal oscillator.
	OSCCON1bits.NDIV = 0b0000;    // 1:1 oscillator postscaler (f_clock = f_oscillator)
	OSCFRQbits.HFFRQ = 0b011;     // 8 MHz oscillator.
	OSCTUNEbits.HFTUN = 0b00000;  // Use calibrated oscillator centre frequency.

	// INTERRUPTS //

	INTCONbits.GIE = 1;    // Disable all interrupts temporarily.
	INTCONbits.PEIE = 1;   // Enable peripherial interrupts

	// PERIPHERALS //

	gpio_initialize();

	// DRIVERS //

	led_initialize();

	// FINALIZE //

	startup_indicator();   // Flash status LED.
	INTCONbits.GIE = 1;    // Re-enable all interrupts.
}

//void system_abort(Abort abort)
//{
//	while (button_released())
//	{
//		if (abort == ABORT_LOW_BATTERY)
//		{
//			led_pulse();   // Fade LED in and out during low battery.
//		}
//		else
//		{
//			led_blink();   // Blink LED during firmware errors.
//		}

//		if (abort < ABORT_count)
//		{
//			char * reason = system_abort_reasons[abort];
//			char * newline = "\r\n";

//			uart_transmit(reason, strlen(reason) + 1);
//			uart_transmit(newline, strlen(newline) + 1);
//		}
//	}

//	system_reboot();
//}

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
