#include "../include/mySimpleComputer.h"

#include <stddef.h>

int
sc_memoryInit (void)
{
  for (int i = 0; i < RAM_SIZE; ++i)
    {
      random_access_memory[i] = 0;
    }

  return 0;
}
