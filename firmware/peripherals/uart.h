#ifndef UART_H
#define UART_H

#include "types.h"

void uart_initialize(void);
void uart_transmit(void const * data, U8 size);
void uart_receive(void * data, U8 size);
void uart_echo(void);

#endif /* UART_H */
