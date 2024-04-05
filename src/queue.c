/*
 *  Author: Huisu Ju <kng0258@naver.com>
 *  License: MIT
 */
#include <assert.h>
#include <stdlib.h>
#include "queue.h"

typedef struct Queue {
    QueueNode *head;
    QueueNode *tail;
} Queue;

Queue *Queue_new(void)
{
    Queue *queue = malloc(sizeof(Queue));
    if (!queue) {
        return NULL;
    }
    queue->head = queue->tail = NULL;
    
    return queue;
}

void Queue_delete(Queue *queue)
{
    if (queue) {
        free(queue);
    }
}

void Queue_push(Queue *queue, QueueNode *node)
{
    assert(queue);
    assert(node);
    
    if (!queue->head) {
        queue->head = node;
        queue->tail = node;
        return;
    }
    queue->tail->next = node;
    queue->tail = node;
    node->next = NULL;
}

QueueNode *Queue_pop(Queue *queue)
{
    assert(queue);
    
    QueueNode *del_node = queue->head;
    if (!del_node) {
        return NULL;
    }
    queue->head = del_node->next;
    if (!queue->head) {
        queue->tail = NULL;
    }
    
    return del_node;
}

QueueNode *Queue_peek(Queue *queue)
{
    assert(queue);
    
    return queue->head;
}

void Queue_iterate(Queue *queue, void (*iter)(QueueNode *node))
{
    assert(queue);
    
    QueueNode *cur = queue->head;
    while (cur) {
        iter(cur);
        cur = cur->next;
    }
}