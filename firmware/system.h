#ifndef SYSTEM_H
#define SYSTEM_H

#define OUTPUT   0
#define INPUT    1

#define DIGITAL    0
#define ANALOGUE   1

#include "types.h"

void system_initialize(void);
void system_abort(void);
void system_fatal(void);
//void system_service(U8 request);
//void system_reboot(void);

#endif /* SYSTEM_H */
