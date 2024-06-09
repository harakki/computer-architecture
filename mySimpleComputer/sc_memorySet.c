#include "../include/mySimpleComputer.h"

#include <limits.h>

int
sc_memorySet (int address, int value)
{
  if (address < 0 || address >= RAM_SIZE || value < 0 || value > USHRT_MAX)
    {
      return -1;
    }

  random_access_memory[address] = value;

  return 0;
}
