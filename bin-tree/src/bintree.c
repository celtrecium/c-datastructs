/*
 * This file is part of Binary Tree.
 *
 * Binary Tree is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * Binary Tree is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Binary Tree.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "bintree.h"
#include <stdlib.h>

#define node_get_left(index) \
  (2 * index + 1)

#define node_get_right(index) \
  (2 * index + 2)

bintree_t *
bintree_create (void)
{
  bintree_t *bt = malloc(sizeof (bintree_t));

  bt->tree = calloc (PAIRS_BLOCK, sizeof (bt_pair_t));
  bt->size = 0;
  bt->_arr_size = PAIRS_BLOCK;

  return bt;
}

static bt_pair_t *
bt_get_f (bintree_t *bt, bt_key_t key)
{
  size_t i = 0;

  while (1)
    {
      if (bt->tree[i].key > key)
        i = node_get_left (i);
      else if (bt->tree[i].key < key)
        i = node_get_right (i);
      else if (bt->tree[i].key == key)
        return bt->tree + i;

      if (bt->tree[i].data == NULL)
        return bt->tree + i;
    }
}

void *
bintree_get_f (bintree_t *bt, bt_key_t key)
{
  if (bt == NULL)
    return NULL;

  return bt_get_f (bt, key)->data;
}

void *
bintree_push_f (bintree_t *bt, bt_key_t key, size_t tsize)
{
  bt_pair_t *ptr = NULL;
  
  if (bt == NULL)
    return NULL;
  
  if (bt->size == bt->_arr_size)
    {
      bt->tree = realloc (bt->tree, bt->_arr_size + PAIRS_BLOCK);
      bt->_arr_size += PAIRS_BLOCK;
    }

  if (bt->size == 0)
    {
      bt->tree[0].data = calloc (1, tsize);
      bt->tree[0].key = key;
      ++bt->size;
      
      return bt->tree[0].data;
    }

  if ((ptr = bt_get_f(bt, key))->data == NULL)
    {
      ptr->key = key;
      
      return ptr->data = calloc (1, tsize);
    }
  else
    {
      free (ptr->data);
      
      return ptr->data = calloc (1, tsize);
    }
}

int
bintree_free (bintree_t *bt)
{
  size_t i = 0;

  if (bt == NULL)
    return EXIT_FAILURE;

  for (; i < bt->_arr_size; ++i)
    if (bt->tree[i].data != NULL)
      free (bt->tree[i].data);

  free (bt->tree);
  free (bt);
  
  return EXIT_SUCCESS;
}
