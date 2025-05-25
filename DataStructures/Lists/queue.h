/**
 * @file      queue.h 
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      24.05.2025
 *
 * @details   
 */
#ifndef QUEUE_H_
#define QUEUE_H_

#include "linked_list.h"

struct queue_t {
    struct linked_list_t list; 

    void (*push)(struct queue_t *queue, void *data, unsigned long size);
    void * (*peek)(struct queue_t *queue);
    void (*pop)(struct queue_t *queue);
}; 


struct queue_t queue_constructor(void); 
void queue_destructor(struct queue_t *queue); 

#endif  /*  QUEUE_H_    */
