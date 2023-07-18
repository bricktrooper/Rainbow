#ifndef TIMER2_H
#define TIMER2_H

#include <stdbool.h>

#include "types.h"

typedef enum T2CKPS T2CKPS;

/* Timer 2 prescaler.
 * Used to prescale clock input. */
enum T2CKPS
{
	T2CKPS_128 = 0b111,   // 1:128
	T2CKPS_64  = 0b110,   // 1:64
	T2CKPS_32  = 0b101,   // 1:32
	T2CKPS_16  = 0b100,   // 1:16
	T2CKPS_8   = 0b011,   // 1:8
	T2CKPS_4   = 0b010,   // 1:4
	T2CKPS_2   = 0b001,   // 1:2
	T2CKPS_1   = 0b000    // 1:1
};

void timer2_initialize(T2CKPS prescaler, U8 period);
void timer2_enable(bool enable);
void timer2_interrupt(bool enable);

#endif /* TIMER2_H */
