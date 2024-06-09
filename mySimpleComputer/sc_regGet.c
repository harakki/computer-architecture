#include "../include/mySimpleComputer.h"

#include <stddef.h>

int
sc_regGet (enum flags reg, int *value)
{

  if (value == NULL || (int)reg >= FLAGS_REG_SIZE)
    {
      return -1;
    }

  *value = (flag_register & (1 << reg)) ? 1 : 0;

  return 0;
}
