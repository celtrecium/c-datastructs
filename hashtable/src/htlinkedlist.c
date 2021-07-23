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

#include "htlinkedlist.h"
#include <stdlib.h>

static htls_node_t *
node_create (void)
{
  htls_node_t *ret = calloc (1, sizeof (htls_node_t));

  ret->next = NULL;
  ret->prev = NULL;

  return ret;
}

static int
node_free (htls_node_t *nd)
{
  if (nd->data.data != NULL)
    free (nd->data.data);
  
  free (nd);

  return EXIT_SUCCESS;
}

static htls_node_t *
list_get_node (list_t *ll, int index)
{
  int i = 0;
  htls_node_t *ptr = ll->first;

  if (ll->size == 0)
    return NULL;
  
  index %= (int)ll->size;

  for (i = 0; i < index; ++i)
    ptr = ptr->next;

  return ptr;
}

list_t *
ht_list_create (void)
{
  list_t *ret = malloc (sizeof (list_t));
  ret->first = ret->last = malloc (sizeof (htls_node_t));

  ret->first->next = NULL;
  ret->first->prev = NULL;
  ret->first->data.data = NULL;
  ret->size = 0;

  return ret;
}

int
ht_list_pop (list_t *ll)
{
  htls_node_t *ptr = ll->last->prev;
  
  if (ll == NULL || ll->size == 0)
    return EXIT_FAILURE;
 
  if (ll->size > 1)
    {
      ll->last->prev->next = NULL;

      node_free (ll->last);

      ll->last = ptr;
    }
  else
    {
      if (ll->first->data.data != NULL)
        free (ll->first->data.data);

      ll->first->data.data = NULL;
      
      ll->first->data.key = 0;
    }
  
  --ll->size;

  return EXIT_SUCCESS;
}

int
ht_list_delete (list_t *ll, int index)
{
  htls_node_t *ptr = ll->first;
  size_t i;
  
  if (ll == NULL)
    return EXIT_FAILURE;
  
  index %= (int)ll->size;

  if ((size_t) index == ll->size - 1)
    return ht_list_pop (ll);

  for (i = 0; i < (size_t)index; ++i)
    ptr = ptr->next;

  ptr->next->prev = ptr->prev;
  
  if (ptr->prev != NULL)
    ptr->prev->next = ptr->next;
  
  --ll->size;

  if (index == 0)
    ll->first = ll->first->next;
  
  node_free (ptr);

  return EXIT_SUCCESS;
}

ht_pair_t *
ht_list_push_front (list_t *ll, ht_pair_t pair)
{
  htls_node_t *nnode = NULL;

  if (ll == NULL)
    return NULL;

  if (ll->size != 0)
    {
      nnode = node_create ();

      nnode->data = ll->first->data;
      nnode->prev = ll->first;
      nnode->next = ll->first->next;
 
      ll->first->next = nnode;
    }
  else
    ll->first->next = NULL;
  
  ll->first->data = pair;
  ll->first->prev = NULL;
  
  ++ll->size;
  
  return &ll->first->data;
}

ht_pair_t *
ht_list_push_back (list_t *ll, ht_pair_t pair)
{
  htls_node_t *nnode = NULL;

  if (ll == NULL)
    return NULL;

  if (ll->size != 0)
    {
      nnode = node_create ();

      nnode->data = pair;
      nnode->prev = ll->last;
      nnode->next = NULL;
  
      ll->last->next = nnode;

      ll->last = nnode;
    }
  else
    {
      nnode = ll->first;

      nnode->data = pair;
    }
  
  ++ll->size;
  
  return &nnode->data;
}

size_t
ht_list_get_size (list_t *ll)
{
  return ll->size;
}

ht_pair_t *
ht_list_get (list_t *ll, int index)
{
  return &list_get_node (ll, index)->data;
}

int
ht_list_free (list_t *ll)
{
  htls_node_t *ptr = ll->first;

  if (ll == NULL)
    return EXIT_SUCCESS;
  
  while (ll->first != NULL)
    {
      ptr = ll->first->next;

      node_free (ll->first);

      ll->first = ptr;
    }

  free (ll);
  
  return EXIT_SUCCESS;
}

void *
ht_list_foreach (list_t *ll, void *(*func) (ht_pair_t *data))
{
  htls_node_t *ptr = ll->first;
  void *retdat = NULL;

  if (ll->size == 0)
    return NULL;
  
  while (ptr != NULL)
    {
      if ((retdat = func (&ptr->data)) != NULL)
        return retdat;
      
      ptr = ptr->next;
    }

  return NULL;
}
