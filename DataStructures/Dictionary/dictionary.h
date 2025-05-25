/**
 * @file      dictionary.h
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      24.05.2025
 *
 * @details   
 */

 #ifndef DICTIONARY_H_
 #define DICTIONARY_H_

#include "binary_seach_tree.h"

#include "../Lists/linked_list.h"
#include "entry.h"

struct dictionary_t {

    struct binary_search_tree_t binary_search_tree;

    struct linked_list_t keys;

    void (*insert)(struct dictionary_t *dictionary, void *key, unsigned long key_size, void *value, unsigned long value_size);
    void * (*search)(struct dictionary_t *dictionary, void *key, unsigned long key_size);
};

struct dictionary_t dictionary_constructor(int (*compare)(void *entry_one, void *entry_two));
void dictionary_destructor(struct dictionary_t *dictionary);

int compare_string_keys(void *entry_one, void *entry_two);

 #endif /*  DICTIONARY_H_   */