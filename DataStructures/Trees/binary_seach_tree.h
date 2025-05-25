/**
 * @file      binary_search_tree.h 
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      24.05.2025
 *
 * @details   
 */

 #ifndef BINARY_SEARCH_TREE_H_
 #define BINARY_SEARCH_TREE_H
 
 
 #include "node.h"
 
 struct binary_search_tree_t {
     struct node_t *head; 
 
     int (*compare)(void *data_one, void *data_two);
     void * (*search)(struct binary_search_tree_t *tree, void *data);
     void (*insert)(struct binary_search_tree_t *tree, void *data, unsigned long size);
 };
 
 struct binary_search_tree_t binary_search_tree_constructor(int (*compare)(void *data_one, void *data_two));
 void binary_search_tree_destructor(struct binary_search_tree_t tree);
 
 int binary_search_tree_int_compare(void *data_one, void *data_two);
 int binary_search_tree_float_compare(void *data_one, void *data_two);
 int binary_search_tree_char_compare(void *data_one, void *data_two);
 int binary_search_tree_str_compare(void *data_one, void *data_two);
 
 
 #endif  /*  BINARY_SEARCH_TREE_H_*/