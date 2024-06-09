#include "../include/mySimpleComputer.h"

int
sc_regSet (enum flags reg, int value)
{
  if (value == 1 && reg >= 0 && (int)reg < FLAGS_AMOUNT)
    {
      flag_register |= (1 << reg);
    }
  else if (value == 0 && reg >= 0 && (int)reg < FLAGS_AMOUNT)
    {
      flag_register &= ~(1 << reg);
    }
  else
    {
      return -1;
    }

  return 0;
}
