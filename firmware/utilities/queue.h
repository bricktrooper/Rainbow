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

void queue_initialize(Queue * queue, U8 * data, U8 size);
bool queue_push(Queue * queue, U8 value);
bool queue_pop(Queue * queue, U8 * value);
bool queue_empty(Queue * queue);
bool queue_full(Queue * queue);

#endif /* QUEUE_H */
