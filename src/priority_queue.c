/*
 *  Author: Huisu Ju <kng0258@naver.com>
 *  License: MIT
 */
#include <assert.h>
#include <stdlib.h>
#include "priority_queue.h"

typedef struct PQueue {
    size_t size;
    size_t num_datas;
    bool (*compare)(const void *, const void *);
    void *datas[];
} PQueue;

PQueue *PQueue_new(size_t size, bool (*compare)(const void *, const void *))
{
    assert(compare);
    
    PQueue *pqueue = malloc(sizeof(PQueue) + sizeof(void *) * (size + 1));
    if (!pqueue) {
        return NULL;
    }
    *pqueue = (PQueue) {
        .size = size,
        .num_datas = 0,
        .compare = compare,
    };
    
    return pqueue;
}

void PQueue_delete(PQueue *pqueue)
{
    if (pqueue) {
        free(pqueue);
    }
}

static int get_prior_child_index(PQueue *pqueue, int index)
{
    if (index * 2 > pqueue->num_datas) {
        return -1;
    }
    if (index * 2 == pqueue->num_datas) {
        return index * 2;
    }
    return pqueue->compare(pqueue->datas[index * 2], pqueue->datas[index * 2 + 1]) ?
           index * 2 : index * 2 + 1;
}

static int get_index(PQueue *pqueue, void *data)
{
    for (int i = 1; i <= pqueue->num_datas; i++) {
        if (pqueue->datas[i] == data) {
            return i;
        }
    }
    return -1;
}

int PQueue_push(PQueue *pqueue, void *data)
{
    if (PQueue_is_full(pqueue)) {
        return -1;
    }
    int index = ++pqueue->num_datas;
    while (index != 1) {
        void *parent_data = pqueue->datas[index / 2];
        if (pqueue->compare(parent_data, data)) {
            break;
        }
        pqueue->datas[index] = parent_data;
        index /= 2;
    }
    pqueue->datas[index] = data;
    
    return 0;
}

void *PQueue_pop(PQueue *pqueue)
{
    if (PQueue_is_empty(pqueue)) {
        return NULL;
    }
    void *pop_data = pqueue->datas[1];
    void *last_data = pqueue->datas[pqueue->num_datas];
    
    int index = 1;
    int child_index;
    while ((child_index = get_prior_child_index(pqueue, index)) >= 0) {
        if (pqueue->compare(last_data, pqueue->datas[child_index])) {
            break;
        }
        pqueue->datas[index] = pqueue->datas[child_index];
        index = child_index;
    }
    pqueue->datas[index] = last_data;
    pqueue->num_datas--;
    
    return pop_data;
}

void *PQueue_peek(PQueue *pqueue)
{
    if (PQueue_is_empty(pqueue)) {
        return NULL;
    }
    return pqueue->datas[1];
}

void PQueue_erase(PQueue *pqueue, void *data)
{
    if (PQueue_is_empty(pqueue)) {
        return;
    }
    void *last_data = pqueue->datas[pqueue->num_datas];
    
    int index = get_index(pqueue, data);
    if (index < 0) {
        return;
    }
    int child_index;
    while ((child_index = get_prior_child_index(pqueue, index)) >= 0) {
        if (pqueue->compare(last_data, pqueue->datas[child_index])) {
            break;
        }
        pqueue->datas[index] = pqueue->datas[child_index];
        index = child_index;
    }
    pqueue->datas[index] = last_data;
    pqueue->num_datas--;
}

bool PQueue_is_empty(PQueue *pqueue)
{
    return (pqueue->num_datas == 0);
}

bool PQueue_is_full(PQueue *pqueue)
{
    return (pqueue->num_datas == pqueue->size);
}