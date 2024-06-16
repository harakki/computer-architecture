#include "../include/mySimpleComputer.h"

#include <stddef.h>

int
sc_memoryGet (int address, int *value)
{
  if (value == NULL || address < 0 || address >= RAM_SIZE)
    {
      return -1;
    }

  sc_cacheUpdate (address, value);

  return 0;
}
