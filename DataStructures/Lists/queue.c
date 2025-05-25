/**
 * @file      queue.c
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      24.05.2025
 *
 * @details   
 */
#include "queue.h"

static void push(struct queue_t *queue, void *data, unsigned long size);
static void * peek(struct queue_t *queue);
static void pop (struct queue_t *queue);

struct queue_t queue_constructor(void) {
    struct queue_t queue; 
    queue.list = linked_list_constructor();

    queue.push = push; 
    queue.peek = peek; 
    queue.pop = pop; 

    return queue; 
}


void queue_destructor(struct queue_t *queue) {
    linked_list_destructor(&queue->list);
}


static void push(struct queue_t *queue, void *data, unsigned long size) {
    queue->list.insert(&queue->list, queue->list.length, data, size); 
}

static void * peek(struct queue_t *queue) {
    void *data = queue->list.retrieve(&queue->list, 0); 
    return data; 
}

static void pop (struct queue_t *queue) {
    queue->list.remove(&queue->list, 0);
}