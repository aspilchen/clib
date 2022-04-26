/**
 * Experimenting with recreating something similar to C++ generics.
 * 
 * This is just so I don't have to constantly re-make queues whenever I need a different queue type.
 * This could also be used as a template, where you make the compiler expand all macros for the type
 * you want, and output the expanded code to a new file. Then make any changes from there.
 */

#ifndef QUEUE_EXPERIMENT_H
#define QUEUE_EXPERIMENT_H

#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>


#define queue_declare(TYPE) struct Queue(TYPE) {\
	TYPE *data;\
	TYPE *front;\
	TYPE *back;\
	size_t capacity;\
} typedef Queue(TYPE);\
declare_new(TYPE)\
declare_destroy(TYPE)\
declare_isEmpty(TYPE)\
declare_isFull(TYPE)\
declare_put(TYPE)\
declare_get(TYPE)\
declare_getChunk(TYPE)


#define Queue(TYPE) queue__ ## TYPE


#define declare_new(TYPE) Queue(TYPE)* queue__ ## TYPE ## __new(size_t capacity) {\
	Queue(TYPE) *q = malloc(sizeof(*q));\
	if(!q) {\
		return NULL;\
	}\
	TYPE *data = malloc((capacity + 1) * sizeof(*data));\
	if(!data) {\
		return NULL;\
	}\
	q->data = data;\
	q->front = data;\
	q->back = data;\
	q->capacity = capacity + 1;\
	return q;\
}

#define declare_destroy(TYPE) void queue__ ## TYPE ## __destroy(Queue(TYPE) *q) {\
	free(q->data);\
	free(q);\
}

#define declare_isEmpty(TYPE) bool queue__ ## TYPE ## __isEmpty(Queue(TYPE) *q) {\
	return q->front == q->back;\
}

#define declare_isFull(TYPE) bool queue__ ## TYPE ## __isFull(Queue(TYPE) *q) {\
	if(q->back + 1 >= q->data + q->capacity) {\
		return q->data == q->front;\
	}\
	return (q->back + 1) == (q->front);\
}

#define declare_put(TYPE) void queue__ ## TYPE ## __put(Queue(TYPE) *q, TYPE value) {\
	if(queue_isFull(q, TYPE)) {\
		return;\
	}\
	*(q->back) = value;\
	q->back += 1;\
	if(q->back >= q->data + q->capacity) {\
		q->back = q->data;\
	}\
}

#define declare_get(TYPE) TYPE queue__ ## TYPE ## __get(Queue(TYPE) *q) {\
	TYPE val = *(q->front);\
	if(q->front == q->back) {\
		return val;\
	}\
	q->front += 1;\
	if(q->front >= q->data + q->capacity) {\
		q->front = q->data;\
	}\
	return val;\
}


#define declare_getChunk(TYPE) size_t queue__ ## TYPE ## __getChunk(Queue(TYPE) *q, TYPE *buff, size_t buffSize) {\
	if(queue_isEmpty(q, TYPE)) {\
		return 0;\
	}\
	if(q->front + buffSize <= q->back) {\
		memcpy(buff, q->front, buffSize * sizeof(*buff));\
		q->front += buffSize;\
		return buffSize;\
	}\
	if(q->front + buffSize < q->data + buffSize) {\
		memcpy(buff, q->front, buffSize * sizeof(*buff));\
		q->front += buffSize;\
		return buffSize;\
	}\
	size_t copySize = q->data + q->capacity - q->front;\
	memcpy(buff, q->front, copySize * sizeof(*buff));\
	q->front = q->data;\
	copySize += queue_getChunk(q, TYPE, buff, buffSize);\
	return copySize;\
}

#define queue_new(TYPE, CAPACITY) queue__ ## TYPE ## __new(CAPACITY)
#define queue_destroy(PTR, TYPE) queue__ ## TYPE ## __destroy(PTR)
#define queue_isEmpty(PTR, TYPE) queue__ ## TYPE ## __isEmpty(PTR)
#define queue_isFull(PTR, TYPE) queue__ ## TYPE ## __isFull(PTR)
#define queue_put(PTR, TYPE, VALUE) queue__ ## TYPE ## __put(PTR, VALUE)
#define queue_get(PTR, TYPE) queue__ ## TYPE ## __get(PTR)
#define queue_getChunk(QPTR, TYPE, BUFF, BUFFSIZE) queue__ ## TYPE ## __getChunk(QPTR, BUFF, BUFFSIZE)

#endif
