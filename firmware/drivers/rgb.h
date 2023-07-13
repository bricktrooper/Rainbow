#ifndef RGB_H
#define RGB_H

#include "types.h"

#define RGB_MAX_BRIGHTNESS   255
#define RGB_MIN_BRIGHTNESS   0

typedef enum Colour Colour;

enum Colour
{
	RED,
	GREEN,
	BLUE
};

void rgb_initialize(void);
void rgb_set(Colour colour, U8 value);
void rgb_colour(U8 red, U8 green, U8 blue);
void rgb_off(void);
void rgb_rainbow(void);
void rgb_brightness(U8 brightness);

#endif /* RGB_H */
