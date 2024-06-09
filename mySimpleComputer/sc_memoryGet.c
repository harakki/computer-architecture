#include "../include/mySimpleComputer.h"

#include <stddef.h>

int
sc_memoryGet (int address, int *value)
{
  if (value == NULL || address < 0 || address >= RAM_SIZE)
    {
      return -1;
    }

  *value = random_access_memory[address];

  return 0;
}
