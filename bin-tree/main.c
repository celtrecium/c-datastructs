#include "bintree.h"
#include <stdlib.h>
#include <stdio.h>

int
main (void)
{
  bintree_t *bt = bintree_create ();
  
  bintree_push (bt, 234, int, 115);
  bintree_push (bt, 123, int, 94);  
  bintree_push (bt, 345, int, 927);

  printf ("%d %d %d\n", bintree_get (bt, 234, int), bintree_get (bt, 345, int),
          bintree_get (bt, 123, int));

  bintree_free (bt);

  return EXIT_SUCCESS;
}
