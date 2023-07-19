#ifndef TIMER0_H
#define TIMER0_H

#include <stdbool.h>

#include "types.h"

typedef enum T0CKPS T0CKPS;

/*
Timer 0 prescaler.
Used to prescale clock input.
*/
enum T0CKPS
{
	T0CKPS_32768 = 0b1111,   // 1:32768
	T0CKPS_16384 = 0b1110,   // 1:16384
	T0CKPS_8192  = 0b1101,   // 1:8192
	T0CKPS_4096  = 0b1100,   // 1:4096
	T0CKPS_2048  = 0b1011,   // 1:2048
	T0CKPS_1024  = 0b1010,   // 1:1024
	T0CKPS_512   = 0b1001,   // 1:512
	T0CKPS_256   = 0b1000,   // 1:256
	T0CKPS_128   = 0b0111,   // 1:128
	T0CKPS_64    = 0b0110,   // 1:64
	T0CKPS_32    = 0b0101,   // 1:32
	T0CKPS_16    = 0b0100,   // 1:16
	T0CKPS_8     = 0b0011,   // 1:8
	T0CKPS_4     = 0b0010,   // 1:4
	T0CKPS_2     = 0b0001,   // 1:2
	T0CKPS_1     = 0b0000    // 1:1
};

void timer0_initialize(T0CKPS prescaler, U8 period);   // initialize timer 0
void timer0_enable(bool enable);                       // enable/disable timer 0
void timer0_interrupt(bool enable);                    // enable/disable timer 0 interrupt
bool timer0_expired(void);                             // check if timer 0 expired
void timer0_period(U8 period);                         // set timer 0 period

#endif /* TIMER0_H */
