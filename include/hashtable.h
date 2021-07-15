#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include "htlinkedlist.h"

typedef struct hashtable {
  list_t **array;
  size_t size;
} hashtable_t;

hash_t hash_f (char *__key, hash_t __k);
hashtable_t *ht_create (size_t __htbuckets);
void *ht_get_f (hashtable_t *__ht, char *__key);
void *ht_update_f (hashtable_t *__ht, char *__key, size_t __tsize);
int ht_pop (hashtable_t *__ht, char *__key);
int ht_free (hashtable_t *__ht);

#define ht_update(ht, key, type, data) \
  *((type *) ht_update_f (ht, key, sizeof (type))) = data

#define ht_get(ht, key, type) \
  *((type *)ht_get_f (ht, key))

#endif /* HASHTABLE_H */
