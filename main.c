#include "hashtable.h"
#include <stdio.h>

int
main (void)
{
  hashtable_t *ht = ht_create (20);

  ht_update (ht, "Alexey", int, 14);
  ht_update (ht, "Maxim",  int, 18);

  printf ("Maxim is %d y.o.\n"
          "Alexey is %d y.o.\n", ht_get (ht, "Maxim", int),
          ht_get (ht, "Alexey", int));

  ht_free (ht);
  
  return EXIT_SUCCESS;
}
