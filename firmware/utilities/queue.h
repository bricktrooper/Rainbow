#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#include "types.h"

typedef struct Queue Queue;

struct Queue
{
	U8 * data;   // pointer to data
	U8 read;     // read pointer
	U8 write;    // write pointer
	U8 size;     // total number of bytes in queue
	U8 length;   // number of used bytes in queue
};

void queue_initialize(Queue * queue, U8 * data, U8 size);   // initialize the queue with a buffer
void queue_reset(Queue * queue);                            // reset the queue and discard all data
bool queue_push(Queue * queue, U8 value);                   // enqueue a byte
bool queue_pop(Queue * queue, U8 * value);                  // dequeue a byte
bool queue_empty(Queue * queue);                            // returns true if the queue is empty
bool queue_full(Queue * queue);                             // returns true if queue.length == queue.size

#endif /* QUEUE_H */
