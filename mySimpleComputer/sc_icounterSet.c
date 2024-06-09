#include "../include/mySimpleComputer.h"

int
sc_icounterSet (int value)
{
  if (value < 0 || value >= RAM_SIZE)
    {
      return -1;
    }

  command_counter = value;

  return 0;
}
