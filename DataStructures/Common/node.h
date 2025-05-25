/**
 * @file      node.h 
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      24.05.2025
 *
 * @details   
 */
#ifndef NODE_H_
#define NODE_H_


struct node_t {
    void *data; 
    struct node_t *next; 
    struct node_t *previous;     
};

struct node_t node_constructor(void *data, unsigned long size); 
void node_destructor(struct node_t *node); 


#endif  /*  NODE_H_ */
