#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdbool.h>

void interrupts_initialize(void);
void interrupts_global(bool enable);
void interrupts_peripheral(bool enable);

#endif /* INTERRUPTS_H */
