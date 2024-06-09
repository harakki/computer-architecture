#include "../include/mySimpleComputer.h"

#include <stddef.h>

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if ((sign != 0 && sign != 1) || (operand < 0 || operand >= 128)
      || value == NULL)
    {
      return -1;
    }

  *value = (sign & 1) << 14 | (command & 127) << 7 | (operand & 127);

  return 0;
}
