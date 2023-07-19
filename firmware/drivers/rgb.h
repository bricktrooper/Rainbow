#ifndef RGB_H
#define RGB_H

#include <stdbool.h>

#include "types.h"

typedef enum RGB_Channel RGB_Channel;

enum RGB_Channel
{
	RED,
	GREEN,
	BLUE
};

void rgb_initialize(void);                         // initialize RGB settings
void rgb_set(RGB_Channel channel, U8 value);       // set the RGB colour for a specific channel
void rgb_colour(U8 red, U8 green, U8 blue);        // set value for each channel (takes brightness into account)
void rgb_off(void);                                // turn lights off
void rgb_brightness(U8 red,  U8 green, U8 blue);   // set maximum brightness for each channel
void rgb_rainbow(bool enable);                     // enable/disable rainbow mode
void rgb_rainbow_speed(U8 speed);                  // set the speed of the rainbow cycle
void rgb_rainbow_update(void);                     // run the rainbow cycle state machine
void rgb_rainbow_cycle(void);                      // cycle through all the rainbow colours once

#endif /* RGB_H */
