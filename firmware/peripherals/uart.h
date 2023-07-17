#ifndef UART_H
#define UART_H

#include <stdbool.h>

#include "types.h"

void uart_initialize(void);
void uart_transmit(void const * data, U8 length);
void uart_receive(void * data, U8 length);
void uart_write(void * data, U8 length);
void uart_read(void * data, U8 length);
void uart_echo(void);
void uart_non_blocking(bool rx, bool tx);
U8 uart_peek(void);
void uart_rx_service(void);
void uart_tx_service(void);

#endif /* UART_H */
