/**
 * @file      entry.h
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      24.05.2025
 *
 * @details   
 */
#ifndef ENTRY_H_
#define ENTRY_H_

struct entry_t {
    void *key; 
    void *value; 
};

struct entry_t entry_constructor(void *key, unsigned long key_size, void *value, unsigned long value_size);
void entry_destructor(struct entry_t *entry);

#endif  /*  ENTRY_H_  */