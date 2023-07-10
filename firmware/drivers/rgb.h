#ifndef RGB_H
#define RGB_H

#include "types.h"

#define RGB_MAX_BIRGHTNESS   255
#define RGB_MIN_BRIGHTNESS   0

void rgb_initialize(void);
void rgb_red(U8 value);
void rgb_green(U8 value);
void rgb_blue(U8 value);
void rgb_colour(U8 red, U8 green, U8 blue);
void rgb_off(void);
void rgb_rainbow(void);
void rgb_brightness(U8 brightness);

#endif /* RGB_H */
