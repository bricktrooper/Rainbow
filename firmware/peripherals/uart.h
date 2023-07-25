#ifndef UART_H
#define UART_H

#include <stdbool.h>

#define NEWLINE   "\r\n"

#define DEFAULT_BAUD_RATE   9600
#define MAX_BAUD_RATE       2000000

#include "types.h"

void uart_initialize(void);                         // initialize UART
void uart_transmit(void const * data, U8 length);   // blocking (busy waiting)
void uart_receive(void * data, U8 length);          // blocking (busy waiting)
void uart_push(void * data, U8 length);             // non-blocking (interrupt)
void uart_pop(void * data, U8 length);              // non-blocking (interrupt)
void uart_read(void * data, U8 length);             // multiplexer for uart_pop() and uart_receive()
void uart_write(void * data, U8 length);            // multiplexer for uart_push() and uart_transmit()
void uart_echo(void);                               // send RX bytes back on TX
void uart_interrupts(bool rx, bool tx);             // enables/disables RX/TX interrupts (blocking/non-blocking)
U8 uart_peek_rx(void);                              // returns the current length of the RX queue
U8 uart_peek_tx(void);                              // returns the current length of the TX queue
void uart_purge_rx(void);                           // discards all data from the RX queue
void uart_purge_tx(void);                           // discards all data from the TX queue
void uart_rx_service(void);                         // RX ISR
void uart_tx_service(void);                         // TX ISR
void uart_set_baud_rate(U32 rate);                  // set the baud rate in bps up to MAX_BAUD_RATE
U32 uart_get_baud_rate(void);                       // get the baud rate in bps

#endif /* UART_H */
