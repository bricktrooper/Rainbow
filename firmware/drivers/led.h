#ifndef LED_H
#define LED_H

#include "types.h"

void led_initialize(void);   // initialize LED
void led_on(void);           // turn the LED on
void led_off(void);          // turn the LED off
void led_blink(U8 count);    // blink the LED a certain number of times

#endif /* LED_H */
