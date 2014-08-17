#ifndef QUEUE_H
#define QUEUE_H

/*
* Queue (doubly linked) implementation with easily changeable data type.
*/

/* Data structure */
typedef struct _queue_data{
    float x;
    float y;
} QueueData;

/* Node structure */
typedef struct _queue Queue;

/* Create an empty queue. */
extern Queue* queue_init(void);

/* Push the data onto the queue. */
extern void queue_enqueue(Queue* aQueue, QueueData data);

/* Pop the data from bottom of the queue.
   Return garbage if the queue is empty.*/
extern QueueData queue_dequeue(Queue* aQueue);

/* Return a copy of the data on the bottom of the queue.
   Return garbage if the queue is empty. */
extern QueueData queue_look(Queue* aQueue);

/* Return true iff the queue is empty. */
extern _Bool queue_empty(Queue* aQueue);

/* Empty the queue */
extern void queue_clear(Queue* aQueue);

/* Delete the entire queue. (makes the ptr to the queue dangling) */
extern void queue_destroy(Queue* aQueue);

extern QueueData queue_data(float x, float y);
#endif
