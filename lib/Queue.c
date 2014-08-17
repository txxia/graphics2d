#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#define DEBUG
#include "debug.h"

#include "Queue.h"

struct _queue{
    struct _queue_data data;
    /* to the prev node */
    struct _queue* prev;
    /* to the next node */
    struct _queue* next;
};

Queue* _queue_search(Queue*, struct _queue_data);

Queue* queue_init(void) {
    Queue* newQueue = (Queue*) malloc(sizeof(struct _queue));
    if(newQueue != NULL){
        newQueue->next = NULL;
        newQueue->prev = NULL;
    }
    else
        fputs("cannot create queue\n", stderr);
    return newQueue;
}

void queue_enqueue(Queue* aQueue, QueueData data) {
    if(_queue_search(aQueue, data))return;
    dbg("enqueuing: (%.1f, %.1f)", data.x, data.y);
    Queue* aNode = queue_init();
    aNode->data = data;
    aNode->next = NULL;
    aNode->prev = aQueue->prev;     // update the new front node

    if(queue_empty(aQueue)){
        aQueue->next = aNode;       // enqueuing the first node
    } else {
        aQueue->prev->next = aNode; // update the previous node
        aNode->prev = aQueue->prev;
    }
    aQueue->prev = aNode;
}

QueueData queue_dequeue(Queue* aQueue) {
    QueueData data;

    if(!queue_empty(aQueue)){
        Queue* first = aQueue->next;
        data = first->data;

        if(first->next != NULL){
            first->next->prev = NULL;   // update the second last node
        } else {
            aQueue->prev = NULL;        // pops the only node
        }
        aQueue->next = first->next;     // update head
        free(first);
        dbg("dequeuing: (%.1f, %.1f).", data.x, data.y);
    } else {
        dbg("dequeuing from empty queue!");
    }
    return data;
}

QueueData queue_look(Queue* aQueue) {
    QueueData data;
    if(!queue_empty(aQueue))
        data = aQueue->next->data;
    return data;
}

bool queue_empty(Queue* aQueue) {
    return (aQueue->next == NULL && aQueue->prev == NULL);
}

void queue_clear(Queue* aQueue) {
    while(!queue_empty(aQueue)) {
        queue_dequeue(aQueue);
    }
}

Queue* _queue_search(Queue* aQueue, struct _queue_data data){
    Queue* pq = aQueue->next;
    while(pq!=NULL){
        if(data.x == (pq->data).x && data.y == (pq->data).y)
            return pq;
        pq = pq->next;
    }
    return NULL;
}

void queue_destroy(Queue* aQueue){
    if(!queue_empty(aQueue))
        queue_clear(aQueue);
    free(aQueue);
    dbg("queue destroyed.");
}
//
//void _printQueue(Queue* queue){
//    Queue* pq=queue;
//    puts("--------------------");
//    while (pq!=NULL && !queue_empty(pq)){
//        pq = pq->next;
//        printf("%5.1f, %5.1f\n", (pq->data).x, (pq->data).y);
//    }
//    getchar();
//}

QueueData queue_data(float x, float y){
    QueueData qd;
    qd.x = x;
    qd.y = y;
    return qd;
}
