/*
 * This file is part of Hashtable.
 *
 * Hashtable is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * Hashtable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hashtable.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include "htlinkedlist.h"

typedef struct hashtable {
  list_t **array;
  size_t size;
} hashtable_t;

hash_t hash_f (char *key, hash_t k);
hashtable_t *ht_create (size_t htbuckets);
void *ht_get_f (hashtable_t *ht, char *key);
void *ht_update_f (hashtable_t *ht, char *key, size_t tsize);
int ht_pop (hashtable_t *ht, char *key);
int ht_free (hashtable_t *ht);

#define ht_update(ht, key, type, data) \
  *((type *) ht_update_f (ht, key, sizeof (type))) = data

#define ht_get(ht, key, type) \
  *((type *)ht_get_f (ht, key))

#endif /* HASHTABLE_H */
