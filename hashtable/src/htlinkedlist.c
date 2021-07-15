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

static node_t *
__node_create (void)
{
  node_t *ret = malloc (sizeof (node_t));

  ret->next = NULL;
  ret->prev = NULL;

  return ret;
}

static int
__node_free (node_t *__nd)
{
  if (__nd->data.data != NULL)
    free (__nd->data.data);
  
  free (__nd);

  return EXIT_SUCCESS;
}

static node_t *
__list_get_node (list_t *__ll, int __index)
{
  int i = 0;
  node_t *ptr = __ll->first;

  if (__ll->size == 0)
    return NULL;
  
  __index %= (int)__ll->size;

  for (i = 0; i < __index; ++i)
    ptr = ptr->next;

  return ptr;
}

list_t *
ht_list_create (void)
{
  list_t *ret = malloc (sizeof (list_t));
  ret->first = ret->last = malloc (sizeof (node_t));

  ret->first->next = NULL;
  ret->first->prev = NULL;
  ret->first->data.data = NULL;
  ret->first->typesize = 0;
  ret->size = 0;

  return ret;
}

int
ht_list_pop (list_t *__ll)
{
  node_t *ptr = __ll->last->prev;
  
  if (__ll == NULL)
    return EXIT_FAILURE;
  else if (__ll->size == 0)
    return EXIT_SUCCESS;
  
  __ll->last->prev->next = NULL;

  __node_free (__ll->last);

  __ll->last = ptr;
  --__ll->size;
  
  return EXIT_SUCCESS;
}

int
ht_list_delete (list_t *__ll, int __index)
{
  node_t *ptr = __ll->first;
  size_t i;
  
  if (__ll == NULL)
    return EXIT_FAILURE;
  
  __index %= (int)__ll->size;

  if ((size_t) __index == __ll->size - 1)
    return ht_list_pop (__ll);

  for (i = 0; i < (size_t)__index; ++i)
    ptr = ptr->next;

  ptr->next->prev = ptr->prev;
  
  if (ptr->prev != NULL)
    ptr->prev->next = ptr->next;
  
  --__ll->size;

  if (__index == 0)
    __ll->first = __ll->first->next;
  
  __node_free (ptr);

  return EXIT_SUCCESS;
}

ht_pair_t *
ht_list_push_front (list_t *__ll, ht_pair_t __pair)
{
  node_t *nnode = NULL;

  if (__ll == NULL)
    return NULL;

  if (__ll->size != 0)
    {
      nnode = __node_create ();

      nnode->data = __ll->first->data;
      nnode->prev = __ll->first;
      nnode->next = __ll->first->next;
      nnode->typesize = __ll->first->typesize;

      __ll->first->next = nnode;
    }
  else
    __ll->first->next = NULL;
  
  __ll->first->data = __pair;
  __ll->first->prev = NULL;
  
  ++__ll->size;
  
  return &__ll->first->data;
}

ht_pair_t *
ht_list_push_back (list_t *__ll, ht_pair_t __pair)
{
  node_t *nnode = NULL;

  if (__ll == NULL)
    return NULL;

  if (__ll->size != 0)
    {
      nnode = __node_create ();

      nnode->data = __pair;
      nnode->prev = __ll->last;
      nnode->next = NULL;
  
      __ll->last->next = nnode;

      __ll->last = nnode;
    }
  else
    {
      nnode = __ll->first;

      nnode->data = __pair;
    }
  
  ++__ll->size;
  
  return &nnode->data;
}

size_t
ht_list_get_size (list_t *__ll)
{
  return __ll->size;
}

ht_pair_t *
ht_list_get (list_t *__ll, int __index)
{
  return &__list_get_node (__ll, __index)->data;
}

int
ht_list_free (list_t *__ll)
{
  node_t *ptr = __ll->first;

  while (__ll->first != NULL)
    {
      ptr = __ll->first->next;

      __node_free (__ll->first);

      __ll->first = ptr;
    }

  free (__ll);
  
  return EXIT_SUCCESS;
}

void *
ht_list_foreach (list_t *__ll, void *(*__func) (ht_pair_t *__data))
{
  node_t *ptr = __ll->first;
  void *retdat = NULL;

  if (__ll->size == 0)
    return NULL;
  
  while (ptr != NULL)
    {
      if ((retdat = __func (&ptr->data)) != NULL)
        return retdat;
      
      ptr = ptr->next;
    }

  return NULL;
}
