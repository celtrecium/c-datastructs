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


#ifndef BINTREE_H
#define BINTREE_H

#include <stdlib.h>
#include <string.h>

#define PAIRS_BLOCK 20

typedef unsigned int bt_key_t;

typedef struct bt_pair    
{
  bt_key_t key;
  void *data;
} bt_pair_t;

typedef struct bintree
{
  bt_pair_t *tree;
  size_t size;
  size_t _arr_size;
  int _is_busy;
} bintree_t;

bintree_t *bintree_create (void);
void *bintree_push_f (bintree_t *bt, bt_key_t key, size_t tsize);
void *bintree_get_f (bintree_t *bt, bt_key_t key);
int bintree_free (bintree_t *bt);

#define bintree_get(bt, key, type) \
  *((type *) bintree_get_f (bt, key))

#define bintree_set(bt, key, type, data) \
  bintree_get (bt, key, type) = data

#define bintree_push(bt, key, type, data) \
  *((type *) bintree_push_f (bt, key, sizeof (type))) = data

#endif  /* BINTREE_H */
