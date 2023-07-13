#ifndef RGB_H
#define RGB_H

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
void rgb_colour(U8 red, U8 green, U8 blue);
void rgb_off(void);
void rgb_rainbow(void);
void rgb_brightness(U8 red,  U8 green, U8 blue);

#endif /* RGB_H */
