/**
 * @file      binary_search_tree.c
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      24.05.2025
 *
 * @details   
 */

 #include "binary_seach_tree.h"

 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>


static struct node_t * create_node_bst(void *data, unsigned long size);
static void destroy_node_bst(struct node_t *node_to_destroy);
static struct node_t * iterate_bst(struct binary_search_tree_t *tree, struct node_t *cursor, void *data, int *direction);
static void recursive_tree_destruction(struct node_t *node);

static void * search_bst(struct binary_search_tree_t *tree, void *data);
static void insert_bst(struct binary_search_tree_t *tree, void *data, unsigned long size);


struct binary_search_tree_t binary_search_tree_constructor(int (*compare)(void *data_one, void *data_two))
{
    struct binary_search_tree_t tree;
    tree.head = NULL;
    tree.compare = compare;
    tree.search = search_bst;
    tree.insert = insert_bst;
    return tree;
}

void binary_search_tree_destructor(struct binary_search_tree_t tree)
{
    recursive_tree_destruction(tree.head);
}

int binary_search_tree_str_compare(void *data_one, void *data_two) {
    int comparison = strcmp(data_one, data_two); 

    if(comparison > 0) {
        return 1; 
    }
    else if(comparison < 0) {
        return -1; 
    }
    else {
        return 0; 
    }
}






static struct node_t * create_node_bst(void *data, unsigned long size) {
    struct node_t *new_node = (struct node_t *)malloc(sizeof(struct node_t));

    *new_node = node_constructor(data, size);
    return new_node;
}

static void destroy_node_bst(struct node_t *node_to_destroy) {
    node_destructor(node_to_destroy);
}

static struct node_t * iterate_bst(struct binary_search_tree_t *tree, struct node_t *cursor, void *data, int *direction) {
    if(tree->compare(cursor->data, data) == 1) {
        if(cursor->next) {
            return iterate_bst(tree, cursor->next, data, direction);
        }
        else {
            *direction = 1; 
            return cursor; 
        }
    }
    else if(tree->compare(cursor->data, data) == -1) {
        if(cursor->previous) {
            return iterate_bst(tree, cursor->previous, data, direction);
        }
        else {
            *direction = -1; 
            return cursor; 
        }
    }

    *direction = 0; 
    return cursor; 
}

static void recursive_tree_destruction(struct node_t *node) {
    if(node->previous) {
        recursive_tree_destruction(node->previous);
    }

    if(node->next) {
        recursive_tree_destruction(node->next);
    }

    destroy_node_bst(node); 
}

static void * search_bst(struct binary_search_tree_t *tree, void *data) {
    int direction = 0; 

    struct node_t *cursor = iterate_bst(tree, tree->head, data, &direction); 
    if(direction == 0) {
        return cursor->data; 
    }

    return NULL; 
}

static void insert_bst(struct binary_search_tree_t *tree, void *data, unsigned long size) {
    if(!tree->head) {
        tree->head = create_node_bst(data, size);
    }
    else {
        int direction = 0; 

        struct node_t *cursor = iterate_bst(tree, tree->head, data, &direction);
        if(direction==1) {
            cursor->next = create_node_bst(data, size); 
        }
        else if(direction == -1) {
            cursor->previous = create_node_bst(data, size); 
        }
    }
}

