#include <stdio.h>

#include "../include/mySimpleComputer.h"
#include "console.h"

int
main (void)
{
  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  for (int i = 0; i < RAM_SIZE; ++i)
    {
      sc_memorySet (i, 0);
    }

  printf ("RAM data:\n");
  for (int i = 0; i < 13; ++i)
    {
      for (int j = 0; j < 10; ++j)
        {
          printCell (i * 10 + j);
          printf (" ");
        }
      printf ("\n");
    }

  printf ("Flag register: ");
  printFlags ();
  printf ("\n");

  printf ("Accumulator: ");
  printAccumulator ();
  printf ("\n");

  printf ("Command counter: ");
  printCounters ();
  printf ("\n");

  printf ("Cell data formats: ");
  printDecodedCommand (0);
  printf ("\n");

  printf ("Return of applying an invalid value to a RAM cell: %i\n",
          sc_memorySet (1000, -7));

  printf ("Return of applying an invalid value to a flags register: %i\n",
          sc_regSet (1, 9));

  printf ("Return of applying an invalid value to a accumulator: %i\n",
          sc_accumulatorSet (-1000 - 7));

  printf ("Return of applying an invalid value to a command counter: %i\n",
          sc_icounterSet (-1000 - 7));

  return 0;
}
