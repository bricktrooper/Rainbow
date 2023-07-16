#ifndef TIMER0_H
#define TIMER0_H

#include <stdbool.h>

#include "types.h"

typedef enum T0CKPS T0CKPS;

/* Timer 0 prescaler.
 * Used to prescale clock input. */
enum T0CKPS
{
	T0CKPS_32768 = 0b1111,   // 1:32768 prescaler
	T0CKPS_16384 = 0b1110,   // 1:16384 prescaler
	T0CKPS_8192  = 0b1101,   // 1:8192 prescaler
	T0CKPS_4096  = 0b1100,   // 1:4096 prescaler
	T0CKPS_2048  = 0b1011,   // 1:2048 prescaler
	T0CKPS_1024  = 0b1010,   // 1:1024 prescaler
	T0CKPS_512   = 0b1001,   // 1:512 prescaler
	T0CKPS_256   = 0b1000,   // 1:256 prescaler
	T0CKPS_128   = 0b0111,   // 1:128 prescaler
	T0CKPS_64    = 0b0110,   // 1:64 prescaler
	T0CKPS_32    = 0b0101,   // 1:32 prescaler
	T0CKPS_16    = 0b0100,   // 1:16 prescaler
	T0CKPS_8     = 0b0011,   // 1:8 prescaler
	T0CKPS_4     = 0b0010,   // 1:4 prescaler
	T0CKPS_2     = 0b0001,   // 1:2 prescaler
	T0CKPS_1     = 0b0000    // 1:1 prescaler
};

void timer0_initialize(T0CKPS prescaler, U8 period);
void timer0_enable(bool enable);

#endif /* TIMER0_H */
