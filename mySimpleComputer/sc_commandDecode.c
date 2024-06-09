#include "../include/mySimpleComputer.h"

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  const int tmp_sign = (value >> 14) & 1;
  const int tmp_command = (value >> 7) & 0x7f;
  const int tmp_operand = value & 0x7F;

  if ((tmp_sign != 0 && tmp_sign != 1)
      || (tmp_operand < 0 || tmp_operand >= RAM_SIZE))
    {
      return -1;
    }

  *sign = tmp_sign;
  *command = tmp_command;
  *operand = tmp_operand;

  return 0;
}
