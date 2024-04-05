/*
 *  Author: Huisu Ju <kng0258@naver.com>
 *  License: MIT
 */
#pragma once

#include <stdlib.h>

typedef struct Queue Queue;

typedef struct QueueNode {
    struct QueueNode *next;
} QueueNode;

#define QUEUE_NODE          \
    QueueNode queue_entry;
     
Queue *Queue_new(void);
void Queue_delete(Queue *queue);

void Queue_push(Queue *queue, QueueNode *node);
QueueNode *Queue_pop(Queue *queue);
QueueNode *Queue_peek(Queue *queue);

void Queue_iterate(Queue *queue, void (*iter)(QueueNode *node));