/**
 * @file      linked_list.h 
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      24.05.2025
 *
 * @details   
 */

 #ifndef LINKED_LIST_H_
 #define LINKED_LIST_H_
 
 
 #include "../Common/node.h"
 
 struct linked_list_t {
     /* data */
     struct node_t *head; 
     int length; 
 
     void (*insert)(struct linked_list_t *linked_list, int index, void *data, unsigned long size); 
     void (*remove)(struct linked_list_t *linked_list, int index); 
 
     void *(*retrieve)(struct linked_list_t *linked_list, int index); 
     void (*sort)(struct linked_list_t *linked_list, int(*compare)(void *a, void *b)); 
     short (*search)(struct linked_list_t *linked_list, void *query, int(*comoare)(void *a, void *b)); 

     void (*push_back)(struct linked_list_t *linked_list, void *data);
};
 
 
 struct linked_list_t linked_list_constructor(void); 
 void linked_list_destructor(struct linked_list_t *linked_list);
 
 
 #endif  /*  LINKED_LIST_H_  */