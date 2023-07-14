#ifndef UART_H
#define UART_H

#include <stdbool.h>

#include "types.h"

void uart_initialize(void);
void uart_transmit(void const * data, U8 size);
void uart_receive(void * data, U8 size);
void uart_write(void * data, U8 size);
void uart_read(void * data, U8 size);
void uart_echo(void);
void uart_asynchronous(bool rx, bool tx);

#endif /* UART_H */
