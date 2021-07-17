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
pow_f (hash_t f, hash_t s)
{
  while (--s != 0)
    f *= f;

  return f;
}

static ht_pair_t
pair_create (hash_t key, void *data)
{
  ht_pair_t pair;

  pair.key = key;
  pair.data = data;

  return pair;
}

hash_t
hash_f (char *key, hash_t k)
{
  hash_t i = 0;
  hash_t res = (hash_t)*key++;

  while (*key != 0)
    {
      ++i;
      res = (res + (hash_t)*key * pow_f (k, i)) % ULONG_MAX;
      ++key;
    }

  return res;
}

hashtable_t *
ht_create (size_t htbuckets)
{
  hashtable_t *ptr = NULL;
  size_t i;

  if (htbuckets == 0)
    return NULL;

  ptr = malloc (sizeof (hashtable_t));

  ptr->array = malloc (sizeof (list_t *) * htbuckets);
  ptr->size = htbuckets;

  for (i = 0; i < htbuckets; ++i)
    ptr->array[i] = ht_list_create ();

  return ptr;
}

void *
ht_get_f (hashtable_t *ht, char *key)
{
  hash_t fullkey = hash_f (key, HASH_N);
  size_t ind = fullkey % ht->size;
  size_t i;
  ht_pair_t *pair;

  if (ht_list_get_size (ht->array[ind]) == 1)
    return ht_list_get (ht->array[ind], 0)->data;

  for (i = 0; i < ht->array[ind]->size; ++i)
    {
      pair = ht_list_get (ht->array[ind], (int)i);

      if (pair->key == fullkey)
        return pair->data;
    }

  return NULL;
}

void *
ht_update_f (hashtable_t *ht, char *key, size_t tsize)
{
  hash_t fullkey = hash_f (key, HASH_N);
  size_t ind = fullkey % ht->size;

  return ht_list_push_back (ht->array[ind],
                            pair_create (fullkey, calloc (1, tsize)))->data;
}

int
ht_pop (hashtable_t *ht, char *key)
{
  hash_t fullkey = hash_f (key, HASH_N);
  size_t ind = fullkey % ht->size;
  size_t i;
  ht_pair_t *pair = NULL;

  if (ht_list_get_size (ht->array[ind]) == 0)
    return EXIT_FAILURE;

  if (ht_list_get_size (ht->array[ind]) == 1)
    ht_list_delete (ht->array[ind], 0);
  else
    for (i = 0; i < ht->array[ind]->size; ++i)
      if ((pair = ht_list_get (ht->array[ind], (int)i))->key == fullkey)
        ht_list_delete (ht->array[ind], (int)i);

  return EXIT_SUCCESS;
}

int
ht_free (hashtable_t *ht)
{
  size_t i;

  for (i = 0; i < ht->size; ++i)
    ht_list_free (ht->array[i]);

  free (ht->array);
  free (ht);

  return EXIT_SUCCESS;
}
