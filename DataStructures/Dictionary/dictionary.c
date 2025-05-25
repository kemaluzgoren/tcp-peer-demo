/**
 * @file      dictionary.c
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      24.05.2025
 *
 * @details   
 */
#include "dictionary.h"

#include <stdlib.h>
#include <string.h>

static void recursive_dictionary_destroy(struct node_t *cursor);
static void insert_dict(struct dictionary_t *dictionary, void *key, unsigned long key_size, void *value, unsigned long value_size);
static void * search_dict(struct dictionary_t *dictionary, void *key, unsigned long key_size);


struct dictionary_t dictionary_constructor(int (*compare)(void *key_one, void *key_two)) {
    struct dictionary_t dictionary;

    dictionary.binary_search_tree = binary_search_tree_constructor(compare);
    dictionary.keys = linked_list_constructor();
    dictionary.insert = insert_dict;
    dictionary.search = search_dict;

    return dictionary;
}

void dictionary_destructor(struct dictionary_t *dictionary) {
    linked_list_destructor(&dictionary->keys);
    recursive_dictionary_destroy(dictionary->binary_search_tree.head);
}

int compare_string_keys(void *entry_one, void *entry_two) {
    if (strcmp((char *)(((struct entry_t *)entry_one)->key), 
                (char *)(((struct entry_t *)entry_two)->key)) > 0) {
        return 1;
    }
    else if (strcmp((char *)(((struct entry_t *)entry_one)->key), 
                (char *)(((struct entry_t *)entry_two)->key)) < 0) {
        return -1;
    }
    else {
        return 0;
    }
}


static void recursive_dictionary_destroy(struct node_t *cursor) {
    if (cursor->previous) {
        recursive_dictionary_destroy(cursor->previous);
    }

    if (cursor->next) {
        recursive_dictionary_destroy(cursor->next);
    }

    entry_destructor((struct entry_t *)cursor->data);
    free(cursor->data);
    free(cursor);
}

static void insert_dict(struct dictionary_t *dictionary, void *key, unsigned long key_size, void *value, unsigned long value_size) {
    struct entry_t entry = entry_constructor(key, key_size, value, value_size);

    dictionary->binary_search_tree.insert(&dictionary->binary_search_tree, &entry, sizeof(entry));
    dictionary->keys.insert(&dictionary->keys, dictionary->keys.length, key, key_size);
}

static void * search_dict(struct dictionary_t *dictionary, void *key, unsigned long key_size) {
    int dummy_value = 0;
    struct entry_t searchable = entry_constructor(key, key_size, &dummy_value, sizeof(dummy_value));

    void * result = dictionary->binary_search_tree.search(&dictionary->binary_search_tree, &searchable);
    // Return either the value for that key or NULL if not found.
    if (result) {
        return ((struct entry_t *)result)->value;
    }
    else {
        return NULL;
    }
}
