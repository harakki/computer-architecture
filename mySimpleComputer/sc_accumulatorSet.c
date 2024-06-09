#include "../include/mySimpleComputer.h"

#include <limits.h>

int
sc_accumulatorSet (int value)
{
  if (value < 0 || value > USHRT_MAX)
    {
      return -1;
    }

  accumulator = value;

  return 0;
}
