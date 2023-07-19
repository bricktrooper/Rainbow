#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdbool.h>

void interrupts_initialize(void);          // initialize interrupts
void interrupts_global(bool enable);       // mask/unmask all interrupts
void interrupts_peripheral(bool enable);   // mask/unmask peripheral interrupts

#endif /* INTERRUPTS_H */
