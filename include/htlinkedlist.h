#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <string.h>

typedef unsigned long int hash_t;

typedef struct ht_pair
{
  hash_t key;
  void *data;
} ht_pair_t;

typedef struct node
{
  ht_pair_t data;
  size_t typesize;
  struct node *next;
  struct node *prev;
} node_t;

typedef struct list
{
  node_t *first;
  node_t *last;
  size_t size;
} list_t;

list_t *ht_list_create (void);
int ht_list_delete (list_t *__ll, int __index);
int ht_list_pop (list_t *__ll);
ht_pair_t *ht_list_get (list_t *__ll, int __index);
size_t ht_list_get_size (list_t *__ll);
int ht_list_free (list_t *__ll);
ht_pair_t *ht_list_push_front (list_t *__ll, ht_pair_t __data);
ht_pair_t *ht_list_push_back (list_t *__ll, ht_pair_t __data);
void *ht_list_foreach (list_t *__ll, void *(*__func) (ht_pair_t *__data));

#define list_set(list, index, type, data) \
  list_get (list, type, index) = data

#endif /* LINKEDLIST_H */
