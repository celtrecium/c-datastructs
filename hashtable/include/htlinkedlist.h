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

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

typedef unsigned long int hash_t;

typedef struct ht_pair
{
  hash_t key;
  void *data;
} ht_pair_t;

typedef struct htls_node
{
  ht_pair_t data;
  struct htls_node *next;
  struct htls_node *prev;
} htls_node_t;

typedef struct list
{
  htls_node_t *first;
  htls_node_t *last;
  size_t size;
} list_t;

list_t *ht_list_create (void);
int ht_list_delete (list_t *ll, int index);
int ht_list_pop (list_t *ll);
ht_pair_t *ht_list_get (list_t *ll, int index);
size_t ht_list_get_size (list_t *ll);
int ht_list_free (list_t *ll);
ht_pair_t *ht_list_push_front (list_t *ll, ht_pair_t data);
ht_pair_t *ht_list_push_back (list_t *ll, ht_pair_t data);
void *ht_list_foreach (list_t *ll, void *(*func) (ht_pair_t *data));

#define list_set(list, index, type, data) \
  list_get (list, type, index) = data

#endif /* LINKEDLIST_H */
