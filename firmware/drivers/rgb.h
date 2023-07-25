#ifndef RGB_H
#define RGB_H

#include <stdbool.h>

#include "types.h"

typedef enum RGB_Channel RGB_Channel;

enum RGB_Channel
{
	RED,
	GREEN,
	BLUE,
};

void rgb_initialize(void);                         // initialize RGB settings
void rgb_set(RGB_Channel channel, U8 value);       // set the RGB colour for a specific channel
void rgb_colour(U8 red, U8 green, U8 blue);        // set value for each channel (takes brightness into account)
void rgb_off(void);                                // turn lights off
void rgb_brightness(U8 red,  U8 green, U8 blue);   // set maximum brightness for each channel
void rgb_cycle(bool enable);                       // enable/disable cycle mode
bool rgb_cycling(void);                            // returns true if cycle mode is enabled
void rgb_cycle_speed(U8 speed);                    // set the speed of the cycle
void rgb_cycle_update(void);                       // run the cycle state machine
void rgb_cycle_single(void);                       // cycle through all the colours once
void rgb_default(void);                            // set default brightness and cycle at default speed

#endif /* RGB_H */
