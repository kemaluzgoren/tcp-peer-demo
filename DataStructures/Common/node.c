/**
 * @file      node.c
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      24.05.2025
 *
 * @details   
 */
#include "node.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node_t node_constructor(void *data, unsigned long size) {
    if(size < 1) {
        printf("Invalid data size for node...\n"); 
        exit(1); 
    }

    struct node_t node; 

    node.data = malloc(size);
    memcpy(node.data, data, size); 

    node.next = NULL; 
    node.previous = NULL; 
    return node; 
}

void node_destructor(struct node_t *node) {
    free(node->data); 
    free(node); 
}
