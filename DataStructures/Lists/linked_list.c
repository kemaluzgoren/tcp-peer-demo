/**
 * @file      linked_list.c
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      24.05.2025
 *
 * @details   
 */
#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>

static struct node_t *create_node_ll(void *data, unsigned long size); 
static void destroy_node_ll(struct node_t *node_to_destroy); 
static struct node_t *iterate_ll(struct linked_list_t *linked_list, int index); 

static void insert_ll(struct linked_list_t *linked_list, int index, void *data, unsigned long size);
static void remove_node_ll(struct linked_list_t *linked_list, int index);
static void * retrieve_ll(struct linked_list_t *linked_list, int index);
static void bubble_sort_ll(struct linked_list_t *linked_list, int (*compare)(void *a, void *b));
static short binary_search_ll(struct linked_list_t *linked_list, void *query, int (*compare)(void *a, void *b));

static void linked_list_push_back(struct linked_list_t *linked_list, void *data);


struct linked_list_t linked_list_constructor(void) {

    struct linked_list_t new_list; 
    new_list.head = NULL; 
    new_list.length = 0; 

    new_list.insert = insert_ll; 
    new_list.remove = remove_node_ll; 
    new_list.retrieve = retrieve_ll; 
    new_list.sort = bubble_sort_ll; 
    new_list.search = binary_search_ll; 

    new_list.push_back = linked_list_push_back;
    return new_list; 
}


void linked_list_destructor(struct linked_list_t *linked_list) {
    for(int i = 0; i < linked_list->length; i++) {
        linked_list->remove(linked_list, 0); 
    }
}


static struct node_t *create_node_ll(void *data, unsigned long size) {
    struct node_t *new_node = (struct node_t*)malloc(sizeof(struct node_t)); 

    *new_node = node_constructor(data, size); 
    return new_node; 
}

static void destroy_node_ll(struct node_t *node_to_destroy) {
    node_destructor(node_to_destroy);
}

static struct node_t *iterate_ll(struct linked_list_t *linked_list, int index) {
    if(index < 0 || index > linked_list->length) {
        return NULL;
    }

    struct node_t *cursor = linked_list->head; 
    for(int i = 0; i < index; i++) {
        cursor = cursor->next;
    }

    return cursor; 
}

static void insert_ll(struct linked_list_t *linked_list, int index, void *data, unsigned long size) {
    // create a new node be inserted
    struct node_t *node_to_insert = create_node_ll(data, size); 

    if(index == 0) {
        node_to_insert->next = linked_list->head; 
        linked_list->head = node_to_insert; 
    }
    else {
        struct node_t *cursor = iterate_ll(linked_list, index-1); 
        node_to_insert->next = cursor->next; 
        cursor->next = node_to_insert; 
    }

    linked_list->length++; 
}

static void remove_node_ll(struct linked_list_t *linked_list, int index) {
    if(index == 0) {
        struct node_t *node_to_remove = linked_list->head; 
        if(node_to_remove) {
            linked_list->head = node_to_remove->next; 
            destroy_node_ll(node_to_remove); 
        }
    }
    else {
        struct node_t *cursor = iterate_ll(linked_list, index-1);
        struct node_t *node_to_remove = cursor->next; 
        cursor->next = node_to_remove->next; 
        destroy_node_ll(node_to_remove); 
    }

    linked_list->length--; 
}

static void * retrieve_ll(struct linked_list_t *linked_list, int index) {
    struct node_t *cursor = iterate_ll(linked_list, index); 
    if(cursor) {
        return cursor->data; 
    }
    
    return NULL; 
}

static void bubble_sort_ll(struct linked_list_t *linked_list, int (*compare)(void *a, void *b)) {
    for(struct node_t *i = linked_list->retrieve(linked_list, 0); i; i = i->next) {
        for(struct node_t *n = i->next; n; n=n->next) {
            if(compare(i->data, n->data) > 0) {
                // swap them
                void *temp = n->data; 
                n->data = i->data; 
                i->data = temp; 
            }
        }
    }
}

static short binary_search_ll(struct linked_list_t *linked_list, void *query, int (*compare)(void *a, void *b)) {
    int position = linked_list->length/2; 
    int min = 0; 
    int max = linked_list->length; 
    while(max > min) {
        void *data = linked_list->retrieve(linked_list, position); 
        if(compare(data, query) == 1) {
            max = position; 
            if(position != (min + position)/2) {
                position = (min+position)/2; 
            }
            else {
                break; 
            }
        }
        else if(compare(data, query) == -1) {
            min = position; 
            if(position != (max+position)/2) {
                position = (max + position) / 2; 
            }
            else {
                break; 
            }
        } 
        else {
            return 1; 
        }
    }

    return 0; 
}

static void linked_list_push_back(struct linked_list_t *linked_list, void *data) {
    struct node_t *new_node = malloc(sizeof(struct node_t));
    if(!new_node) {
        return;
    }

    new_node->data = data; 
    new_node->next = NULL; 

    if(linked_list->head == NULL) {
        linked_list->head = new_node; 
    }
    else {
        struct node_t *cursor = linked_list->head; 
        while(cursor->next != NULL) {
            cursor = cursor->next;
        }
        cursor->next = new_node; 
    }

}