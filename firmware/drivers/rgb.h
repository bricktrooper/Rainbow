#ifndef RGB_H
#define RGB_H

#include <stdbool.h>

#include "types.h"

typedef enum Colour Colour;

enum Colour
{
	RED,
	GREEN,
	BLUE
};

void rgb_initialize(void);
void rgb_set(Colour colour, U8 value);
void rgb_colour(U8 red, U8 green, U8 blue);   // set value for each channel (takes brightness into account)
void rgb_off(void);
void rgb_rainbow(bool enable);
void rgb_rainbow_cycle(void);
void rgb_brightness(U8 red,  U8 green, U8 blue);   // set maximum brightness for each channel
void rgb_rainbow_update(void);

#endif /* RGB_H */
