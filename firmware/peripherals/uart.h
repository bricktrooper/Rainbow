#ifndef UART_H
#define UART_H

#include <stdbool.h>

#include "types.h"

void uart_initialize(void);
void uart_transmit(void const * data, U8 length);   // blocking (busy waiting)
void uart_receive(void * data, U8 length);          // blocking (busy waiting)
void uart_push(void * data, U8 length);             // non-blocking (interrupt)
void uart_pop(void * data, U8 length);              // non-blocking (interrupt)
void uart_read(void * data, U8 length);             // multiplexer for uart_pop() and uart_receive()
void uart_write(void * data, U8 length);            // multiplexer for uart_push() and uart_transmit()
void uart_echo(void);
void uart_interrupt(bool rx, bool tx);              // enables/disables RX/TX interrupts (blocking/non-blocking)
U8 uart_peek(void);
void uart_rx_service(void);
void uart_tx_service(void);

#endif /* UART_H */
