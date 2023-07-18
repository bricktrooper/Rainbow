#ifndef LED_H
#define LED_H

#include "types.h"

void led_initialize(void);
void led_on(void);
void led_off(void);
void led_blink(U8 count);

#endif /* LED_H */
