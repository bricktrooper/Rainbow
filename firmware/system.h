#ifndef SYSTEM_H
#define SYSTEM_H

#define OUTPUT   0
#define INPUT    1

#define DIGITAL    0
#define ANALOGUE   1

#define ABORT(reason)   system_abort(reason, __func__)

#include "types.h"

typedef enum Abort Abort;

enum Abort
{
	ABORT_RX_OVERRUN,
	ABORT_RX_BUFFER_OVERFLOW,
	ABORT_TX_BUFFER_OVERFLOW,

	ABORT_count,
};

void system_initialize(void);
void system_abort(Abort abort, char const * caller);
//void system_reboot(void);

#endif /* SYSTEM_H */
