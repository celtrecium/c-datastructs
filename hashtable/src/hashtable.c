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

#include "hashtable.h"
#include <limits.h>

#define HASH_N 3

static hash_t
__pow (hash_t __f, hash_t __s)
{
  while (--__s != 0)
    __f *= __f;

  return __f;
}

static ht_pair_t
__pair_create (hash_t __key, void *__data)
{
  ht_pair_t pair;

  pair.key = __key;
  pair.data = __data;

  return pair;
}

hash_t
hash_f (char *__key, hash_t __k)
{
  hash_t i = 0;
  hash_t res = (hash_t)*__key++;

  while (*__key != 0)
    {
      ++i;
      res = (res + (hash_t)*__key * __pow (__k, i)) % ULONG_MAX;
      ++__key;
    }

  return res;
}

hashtable_t *
ht_create (size_t __htbuckets)
{
  hashtable_t *ptr = NULL;
  size_t i;

  if (__htbuckets == 0)
    return NULL;

  ptr = malloc (sizeof (hashtable_t));

  ptr->array = malloc (sizeof (list_t *) * __htbuckets);
  ptr->size = __htbuckets;

  for (i = 0; i < __htbuckets; ++i)
    ptr->array[i] = ht_list_create ();

  return ptr;
}

void *
ht_get_f (hashtable_t *__ht, char *__key)
{
  hash_t fullkey = hash_f (__key, HASH_N);
  size_t ind = fullkey % __ht->size;
  size_t i;
  ht_pair_t *pair;

  if (ht_list_get_size (__ht->array[ind]) == 1)
    return ht_list_get (__ht->array[ind], 0)->data;

  for (i = 0; i < __ht->array[ind]->size; ++i)
    {
      pair = ht_list_get (__ht->array[ind], (int)i);

      if (pair->key == fullkey)
        return pair->data;
    }

  return NULL;
}

void *
ht_update_f (hashtable_t *__ht, char *__key, size_t __tsize)
{
  hash_t fullkey = hash_f (__key, HASH_N);
  size_t ind = fullkey % __ht->size;

  return ht_list_push_back (__ht->array[ind],
                            __pair_create (fullkey,
                                           calloc (1, __tsize)))->data;
}

int
ht_pop (hashtable_t *__ht, char *__key)
{
  hash_t fullkey = hash_f (__key, HASH_N);
  size_t ind = fullkey % __ht->size;
  size_t i;
  ht_pair_t *pair = NULL;

  if (ht_list_get_size (__ht->array[ind]) == 0)
    return EXIT_FAILURE;

  if (ht_list_get_size (__ht->array[ind]) == 1)
    ht_list_delete (__ht->array[ind], 0);
  else
    for (i = 0; i < __ht->array[ind]->size; ++i)
      if ((pair = ht_list_get (__ht->array[ind], (int)i))->key
          == fullkey)
        ht_list_delete (__ht->array[ind], (int)i);

  return EXIT_SUCCESS;
}

int
ht_free (hashtable_t *__ht)
{
  size_t i;

  for (i = 0; i < __ht->size; ++i)
    ht_list_free (__ht->array[i]);

  free (__ht->array);
  free (__ht);

  return EXIT_SUCCESS;
}
